import { NextResponse } from 'next/server';
import type { NextRequest } from 'next/server';

export function middleware(request: NextRequest) {
  const { pathname } = request.nextUrl;
  
  // Check for auth token in protected routes
  if (pathname.startsWith('/home') || pathname.startsWith('/blog/')) {
    const authToken = request.cookies.get('user')?.value;
    
    if (!authToken) {
      return NextResponse.redirect(new URL('/', request.url));
    }
  }
  
  return NextResponse.next();
}

export const config = {
  matcher: ['/home/:path*', '/blog/:path*'],
};