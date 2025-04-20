'use client';

import Link from 'next/link';
import { Blog } from '@/lib/types';
import { Card, CardContent } from '@/components/ui/card';
import { Skeleton } from '@/components/ui/skeleton';
import { Badge } from '@/components/ui/badge';
import { formatDistanceToNow } from 'date-fns';

interface SimilarBlogsProps {
  blogs: Blog[];
  loading: boolean;
}

export function SimilarBlogs({ blogs, loading }: SimilarBlogsProps) {
  if (loading) {
    return (
      <div className="grid grid-cols-1 md:grid-cols-3 gap-6">
        {[1, 2, 3].map((i) => (
          <div key={i} className="space-y-3">
            <Skeleton className="h-[150px] w-full rounded-lg" />
            <Skeleton className="h-5 w-3/4" />
            <Skeleton className="h-4 w-full" />
          </div>
        ))}
      </div>
    );
  }

  if (blogs.length === 0) {
    return (
      <div className="text-center py-6">
        <p className="text-muted-foreground">No similar articles found.</p>
      </div>
    );
  }

  return (
    <div className="grid grid-cols-1 md:grid-cols-3 gap-6">
      {blogs.map((blog) => (
        <Link href={`/blog/${blog.id}`} key={blog.id}>
          <Card className="h-full hover:shadow-md transition-shadow duration-300">
            <div className="aspect-video overflow-hidden">
              <img 
                src={blog.previewImage} 
                alt={blog.title}
                className="object-cover w-full h-full"
              />
            </div>
            
            <CardContent className="pt-4">
              <h3 className="font-semibold text-base mb-2 line-clamp-2">
                {blog.title}
              </h3>
              
              <p className="text-muted-foreground text-sm line-clamp-2 mb-2">
                {blog.content}
              </p>
              
              <div className="flex flex-wrap gap-1 mt-2">
                {blog.topics.slice(0, 2).map((topic) => (
                  <Badge key={topic} variant="secondary" className="text-xs font-normal">
                    {topic.toLowerCase()}
                  </Badge>
                ))}
              </div>
              
              <div className="mt-3 text-xs text-muted-foreground">
                {formatDistanceToNow(new Date(blog.createdAt), { addSuffix: true })}
              </div>
            </CardContent>
          </Card>
        </Link>
      ))}
    </div>
  );
}