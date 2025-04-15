package com.blog_platform.recommendation.service;

import com.blog_platform.recommendation.repository.BlogRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.Collections;
import java.util.List;

@Service
@RequiredArgsConstructor
public class RecommendationService {
    private final BlogRepository blogRepository;
    private final EmbeddingService embeddingService;

    public List<Long> getTopicBasedRecommendations(List<String> topics, int limit) {
        return blogRepository.findBlogIdsByTopics(topics, limit);
    }

    public List<Long> getContentBasedRecommendations(String query, int limit) {
        if (!embeddingService.isModelsLoaded()) {
            return Collections.emptyList(); // or fallback to topic-based
        }
        String embedding = embeddingService.arrayToPgVector(
                embeddingService.generateContentEmbedding(query)
        );
        return blogRepository.findBlogIdsByContent(embedding, limit);
    }

    public List<Long> getHybridRecommendations(List<String> topics, String query, int limit) {
        String titleEmbedding = embeddingService.arrayToPgVector(
                embeddingService.generateTitleEmbedding(query)
        );
        String contentEmbedding = embeddingService.arrayToPgVector(
                embeddingService.generateContentEmbedding(query)
        );

        return blogRepository.findBlogIdsByTopicsAndContent(
                topics, titleEmbedding, contentEmbedding, limit
        );
    }
}