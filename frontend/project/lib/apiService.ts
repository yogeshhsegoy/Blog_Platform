import { API_ROUTES } from './constants';
import {useAuth} from "@/context/AuthContext";
import {Blog} from "@/lib/types";
import {BlogList} from "@/components/BlogList";

interface SignupData {
  username: string;
  email: string;
  password: string;
  topics: string[];
}

interface VerifyOtpData {
  username: string;
  otp: string;
}

interface TopicBasedRecommendationsParams {
  topics: string[];
  limit: number;
}

interface HybridRecommendationsParams {
  topics: string[];
  query: string;
  limit: number;
}

interface SimilarBlogsParams {
  topics: string[];
  title: string;
  content: string;
  limit: number;
}

class ApiService {
  async signup(data: SignupData): Promise<string> {
    const response = await fetch(API_ROUTES.AUTH.SIGNUP, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(data),
    });

    if (!response.ok) {
      throw new Error('Signup failed');
    }

    return response.text();
  }

  async verifyOtp(data: VerifyOtpData) {
    const response = await fetch(API_ROUTES.AUTH.VERIFY_OTP, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(data),
    });

    if (!response.ok) {
      throw new Error('OTP verification failed');
    }

    return response.json();
  }

  async getTopicBasedRecommendations(
      { topics, limit }: TopicBasedRecommendationsParams,
      token?: string
  ) {
    const topicsParam = topics.join(',');
    const headers: HeadersInit = {};
    if (token) {
      headers['Authorization'] = `Bearer ${token}`;
    }

    const response = await fetch(
        `${API_ROUTES.RECOMMENDATIONS.TOPIC_BASED}?topics=${topicsParam}&limit=${limit}`,
        {
          headers,
        }
    );

    if (!response.ok) {
      throw new Error('Failed to fetch recommendations');
    }

    return response.json();
  }

  async getHybridRecommendations({ topics, query, limit }: HybridRecommendationsParams,token?: string) {
    const topicsParam = topics.join(',');
    const encodedQuery = encodeURIComponent(query);
    const response = await fetch(
      `${API_ROUTES.RECOMMENDATIONS.HYBRID}?topics=${topicsParam}&limit=${limit}&query=${encodedQuery}`,{
        method: 'GET',
          headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer ${token}`
          }
        }
    );

    if (!response.ok) {
      throw new Error('Failed to fetch search results');
    }

    return response.json();
  }

  async getSimilarBlogs({ topics, title, content, limit }: SimilarBlogsParams,token?: string) {
    const topicsParam = topics.join(',');
    const encodedTitle = encodeURIComponent(title);
    const encodedContent = encodeURIComponent(content);
    const response = await fetch(
      `${API_ROUTES.RECOMMENDATIONS.SIMILAR_BLOGS}?topics=${topicsParam}&title=${encodedTitle}&content=${encodedContent}&limit=${limit}`,{
        method: 'GET',
          headers : {
           'Content-Type': 'application/json',
            'Authorization': `Bearer ${token}`,
          }
        }
    );

    if (!response.ok) {
      throw new Error('Failed to fetch similar blogs');
    }

    return response.json();
  }

  async getBlogsByIds(blogIds: number[]) {
    const response = await fetch(API_ROUTES.BLOGS.LIST, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(blogIds),
    });

    if (!response.ok) {
      throw new Error('Failed to fetch blogs');
    }

    return response.json();
  }

  async getAllBlogs(){
    const response = await fetch(`${API_ROUTES.BLOGS.ALL}`)
    if(!response.ok){
        throw new Error('Failed to fetch blogs');
    }
    return response.json();
  }

}

export const apiService = new ApiService();