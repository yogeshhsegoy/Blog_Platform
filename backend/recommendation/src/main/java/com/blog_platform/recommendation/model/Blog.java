package com.blog_platform.recommendation.model;

import io.hypersistence.utils.hibernate.type.array.FloatArrayType;
import jakarta.persistence.*;
import lombok.Data;
import org.hibernate.annotations.Type;
import java.util.List;

@Data
@Entity
@Table(name = "blogs")
public class Blog {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String title;

    @Column(columnDefinition = "TEXT")
    private String content;

    private String userId;

    @ElementCollection
    @CollectionTable(name = "blog_topics", joinColumns = @JoinColumn(name = "blog_id"))
    @Column(name = "topic")
    private List<String> topics;

    @Type(FloatArrayType.class)
    @Column(name = "title_embedding", columnDefinition = "float8[]")
    private float[] titleEmbedding;

    @Type(FloatArrayType.class)
    @Column(name = "content_embedding", columnDefinition = "float8[]")
    private float[] contentEmbedding;
}