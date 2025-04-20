import requests

# URL and headers
URL = "http://localhost:8082/api/blogs"
HEADERS = {
    "Content-Type": "application/json",
    "Authorization": "Bearer eyJhbGciOiJIUzI1NiJ9.eyJ0b3BpY3MiOlsic3BvcnRzIiwiY3JpY2tldCJdLCJzdWIiOiJ5b2dlc2giLCJpYXQiOjE3NDUxNzYxMTksImV4cCI6MTc0NTI2MjUxOX0.LlcXA9jT90wTouJzNtpzCjcRLhaxY6GhAzkfXsJYcCw"  # Replace with your actual token
}

# List of posts
posts = [
    {
        "title": "AI’s Rapid Takeover of Software Development",
        "content": "AI tools like Grok and Copilot are transforming coding. I tried using them for a Python project, and they generated clean, functional code in seconds. It’s both exciting and scary—am I obsolete? These models understand context better than ever, but they lack human creativity for complex systems. Still, they’re saving hours of debugging. On X, developers are debating if AI will replace us. I think it’s a tool, not a threat, if we adapt. The real issue? Companies might prioritize cheap AI over skilled coders. Upskilling in AI itself is the way forward. What’s your take on this tech revolution?",
        "previewImage": "https://images.unsplash.com/photo-1605379399642-870262d3d051",
        "topics": ["AIML", "CODING"]
    },
    {
        "title": "Effective Strategies for GATE 2025 Preparation",
        "content": "Prepping for GATE 2025 is intense, but I’ve found a rhythm. Focus on core subjects like algorithms, DBMS, and OS—they carry the most weight. Daily practice with past papers is crucial; I’m solving 10 questions a day. Mock tests reveal weak spots—my networks score needs work. Online forums on X are goldmines for tips, with #GATE2025 trending. Time management’s key: I study 6 hours daily, balancing theory and problems. Don’t skip revisions; they cement concepts. Coaching helps, but self-study builds discipline. The syllabus feels endless, but consistency wins. Anyone else grinding for GATE? Share your hacks!",
        "previewImage": "https://images.unsplash.com/photo-1581093588401-79a4d55cde6f",
        "topics": ["CODING", "GATE"]
    },
    {
        "title": "Neural Networks’ Breakthrough in Image Recognition",
        "content": "I trained a convolutional neural network for image classification, and the results blew me away—98% accuracy on a dataset of 10,000 images. Using PyTorch and a pre-trained ResNet model, I fine-tuned it for custom classes. The process took 8 hours on my GPU, but the precision was worth it. X users are sharing similar projects, with #AIRevolution trending. The catch? Data quality matters more than model complexity. Bad inputs ruin everything. I’m now experimenting with GANs for fun. AI’s potential feels limitless, but scaling these models for real-world use is tricky. What’s your latest AI project?",
        "previewImage": "https://images.unsplash.com/photo-1620712943543-bcc4688e7485",
        "topics": ["AIML"]
    },
    {
        "title": "Big Tech’s Aggressive Push into AI Innovation",
        "content": "The AI race among tech giants is intense. Google’s pumping billions into LLMs, while Microsoft’s betting on OpenAI’s tech. On X, analysts debate who’s leading—#AIWars is trending. But innovation feels incremental; most firms just scale existing models. Smaller startups, though, are experimenting boldly with niche applications. The problem? Monopolies could stifle creativity. Governments are watching closely, with the USA hinting at regulations. India’s tech scene is catching up, but funding lags. Consumers benefit from smarter tools, yet privacy concerns loom. Can Big Tech balance profit and ethics? The AI landscape’s evolving fast, and we’re all along for the ride.",
        "previewImage": "https://images.unsplash.com/photo-1516321318423-f06f85e504b3",
        "topics": ["AIML", "POLITICS"]
    },
    {
        "title": "Python vs. Rust: Best for Machine Learning?",
        "content": "Choosing between Python and Rust for ML projects is tough. Python’s simplicity and libraries like TensorFlow make it a go-to—I built a classifier in hours. But Rust’s speed and memory safety are tempting for production-grade models. I tested a Rust-based inference engine; it was 30% faster than Python. X developers are split, with #PythonVsRust trending. Python’s ecosystem is unmatched, but Rust’s performance shines for large-scale deployments. The learning curve for Rust is steep, though. For now, I’m sticking with Python for prototyping. What’s your pick for ML—ease or efficiency? The debate’s heating up!",
        "previewImage": "https://images.unsplash.com/photo-1564865878688-9b9f7f856e5c",
        "topics": ["AIML", "CODING"]
    },
    {
        "title": "Analyzing GATE CS Mock Test Results",
        "content": "Took a GATE CS mock test and scored 68/100—not bad, but room for improvement. Algorithms and DBMS were strong, but networks and compilers tripped me up. I missed 5 marks due to silly mistakes in time complexity questions. X forums are buzzing with tips—#GATEPrep is trending. I’m revising weak areas daily and timing my practice to mimic exam pressure. The key is understanding concepts, not memorizing. Online resources like GeeksforGeeks are lifesavers. My goal’s 80+ in the next mock. Anyone else struggling with specific topics? Let’s share strategies to ace GATE 2025!",
        "previewImage": "https://images.unsplash.com/photo-1454165804606-c3d57bc86b40",
        "topics": ["CODING", "GATE"]
    },
    {
        "title": "Why AI Ethics Must Be Prioritized Now",
        "content": "AI’s power comes with responsibility. I built a facial recognition model, but its bias against certain demographics was alarming. Datasets often reflect real-world inequalities, and fixing them isn’t easy. On X, #AIEthics is trending as experts demand stricter guidelines. Companies prioritize profits over fairness, which risks harm. Governments are slow to regulate, leaving users vulnerable. India’s drafting AI policies, but enforcement’s unclear. Developers must embed ethics in design—diverse datasets, transparent algorithms. If we ignore this, AI could deepen societal divides. Can we build tech that uplifts everyone? The clock’s ticking for responsible innovation.",
        "previewImage": "https://images.unsplash.com/photo-1504384308090-c894fdcc538d",
        "topics": ["AIML", "POLITICS"]
    },
    {
        "title": "Surviving All-Nighters While Coding",
        "content": "Coding at 3 AM is brutal. I was debugging a Flask app, chasing a sneaky null pointer error for hours. Coffee kept me going, but my brain was mush. X coders share similar war stories—#CodeLife is trending. The worst part? Bugs hide until you’re exhausted. I finally fixed it by rewriting a function. Late-night coding’s unproductive; I’m switching to morning sessions. Pomodoro timers help too—25 minutes of focus, then breaks. Burnout’s real, so balance is key. Any tips for staying sharp during crunch time? Let’s make coding marathons less painful!",
        "previewImage": "https://images.unsplash.com/photo-1516321318423-f06f85e504b3",
        "topics": ["CODING"]
    },
    {
        "title": "Transformers Revolutionize Natural Language Processing",
        "content": "Transformers like BERT and GPT-4 are NLP game-changers. I fine-tuned a BERT model for sentiment analysis, and it nailed 95% accuracy on movie reviews. The attention mechanism is genius, capturing context like never before. X is buzzing with NLP projects—#TransformersRock is trending. But training’s a beast; my GPU was sweating for 12 hours. Data quality’s critical—garbage in, garbage out. Scaling these models for real-time apps is the next frontier. I’m experimenting with smaller models for efficiency. Can transformers keep evolving, or is the hype peaking? The future of language AI looks wild!",
        "previewImage": "https://images.unsplash.com/photo-1620712943543-bcc4688e7485",
        "topics": ["AIML"]
    },
    {
        "title": "USA’s Lag in AI Policy Development",
        "content": "The USA’s trailing in AI regulation while China pours billions into its AI ecosystem. I read a report on X—#AIPolicy is trending—saying the USA’s fragmented laws stifle innovation. Startups struggle with unclear guidelines, while Big Tech lobbies for leniency. India’s drafting unified AI rules, which could leapfrog both. National security’s a concern; AI’s dual-use potential is scary. The government needs a task force to balance growth and safety. If the USA doesn’t act, it risks losing the AI race. Can they catch up, or is China’s lead too big? The stakes are massive.",
        "previewImage": "https://images.unsplash.com/photo-1610901491660-0bd5882c8387",
        "topics": ["AIML", "USA"]
    },
    {
        "title": "Mastering Algorithms for GATE Success",
        "content": "GATE’s algorithm section is a beast, but I’m cracking it. Dynamic programming and graph theory questions are brutal—think knapsack or Dijkstra’s under time pressure. I practice 15 problems daily, focusing on edge cases. X study groups are gold—#GATEAlgorithms is trending. Visualizing recursion trees helps, and GeeksforGeeks explains beautifully. My weak spot? Greedy algorithms; I keep misjudging optimal choices. Mock tests mimic exam stress, so I’m timing myself. Consistency’s key—don’t cram. I’m aiming for 20/25 marks in this section. Anyone got tips for greedy or backtracking? Let’s ace GATE 2025 together!",
        "previewImage": "https://images.unsplash.com/photo-1581093588401-79a4d55cde6f",
        "topics": ["CODING", "GATE"]
    },
    {
        "title": "AI’s Growing Energy Consumption Problem",
        "content": "Training AI models is an energy hog. My last GPT-style model took 15 hours on a high-end GPU, burning through power like crazy. A study on X—#GreenAI is trending—says AI’s carbon footprint rivals aviation. Data centers are straining grids, and renewables can’t keep up. Companies like Google claim ‘net-zero’ goals, but it’s mostly PR. Smaller models or optimized algorithms could help, but scaling’s the issue. I’m experimenting with distilled models for efficiency. If we don’t prioritize sustainable AI, the planet pays the price. Can tech go green without slowing progress? It’s a tough balance.",
        "previewImage": "https://images.unsplash.com/photo-1504384308090-c894fdcc538d",
        "topics": ["AIML"]
    },
    {
        "title": "Open-Source AI Drives Community Innovation",
        "content": "Hugging Face’s open-source libraries are a godsend for AI devs. I used their Transformers to build a chatbot in a weekend—plug-and-play models saved hours. X is hyped about it—#OpenSourceAI is trending. The community’s collaborative spirit fuels innovation; anyone can contribute. But funding’s a challenge; donations don’t scale. Big Tech benefits from open-source without giving back enough. India’s open-source scene is growing, with startups joining in. These tools democratize AI, but sustainability’s key. Can the community keep this momentum? Let’s keep sharing code and ideas to push AI forward for all!",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["AIML", "CODING"]
    },
    {
        "title": "Avoiding Burnout During GATE Prep",
        "content": "GATE prep is a marathon, and I’m feeling the strain. Studying 8 hours daily—algorithms, OS, networks—is draining. I hit a wall last week, forgetting basic BFS logic. X forums share similar struggles—#GATEBurnout is trending. Breaks and exercise help; I jog 20 minutes daily. Pomodoro’s a lifesaver: 25-minute study sprints keep me focused. I’m also limiting social media to avoid distractions. Sleep’s non-negotiable—7 hours minimum. My mock scores are climbing, but balance is everything. Anyone else battling burnout? Share your tips to stay sane while grinding for GATE 2025!",
        "previewImage": "https://images.unsplash.com/photo-1454165804606-c3d57bc86b40",
        "topics": ["CODING", "GATE"]
    },
    {
        "title": "AI’s Role in India’s Tech Future",
        "content": "India’s tech scene is exploding, and AI’s at the heart of it. Startups in Bangalore are building AI-driven apps for healthcare and agriculture—think crop yield predictors. X is buzzing—#AIIndia is trending. But funding’s tight; VCs favor quick wins over R&D. Talent’s abundant, with IIT grads leading, but brain drain’s real. The government’s AI mission promises billions, yet bureaucracy slows progress. If India nails policy and investment, it could rival Silicon Valley. The potential’s huge, but execution’s everything. Can India become an AI superpower by 2030? The race is on, and I’m rooting for us.",
        "previewImage": "https://images.unsplash.com/photo-1569172122309-bc25d0109709",
        "topics": ["AIML", "INDIA"]
    },
    {
        "title": "Regular Expressions: A Coder’s Nightmare",
        "content": "Regex is my coding kryptonite. I spent hours crafting a pattern to parse logs, only for it to fail on edge cases. Why is regex so cryptic? X devs feel my pain—#RegexHell is trending. Tutorials on Regex101 help, but real-world data’s messy. I finally got it working with lookaheads, but it’s fragile. Python’s re module is decent, but I’m tempted to avoid regex entirely. Learning it feels like decoding hieroglyphs. Anyone got a foolproof regex strategy? I need to master this for GATE and work. Let’s tame this beast together!",
        "previewImage": "https://images.unsplash.com/photo-1564865878688-9b9f7f856e5c",
        "topics": ["CODING"]
    },
    {
        "title": "AI’s Impact on Future Job Markets",
        "content": "AI’s reshaping jobs, and it’s a double-edged sword. Automation’s cutting manual tasks—my friend’s data entry job got replaced by a bot. But it’s creating roles too; I’m learning AI engineering. X debates are heated—#AIJobs is trending. Routine jobs are at risk, but creative and strategic ones thrive. Upskilling’s critical—Python and ML are hot skills. India’s IT sector is adapting, but rural workers need training. If we don’t prepare, inequality grows. Companies must invest in reskilling, and governments should incentivize it. Can we navigate this shift without leaving millions behind? The future’s uncertain.",
        "previewImage": "https://images.unsplash.com/photo-1516321318423-f06f85e504b3",
        "topics": ["AIML", "POLITICS"]
    },
    {
        "title": "GATE 2025 Syllabus Updates and Challenges",
        "content": "GATE 2025’s syllabus has a heavier ML focus, which caught me off-guard. New topics like neural networks and SVMs are tough but exciting. I’m diving into Andrew Ng’s course to catch up. X students are stressed—#GATE2025Syllabus is trending. Algorithms and DBMS remain core, so I’m not starting from scratch. The challenge? Balancing depth with breadth; there’s too much to cover. Daily mocks help, but time’s tight. I’m prioritizing high-weightage topics and skipping low-scoring ones. Anyone else adapting to the ML push? Share your study plans—let’s conquer GATE together!",
        "previewImage": "https://images.unsplash.com/photo-1581093588401-79a4d55cde6f",
        "topics": ["CODING", "GATE"]
    },
    {
        "title": "AI’s Creative Potential in Art Generation",
        "content": "I played with DALL-E to generate art, and it’s mind-blowing. Input ‘futuristic city,’ and it created a neon-lit masterpiece in seconds. X is full of AI art—#CreativeAI is trending. The tech’s not perfect; some outputs are blurry or weird. But the potential’s huge for designers and creators. Ethical questions linger—who owns AI art? I’m experimenting with Stable Diffusion next for more control. Artists worry about job loss, but AI could amplify creativity, not replace it. Can AI and humans co-create the future of art? This tech’s opening wild new doors.",
        "previewImage": "https://images.unsplash.com/photo-1620712943543-bcc4688e7485",
        "topics": ["AIML"]
    },
    {
        "title": "Tech Hiring Boom in India’s IT Sector",
        "content": "India’s tech hiring is on fire. FAANG companies are snapping up IIT and NIT grads for AI and cloud roles. I’m polishing my resume for a Google interview—fingers crossed! X is hyped—#TechJobsIndia is trending. Salaries are soaring, with freshers getting 20 LPA offers. But the pressure’s intense; coding rounds are brutal. Startups are hiring too, offering equity but less stability. The downside? Rural talent’s left out, and upskilling programs are scarce. If India bridges this gap, the tech boom could lift millions. Can I land my dream job? The competition’s fierce, but I’m ready.",
        "previewImage": "https://images.unsplash.com/photo-1569172122309-bc25d0109709",
        "topics": ["CODING", "INDIA"]
    }
]

# Send POST requests
for i, post in enumerate(posts, start=1):
    response = requests.post(URL, json=post, headers=HEADERS)
    if response.status_code == 201:
        print(f"[{i}] ✅ Post '{post['title']}' created successfully.")
    else:
        print(f"[{i}] ❌ Failed to create post '{post['title']}': {response.status_code} - {response.text}")
