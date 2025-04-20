import Link from 'next/link';
import { Button } from '@/components/ui/button';
import { ArrowRight, Newspaper, Users, Search, BookOpen } from 'lucide-react';

export default function LandingPage() {
  return (
    <div className="min-h-screen">
      {/* Hero Section */}
      <section className="py-20 px-4 md:py-32 bg-gradient-to-br from-background to-secondary/30">
        <div className="container mx-auto text-center">
          <h1 className="text-4xl md:text-6xl font-bold mb-6">
            Where good ideas find you
          </h1>
          <p className="text-xl md:text-2xl text-muted-foreground mb-10 max-w-3xl mx-auto">
            Read and share ideas from independent voices, world-class publications, and experts from around the globe.
          </p>
          <div className="flex flex-col sm:flex-row justify-center gap-4">
            <Link href="/auth/signin">
              <Button variant="outline" size="lg">Sign In</Button>
            </Link>
            <Link href="/auth/signup">
              <Button size="lg">Start reading</Button>
            </Link>
          </div>
        </div>
      </section>

      {/* Features */}
      <section className="py-16 px-4 bg-background">
        <div className="container mx-auto">
          <h2 className="text-3xl font-bold text-center mb-12">Why join Blogspace?</h2>
          
          <div className="grid md:grid-cols-3 gap-8">
            <div className="flex flex-col items-center text-center p-6 rounded-lg">
              <div className="bg-primary/10 p-4 rounded-full mb-4">
                <Newspaper className="h-8 w-8 text-primary" />
              </div>
              <h3 className="text-xl font-semibold mb-3">Personalized content</h3>
              <p className="text-muted-foreground">Discover stories curated to your interests and preferences.</p>
            </div>
            
            <div className="flex flex-col items-center text-center p-6 rounded-lg">
              <div className="bg-primary/10 p-4 rounded-full mb-4">
                <Search className="h-8 w-8 text-primary" />
              </div>
              <h3 className="text-xl font-semibold mb-3">Deep insights</h3>
              <p className="text-muted-foreground">Find the topics that matter to you with our powerful recommendation engine.</p>
            </div>
            
            <div className="flex flex-col items-center text-center p-6 rounded-lg">
              <div className="bg-primary/10 p-4 rounded-full mb-4">
                <Users className="h-8 w-8 text-primary" />
              </div>
              <h3 className="text-xl font-semibold mb-3">Join the community</h3>
              <p className="text-muted-foreground">Connect with readers and writers who share your interests.</p>
            </div>
          </div>
        </div>
      </section>

      {/* CTA */}
      <section className="py-16 px-4 bg-card">
        <div className="container mx-auto text-center">
          <div className="max-w-3xl mx-auto">
            <BookOpen className="h-12 w-12 mx-auto mb-6" />
            <h2 className="text-3xl font-bold mb-4">Join millions of readers today</h2>
            <p className="text-muted-foreground mb-8">Start exploring personalized content from writers around the world.</p>
            <Link href="/auth/signup">
              <Button size="lg" className="group">
                Get started
                <ArrowRight className="ml-2 h-4 w-4 transition-transform group-hover:translate-x-1" />
              </Button>
            </Link>
          </div>
        </div>
      </section>
    </div>
  );
}