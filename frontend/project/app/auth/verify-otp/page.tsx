'use client';

import { useState, useEffect } from 'react';
import { useRouter } from 'next/navigation';
import { z } from 'zod';
import { useForm } from 'react-hook-form';
import { zodResolver } from '@hookform/resolvers/zod';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { useToast } from '@/hooks/use-toast';
import { apiService } from '@/lib/apiService';
import { useAuth } from '@/context/AuthContext';
import { BookOpen, Clock } from 'lucide-react';

const formSchema = z.object({
  otp: z.string().min(6, 'OTP must be 6 digits').max(6),
});

type FormData = z.infer<typeof formSchema>;

export default function VerifyOtpPage() {
  const router = useRouter();
  const { toast } = useToast();
  const { login } = useAuth();
  const [isLoading, setIsLoading] = useState(false);
  const [username, setUsername] = useState<string>('');
  const [timeLeft, setTimeLeft] = useState(300); // 5 minutes in seconds

  const {
    register,
    handleSubmit,
    formState: { errors },
  } = useForm<FormData>({
    resolver: zodResolver(formSchema),
    defaultValues: {
      otp: '',
    },
  });

  useEffect(() => {
    // Get the username from session storage
    const storedUsername = sessionStorage.getItem('pendingUsername');
    if (!storedUsername) {
      toast({
        title: 'Error',
        description: 'No pending verification found. Please sign up again.',
        variant: 'destructive',
      });
      router.push('/auth/signup');
      return;
    }
    
    setUsername(storedUsername);
    
    // Set up countdown timer
    const timer = setInterval(() => {
      setTimeLeft((prevTime) => {
        if (prevTime <= 1) {
          clearInterval(timer);
          return 0;
        }
        return prevTime - 1;
      });
    }, 1000);
    
    return () => clearInterval(timer);
  }, [router, toast]);

  const formatTime = (seconds: number) => {
    const mins = Math.floor(seconds / 60);
    const secs = seconds % 60;
    return `${mins}:${secs < 10 ? '0' : ''}${secs}`;
  };

  const onSubmit = async (data: FormData) => {
    if (timeLeft === 0) {
      toast({
        title: 'OTP Expired',
        description: 'Your OTP has expired. Please sign up again.',
        variant: 'destructive',
      });
      router.push('/auth/signup');
      return;
    }
    
    setIsLoading(true);
    try {
      const response = await apiService.verifyOtp({
        username,
        otp: data.otp,
      });
      
      if (response) {
        // Clear the pending username from session storage
        sessionStorage.removeItem('pendingUsername');
        
        // Log the user in with the returned data
        login({
          username: response.username,
          token: response.token,
          topics: response.topics,
        });
        
        toast({
          title: 'Success',
          description: 'OTP verified successfully',
        });
        
        // Redirect to home page
        router.push('/home');
      }
    } catch (error) {
      console.error('OTP verification error:', error);
      toast({
        title: 'Error',
        description: 'Failed to verify OTP. Please try again.',
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
      
      <h1 className="text-2xl font-bold text-center mb-2">Verify your email</h1>
      <p className="text-center text-muted-foreground mb-6">
        We've sent a 6-digit code to your email. Enter it below to verify your account.
      </p>
      
      <div className="flex items-center justify-center mb-6 text-muted-foreground">
        <Clock className="h-4 w-4 mr-2" />
        <span>Valid for: {formatTime(timeLeft)}</span>
      </div>
      
      <form onSubmit={handleSubmit(onSubmit)} className="space-y-6">
        <div className="space-y-2">
          <Label htmlFor="otp">Enter OTP</Label>
          <Input
            id="otp"
            {...register('otp')}
            placeholder="123456"
            maxLength={6}
            disabled={isLoading || timeLeft === 0}
          />
          {errors.otp && (
            <p className="text-sm text-destructive">{errors.otp.message}</p>
          )}
        </div>
        
        <Button 
          type="submit" 
          className="w-full" 
          disabled={isLoading || timeLeft === 0}
        >
          {isLoading ? 'Verifying...' : 'Verify OTP'}
        </Button>
        
        {timeLeft === 0 && (
          <p className="text-center text-destructive">
            OTP has expired. Please sign up again.
          </p>
        )}
      </form>
    </div>
  );
}