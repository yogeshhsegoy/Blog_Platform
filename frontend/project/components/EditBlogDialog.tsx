'use client';

import { useState } from 'react';
import { useForm } from 'react-hook-form';
import { zodResolver } from '@hookform/resolvers/zod';
import { z } from 'zod';
import { Dialog, DialogContent, DialogHeader, DialogTitle } from '@/components/ui/dialog';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { Textarea } from '@/components/ui/textarea';
import { Checkbox } from '@/components/ui/checkbox';
import { AVAILABLE_TOPICS } from '@/lib/constants';
import { useAuth } from '@/context/AuthContext';
import { useToast } from '@/hooks/use-toast';
import { Blog } from '@/lib/types';

const formSchema = z.object({
    title: z.string().min(1, 'Title is required'),
    content: z.string().min(1, 'Content is required'),
    previewImage: z.string().url('Must be a valid URL'),
    topics: z.array(z.string()).min(1, 'Select at least one topic'),
    anonymous: z.boolean(),
});

type FormData = z.infer<typeof formSchema>;

interface EditBlogDialogProps {
    blog: Blog;
    open: boolean;
    onOpenChange: (open: boolean) => void;
    onBlogUpdated: () => void;
}

export function EditBlogDialog({ blog, open, onOpenChange, onBlogUpdated }: EditBlogDialogProps) {
    const { user } = useAuth();
    const { toast } = useToast();
    const [isLoading, setIsLoading] = useState(false);

    const {
        register,
        handleSubmit,
        setValue,
        watch,
        formState: { errors },
    } = useForm<FormData>({
        resolver: zodResolver(formSchema),
        defaultValues: {
            title: blog.title,
            content: blog.content,
            previewImage: blog.previewImage,
            topics: blog.topics,
            anonymous: blog.anonymous,
        },
    });

    const selectedTopics = watch('topics');

    const handleTopicChange = (topic: string, checked: boolean) => {
        const currentTopics = selectedTopics;
        if (checked) {
            setValue('topics', [...currentTopics, topic]);
        } else {
            setValue('topics', currentTopics.filter(t => t !== topic));
        }
    };

    const onSubmit = async (data: FormData) => {
        if (!user) return;

        setIsLoading(true);
        try {
            const response = await fetch(`http://localhost:8082/api/blogs/${blog.id}`, {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${user.token}`,
                },
                body: JSON.stringify({
                    ...data,
                    topics: data.topics.map(t => t.toUpperCase()),
                }),
            });

            if (!response.ok) {
                throw new Error('Failed to update blog');
            }

            onBlogUpdated();
        } catch (error) {
            console.error('Error updating blog:', error);
            toast({
                title: 'Error',
                description: 'Failed to update blog',
                variant: 'destructive',
            });
        } finally {
            setIsLoading(false);
        }
    };

    return (
        <Dialog open={open} onOpenChange={onOpenChange}>
            <DialogContent className="sm:max-w-[600px]">
                <DialogHeader>
                    <DialogTitle>Edit Blog</DialogTitle>
                </DialogHeader>

                <form onSubmit={handleSubmit(onSubmit)} className="space-y-6">
                    <div className="space-y-2">
                        <Label htmlFor="title">Title</Label>
                        <Input
                            id="title"
                            {...register('title')}
                            disabled={isLoading}
                        />
                        {errors.title && (
                            <p className="text-sm text-destructive">{errors.title.message}</p>
                        )}
                    </div>

                    <div className="space-y-2">
                        <Label htmlFor="content">Content</Label>
                        <Textarea
                            id="content"
                            {...register('content')}
                            disabled={isLoading}
                            rows={5}
                        />
                        {errors.content && (
                            <p className="text-sm text-destructive">{errors.content.message}</p>
                        )}
                    </div>

                    <div className="space-y-2">
                        <Label htmlFor="previewImage">Preview Image URL</Label>
                        <Input
                            id="previewImage"
                            {...register('previewImage')}
                            disabled={isLoading}
                        />
                        {errors.previewImage && (
                            <p className="text-sm text-destructive">{errors.previewImage.message}</p>
                        )}
                    </div>

                    <div className="space-y-2">
                        <Label>Topics</Label>
                        <div className="grid grid-cols-2 md:grid-cols-3 gap-3">
                            {AVAILABLE_TOPICS.map((topic) => (
                                <div
                                    key={topic}
                                    className="flex items-center space-x-2 rounded-md border p-3"
                                >
                                    <Checkbox
                                        id={`topic-${topic}`}
                                        checked={selectedTopics.includes(topic)}
                                        onCheckedChange={(checked) => handleTopicChange(topic, checked as boolean)}
                                        disabled={isLoading}
                                    />
                                    <label
                                        htmlFor={`topic-${topic}`}
                                        className="text-sm font-medium leading-none peer-disabled:cursor-not-allowed peer-disabled:opacity-70"
                                    >
                                        {topic}
                                    </label>
                                </div>
                            ))}
                        </div>
                        {errors.topics && (
                            <p className="text-sm text-destructive">{errors.topics.message}</p>
                        )}
                    </div>

                    <div className="flex items-center space-x-2">
                        <Checkbox
                            id="anonymous"
                            {...register('anonymous')}
                            disabled={isLoading}
                        />
                        <Label htmlFor="anonymous">Post anonymously</Label>
                    </div>

                    <div className="flex justify-end space-x-2">
                        <Button
                            type="button"
                            variant="outline"
                            onClick={() => onOpenChange(false)}
                            disabled={isLoading}
                        >
                            Cancel
                        </Button>
                        <Button type="submit" disabled={isLoading}>
                            {isLoading ? 'Updating...' : 'Update Blog'}
                        </Button>
                    </div>
                </form>
            </DialogContent>
        </Dialog>
    );
}