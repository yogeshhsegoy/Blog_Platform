export interface Blog {
  id: number;
  title: string;
  content: string;
  previewImage: string;
  createdAt: string;
  updatedAt: string;
  likes: number;
  dislikes: number;
  comments: any[];
  anonymous: boolean;
  userId: string;
  topics: string[];
  dislikedByCurrentUser: boolean;
  likedByCurrentUser: boolean;
}

export interface BlogRecommendation {
  blogIds: number[];
  recommendationType: string;
}