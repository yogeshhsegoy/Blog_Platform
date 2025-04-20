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
        "title": "Lionel Messi’s Free-Kick Magic in La Liga",
        "content": "Messi’s latest free-kick goal for Barcelona was pure artistry. Curving it over the wall into the top corner, he left the keeper rooted. The Camp Nou erupted, and X exploded with #MessiGOAT trending. At 37, he’s still untouchable, but Barca’s defense is leaky, conceding soft goals. The team’s youth, like Yamal, show promise, but they need structure. Fans are debating if Messi can carry them to the title. His vision and precision are unmatched, yet the squad’s inconsistency frustrates. Can Messi defy age and win another Ballon d’Or? Football’s blessed to witness this genius.",
        "previewImage": "https://images.unsplash.com/photo-1518091043644-c1d4457512c6",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "Premier League’s VAR Decisions Spark Outrage",
        "content": "VAR in the Premier League is a mess. Last weekend, a clear penalty for Arsenal was waved off, costing them the game. Fans on X are furious—#VAROut is trending. The tech’s meant to ensure fairness, but inconsistent calls favor big clubs like City. Referees seem scared to overturn decisions, undermining trust. The FA needs clearer protocols or human oversight. Smaller teams suffer most, and fans feel cheated. Football’s soul is at stake when tech fails. Can the Premier League fix VAR, or is it doomed to ruin matches? The debate’s raging, and fans want justice.",
        "previewImage": "https://images.unsplash.com/photo-1551958219-3b8fcadae305",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "USMNT’s Rise Ahead of 2026 World Cup",
        "content": "The USMNT is turning heads with young stars like Pulisic and Musah. Their recent 3-0 win over Mexico showed grit and flair. X fans are hyped—#USMNT2026 is trending. Hosting the World Cup adds pressure, but the squad’s depth is improving. Coach Berhalter’s tactics are debated; some want a bolder style. The MLS is feeding talent, but Europe-based players are key. Fans dream of a quarterfinal run, but consistency’s the challenge. Can the USA become a football powerhouse by 2026? The potential’s there, but they must seize this moment.",
        "previewImage": "https://images.unsplash.com/photo-1570498432553-7a8d6974b6c7",
        "topics": ["SPORTS", "USA"]
    },
    {
        "title": "Russia’s Olympic Ban Hurts Athletes",
        "content": "Russia’s ongoing Olympic ban is crushing its athletes. Clean competitors are punished for state doping scandals, which feels unfair. X discussions are heated—#SportsPolitics is trending. Politics shouldn’t rob talents of their dreams, yet geopolitics dominates. Russian footballers are fleeing to European leagues, but opportunities are limited. The IOC’s stance is firm, but fans argue for individual clearances. Athletes train their whole lives for these moments—why penalize them? Russia’s sports culture is suffering, and recovery’s uncertain. Can the system find a fairer way, or will politics keep winning? The human cost is heartbreaking.",
        "previewImage": "https://images.unsplash.com/photo-1526378722484-cc5e4d5b2c4d",
        "topics": ["SPORTS", "RUSSIA"]
    },
    {
        "title": "Kylian Mbappé’s Speed Redefines Football",
        "content": "Mbappé’s pace is unreal—he outran three defenders in PSG’s last match, setting up a tap-in. His 90-meter sprint was clocked at 36 km/h! X is buzzing—#MbappéMagic is trending. At 26, he’s a generational talent, but his finishing needs polish; he missed two sitters. PSG’s attack relies on him, which exposes their lack of depth. Fans debate if he’s surpassed Neymar. Real Madrid rumors swirl, adding pressure. Can Mbappé lead France to another World Cup? His potential’s limitless, but consistency’s the key to greatness.",
        "previewImage": "https://images.unsplash.com/photo-1518091043644-c1d4457512c6",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "FIFA’s Corruption Scandals Erode Fan Trust",
        "content": "Another FIFA scandal dropped, with officials caught in a World Cup bidding scheme. Bribes and backroom deals are tainting football’s spirit. X fans are livid—#FIFACorrupt is trending. The organization’s history of greed—Qatar 2022, anyone?—breeds cynicism. Fans want transparency: open voting, audited funds. Players and coaches deserve a clean governing body. Smaller nations lose out most, as rich countries dominate. The beautiful game’s at risk of losing its soul. Can FIFA reform, or is corruption too entrenched? Fans are organizing protests, demanding change before the next World Cup. It’s now or never.",
        "previewImage": "https://images.unsplash.com/photo-1526378722484-cc5e4d5b2c4d",
        "topics": ["FOOTBALL", "POLITICS"]
    },
    {
        "title": "Champions League Delivers Unforgettable Drama",
        "content": "This season’s Champions League is pure chaos. Bayern’s last-gasp winner against PSG and Liverpool’s 4-3 thriller over Real had fans screaming. X is on fire—#UCLDrama is trending. Underdogs like Porto are stealing the show, upsetting giants. The knockout format rewards bravery, but VAR controversies linger. Fans love the unpredictability, though ticket prices are insane—some paid €500! UEFA needs to cap costs for accessibility. The final’s shaping up to be epic. Can a non-English club win, or will City dominate again? Football’s never been this thrilling.",
        "previewImage": "https://images.unsplash.com/photo-1551958219-3b8fcadae305",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "Women’s Football Gains Massive Global Support",
        "content": "Women’s football is soaring. The Women’s Euros drew 80,000 fans per match, rivaling men’s crowds. X is celebrating—#WomensFootball is trending. Stars like Alexia Putellas are household names, and clubs are investing in academies. But pay gaps persist; top women earn 10% of men’s salaries. Fans demand equality, and sponsors are listening. The game’s technical quality—passing, tactics—is world-class. Broadcasting deals are growing, but smaller leagues need funds. Can women’s football overtake men’s in popularity? The momentum’s unstoppable, and I’m all in for this revolution. Let’s keep pushing!",
        "previewImage": "https://images.unsplash.com/photo-1570498432553-7a8d6974b6c7",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "USA’s Plans for 2026 World Cup Glory",
        "content": "The USA’s gearing up for the 2026 World Cup, and the hype’s real. Stadiums are being upgraded, and cities like LA are buzzing. X fans are dreaming big—#WorldCup2026 is trending. The USMNT’s young core—Weah, Reyna—is maturing fast, but depth’s a concern. Hosting brings pressure; fans expect a deep run. MLS academies are churning out talent, but Europe’s where stars shine. The economic boost could hit $10 billion, yet ticket affordability’s an issue. Can the USA make this a legendary tournament? The stage is set, and the world’s watching.",
        "previewImage": "https://images.unsplash.com/photo-1610901491660-0bd5882c8387",
        "topics": ["FOOTBALL", "USA"]
    },
    {
        "title": "Football’s Transfer Market Hits New Highs",
        "content": "The transfer window’s gone wild—clubs spent €7 billion this summer. Chelsea’s €200M spree led the pack, but fans on X are skeptical—#TransferMadness is trending. Are these fees sustainable, or is football eating itself? Young stars like Bellingham justify costs, but flops like Lukaku burn clubs. Financial fair play rules feel toothless; rich owners dodge them. Fans worry about ticket prices rising to cover debts. Smaller clubs can’t compete, widening the gap. Can UEFA regulate this chaos, or will money ruin the game? The market’s a circus, and fans are paying the price.",
        "previewImage": "https://images.unsplash.com/photo-1551288049-b1f3c6f3c7d6",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "Cristiano Ronaldo’s Legacy in Modern Football",
        "content": "Ronaldo’s 900th career goal sparked debates: is he the GOAT? His header for Al-Nassr was vintage CR7—power and precision. X is divided—#RonaldoVsMessi is trending. At 40, his work ethic’s unreal, but critics say he’s stat-padding in a weaker league. His five Ballons d’Or and UCL titles speak volumes. Yet, Messi’s playmaking edges him for some. Ronaldo’s marketability transformed football, but his Portugal record’s mixed. Fans love his charisma; haters call him selfish. Can he hit 1,000 goals? His legacy’s secure, but the GOAT race is tight.",
        "previewImage": "https://images.unsplash.com/photo-1518091043644-c1d4457512c6",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "Politics Continues to Undermine Sports Integrity",
        "content": "Politics is poisoning sports. From Russia’s bans to Qatar’s World Cup controversies, athletes are caught in the crossfire. X fans are fed up—#KeepPoliticsOut is trending. Geopolitical agendas—sanctions, boycotts—rob players of fair chances. FIFA and the IOC bow to powerful nations, ignoring smaller ones. Fans want sports to unite, not divide. The human cost is real; imagine training for years, only to be excluded. Transparency in governance could help, but money and power rule. Can sports stay pure, or is politics too entrenched? Fans are rallying for change, but it’s an uphill fight.",
        "previewImage": "https://images.unsplash.com/photo-1526378722484-cc5e4d5b2c4d",
        "topics": ["SPORTS", "POLITICS"]
    },
    {
        "title": "La Liga’s Emerging Stars Steal the Spotlight",
        "content": "La Liga’s young guns are shining. Lamine Yamal, 17, dribbled past four defenders to score for Barca last week. X is hyped—#LaLigaNextGen is trending. Players like Cubarsí and Pedri signal a bright future, but clubs lean heavily on youth due to budget cuts. Veterans like Modric still contribute, balancing the squad. Real Madrid’s dominance overshadows smaller teams, though. Fans want more parity; the wealth gap’s growing. Spain’s youth academies are world-class, but burnout’s a risk. Can these kids lead La Liga to glory? The talent’s there, and the world’s watching.",
        "previewImage": "https://images.unsplash.com/photo-1570498432553-7a8d6974b6c7",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "Russia’s Football League Faces Challenges",
        "content": "Russia’s Premier League is struggling under sanctions. Top players are bolting to Europe, and clubs can’t afford replacements. X fans are vocal—#RussianFootball is trending. Sponsorships are drying up, and stadiums sit half-empty. The national team’s banned from UEFA, crushing morale. Youth academies still produce talent, but opportunities are scarce. Politics, not performance, is the enemy here. Fans want their league to thrive, but global isolation hurts. Can Russian football rebuild, or will it fade further? The passion’s there, but the path’s brutal. Players deserve better than this mess.",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["FOOTBALL", "RUSSIA"]
    },
    {
        "title": "Football Fan Culture Fuels Matchday Passion",
        "content": "Football’s fan culture is unmatched. At Anfield, Liverpool’s ‘You’ll Never Walk Alone’ gave me chills. Flags, chants, and flares create electric vibes. X is full of fan videos—#FootballFans is trending. But hooliganism and pricey tickets tarnish the experience. Some finals cost €1,000 per seat! Clubs must cap prices and crack down on violence. Ultras bring soul, but safety’s non-negotiable. Fans drive the game’s heart—players feed off their energy. Can football stay accessible and safe? The culture’s magic, but it needs protecting. Let’s keep matchdays unforgettable for all.",
        "previewImage": "https://images.unsplash.com/photo-1560272564-c83b99b6c9c9",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "Mohamed Salah’s Contract Drama at Liverpool",
        "content": "Mo Salah’s contract saga is stressing Liverpool fans. His 15 goals this season prove he’s irreplaceable, yet talks are stalled. X is anxious—#PaySalah is trending. At 32, he wants a three-year deal, but the club’s offering two. His work rate and leadership define the team; losing him would gut Anfield. FSG’s cautious spending frustrates supporters—why risk their star? Rivals like PSG are circling. Salah’s calm, but fans aren’t. Can Liverpool secure their king, or will he leave a legend? The clock’s ticking, and the stakes are massive.",
        "previewImage": "https://images.unsplash.com/photo-1551958219-3b8fcadae305",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "MLS Growth Signals USA’s Football Ambition",
        "content": "The MLS is stepping up. Stars like Messi joining Inter Miami have boosted global eyes on the league. X fans are excited—#MLS2025 is trending. Attendance is up 20%, and TV deals are soaring. But the gap with Europe’s leagues persists; MLS lacks tactical depth. Academies are improving, feeding the USMNT. Yet, ticket prices are climbing, alienating core fans. The 2026 World Cup will showcase the league—can it deliver? Expansion’s risky; quality over quantity matters. Can MLS become a top league? The trajectory’s strong, but challenges remain.",
        "previewImage": "https://images.unsplash.com/photo-1610901491660-0bd5882c8387",
        "topics": ["FOOTBALL", "USA"]
    },
    {
        "title": "Football’s Injury Crisis Demands Action",
        "content": "Football’s injury epidemic is alarming. Top players like De Bruyne and Alaba missed half the season with knee issues. X fans are worried—#PlayerHealth is trending. Packed schedules—50+ games a year—leave no recovery time. Clubs prioritize profits over rest, burning out stars. UEFA’s new formats add more matches, ignoring science. Sports medicine’s advancing, but prevention’s better. Fans want shorter seasons or mandatory breaks. Players’ unions are pushing back, but owners resist. Can football protect its athletes, or will greed win? The human toll’s too high to ignore.",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["SPORTS", "FOOTBALL"]
    },
    {
        "title": "Fan Protests Shape Football’s Future",
        "content": "Football fans are flexing their power. Manchester United’s ticket price hike was scrapped after protests outside Old Trafford. X is cheering—#FanPower is trending. From boycotts to banners, supporters are forcing change. German fans’ 50+1 rule keeps clubs fan-owned, a model others envy. But rising costs—€100 for some matches—lock out loyalists. Clubs listen when revenue’s threatened, proving fans’ clout. Social media amplifies their voice; petitions go viral. Can fans keep football affordable and democratic? Their unity’s shaking boardrooms, and the fight’s just starting. Power to the people!",
        "previewImage": "https://images.unsplash.com/photo-1560272564-c83b99b6c9c9",
        "topics": ["FOOTBALL", "POLITICS"]
    },
    {
        "title": "Who Will Win the Next Ballon d’Or?",
        "content": "The Ballon d’Or race is neck-and-neck. Haaland’s 40 goals for City make him a frontrunner, but Bellingham’s all-around brilliance at Real shines. X debates are wild—#BallonDOr2025 is trending. Mbappé’s in the mix too, with his flair and stats. Voters love goalscorers, but midfield maestros like Rodri deserve love. Messi and Ronaldo still linger, but their era’s fading. The award’s prestige is unmatched, yet biases toward big clubs persist. Fans want fairness—smaller leagues get ignored. Who’s your pick? The ceremony’s months away, but the hype’s already electric.",
        "previewImage": "https://images.unsplash.com/photo-1518091043644-c1d4457512c6",
        "topics": ["SPORTS", "FOOTBALL"]
    }
]

# Send POST requests
for i, post in enumerate(posts, start=1):
    response = requests.post(URL, json=post, headers=HEADERS)
    if response.status_code == 201:
        print(f"[{i}] ✅ Post '{post['title']}' created successfully.")
    else:
        print(f"[{i}] ❌ Failed to create post '{post['title']}': {response.status_code} - {response.text}")
