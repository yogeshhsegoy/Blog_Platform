'use client';

import { useEffect, useState } from 'react';
import { useParams, useRouter } from 'next/navigation';
import { Blog } from '@/lib/types';
import { apiService } from '@/lib/apiService';
import { Avatar, AvatarFallback } from '@/components/ui/avatar';
import { Badge } from '@/components/ui/badge';
import { formatDistanceToNow } from 'date-fns';
import { Skeleton } from '@/components/ui/skeleton';
import { SimilarBlogs } from '@/components/SimilarBlogs';
import { useAuth } from '@/context/AuthContext';
import { ThumbsUp, MessageSquare, ArrowLeft } from 'lucide-react';
import { Button } from '@/components/ui/button';
import { Separator } from '@/components/ui/separator';
import { Input } from '@/components/ui/input';
import { useToast } from '@/hooks/use-toast';

interface Comment {
    id: number;
    content: string;
    userId: string;
    createdAt: string;
}

export default function BlogPageClient() {
    const { id } = useParams();
    const router = useRouter();
    const { user, isLoading: authLoading } = useAuth();
    const { toast } = useToast();
    const [blog, setBlog] = useState<Blog | null>(null);
    const [loading, setLoading] = useState(true);
    const [similarBlogs, setSimilarBlogs] = useState<Blog[]>([]);
    const [loadingSimilar, setLoadingSimilar] = useState(true);
    const [comment, setComment] = useState('');
    const [isSubmitting, setIsSubmitting] = useState(false);

    // Fetch the main blog post
    useEffect(() => {
        if (!id) return;

        const fetchBlog = async () => {
            try {
                setLoading(true);
                const blogs = await apiService.getBlogsByIds([Number(id)]);
                if (blogs.length > 0) {
                    setBlog(blogs[0]);
                }
            } catch (error) {
                console.error('Error fetching blog:', error);
                toast({
                    title: 'Error',
                    description: 'Failed to load blog post',
                    variant: 'destructive',
                });
            } finally {
                setLoading(false);
            }
        };

        fetchBlog();
    }, [id, toast]);

    // Fetch similar blogs when blog data and token are available
    useEffect(() => {
        if (!blog || !user?.token) return;

        const fetchSimilarBlogs = async () => {
            try {
                setLoadingSimilar(true);
                const recommendations = await apiService.getSimilarBlogs(
                    {
                        topics: blog.topics,
                        title: blog.title,
                        content: blog.content,
                        limit: 3,
                    },
                    user.token
                );

                if (recommendations.blogIds.length > 0) {
                    const filteredIds = recommendations.blogIds.filter(
                        (blogId: number) => blogId !== Number(id)
                    );

                    if (filteredIds.length > 0) {
                        const blogs = await apiService.getBlogsByIds(filteredIds, user.token);
                        setSimilarBlogs(blogs);
                    }
                }
            } catch (error) {
                console.error('Error fetching similar blogs:', error);
            } finally {
                setLoadingSimilar(false);
            }
        };

        fetchSimilarBlogs();
    }, [blog, user?.token, id]);

    const handleLike = async () => {
        if (!user?.token) {
            toast({
                title: 'Please sign in',
                description: 'You need to be signed in to like posts',
                variant: 'default',
            });
            return;
        }

        if (!blog) return;

        try {
            const endpoint = blog.likedByCurrentUser
                ? `http://localhost:8082/api/blogs/${blog.id}/dislike`
                : `http://localhost:8082/api/blogs/${blog.id}/like`;

            const response = await fetch(endpoint, {
                method: 'POST',
                headers: {
                    Authorization: `Bearer ${user.token}`,
                },
            });

            if (!response.ok) {
                throw new Error('Failed to update like status');
            }

            setBlog((prev) => {
                if (!prev) return null;
                return {
                    ...prev,
                    likes: prev.likedByCurrentUser ? prev.likes - 1 : prev.likes + 1,
                    likedByCurrentUser: !prev.likedByCurrentUser,
                };
            });
        } catch (error) {
            console.error('Error updating like:', error);
            toast({
                title: 'Error',
                description: 'Failed to update like status',
                variant: 'destructive',
            });
        }
    };

    const handleComment = async (e: React.FormEvent) => {
        e.preventDefault();

        if (!user?.token) {
            toast({
                title: 'Please sign in',
                description: 'You need to be signed in to comment',
                variant: 'default',
            });
            return;
        }

        if (!blog || !comment.trim()) return;

        setIsSubmitting(true);
        try {
            const response = await fetch(
                `http://localhost:8082/api/blogs/${blog.id}/comment`,
                {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                        Authorization: `Bearer ${user.token}`,
                    },
                    body: JSON.stringify({ content: comment }),
                }
            );

            if (!response.ok) {
                throw new Error('Failed to add comment');
            }

            const newComment = await response.json();
            setBlog((prev) => {
                if (!prev) return null;
                return {
                    ...prev,
                    comments: [...prev.comments, newComment],
                };
            });

            setComment('');
            toast({
                title: 'Success',
                description: 'Comment added successfully',
            });
        } catch (error) {
            console.error('Error adding comment:', error);
            toast({
                title: 'Error',
                description: 'Failed to add comment',
                variant: 'destructive',
            });
        } finally {
            setIsSubmitting(false);
        }
    };

    if (authLoading || loading) {
        return (
            <div className="container mx-auto py-8 px-4 max-w-4xl">
                <Skeleton className="h-8 w-3/4 mb-4" />
                <Skeleton className="h-6 w-1/4 mb-8" />
                <Skeleton className="h-[300px] w-full mb-8 rounded-lg" />
                <div className="space-y-4">
                    <Skeleton className="h-4 w-full" />
                    <Skeleton className="h-4 w-full" />
                    <Skeleton className="h-4 w-5/6" />
                </div>
            </div>
        );
    }

    if (!blog) {
        return (
            <div className="container mx-auto py-8 px-4 text-center">
                <h2 className="text-2xl font-bold mb-4">Blog not found</h2>
                <p className="text-muted-foreground mb-6">
                    The blog you're looking for doesn't exist or has been removed.
                </p>
                <Button onClick={() => router.push('/home')}>Back to Home</Button>
            </div>
        );
    }

    return (
        <div className="container mx-auto py-8 px-4">
            <button
                onClick={() => router.back()}
                className="flex items-center text-sm text-muted-foreground hover:text-foreground mb-6 transition-colors"
            >
                <ArrowLeft className="h-4 w-4 mr-1" />
                Back
            </button>

            <div className="max-w-4xl mx-auto">
                <article>
                    <h1 className="text-3xl md:text-4xl font-bold mb-4">{blog.title}</h1>

                    <div className="flex items-center space-x-4 mb-8">
                        <Avatar>
                            <AvatarFallback>
                                {blog.userId.substring(0, 2).toUpperCase()}
                            </AvatarFallback>
                        </Avatar>

                        <div>
                            <div className="font-medium">
                                {blog.anonymous ? 'Anonymous' : blog.userId}
                            </div>
                            <div className="text-sm text-muted-foreground">
                                {formatDistanceToNow(new Date(blog.createdAt), {
                                    addSuffix: true,
                                })}
                            </div>
                        </div>
                    </div>

                    {blog.previewImage && (
                        <div className="aspect-video mb-8 overflow-hidden rounded-lg">
                            <img
                                src={blog.previewImage}
                                alt={blog.title}
                                className="object-cover w-full h-full"
                            />
                        </div>
                    )}

                    <div className="prose prose-lg max-w-none">
                        <p className="whitespace-pre-line">{blog.content}</p>
                    </div>

                    <div className="flex flex-wrap gap-2 mt-6">
                        {blog.topics.map((topic) => (
                            <Badge key={topic} variant="secondary">
                                {topic.toLowerCase()}
                            </Badge>
                        ))}
                    </div>

                    <div className="flex items-center space-x-4 mt-8">
                        <Button
                            variant="outline"
                            size="sm"
                            className={`flex items-center space-x-2 ${
                                blog.likedByCurrentUser ? 'bg-primary text-primary-foreground' : ''
                            }`}
                            onClick={handleLike}
                            disabled={!user}
                        >
                            <ThumbsUp className="h-4 w-4" />
                            <span>{blog.likes}</span>
                        </Button>

                        <Button
                            variant="outline"
                            size="sm"
                            className="flex items-center space-x-2"
                            onClick={() => document.getElementById('comment-input')?.focus()}
                            disabled={!user}
                        >
                            <MessageSquare className="h-4 w-4" />
                            <span>{blog.comments.length}</span>
                        </Button>
                    </div>
                </article>

                <Separator className="my-8" />

                <section className="space-y-6">
                    <h2 className="text-2xl font-bold">Comments</h2>

                    {user ? (
                        <form onSubmit={handleComment} className="space-y-4">
                            <Input
                                id="comment-input"
                                placeholder="Add a comment..."
                                value={comment}
                                onChange={(e) => setComment(e.target.value)}
                                disabled={isSubmitting}
                            />
                            <Button
                                type="submit"
                                disabled={isSubmitting || !comment.trim()}
                            >
                                {isSubmitting ? 'Posting...' : 'Post Comment'}
                            </Button>
                        </form>
                    ) : (
                        <p className="text-muted-foreground">
                            Please{' '}
                            <Button
                                variant="link"
                                className="px-1"
                                onClick={() => router.push('/auth/signin')}
                            >
                                sign in
                            </Button>{' '}
                            to comment.
                        </p>
                    )}

                    <div className="space-y-4">
                        {blog.comments.length > 0 ? (
                            blog.comments.map((comment: Comment) => (
                                <div key={comment.id} className="border rounded-lg p-4">
                                    <div className="flex items-center space-x-2 mb-2">
                                        <Avatar className="h-6 w-6">
                                            <AvatarFallback>
                                                {comment.userId.substring(0, 2).toUpperCase()}
                                            </AvatarFallback>
                                        </Avatar>
                                        <span className="font-medium">{comment.userId}</span>
                                        <span className="text-sm text-muted-foreground">
                      {formatDistanceToNow(new Date(comment.createdAt), {
                          addSuffix: true,
                      })}
                    </span>
                                    </div>
                                    <p className="text-sm">{comment.content}</p>
                                </div>
                            ))
                        ) : (
                            <p className="text-muted-foreground text-center py-4">
                                No comments yet. Be the first to comment!
                            </p>
                        )}
                    </div>
                </section>

                <Separator className="my-12" />

                <section>
                    <h2 className="text-2xl font-bold mb-6">Similar articles</h2>
                    <SimilarBlogs blogs={similarBlogs} loading={loadingSimilar} />
                </section>
            </div>
        </div>
    );
}