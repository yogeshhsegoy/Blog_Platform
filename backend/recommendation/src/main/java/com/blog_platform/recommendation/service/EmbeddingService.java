package com.blog_platform.recommendation.service;

import ai.djl.huggingface.tokenizers.Encoding;
import ai.djl.huggingface.tokenizers.HuggingFaceTokenizer;
import ai.djl.inference.Predictor;
import ai.djl.ndarray.NDArray;
import ai.djl.ndarray.NDList;
import ai.djl.ndarray.NDManager;
import ai.djl.repository.zoo.Criteria;
import ai.djl.repository.zoo.ModelZoo;
import ai.djl.repository.zoo.ZooModel;
import ai.djl.training.util.ProgressBar;
import ai.djl.translate.Batchifier;
import ai.djl.translate.Translator;
import ai.djl.translate.TranslatorContext;
import jakarta.annotation.PostConstruct;
import jakarta.annotation.PreDestroy;
import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.nio.file.Path;
import java.util.Map;

@Service
@Slf4j
public class EmbeddingService {

    private static final int TITLE_EMBEDDING_DIM = 384;
    private static final int CONTENT_EMBEDDING_DIM = 768;
    private static final int MAX_CONTENT_LENGTH = 5000;

    private ZooModel<String, float[]> titleEmbeddingModel;
    private ZooModel<String, float[]> contentEmbeddingModel;
    private Predictor<String, float[]> titlePredictor;
    private Predictor<String, float[]> contentPredictor;
    @Getter
    private boolean modelsLoaded = false;

    @PostConstruct
    public void init() {
        try {
            // Use a more recent PyTorch version that's available in the repository
            System.setProperty("DJL_CACHE_DIR", "/app/.djl.ai");
            System.setProperty("PYTORCH_VERSION", "1.13.1");

            // Add options to control resource loading
            Map<String, String> options = Map.of(
                    "mapLocation", "cpu",
                    "extraFiles", "tokenizer.json,config.json,vocab.txt"
            );

            // BERT model with CLS pooling for titles
            Criteria<String, float[]> titleCriteria = Criteria.builder()
                    .setTypes(String.class, float[].class)
                    .optModelUrls("djl://ai.djl.huggingface.pytorch/sentence-transformers/all-MiniLM-L6-v2")
                    .optTranslator(new SentenceTransformerTranslator())
                    .optEngine("PyTorch")
                    .optProgress(new ProgressBar())
                    .optOptions(options)
                    .build();

            // RoBERTa model with mean pooling for content
            Criteria<String, float[]> contentCriteria = Criteria.builder()
                    .setTypes(String.class, float[].class)
                    .optModelUrls("djl://ai.djl.huggingface.pytorch/sentence-transformers/all-roberta-large-v1")
                    .optTranslator(new SentenceTransformerTranslator())
                    .optEngine("PyTorch")
                    .optProgress(new ProgressBar())
                    .optOptions(options)
                    .build();

            log.info("Loading embedding models...");

            // Load models with better error handling
            try {
                titleEmbeddingModel = ModelZoo.loadModel(titleCriteria);
                titlePredictor = titleEmbeddingModel.newPredictor();
                log.info("Title embedding model loaded successfully");
            } catch (Exception e) {
                log.error("Failed to load title embedding model", e);
                closeModel(titleEmbeddingModel, "title embedding model");
                titleEmbeddingModel = null;
            }

            try {
                contentEmbeddingModel = ModelZoo.loadModel(contentCriteria);
                contentPredictor = contentEmbeddingModel.newPredictor();
                log.info("Content embedding model loaded successfully");
            } catch (Exception e) {
                log.error("Failed to load content embedding model", e);
                closeModel(contentEmbeddingModel, "content embedding model");
                contentEmbeddingModel = null;
            }

            modelsLoaded = (titleEmbeddingModel != null && contentEmbeddingModel != null);

            if (modelsLoaded) {
                log.info("All models loaded successfully");
            } else {
                log.warn("Some models failed to load - service will operate in degraded mode");
            }

        } catch (Exception e) {
            log.error("Model initialization failed", e);
            modelsLoaded = false;
            closeResources();
        }
    }

    // Improved translator with better error handling
    private static class SentenceTransformerTranslator implements Translator<String, float[]> {
        private HuggingFaceTokenizer tokenizer;

        @Override
        public void prepare(TranslatorContext ctx) throws IOException {
            try {
                tokenizer = HuggingFaceTokenizer.newInstance((Path) ctx.getModel());
            } catch (Exception e) {
                throw new IOException("Failed to initialize tokenizer", e);
            }
        }

        @Override
        public NDList processInput(TranslatorContext ctx, String input) {
            try {
                Encoding encoding = tokenizer.encode(input);
                long[] indices = encoding.getIds();
                long[] attentionMask = encoding.getAttentionMask();
                NDManager manager = ctx.getNDManager();

                NDArray indicesArray = manager.create(indices).expandDims(0);
                NDArray attentionMaskArray = manager.create(attentionMask).expandDims(0);

                return new NDList(indicesArray, attentionMaskArray);
            } catch (Exception e) {
                throw new RuntimeException("Failed to process input", e);
            }
        }

        @Override
        public float[] processOutput(TranslatorContext ctx, NDList list) {
            try {
                NDArray embeddings = list.get(0);
                NDArray attentionMask = list.get(1);

                // Apply mean pooling
                NDArray mask = attentionMask.expandDims(-1);
                NDArray sumEmbeddings = embeddings.mul(mask).sum(new int[]{1});
                NDArray sumMask = mask.sum(new int[]{1});
                NDArray pooled = sumEmbeddings.div(sumMask);

                return pooled.toFloatArray();
            } catch (Exception e) {
                throw new RuntimeException("Failed to process output", e);
            }
        }

        @Override
        public Batchifier getBatchifier() {
            return Batchifier.STACK;
        }
    }

    private void closeResources() {
        closePredictor(titlePredictor, "title predictor");
        closePredictor(contentPredictor, "content predictor");
        closeModel(titleEmbeddingModel, "title embedding model");
        closeModel(contentEmbeddingModel, "content embedding model");
    }

    @PreDestroy
    public void cleanup() {
        closeResources();
    }

    private void closePredictor(Predictor<?, ?> predictor, String name) {
        if (predictor != null) {
            try {
                predictor.close();
                log.debug("Closed {}", name);
            } catch (Exception e) {
                log.warn("Error closing {}", name, e);
            }
        }
    }

    private void closeModel(ZooModel<?, ?> model, String name) {
        if (model != null) {
            try {
                model.close();
                log.debug("Closed {}", name);
            } catch (Exception e) {
                log.warn("Error closing {}", name, e);
            }
        }
    }

    public float[] generateTitleEmbedding(String title) {
        if (!modelsLoaded || titlePredictor == null || title == null || title.trim().isEmpty()) {
            log.warn("Title embedding requested but service not fully initialized - returning zero vector");
            return new float[TITLE_EMBEDDING_DIM];
        }
        try {
            return titlePredictor.predict(title);
        } catch (Exception e) {
            log.error("Error generating title embedding", e);
            return new float[TITLE_EMBEDDING_DIM];
        }
    }

    public float[] generateContentEmbedding(String content) {
        if (!modelsLoaded || contentPredictor == null || content == null || content.trim().isEmpty()) {
            log.warn("Content embedding requested but service not fully initialized - returning zero vector");
            return new float[CONTENT_EMBEDDING_DIM];
        }
        try {
            String truncated = content.length() > MAX_CONTENT_LENGTH ?
                    content.substring(0, MAX_CONTENT_LENGTH) : content;
            return contentPredictor.predict(truncated);
        } catch (Exception e) {
            log.error("Error generating content embedding", e);
            return new float[CONTENT_EMBEDDING_DIM];
        }
    }

    public String arrayToPgVector(float[] array) {
        if (array == null || array.length == 0) {
            return "[]";
        }

        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < array.length; i++) {
            if (i > 0) {
                sb.append(",");
            }
            sb.append(array[i]);
        }
        sb.append("]");
        return sb.toString();
    }

    public String generateTitleEmbeddingAsPgVector(String title) {
        return arrayToPgVector(generateTitleEmbedding(title));
    }

    public String generateContentEmbeddingAsPgVector(String content) {
        return arrayToPgVector(generateContentEmbedding(content));
    }

    // New method to check if a specific model is available
    public boolean isTitleModelAvailable() {
        return modelsLoaded && titlePredictor != null;
    }

    public boolean isContentModelAvailable() {
        return modelsLoaded && contentPredictor != null;
    }
}