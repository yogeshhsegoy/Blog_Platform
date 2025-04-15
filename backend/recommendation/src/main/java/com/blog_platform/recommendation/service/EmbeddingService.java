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
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
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

    // Define a fallback embedding generator that doesn't use ML models
    private SimpleFallbackEmbedding fallbackEmbedding = new SimpleFallbackEmbedding();

    @PostConstruct
    public void init() {
        try {
            // Set up the DJL cache directory and ensure it exists
            String cacheDir = "/app/.djl.ai";
            Path cacheDirPath = Paths.get(cacheDir);
            if (!Files.exists(cacheDirPath)) {
                try {
                    Files.createDirectories(cacheDirPath);
                    log.info("Created DJL cache directory: {}", cacheDir);
                } catch (IOException e) {
                    log.warn("Could not create DJL cache directory: {}", cacheDir, e);
                    // Try to use a temp directory instead
                    cacheDir = System.getProperty("java.io.tmpdir") + "/.djl.ai";
                    cacheDirPath = Paths.get(cacheDir);
                    Files.createDirectories(cacheDirPath);
                    log.info("Created alternative DJL cache directory: {}", cacheDir);
                }
            }

            System.setProperty("DJL_CACHE_DIR", cacheDir);

            // Try a more compatible PyTorch version
            System.setProperty("PYTORCH_VERSION", "1.12.1");

            log.info("Using DJL cache directory: {}", cacheDir);
            log.info("Using PyTorch version: {}", System.getProperty("PYTORCH_VERSION"));

            // Add options to control resource loading
            Map<String, String> options = new HashMap<>();
            options.put("mapLocation", "cpu");
            options.put("extraFiles", "tokenizer.json,config.json,special_tokens_map.json,vocab.txt");
            options.put("modelName", "sentence-transformer");

            // Use the smaller model for both to simplify setup
            String modelUrl = "djl://ai.djl.huggingface.pytorch/sentence-transformers/all-MiniLM-L6-v2";

            log.info("Trying to load model from URL: {}", modelUrl);

            // BERT model with CLS pooling for titles
            Criteria<String, float[]> titleCriteria = Criteria.builder()
                    .setTypes(String.class, float[].class)
                    .optModelUrls(modelUrl)
                    .optTranslator(new DebugSentenceTransformerTranslator())
                    .optEngine("PyTorch")
                    .optProgress(new ProgressBar())
                    .optOptions(options)
                    .build();

            // Use the same model for content to simplify
            Criteria<String, float[]> contentCriteria = Criteria.builder()
                    .setTypes(String.class, float[].class)
                    .optModelUrls(modelUrl)
                    .optTranslator(new DebugSentenceTransformerTranslator())
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

                // Test the model with a simple input
                try {
                    float[] testEmbedding = titlePredictor.predict("Test sentence");
                    log.info("Title model test successful - generated vector of length {}", testEmbedding.length);
                } catch (Exception e) {
                    log.error("Title model test failed", e);
                    throw new RuntimeException("Title model test failed", e);
                }
            } catch (Exception e) {
                log.error("Failed to load title embedding model", e);
                closeModel(titleEmbeddingModel, "title embedding model");
                titleEmbeddingModel = null;
                titlePredictor = null;
            }

            try {
                contentEmbeddingModel = ModelZoo.loadModel(contentCriteria);
                contentPredictor = contentEmbeddingModel.newPredictor();
                log.info("Content embedding model loaded successfully");

                // Test the model with a simple input
                try {
                    float[] testEmbedding = contentPredictor.predict("Test sentence");
                    log.info("Content model test successful - generated vector of length {}", testEmbedding.length);
                } catch (Exception e) {
                    log.error("Content model test failed", e);
                    throw new RuntimeException("Content model test failed", e);
                }
            } catch (Exception e) {
                log.error("Failed to load content embedding model", e);
                closeModel(contentEmbeddingModel, "content embedding model");
                contentEmbeddingModel = null;
                contentPredictor = null;
            }

            modelsLoaded = (titleEmbeddingModel != null || contentEmbeddingModel != null);

            if (modelsLoaded) {
                log.info("At least one model loaded successfully - service will operate in partial mode");
            } else {
                log.warn("All models failed to load - service will operate in fallback mode");
            }

        } catch (Exception e) {
            log.error("Model initialization failed", e);
            modelsLoaded = false;
            closeResources();
        }
    }

    // Improved translator with better error handling and debugging
    private static class DebugSentenceTransformerTranslator implements Translator<String, float[]> {
        private HuggingFaceTokenizer tokenizer;

        @Override
        public void prepare(TranslatorContext ctx) throws IOException {
            try {
                Path modelPath = (Path) ctx.getModel();
                log.info("Initializing tokenizer from model path: {}", modelPath);

                // List the contents of the model directory
                if (Files.exists(modelPath) && Files.isDirectory(modelPath)) {
                    log.info("Model directory contents:");
                    Files.list(modelPath).forEach(p -> log.info(" - {}", p));
                } else {
                    log.warn("Model path doesn't exist or is not a directory: {}", modelPath);
                }

                // Initialize the tokenizer
                tokenizer = HuggingFaceTokenizer.newInstance(modelPath);
                log.info("Tokenizer initialized successfully");

                // Test the tokenizer
                Encoding encoding = tokenizer.encode("Test sentence");
                log.info("Tokenizer test successful - encoded to {} tokens", encoding.getIds().length);
            } catch (Exception e) {
                String errorMsg = "Failed to initialize tokenizer";
                log.error(errorMsg, e);
                throw new IOException(errorMsg, e);
            }
        }

        @Override
        public NDList processInput(TranslatorContext ctx, String input) {
            try {
                if (tokenizer == null) {
                    throw new RuntimeException("Tokenizer not initialized");
                }

                log.debug("Encoding input: {}", input);
                Encoding encoding = tokenizer.encode(input);
                long[] indices = encoding.getIds();
                long[] attentionMask = encoding.getAttentionMask();

                log.debug("Input encoded to {} tokens", indices.length);

                NDManager manager = ctx.getNDManager();
                NDArray indicesArray = manager.create(indices).expandDims(0);
                NDArray attentionMaskArray = manager.create(attentionMask).expandDims(0);

                return new NDList(indicesArray, attentionMaskArray);
            } catch (Exception e) {
                log.error("Failed to process input: {}", input, e);
                throw new RuntimeException("Failed to process input", e);
            }
        }

        @Override
        public float[] processOutput(TranslatorContext ctx, NDList list) {
            try {
                log.debug("Processing output NDList with {} items", list.size());

                NDArray embeddings = list.get(0);
                log.debug("Embeddings shape: {}", embeddings.getShape());

                NDArray attentionMask = list.get(1);
                log.debug("Attention mask shape: {}", attentionMask.getShape());

                // Apply mean pooling
                NDArray mask = attentionMask.expandDims(-1);
                NDArray sumEmbeddings = embeddings.mul(mask).sum(new int[]{1});
                NDArray sumMask = mask.sum(new int[]{1});
                NDArray pooled = sumEmbeddings.div(sumMask);

                log.debug("Pooled embeddings shape: {}", pooled.getShape());

                return pooled.toFloatArray();
            } catch (Exception e) {
                log.error("Failed to process output", e);
                throw new RuntimeException("Failed to process output", e);
            }
        }

        @Override
        public Batchifier getBatchifier() {
            return Batchifier.STACK;
        }
    }

    // Fallback embedding generator that doesn't use ML
    private static class SimpleFallbackEmbedding {
        public float[] generateTitleEmbedding(String title, int dimension) {
            return generateSimpleEmbedding(title, dimension);
        }

        public float[] generateContentEmbedding(String content, int dimension) {
            return generateSimpleEmbedding(content, dimension);
        }

        private float[] generateSimpleEmbedding(String text, int dimension) {
            float[] embedding = new float[dimension];

            if (text == null || text.isEmpty()) {
                return embedding;
            }

            // Use a simple hash-based approach to generate pseudo-embeddings
            int hash = text.hashCode();
            // Seed the random generator
            java.util.Random random = new java.util.Random(hash);

            // Generate pseudo-random values, normalize to unit length
            double sumSquares = 0.0;
            for (int i = 0; i < dimension; i++) {
                embedding[i] = (random.nextFloat() * 2 - 1);
                sumSquares += embedding[i] * embedding[i];
            }

            double norm = Math.sqrt(sumSquares);
            if (norm > 0) {
                for (int i = 0; i < dimension; i++) {
                    embedding[i] /= norm;
                }
            }

            return embedding;
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
        if (title == null || title.trim().isEmpty()) {
            log.warn("Empty title provided - returning zero vector");
            return new float[TITLE_EMBEDDING_DIM];
        }

        if (modelsLoaded && titlePredictor != null) {
            try {
                return titlePredictor.predict(title);
            } catch (Exception e) {
                log.error("Error generating title embedding with model, falling back to simple embedding", e);
            }
        }

        // Use fallback if model failed or isn't available
        log.info("Using fallback embedding generator for title");
        return fallbackEmbedding.generateTitleEmbedding(title, TITLE_EMBEDDING_DIM);
    }

    public float[] generateContentEmbedding(String content) {
        if (content == null || content.trim().isEmpty()) {
            log.warn("Empty content provided - returning zero vector");
            return new float[CONTENT_EMBEDDING_DIM];
        }

        String truncated = content.length() > MAX_CONTENT_LENGTH ?
                content.substring(0, MAX_CONTENT_LENGTH) : content;

        if (modelsLoaded && contentPredictor != null) {
            try {
                return contentPredictor.predict(truncated);
            } catch (Exception e) {
                log.error("Error generating content embedding with model, falling back to simple embedding", e);
            }
        }

        // Use fallback if model failed or isn't available
        log.info("Using fallback embedding generator for content");
        return fallbackEmbedding.generateContentEmbedding(truncated, CONTENT_EMBEDDING_DIM);
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

    // Public methods to check service status
    public boolean isTitleModelAvailable() {
        return modelsLoaded && titlePredictor != null;
    }

    public boolean isContentModelAvailable() {
        return modelsLoaded && contentPredictor != null;
    }

    public boolean isUsingFallbackMode() {
        return !isTitleModelAvailable() && !isContentModelAvailable();
    }
}