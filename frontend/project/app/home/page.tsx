'use client';

import { useEffect, useState } from 'react';
import { useAuth } from '@/context/AuthContext';
import { useRouter } from 'next/navigation';
import { apiService } from '@/lib/apiService';
import { BlogList } from '@/components/BlogList';
import { SearchHeader } from '@/components/SearchHeader';
import { Blog } from '@/lib/types';
import { Skeleton } from '@/components/ui/skeleton';




export default function HomePage() {
  const { user, isLoading: authLoading } = useAuth();
  const router = useRouter();
  const [blogs, setBlogs] = useState<Blog[]>([]);
  const [loading, setLoading] = useState(true);
  const [searchQuery, setSearchQuery] = useState('');

  useEffect(() => {
    // Redirect if not authenticated
    if (!authLoading && !user) {
      router.push('/');
      return;
    }

    if (user) {
      fetchRecommendedBlogs();
    }
  }, [authLoading, user, router]);

  const fetchRecommendedBlogs = async () => {
    try {
      setLoading(true);
      // Get topic-based recommendations
      const recommendations = await apiService.getTopicBasedRecommendations({
        topics: user?.topics.map(t => t.toUpperCase()) || [],
        limit: 10,
      },user.token);

      // Fetch the actual blogs using the recommended blog IDs
      if (recommendations.blogIds.length > 0) {
        const fetchedBlogs = await apiService.getBlogsByIds(recommendations.blogIds);
        setBlogs(fetchedBlogs);
      } else {
        setBlogs([]);
      }
    } catch (error) {
      console.error('Error fetching blogs:', error);
    } finally {
      setLoading(false);
    }
  };

  const handleSearch = async (query: string) => {
    try {
      setLoading(true);
      setSearchQuery(query);

      if (query.trim() === '') {
        // If search is cleared, return to recommended blogs
        fetchRecommendedBlogs();
        return;
      }

      // Get hybrid recommendations based on search query
      const recommendations = await apiService.getHybridRecommendations({
        topics: user?.topics.map(t => t.toUpperCase()) || [],
        query,
        limit: 10,
      },user.token);

      // Fetch the actual blogs using the recommended blog IDs
      if (recommendations.blogIds.length > 0) {
        const fetchedBlogs = await apiService.getBlogsByIds(recommendations.blogIds);
        setBlogs(fetchedBlogs);
      } else {
        setBlogs([]);
      }
    } catch (error) {
      console.error('Error searching blogs:', error);
    } finally {
      setLoading(false);
    }
  };

  if (authLoading) {
    return (
      <div className="container mx-auto py-8 px-4">
        <div className="w-full h-12 mb-6 animate-pulse bg-muted rounded"></div>
        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
          {[1, 2, 3, 4, 5, 6].map((i) => (
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
    return null; // Will redirect in useEffect
  }

  return (
    <div className="container mx-auto py-8 px-4">
      <SearchHeader onSearch={handleSearch} initialQuery={searchQuery} />
      
      <div className="mt-8">
        <h2 className="text-2xl font-bold mb-6">
          {searchQuery ? 'Search Results' : 'Recommended for you'}
        </h2>
        
        {loading ? (
          <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
            {[1, 2, 3, 4, 5, 6].map((i) => (
              <div key={i} className="space-y-3">
                <Skeleton className="h-[200px] w-full rounded-lg" />
                <Skeleton className="h-6 w-3/4" />
                <Skeleton className="h-4 w-full" />
                <Skeleton className="h-4 w-5/6" />
              </div>
            ))}
          </div>
        ) : blogs.length > 0 ? (
          <BlogList blogs={blogs} />
        ) : (
          <div className="text-center py-12">
            <p className="text-muted-foreground">
              {searchQuery 
                ? 'No blogs found matching your search.' 
                : 'No recommended blogs found. Try exploring different topics.'}
            </p>
          </div>
        )}
      </div>
    </div>
  );
}