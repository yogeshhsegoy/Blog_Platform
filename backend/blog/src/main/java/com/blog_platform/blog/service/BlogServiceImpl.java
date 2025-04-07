package com.blog_platform.blog.service;
import com.blog_platform.blog.model.Comment;

import com.blog_platform.blog.dto.BlogRequest;
import com.blog_platform.blog.dto.BlogResponse;
import com.blog_platform.blog.exceptions.BlogNotFoundException;
import com.blog_platform.blog.model.Blog;
import com.blog_platform.blog.repository.BlogRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class BlogServiceImpl implements BlogService {

    private final BlogRepository blogRepository;

    @Override
    @Transactional
    public BlogResponse createBlog(BlogRequest blogRequest, String userId) {
        Blog blog = new Blog();
        blog.setTopics(blogRequest.getTopics());  // Updated to set topics list
        blog.setTitle(blogRequest.getTitle());
        blog.setContent(blogRequest.getContent());
        blog.setPreviewImage(blogRequest.getPreviewImage());
        blog.setAnonymous(blogRequest.isAnonymous());
        blog.setUserId(userId);

        Blog savedBlog = blogRepository.save(blog);
        return mapToBlogResponse(savedBlog);
    }

    @Override
    public BlogResponse getBlogById(Long id) {
        Blog blog = blogRepository.findById(id)
                .orElseThrow(() -> new BlogNotFoundException("Blog not found with id: " + id));
        return mapToBlogResponse(blog);
    }

    @Override
    public List<BlogResponse> getAllBlogs() {
        return blogRepository.findAll().stream()
                .map(this::mapToBlogResponse)
                .collect(Collectors.toList());
    }

    @Override
    public List<BlogResponse> getBlogsByUser(String userId) {
        return blogRepository.findByUserId(userId).stream()
                .map(this::mapToBlogResponse)
                .collect(Collectors.toList());
    }

    @Override
    @Transactional
    public BlogResponse updateBlog(Long id, BlogRequest blogRequest, String userId) {
        Blog blog = blogRepository.findById(id)
                .orElseThrow(() -> new BlogNotFoundException("Blog not found with id: " + id));

        if (!blog.getUserId().equals(userId)) {
            throw new RuntimeException("You are not authorized to update this blog");
        }

        blog.setTitle(blogRequest.getTitle());
        blog.setTopics(blogRequest.getTopics());  // Updated to set topics list
        blog.setContent(blogRequest.getContent());
        blog.setPreviewImage(blogRequest.getPreviewImage());
        blog.setAnonymous(blogRequest.isAnonymous());

        Blog updatedBlog = blogRepository.save(blog);
        return mapToBlogResponse(updatedBlog);
    }

    @Override
    @Transactional
    public void deleteBlog(Long id, String userId) {
        Blog blog = blogRepository.findById(id)
                .orElseThrow(() -> new BlogNotFoundException("Blog not found with id: " + id));

        if (!blog.getUserId().equals(userId)) {
            throw new RuntimeException("You are not authorized to delete this blog");
        }

        blogRepository.delete(blog);
    }

    @Override
    @Transactional
    public BlogResponse likeBlog(Long id, String userId) {
        Blog blog = blogRepository.findById(id)
                .orElseThrow(() -> new BlogNotFoundException("Blog not found with id: " + id));

        blog.setLikes(blog.getLikes() + 1);
        Blog likedBlog = blogRepository.save(blog);
        return mapToBlogResponse(likedBlog);
    }

    @Override
    @Transactional
    public BlogResponse addComment(Long id, String commentContent, String userId) {
        Blog blog = blogRepository.findById(id)
                .orElseThrow(() -> new BlogNotFoundException("Blog not found with id: " + id));

        // Create a new Comment object
        Comment comment = new Comment();
        comment.setContent(commentContent);
        comment.setUserId(userId);
        comment.setBlog(blog); // Set the blog reference

        // Add the comment to the blog's comment list
        blog.getComments().add(comment);

        Blog updatedBlog = blogRepository.save(blog);
        return mapToBlogResponse(updatedBlog);
    }

    private BlogResponse mapToBlogResponse(Blog blog) {
        BlogResponse response = new BlogResponse();
        response.setId(blog.getId());
        response.setTopics(blog.getTopics());  // Updated to get topics list
        response.setTitle(blog.getTitle());
        response.setContent(blog.getContent());
        response.setPreviewImage(blog.getPreviewImage());
        response.setCreatedAt(blog.getCreatedAt());
        response.setUpdatedAt(blog.getUpdatedAt());
        response.setLikes(blog.getLikes());
        response.setComments(blog.getComments());
        response.setAnonymous(blog.isAnonymous());
        response.setUserId(blog.isAnonymous() ? null : blog.getUserId());
        return response;
    }
}