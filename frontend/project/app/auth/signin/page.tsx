'use client';

import { useState } from 'react';
import { useRouter } from 'next/navigation';
import { z } from 'zod';
import { useForm } from 'react-hook-form';
import { zodResolver } from '@hookform/resolvers/zod';
import Link from 'next/link';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { useToast } from '@/hooks/use-toast';
import { apiService } from '@/lib/apiService';
import { useAuth } from '@/context/AuthContext';
import { BookOpen } from 'lucide-react';

const formSchema = z.object({
  username: z.string().min(1, 'Username is required'),
  password: z.string().min(1, 'Password is required'),
});

type FormData = z.infer<typeof formSchema>;
interface SignInResponse {
  username: string;
  token: string;
  topics: string[]; // Adjust the type of `topics` based on your API (e.g., array of strings, objects, etc.)
}
export default function SignInPage() {
  const router = useRouter();
  const { toast } = useToast();
  const { login } = useAuth();
  const [isLoading, setIsLoading] = useState(false);

  const {
    register,
    handleSubmit,
    formState: { errors },
  } = useForm<FormData>({
    resolver: zodResolver(formSchema),
    defaultValues: {
      username: '',
      password: '',
    },
  });
  const onSubmit = async (data: FormData) => {
    setIsLoading(true);
    try {
      const response = await fetch('http://localhost:8081/api/auth/signin', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          username: data.username,
          password: data.password,
        }),
      });

      if (!response.ok) {
        throw new Error('Failed to sign in');
      }

      const responseData: SignInResponse = await response.json();

      // Log the user in with the returned data
      login({
        username: responseData.username,
        token: responseData.token,
        topics: responseData.topics,
      });

      toast({
        title: 'Success',
        description: 'You have successfully signed in',
      });

      // Redirect to home page
      router.push('/home');
    } catch (error) {
      console.error('Signin error:', error);
      toast({
        title: 'Error',
        description: 'Failed to sign in. Please check your credentials and try again.',
        variant: 'destructive',
      });
    } finally {
      setIsLoading(false);
    }
  };

  return (
      <div className="container max-w-md mx-auto py-10 px-4">
        <div className="flex justify-center mb-6">
          <BookOpen className="h-10 w-10" />
        </div>

        <h1 className="text-2xl font-bold text-center mb-6">Sign in to your account</h1>

        <form onSubmit={handleSubmit(onSubmit)} className="space-y-6">
          <div className="space-y-2">
            <Label htmlFor="username">Username</Label>
            <Input
                id="username"
                {...register('username')}
                placeholder="johndoe"
                disabled={isLoading}
            />
            {errors.username && (
                <p className="text-sm text-destructive">{errors.username.message}</p>
            )}
          </div>

          <div className="space-y-2">
            <Label htmlFor="password">Password</Label>
            <Input
                id="password"
                type="password"
                {...register('password')}
                placeholder="••••••••"
                disabled={isLoading}
            />
            {errors.password && (
                <p className="text-sm text-destructive">{errors.password.message}</p>
            )}
          </div>

          <Button type="submit" className="w-full" disabled={isLoading}>
            {isLoading ? 'Signing in...' : 'Sign In'}
          </Button>
        </form>

        <div className="mt-6 text-center text-sm">
          <p className="text-muted-foreground">
            Don&#39;t have an account?{' '}
            <Link href="/auth/signup" className="font-medium text-primary hover:underline">
              Sign up
            </Link>
          </p>
        </div>
      </div>
  );
}