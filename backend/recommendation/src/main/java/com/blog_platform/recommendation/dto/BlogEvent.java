package com.blog_platform.recommendation.dto;


import lombok.Data;

import java.util.List;

@Data
public class BlogEvent {
    private String eventType;
    private Long blogId;
    private String title;
    private String content;
    private List<String> topics;
    private String userId;
}