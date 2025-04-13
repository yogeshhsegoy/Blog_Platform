package com.blog_platform.recommendation.service;

import ai.djl.Application;
import ai.djl.inference.Predictor;
import ai.djl.repository.zoo.Criteria;
import ai.djl.repository.zoo.ZooModel;
import ai.djl.training.util.ProgressBar;
import ai.djl.translate.TranslateException;
import jakarta.annotation.PreDestroy;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class EmbeddingService {

    private ZooModel<String, float[]> titleEmbeddingModel;
    private ZooModel<String, float[]> contentEmbeddingModel;
    private Predictor<String, float[]> titlePredictor;
    private Predictor<String, float[]> contentPredictor;

    public EmbeddingService() throws Exception {
        // Load title embedding model (384 dimensions)
        Criteria<String, float[]> titleCriteria = Criteria.builder()
                .optApplication(Application.NLP.TEXT_EMBEDDING)
                .setTypes(String.class, float[].class)
                .optModelUrls("djl://ai.djl.huggingface.pytorch/sentence-transformers/all-MiniLM-L6-v2")
                .optProgress(new ProgressBar())
                .build();

        // Load content embedding model (768 dimensions)
        Criteria<String, float[]> contentCriteria = Criteria.builder()
                .optApplication(Application.NLP.TEXT_EMBEDDING)
                .setTypes(String.class, float[].class)
                .optModelUrls("djl://ai.djl.huggingface.pytorch/sentence-transformers/all-mpnet-base-v2")
                .optProgress(new ProgressBar())
                .build();

        try {
            this.titleEmbeddingModel = titleCriteria.loadModel();
            this.contentEmbeddingModel = contentCriteria.loadModel();
            this.titlePredictor = titleEmbeddingModel.newPredictor();
            this.contentPredictor = contentEmbeddingModel.newPredictor();
        } catch (Exception e) {
            log.error("Failed to load embedding models", e);
            throw new RuntimeException("Failed to initialize embedding models", e);
        }
    }

    @PreDestroy
    public void cleanup() {
        if (titlePredictor != null) {
            titlePredictor.close();
        }
        if (contentPredictor != null) {
            contentPredictor.close();
        }
        if (titleEmbeddingModel != null) {
            titleEmbeddingModel.close();
        }
        if (contentEmbeddingModel != null) {
            contentEmbeddingModel.close();
        }
    }

    public float[] generateTitleEmbedding(String title) {
        try {
            if (title == null || title.trim().isEmpty()) {
                return new float[384]; // Return empty embedding for empty title
            }
            return titlePredictor.predict(title);
        } catch (TranslateException e) {
            log.error("Error generating title embedding", e);
            return new float[384]; // Return zero embedding as fallback with correct dimension
        }
    }

    public float[] generateContentEmbedding(String content) {
        try {
            if (content == null || content.trim().isEmpty()) {
                return new float[768]; // Return empty embedding for empty content
            }
            String truncated = content.length() > 5000 ? content.substring(0, 5000) : content;
            return contentPredictor.predict(truncated);
        } catch (TranslateException e) {
            log.error("Error generating content embedding", e);
            return new float[768]; // Return zero embedding as fallback with correct dimension
        }
    }
}