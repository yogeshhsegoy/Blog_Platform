package com.blog_platform.recommendation.service;

import com.blog_platform.recommendation.dto.BlogEvent;
import com.blog_platform.recommendation.model.Blog;
import com.blog_platform.recommendation.repository.BlogRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
@RequiredArgsConstructor
@Slf4j
public class KafkaConsumerService {

    private final BlogRepository blogRepository;
    private final RecommendationService recommendationService;

    @KafkaListener(topics = "blog-events", groupId = "recommendation-service")
    @Transactional
    public void handleBlogEvent(BlogEvent event) {
        try {
            switch (event.getEventType()) {
                case "CREATE":
                case "UPDATE":
                    processBlogUpdate(event);
                    break;
                case "DELETE":
                    blogRepository.deleteById(event.getBlogId());
                    break;
                default:
                    log.warn("Unknown event type: {}", event.getEventType());
            }
        } catch (Exception e) {
            log.error("Error processing blog event", e);
        }
    }

    private void processBlogUpdate(BlogEvent event) {
        Blog blog = blogRepository.findById(event.getBlogId()).orElse(new Blog());

        blog.setId(event.getBlogId());
        blog.setTitle(event.getTitle());
        blog.setContent(event.getContent());
        blog.setTopics(event.getTopics());
        blog.setUserId(event.getUserId());

        // Generate embeddings
        recommendationService.updateBlogEmbeddings(blog);

        blogRepository.save(blog);
    }
}
