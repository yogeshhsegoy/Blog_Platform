import requests

# URL and headers
URL = "http://localhost:8082/api/blogs"
HEADERS = {
    "Content-Type": "application/json",
    "Authorization": "Bearer eyJhbGciOiJIUzI1NiJ9.eyJ0b3BpY3MiOlsiQ1JJQ0tFVCIsIlNQT1JUUyIsIklORElBIl0sInN1YiI6InlvZ2VzaCIsImlhdCI6MTc0NTE4MzgxMywiZXhwIjoxNzQ1MjcwMjEzfQ.NwngRWlu6BIwCpl3aAKDbHgbS6N5W71iWvHixyNDcKs"  # Replace with your actual token
}

# List of posts
posts = [
    {
        "title": "Virat Kohli’s Century Sparks RCB’s Epic Comeback",
        "content": "Last night’s IPL match was a rollercoaster, and Virat Kohli proved why he’s a legend. His 120 off 60 balls turned a hopeless chase into a thrilling victory for RCB. The crowd at Chinnaswamy was electric, chanting his name as he smashed boundaries. But let’s talk about the bowling—RCB’s weakness is glaring. They leaked runs in the powerplay, and without Kohli’s heroics, this could’ve been another loss. The team needs a reliable pace attack to complement their batting. Fans are hopeful, but the management must act fast to fix these gaps before the playoffs. Can Kohli carry RCB to the title, or will the bowling woes continue?",
        "previewImage": "https://images.unsplash.com/photo-1622270396078-c2db2e252d3b",
        "topics": ["SPORTS", "CRICKET"]
    },
    {
        "title": "CSK’s Death Bowling Crisis in IPL 2025",
        "content": "Chennai Super Kings are struggling, and their death bowling is the culprit. In their last three matches, they’ve conceded over 60 runs in the final five overs, losing games they should’ve won. The absence of a clutch bowler like Dwayne Bravo is painfully obvious. Youngsters like Pathirana show promise, but they lack consistency. Dhoni’s leadership keeps the team afloat, but even he can’t fix everything. Fans are frustrated, flooding social media with complaints about the bowling strategy. CSK needs to scout talent or rethink their game plan. Will they bounce back, or is this season a write-off for the yellow army?",
        "previewImage": "https://images.unsplash.com/photo-1593341646782-e0b495cff86d",
        "topics": ["SPORTS", "CRICKET"]
    },
    {
        "title": "Rohit Sharma’s Tactical Genius in ODIs",
        "content": "Rohit Sharma’s captaincy in the recent ODI series against Australia was a masterclass. His bold field placements and timely bowling changes outsmarted the Aussies, leading India to a 3-1 series win. The way he rotated spinners in the middle overs choked their batting lineup. Off the field, his calm demeanor inspires the team, but on it, he’s a chess grandmaster. Fans are buzzing about India’s World Cup chances with him at the helm. However, the middle order needs stability—too many collapses this year. Can Rohit’s leadership and batting prowess carry India to another title? The nation’s watching.",
        "previewImage": "https://images.unsplash.com/photo-1607990283143-bfa3b0f776d4",
        "topics": ["CRICKET", "INDIA"]
    },
    {
        "title": "Monsoon Delays Disrupt India’s Cricket Calendar",
        "content": "The monsoon season is wreaking havoc on India’s domestic cricket schedule. Matches in Mumbai and Delhi have been washed out, frustrating players and fans alike. Stadiums lack modern drainage systems, and scheduling games during peak rains is questionable. The BCCI needs to invest in infrastructure or adjust the calendar to avoid these disruptions. Fans are venting online, demanding covered stadiums or indoor facilities. Meanwhile, young players lose crucial match practice, which could hurt their development. Cricket’s the heartbeat of India, so why aren’t we prioritizing solutions? Hopefully, the authorities wake up before the next season gets drowned.",
        "previewImage": "https://images.unsplash.com/photo-1534274988757-a28bf1a57c17",
        "topics": ["WEATHER", "INDIA"]
    },
    {
        "title": "Jasprit Bumrah’s Return Boosts India’s Hopes",
        "content": "Jasprit Bumrah is back, and India’s pace attack looks lethal again. His spell against England, where he took three wickets in quick succession, was pure magic. That toe-crushing yorker to dismiss Joe Root? Unplayable. His comeback after injury is a massive boost for the World Cup. However, India must manage his workload carefully—overbowling him could risk another injury. The team’s reliance on him is a concern; other pacers like Siraj need to step up. Fans are thrilled, flooding X with memes praising ‘Boom Boom.’ Can Bumrah stay fit and lead India to glory? The nation’s holding its breath.",
        "previewImage": "https://images.unsplash.com/photo-1614281512364-2ed673b4ec70",
        "topics": ["SPORTS", "CRICKET"]
    },
    {
        "title": "Delhi’s Pollution Affects Cricket Matches",
        "content": "Delhi’s air quality is a nightmare for cricketers. During the recent Ranji Trophy match, players were coughing and struggling to breathe due to smog. The AQI hit 400, forcing umpires to pause play. This isn’t just about comfort—it’s a health crisis. The BCCI must consider relocating matches or investing in air purifiers for stadiums. Fans are furious, trending #CleanAirForCricket on X. Players’ long-term health is at risk, and young athletes are suffering the most. Why isn’t there a clear policy to tackle this? Delhi’s hosting international games soon—will the world see India’s pollution problem in 4K?",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["INDIA", "WEATHER"]
    },
    {
        "title": "IPL 2025 Playoff Predictions and Analysis",
        "content": "The IPL 2025 race is heating up, and fans are buzzing with predictions. CSK, MI, and RCB are frontrunners, but dark horses like Gujarat Titans could surprise. RCB’s batting is explosive, but their bowling remains shaky. MI’s all-round strength makes them favorites, while CSK’s experience is unmatched. Social media’s flooded with debates—can Kohli finally win a title? The playoff format rewards consistency, but one bad day can end your season. Franchises need to balance star players with domestic talent. The real question: will the BCCI tweak the rules again? Fans await the drama in the coming weeks.",
        "previewImage": "https://images.unsplash.com/photo-1587281203230-0b39e95bf2f4",
        "topics": ["SPORTS", "CRICKET"]
    },
    {
        "title": "Suryakumar Yadav’s T20 Dominance Continues",
        "content": "Suryakumar Yadav is rewriting T20 cricket’s rulebook. His 360-degree shots in the recent India-South Africa series left bowlers clueless. Scoring 80 off 40 balls, he turned a tricky chase into a cakewalk. His innovation—scoops, lofts, and reverse sweeps—is unmatched. But consistency is key; he needs to perform in big tournaments. Fans on X are calling him the ‘T20 GOAT,’ but can he outshine Kohli or Rohit? The team’s overreliance on him in the middle order is risky. Mumbai Indians must back him as a leader too. Will Suryakumar’s flair win India the next World Cup?",
        "previewImage": "https://images.unsplash.com/photo-1593341646782-e0b495cff86d",
        "topics": ["CRICKET", "INDIA"]
    },
    {
        "title": "Politics in Cricket Selection Sparks Debate",
        "content": "The BCCI’s selection process is under fire again. Fans and analysts on X are questioning why certain players are consistently overlooked despite stellar domestic performances. Regional biases and favoritism rumors are rife, with some claiming big franchises influence picks. Transparency is desperately needed—why not publish selection criteria? Young talents like Sarfaraz Khan deserve a fair shot, but they’re stuck in the Ranji grind. The board’s silence is fueling frustration, and hashtags like #FairSelection are trending. Cricket’s India’s religion, so why taint it with politics? The system needs an overhaul before fans lose trust completely.",
        "previewImage": "https://images.unsplash.com/photo-1526378722484-cc5e4d5b2c4d",
        "topics": ["CRICKET", "POLITICS"]
    },
    {
        "title": "Chennai Super Kings’ Loyal Fanbase Shines",
        "content": "CSK’s fans, the ‘Yellow Army,’ are a phenomenon. At every IPL match, they turn stadiums into a sea of yellow, chanting ‘Thala Dhoni’ with unmatched passion. Their loyalty, even after tough seasons, is inspiring. Social media’s full of fan-made tributes, from murals to viral reels. This fanbase transcends cricket—it’s a culture. But the team needs to reward them with better performances. The bowling unit’s struggles are testing even their patience. Can CSK’s management build a squad worthy of this devotion? The fans deserve a title run in 2025. Let’s see if the team delivers.",
        "previewImage": "https://images.unsplash.com/photo-1604558980752-204bd193d209",
        "topics": ["SPORTS", "CRICKET"]
    },
    {
        "title": "India’s Pace Attack Dominates World Cricket",
        "content": "India’s pace trio—Bumrah, Shami, and Siraj—is terrorizing batters globally. In the recent Test series, they took 25 wickets in three matches, with Bumrah’s swing and Siraj’s aggression standing out. Their ability to bowl long spells in tough conditions is unreal. Fans on X are hyped, trending #PaceIsLethal. But depth is a concern—what if injuries hit? Youngsters like Umran Malik need grooming. The BCCI must prioritize workload management to keep this unit fresh. Can India’s pacers win the World Test Championship? They’re the best in the world, but consistency is everything.",
        "previewImage": "https://images.unsplash.com/photo-1578425578640-2fe981538c3c",
        "topics": ["CRICKET", "INDIA"]
    },
    {
        "title": "Mumbai’s Traffic Jams Frustrate Cricket Fans",
        "content": "Mumbai’s traffic is a nightmare for cricket fans. Getting to Wankhede Stadium for IPL matches feels like a marathon. Last week, I missed the powerplay stuck on Western Express Highway. The city’s infrastructure hasn’t kept up with its growth, and fans are fed up. Social media’s buzzing with complaints—#MumbaiTrafficSucks is trending. The BMC needs to fast-track metro projects or add shuttle services for match days. Cricket’s a religion here, so why make it so hard to enjoy? Better planning could turn game days into a celebration, not a chore. Will the authorities listen?",
        "previewImage": "https://images.unsplash.com/photo-1565118535070-4c3ab6b2c2c2",
        "topics": ["INDIA"]
    },
    {
        "title": "MS Dhoni Defies Age with Six-Hitting",
        "content": "At 43, MS Dhoni is still hitting monstrous sixes, and fans can’t get enough. His 20-ball 40 in a recent IPL game silenced doubters. That helicopter shot? Timeless. Social media’s exploding with #ThalaForever trending. But CSK’s overreliance on him is risky—he can’t bat up the order forever. The team needs young finishers to step up. Dhoni’s leadership is invaluable, but his body needs care. Fans are emotional, knowing his retirement’s near. Can he lead CSK to one more title? The yellow army’s praying for a fairytale ending in 2025.",
        "previewImage": "https://images.unsplash.com/photo-1585079542061-2811c38d6d8b",
        "topics": ["SPORTS", "CRICKET"]
    },
    {
        "title": "T20 World Cup Hype Builds for India",
        "content": "The T20 World Cup is months away, but India’s squad announcement has fans buzzing. With Rohit leading and stars like Suryakumar and Bumrah in form, the team looks balanced. The spin duo of Kuldeep and Chahal could be game-changers. X is flooded with fan predictions—#IndiaForWC is trending. But the middle order’s inconsistency is a worry; too many collapses in 2024. The BCCI’s selection debates are heating up too—why no Rinku Singh? India’s got the talent, but can they handle pressure? Fans are dreaming of lifting the trophy again.",
        "previewImage": "https://images.unsplash.com/photo-1607990283323-bfa3b0f776d4",
        "topics": ["CRICKET", "INDIA"]
    },
    {
        "title": "Electric Atmosphere at IPL Stadiums",
        "content": "Nothing beats the vibe of an IPL match live. The roaring crowds, dazzling light shows, and non-stop chants create an unmatched atmosphere. At Eden Gardens, fans danced to ‘Sweet Caroline’ between overs. Social media’s full of videos—#IPLVibes is trending. But high ticket prices are locking out some fans, and that’s unfair. The BCCI should cap costs to keep cricket accessible. Players feed off the energy, but teams need to deliver performances worthy of it. Can the IPL keep this magic while staying fan-friendly? The 2025 season will test that balance.",
        "previewImage": "https://images.unsplash.com/photo-1560272564-c83b99b6c9c9",
        "topics": ["SPORTS", "CRICKET"]
    },
    {
        "title": "Hardik Pandya’s Captaincy Faces Criticism",
        "content": "Hardik Pandya’s stint as MI captain is under scrutiny. Fans on X are slamming his tactical decisions, like delaying Bumrah’s overs in key games. MI’s inconsistent season has fueled the #HardikOut trend. His batting’s been patchy too, raising questions about his leadership. But Hardik’s shown resilience before—can he turn it around? The team needs to rally behind him, and he must trust his instincts. Mumbai’s fanbase is passionate but unforgiving. The pressure’s on for 2025. Will Hardik silence the critics, or is his captaincy tenure doomed? Only results will tell.",
        "previewImage": "https://images.unsplash.com/photo-1593341646782-e0b495cff86d",
        "topics": ["CRICKET"]
    },
    {
        "title": "Rain Continues to Ruin Cricket Matches",
        "content": "Rain’s been a buzzkill for cricket fans this season. Three matches in a row were abandoned in Hyderabad due to storms, leaving players and fans frustrated. Why don’t Indian stadiums have retractable roofs or better drainage? Social media’s raging—#FixOurStadiums is trending. The BCCI’s sitting on billions, so where’s the investment? Fans deserve better than soggy disappointments. Domestic players lose vital game time, which hurts their growth. The authorities need to prioritize infrastructure upgrades. Will we see modern stadiums by 2026, or is this just wishful thinking?",
        "previewImage": "https://images.unsplash.com/photo-1519750783825-cb0ca6e83417",
        "topics": ["WEATHER", "INDIA"]
    },
    {
        "title": "Shubman Gill: India’s Next Big Star",
        "content": "Shubman Gill’s rise is unstoppable. His elegant 150 in the recent Test against New Zealand was a batting clinic—pure timing and grace. Fans on X are calling him India’s future captain, with #GillForPM trending. His consistency across formats is remarkable, but he needs to conquer big finals. The pressure of replacing Kohli looms large. Gill’s calm demeanor helps, but the spotlight’s intense. The BCCI should groom him for leadership roles early. Can he become India’s next batting legend? The signs are promising, but the journey’s just begun for this 25-year-old.",
        "previewImage": "https://images.unsplash.com/photo-1614281512364-2ed673b4ec70",
        "topics": ["CRICKET", "INDIA"]
    },
    {
        "title": "Cricket Needs Video Tech Like VAR",
        "content": "Umpiring errors are ruining cricket matches, and fans are fed up. In a recent ODI, a clear LBW was missed, costing India the game. Social media’s exploding—#CricketNeedsVAR is trending. Why not adopt a football-style video review system for all decisions? The DRS helps, but it’s limited. Tech can ensure fairness, especially in high-stakes games. The ICC’s slow to innovate, but fans and players deserve accuracy. Bad calls hurt the game’s credibility. Can cricket embrace modern tech, or will tradition hold it back? The debate’s heating up, and change feels overdue.",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["SPORTS", "CRICKET"]
    },
    {
        "title": "BCCI’s Funds Must Support Grassroots Cricket",
        "content": "The BCCI’s swimming in IPL cash, but grassroots cricket is starving. Rural academies lack coaches, equipment, and grounds, stunting talent growth. Fans on X are vocal—#FundTheFuture is trending. Why prioritize glitzy tournaments over young players? The board must invest in school-level programs and regional leagues. Stars like Kohli came from humble beginnings—more could follow with support. The BCCI’s legacy depends on nurturing the next generation. Will they step up, or keep chasing profits? India’s cricket dominance is at stake if they don’t act soon. The clock’s ticking.",
        "previewImage": "https://images.unsplash.com/photo-1551288049-b1f3c6f3c7d6",
        "topics": ["CRICKET", "INDIA"]
    }
]

# Send POST requests
for i, post in enumerate(posts, start=1):
    response = requests.post(URL, json=post, headers=HEADERS)
    if response.status_code == 201:
        print(f"[{i}] ✅ Post '{post['title']}' created successfully.")
    else:
        print(f"[{i}] ❌ Failed to create post '{post['title']}': {response.status_code} - {response.text}")
