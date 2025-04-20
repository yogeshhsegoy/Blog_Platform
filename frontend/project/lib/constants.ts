export const AVAILABLE_TOPICS = [
  'SPORTS',
  'FOOTBALL',
  'CRICKET',
  'BADMINTON',
  'POLITICS',
  'AIML',
  'WEATHER',
  'USA',
  'INDIA',
  'RUSSIA',
  'CODING',
  'GATE'
];

export const API_ROUTES = {
  AUTH: {
    SIGNUP: 'http://localhost:8081/api/auth/signup',
    VERIFY_OTP: 'http://localhost:8081/api/auth/verify-otp',
  },
  RECOMMENDATIONS: {
    TOPIC_BASED: 'http://localhost:8083/api/recommendations/topic-based',
    HYBRID: 'http://localhost:8083/api/recommendations/hybrid',
    SIMILAR_BLOGS: 'http://localhost:8083/api/recommendations/similar-blogs',
  },
  BLOGS: {
    LIST: 'http://localhost:8082/api/blogs/blogsByList',
    ALL: 'http://localhost:8082/api/blogs/all',
    BLOG: 'http://localhost:8082/api/blogs',
  },
};