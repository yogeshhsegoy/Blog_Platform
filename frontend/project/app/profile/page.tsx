'use client';

import { useEffect, useState } from 'react';
import { useAuth } from '@/context/AuthContext';
import { useRouter } from 'next/navigation';
import { Blog } from '@/lib/types';
import { Button } from '@/components/ui/button';
import { Plus } from 'lucide-react';
import { BlogList } from '@/components/BlogList';
import { CreateBlogDialog } from '@/components/CreateBlogDialog';
import { Skeleton } from '@/components/ui/skeleton';
import { useToast } from '@/hooks/use-toast';

export default function ProfilePage() {
    const { user, isLoading: authLoading } = useAuth();
    const router = useRouter();
    const { toast } = useToast();
    const [blogs, setBlogs] = useState<Blog[]>([]);
    const [loading, setLoading] = useState(true);
    const [isCreateDialogOpen, setIsCreateDialogOpen] = useState(false);

    useEffect(() => {
        if (!authLoading && !user) {
            router.push('/');
            return;
        }

        if (user) {
            fetchUserBlogs();
        }
    }, [user, authLoading, router]);

    const fetchUserBlogs = async () => {
        try {
            setLoading(true);
            const response = await fetch('http://localhost:8082/api/blogs/user', {
                headers: {
                    'Authorization': `Bearer ${user?.token}`,
                },
            });

            if (!response.ok) {
                throw new Error('Failed to fetch user blogs');
            }

            const data = await response.json();
            setBlogs(data);
        } catch (error) {
            console.error('Error fetching user blogs:', error);
            toast({
                title: 'Error',
                description: 'Failed to fetch your blogs',
                variant: 'destructive',
            });
        } finally {
            setLoading(false);
        }
    };

    const handleBlogCreated = () => {
        setIsCreateDialogOpen(false);
        fetchUserBlogs();
        toast({
            title: 'Success',
            description: 'Blog created successfully',
        });
    };

    if (authLoading || loading) {
        return (
            <div className="container mx-auto py-8 px-4">
                <div className="flex justify-between items-center mb-8">
                    <Skeleton className="h-8 w-48" />
                    <Skeleton className="h-10 w-32" />
                </div>
                <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
                    {[1, 2, 3].map((i) => (
                        <div key={i} className="space-y-3">
                            <Skeleton className="h-[200px] w-full rounded-lg" />
                            <Skeleton className="h-6 w-3/4" />
                            <Skeleton className="h-4 w-full" />
                            <Skeleton className="h-4 w-5/6" />
                        </div>
                    ))}
                </div>
            </div>
        );
    }

    if (!user) {
        return null;
    }

    return (
        <div className="container mx-auto py-8 px-4">
            <div className="flex justify-between items-center mb-8">
                <h1 className="text-2xl font-bold">My Blogs</h1>
                <Button onClick={() => setIsCreateDialogOpen(true)}>
                    <Plus className="h-4 w-4 mr-2" />
                    Create Blog
                </Button>
            </div>

            {blogs.length > 0 ? (
                <BlogList blogs={blogs} showActions onBlogDeleted={fetchUserBlogs} />
            ) : (
                <div className="text-center py-12">
                    <p className="text-muted-foreground mb-4">
                        You haven't created any blogs yet.
                    </p>
                    <Button onClick={() => setIsCreateDialogOpen(true)}>
                        Create Your First Blog
                    </Button>
                </div>
            )}

            <CreateBlogDialog
                open={isCreateDialogOpen}
                onOpenChange={setIsCreateDialogOpen}
                onBlogCreated={handleBlogCreated}
            />
        </div>
    );
}