import { Blog } from '@/lib/types';
import { apiService } from '@/lib/apiService';
import BlogPageClient from './BlogPageClient';

export async function generateStaticParams() {
  try {
    const blogs = await apiService.getAllBlogs();
    return blogs.map((blog: Blog) => ({
      id: blog.id.toString(),
    }));
  } catch (error) {
    console.error('Error generating static params:', error);
    return [];
  }
}

export default async function BlogPage({ params }: { params: { id: string } }) {
  const blog = await apiService.getBlogsByIds([Number(params.id)]);

  if (!blog || blog.length === 0) {
    return (
        <div className="container mx-auto py-8 px-4 text-center">
          <h2 className="text-2xl font-bold mb-4">Blog not found</h2>
          <p className="text-muted-foreground mb-6">
            The blog you&#39;re looking for doesn&#39;t exist or has been removed.
          </p>
        </div>
    );
  }

  return <BlogPageClient blog={blog[0]} />;
}