package com.blog_platform.recommendation.service;

import ai.djl.Application;
import ai.djl.inference.Predictor;
import ai.djl.repository.zoo.Criteria;
import ai.djl.repository.zoo.ZooModel;
import ai.djl.training.util.ProgressBar;
import ai.djl.translate.TranslateException;
import com.blog_platform.recommendation.model.Blog;
import com.blog_platform.recommendation.repository.BlogRepository;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import jakarta.annotation.PreDestroy;

import java.util.List;
import java.util.Map;
import java.util.HashMap;

@Service
@Slf4j
public class RecommendationService {

    private final BlogRepository blogRepository;
    private ZooModel<String, float[]> titleEmbeddingModel;
    private ZooModel<String, float[]> contentEmbeddingModel;
    private Predictor<String, float[]> titlePredictor;
    private Predictor<String, float[]> contentPredictor;

    public RecommendationService(BlogRepository blogRepository) throws Exception {
        this.blogRepository = blogRepository;

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

    // Clean up resources when the service is destroyed
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

    public void updateBlogEmbeddings(Blog blog) {
        try {
            blog.setTitleEmbedding(generateTitleEmbedding(blog.getTitle()));
            blog.setContentEmbedding(generateContentEmbedding(blog.getContent()));
        } catch (Exception e) {
            log.error("Failed to generate embeddings for blog {}", blog.getId(), e);
        }
    }

    public List<Long> getTopicBasedRecommendations(List<String> topics, int limit) {
        return blogRepository.findBlogIdsByTopics(topics, limit);
    }

    public List<Long> getContentBasedRecommendations(String query, int limit) {
        float[] embedding = generateContentEmbedding(query);
        String embeddingStr = arrayToPgVector(embedding);
        return blogRepository.findBlogIdsByContent(embeddingStr, limit);
    }

    public List<Long> getHybridRecommendations(List<String> topics, String query, int limit) {
        float[] titleEmbedding = generateTitleEmbedding(query);
        float[] contentEmbedding = generateContentEmbedding(query);

        return blogRepository.findBlogIdsByTopicsAndContent(
                topics,
                arrayToPgVector(titleEmbedding),
                arrayToPgVector(contentEmbedding),
                limit
        );
    }

    private float[] generateTitleEmbedding(String title) {
        try {
            return titlePredictor.predict(title);
        } catch (TranslateException e) {
            log.error("Error generating title embedding", e);
            return new float[384]; // Return zero embedding as fallback with correct dimension
        }
    }

    private float[] generateContentEmbedding(String content) {
        try {
            String truncated = content.length() > 5000 ? content.substring(0, 5000) : content;
            return contentPredictor.predict(truncated);
        } catch (TranslateException e) {
            log.error("Error generating content embedding", e);
            return new float[768]; // Return zero embedding as fallback with correct dimension
        }
    }

    private String arrayToPgVector(float[] array) {
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < array.length; i++) {
            if (i > 0) sb.append(",");
            sb.append(array[i]);
        }
        sb.append("]");
        return sb.toString();
    }
}