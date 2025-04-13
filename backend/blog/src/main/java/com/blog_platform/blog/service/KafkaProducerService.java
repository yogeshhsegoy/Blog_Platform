package com.blog_platform.blog.service;

import com.blog_platform.blog.dto.BlogEvent;
import com.blog_platform.blog.enums.Topic;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@RequiredArgsConstructor
@Slf4j
public class KafkaProducerService {

    private final KafkaTemplate<String, BlogEvent> kafkaTemplate;

    @Async
    public void sendBlogEvent(String eventType, Long blogId, String title, String content, List<Topic> topics, String userId) {
        try {
            BlogEvent event = new BlogEvent(eventType, blogId, title, content, topics, userId);
            kafkaTemplate.send("blog-events", event)
                    .addCallback(
                            result -> log.info("Successfully sent event for blog {}", blogId),
                            ex -> log.error("Failed to send event for blog {}", blogId, ex)
                    );
        } catch (Exception e) {
            log.error("Error sending Kafka message", e);
        }
    }
}