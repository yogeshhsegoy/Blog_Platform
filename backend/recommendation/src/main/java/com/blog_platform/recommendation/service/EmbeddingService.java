package com.blog_platform.recommendation.service;

import ai.djl.Application;
import ai.djl.inference.Predictor;
import ai.djl.repository.zoo.Criteria;
import ai.djl.repository.zoo.ModelZoo;
import ai.djl.repository.zoo.ZooModel;
import ai.djl.training.util.ProgressBar;
import ai.djl.translate.TranslateException;
import jakarta.annotation.PostConstruct;
import jakarta.annotation.PreDestroy;
import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.util.Arrays;

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
            System.setProperty("PYTORCH_VERSION", "2.0.1");
            System.setProperty("DJL_CACHE_DIR", "/root/.djl.ai");

            // Initialize title embedding model
            Criteria<String, float[]> titleCriteria = Criteria.builder()
                    .setTypes(String.class, float[].class)
                    .optApplication(Application.NLP.TEXT_EMBEDDING)
                    .optFilter("backbone", "bert")
                    .optEngine("PyTorch")
                    .optProgress(new ProgressBar())
                    .build();

            // Initialize content embedding model
            Criteria<String, float[]> contentCriteria = Criteria.builder()
                    .setTypes(String.class, float[].class)
                    .optApplication(Application.NLP.TEXT_EMBEDDING)
                    .optFilter("backbone", "roberta")
                    .optEngine("PyTorch")
                    .optProgress(new ProgressBar())
                    .build();

            // Load models
            titleEmbeddingModel = ModelZoo.loadModel(titleCriteria);
            contentEmbeddingModel = ModelZoo.loadModel(contentCriteria);

            // Create predictors
            titlePredictor = titleEmbeddingModel.newPredictor();
            contentPredictor = contentEmbeddingModel.newPredictor();

            modelsLoaded = true;
            log.info("Successfully loaded embedding models");
        } catch (Exception e) {
            log.error("Failed to load embedding models. Falling back to no-op implementation", e);
            modelsLoaded = false;
            closeResources(); // Clean up any partial initialization
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
        closePredictor(titlePredictor, "title predictor");
        closePredictor(contentPredictor, "content predictor");
        closeModel(titleEmbeddingModel, "title embedding model");
        closeModel(contentEmbeddingModel, "content embedding model");
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
        if (!modelsLoaded || title == null || title.trim().isEmpty()) {
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
        if (!modelsLoaded || content == null || content.trim().isEmpty()) {
            return new float[CONTENT_EMBEDDING_DIM];
        }
        try {
            String truncated = content.length() > MAX_CONTENT_LENGTH ?
                    content.substring(0, MAX_CONTENT_LENGTH) : content;
            return contentPredictor.predict(truncated);
        } catch (Exception e) { // Broaden exception catch
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

}
