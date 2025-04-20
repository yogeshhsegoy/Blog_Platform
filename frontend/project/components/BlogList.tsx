'use client';

import Link from 'next/link';
import { Blog } from '@/lib/types';
import { Card, CardContent, CardFooter } from '@/components/ui/card';
import { Avatar, AvatarFallback } from '@/components/ui/avatar';
import { Badge } from '@/components/ui/badge';
import { formatDistanceToNow } from 'date-fns';
import { Button } from '@/components/ui/button';
import { Pencil, Trash2 } from 'lucide-react';
import {
  AlertDialog,
  AlertDialogAction,
  AlertDialogCancel,
  AlertDialogContent,
  AlertDialogDescription,
  AlertDialogFooter,
  AlertDialogHeader,
  AlertDialogTitle,
} from "@/components/ui/alert-dialog";
import { useState } from 'react';
import { useAuth } from '@/context/AuthContext';
import { useToast } from '@/hooks/use-toast';
import { EditBlogDialog } from './EditBlogDialog';

interface BlogListProps {
  blogs: Blog[];
  showActions?: boolean;
  onBlogDeleted?: () => void;
}

export function BlogList({ blogs, showActions = false, onBlogDeleted }: BlogListProps) {
  const { user } = useAuth();
  const { toast } = useToast();
  const [blogToDelete, setBlogToDelete] = useState<number | null>(null);
  const [blogToEdit, setBlogToEdit] = useState<Blog | null>(null);

  const handleDelete = async () => {
    if (!blogToDelete || !user) return;

    try {
      const response = await fetch(`http://localhost:8082/api/blogs/${blogToDelete}`, {
        method: 'DELETE',
        headers: {
          'Authorization': `Bearer ${user.token}`,
        },
      });

      if (!response.ok) {
        throw new Error('Failed to delete blog');
      }

      toast({
        title: 'Success',
        description: 'Blog deleted successfully',
      });

      onBlogDeleted?.();
    } catch (error) {
      console.error('Error deleting blog:', error);
      toast({
        title: 'Error',
        description: 'Failed to delete blog',
        variant: 'destructive',
      });
    } finally {
      setBlogToDelete(null);
    }
  };

  const handleBlogUpdated = () => {
    setBlogToEdit(null);
    onBlogDeleted?.();
    toast({
      title: 'Success',
      description: 'Blog updated successfully',
    });
  };

  return (
      <>
        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
          {blogs.map((blog) => (
              <div key={blog.id} className="h-full">
                <Card className="h-full flex flex-col hover:shadow-md transition-shadow duration-300">
                  <Link href={`/blog/${blog.id}`}>
                    <div className="relative h-44 overflow-hidden">
                      <img
                          src={blog.previewImage}
                          alt={blog.title}
                          className="object-cover w-full h-full"
                      />
                    </div>
                  </Link>

                  <CardContent className="flex-grow pt-6">
                    <Link href={`/blog/${blog.id}`}>
                      <h3 className="font-semibold text-lg mb-2 line-clamp-2">
                        {blog.title}
                      </h3>
                      <p className="text-muted-foreground text-sm line-clamp-3 mb-4">
                        {blog.content}
                      </p>
                    </Link>

                    <div className="flex flex-wrap gap-2 mt-2">
                      {blog.topics.slice(0, 2).map((topic) => (
                          <Badge key={topic} variant="secondary" className="text-xs font-normal">
                            {topic.toLowerCase()}
                          </Badge>
                      ))}
                      {blog.topics.length > 2 && (
                          <Badge variant="outline" className="text-xs font-normal">
                            +{blog.topics.length - 2}
                          </Badge>
                      )}
                    </div>
                  </CardContent>

                  <CardFooter className="border-t pt-4">
                    <div className="flex items-center justify-between w-full">
                      <div className="flex items-center space-x-2">
                        <Avatar className="h-6 w-6">
                          <AvatarFallback>
                            {blog.userId.substring(0, 2).toUpperCase()}
                          </AvatarFallback>
                        </Avatar>
                        <span className="text-sm text-muted-foreground">
                      {blog.anonymous ? 'Anonymous' : blog.userId}
                    </span>
                      </div>

                      {showActions && (
                          <div className="flex items-center space-x-2">
                            <Button
                                variant="ghost"
                                size="icon"
                                onClick={() => setBlogToEdit(blog)}
                            >
                              <Pencil className="h-4 w-4" />
                            </Button>
                            <Button
                                variant="ghost"
                                size="icon"
                                onClick={() => setBlogToDelete(blog.id)}
                            >
                              <Trash2 className="h-4 w-4" />
                            </Button>
                          </div>
                      )}

                      <span className="text-xs text-muted-foreground">
                    {formatDistanceToNow(new Date(blog.createdAt), { addSuffix: true })}
                  </span>
                    </div>
                  </CardFooter>
                </Card>
              </div>
          ))}
        </div>

        <AlertDialog open={!!blogToDelete} onOpenChange={() => setBlogToDelete(null)}>
          <AlertDialogContent>
            <AlertDialogHeader>
              <AlertDialogTitle>Are you sure?</AlertDialogTitle>
              <AlertDialogDescription>
                This action cannot be undone. This will permanently delete your blog.
              </AlertDialogDescription>
            </AlertDialogHeader>
            <AlertDialogFooter>
              <AlertDialogCancel>Cancel</AlertDialogCancel>
              <AlertDialogAction onClick={handleDelete}>Delete</AlertDialogAction>
            </AlertDialogFooter>
          </AlertDialogContent>
        </AlertDialog>

        {blogToEdit && (
            <EditBlogDialog
                blog={blogToEdit}
                open={!!blogToEdit}
                onOpenChange={() => setBlogToEdit(null)}
                onBlogUpdated={handleBlogUpdated}
            />
        )}
      </>
  );
}