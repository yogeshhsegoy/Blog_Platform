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
import { Checkbox } from '@/components/ui/checkbox';
import { useToast } from '@/hooks/use-toast';
import { apiService } from '@/lib/apiService';
import { TopicSelector } from '@/components/TopicSelector';
import { BookOpen } from 'lucide-react';

const formSchema = z.object({
  username: z.string().min(3, 'Username must be at least 3 characters'),
  email: z.string().email('Please enter a valid email'),
  password: z.string().min(8, 'Password must be at least 8 characters'),
  topics: z.array(z.string()).min(1, 'Please select at least one topic'),
});

type FormData = z.infer<typeof formSchema>;

export default function SignUpPage() {
  const router = useRouter();
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
      username: '',
      email: '',
      password: '',
      topics: [],
    },
  });

  const selectedTopics = watch('topics');

  const onSubmit = async (data: FormData) => {
    setIsLoading(true);
    try {
      const response = await apiService.signup(data);
      
      if (response) {
        toast({
          title: 'Success',
          description: 'OTP sent to your email',
        });
        
        // Store username temporarily for the verification page
        sessionStorage.setItem('pendingUsername', data.username);
        
        // Redirect to OTP verification
        router.push('/auth/verify-otp');
      }
    } catch (error) {
      console.error('Signup error:', error);
      toast({
        title: 'Error',
        description: 'Failed to sign up. Please try again.',
        variant: 'destructive',
      });
    } finally {
      setIsLoading(false);
    }
  };

  const handleTopicChange = (topic: string, checked: boolean) => {
    const currentTopics = watch('topics');
    
    if (checked) {
      setValue('topics', [...currentTopics, topic]);
    } else {
      setValue('topics', currentTopics.filter(t => t !== topic));
    }
  };

  return (
    <div className="container max-w-md mx-auto py-10 px-4">
      <div className="flex justify-center mb-6">
        <BookOpen className="h-10 w-10" />
      </div>
      
      <h1 className="text-2xl font-bold text-center mb-6">Create your account</h1>
      
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
          <Label htmlFor="email">Email</Label>
          <Input
            id="email"
            type="email"
            {...register('email')}
            placeholder="john@example.com"
            disabled={isLoading}
          />
          {errors.email && (
            <p className="text-sm text-destructive">{errors.email.message}</p>
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
        
        <div className="space-y-2">
          <Label>Select your interests</Label>
          <TopicSelector 
            selectedTopics={selectedTopics} 
            onTopicChange={handleTopicChange} 
          />
          {errors.topics && (
            <p className="text-sm text-destructive">{errors.topics.message}</p>
          )}
        </div>
        
        <Button type="submit" className="w-full" disabled={isLoading}>
          {isLoading ? 'Creating account...' : 'Sign Up'}
        </Button>
      </form>
      
      <div className="mt-6 text-center text-sm">
        <p className="text-muted-foreground">
          Already have an account?{' '}
          <Link href="/auth/signin" className="font-medium text-primary hover:underline">
            Sign in
          </Link>
        </p>
      </div>
    </div>
  );
}