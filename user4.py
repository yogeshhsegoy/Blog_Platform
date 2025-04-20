import requests

# URL and headers
URL = "http://localhost:8082/api/blogs"
HEADERS = {
    "Content-Type": "application/json",
    "Authorization": "Bearer eyJhbGciOiJIUzI1NiJ9.eyJ0b3BpY3MiOlsiUE9MSVRJQ1MiLCJVU0EiLCJSVVNTSUEiXSwic3ViIjoic3VrZXNoIiwiaWF0IjoxNzQ1MTg0MDc3LCJleHAiOjE3NDUyNzA0Nzd9.Ivqb7I99v3nYIxq8i6cab5R-9F4eiSwyzNmJYWqzXBQ"  # Replace with your actual token
}

# List of posts
posts = [
    {
        "title": "PV Sindhu’s Dominant Return to BWF Circuit",
        "content": "PV Sindhu’s back with a vengeance, winning the Malaysia Open with ferocious smashes. Her court coverage and deceptive drops were untouchable. X fans are ecstatic—#SindhuRules is trending. At 29, she’s sharper than ever, but the young Chinese players are relentless. India’s badminton scene owes her for inspiring millions. Still, her stamina in five-setters needs work; she faded in a recent semifinal. The BWF’s grueling schedule tests even the best. Fans want another Olympic medal—can she deliver? Her mental toughness is her edge. India’s cheering, and I’m glued to her next match.",
        "previewImage": "https://images.unsplash.com/photo-1630524706760-067c1308e27c",
        "topics": ["SPORTS", "BADMINTON"]
    },
    {
        "title": "India’s Badminton Talent Pipeline Looks Promising",
        "content": "India’s badminton future is bright, with youngsters like Lakshya Sen and Anmol Kharb shining. Sen’s bronze at the Worlds was a statement; his net play’s world-class. X is hyped—#BadmintonIndia is trending. Academies in Hyderabad and Bangalore are churning out talent, but funding’s uneven. Cricket overshadows, siphoning resources. The BAI must invest in grassroots and coaching. Fans dream of multiple Olympic medals in 2028. The challenge? Keeping players injury-free in a brutal sport. Can India dominate badminton like China? The kids are hungry, and the system needs to back them.",
        "previewImage": "https://images.unsplash.com/photo-1622270396078-c2db2e252d3b",
        "topics": ["SPORTS", "BADMINTON", "INDIA"]
    },
    {
        "title": "Monsoon Floods Disrupt Badminton Tournaments",
        "content": "The monsoon’s a nightmare for badminton in India. Outdoor courts in Mumbai were flooded, canceling a junior tournament. Even indoor venues struggled with leaks. X fans are frustrated—#FixOurCourts is trending. The BAI’s slow to upgrade facilities; most arenas lack proper drainage. Players lose critical match practice, and organizers lose revenue. Fans demand modern indoor stadiums—cricket grounds get all the funds. Scheduling during dry months could help, but planning’s poor. Can India host world-class events in these conditions? The sport’s growing, but infrastructure’s stuck in the past. It’s time for change.",
        "previewImage": "https://images.unsplash.com/photo-1534274988757-a28bf1a57c17",
        "topics": ["WEATHER", "INDIA"]
    },
    {
        "title": "Saina Nehwal’s Enduring Legacy in Badminton",
        "content": "Saina Nehwal’s impact on Indian badminton is unmatched. Her 2012 Olympic bronze broke barriers, inspiring a generation. X tributes are pouring in—#SainaLegend is trending. Her aggressive style and work ethic set the standard. Now coaching, she’s shaping the next wave. But her prime showed India’s potential—and its limits. Funding and facilities lagged then, and still do. Saina’s vocal about systemic fixes, but change is slow. Fans want her statue at a stadium. Can her legacy push India to global dominance? She’s a trailblazer, and her story’s far from over.",
        "previewImage": "https://images.unsplash.com/photo-1630524706760-067c1308e27c",
        "topics": ["SPORTS", "BADMINTON"]
    },
    {
        "title": "Sports Funding Imbalance in Indian Budgets",
        "content": "India’s sports budget is a joke—cricket hogs 70% of funds, leaving badminton in the dust. The BAI gets scraps, barely enough for academies or travel. X fans are angry—#FundBadminton is trending. Talents like Sindhu succeeded despite the system, not because of it. Other sports—hockey, wrestling—suffer too. The government’s ‘Khelo India’ scheme helps, but it’s underfunded. Fans want parity; cricket’s rich enough. Without investment, India’s losing future medals. Can the budget prioritize diverse sports? Badminton’s rise shows what’s possible with support. It’s time to level the playing field.",
        "previewImage": "https://images.unsplash.com/photo-1551288049-b1f3c6f3c7d6",
        "topics": ["SPORTS", "INDIA"]
    },
    {
        "title": "Delhi’s Heatwave Challenges Badminton Players",
        "content": "Delhi’s summer heat is brutal for badminton players. Temperatures hit 45°C, making training unbearable. Courts lack AC, and hydration breaks aren’t enough. X players are venting—#CoolOurCourts is trending. Heatstroke risks are real; a junior collapsed last week. The BAI must install cooling systems or shift tournaments to cooler months. Fans worry about long-term health impacts. Cricket stadiums get upgrades—why not badminton? India’s hosting BWF events soon; this can’t continue. Can facilities step up, or will players keep suffering? The sport’s growth demands better conditions now.",
        "previewImage": "https://images.unsplash.com/photo-1622310409315-85f92de6b7a6",
        "topics": ["WEATHER", "INDIA"]
    },
    {
        "title": "India’s Olympic Badminton Medal Hopes",
        "content": "India’s badminton squad is eyeing multiple medals in 2028. Sindhu’s leading, but doubles pairs like Satwik-Chirag are world-class. Their bronze at the 2024 Games was a teaser. X fans are pumped—#BadmintonOlympics is trending. The challenge? China and Denmark’s depth. India needs more elite coaches and international exposure. Injuries are a worry; the sport’s brutal on joints. The BAI’s planning training camps, but funds are tight. Fans dream of gold, and the talent’s there. Can India outplay the giants? The road’s tough, but the hunger’s real.",
        "previewImage": "https://images.unsplash.com/photo-1622270396078-c2db2e252d3b",
        "topics": ["SPORTS", "BADMINTON"]
    },
    {
        "title": "Corruption in Sports Federations Hurts Athletes",
        "content": "Indian sports federations are a mess. Badminton’s BAI faces allegations of fund mismanagement and favoritism in selections. X fans are outraged—#CleanUpSports is trending. Athletes train relentlessly, only to lose spots to politics. Transparency’s nonexistent—where’s the money going? Cricket’s BCCI isn’t perfect, but it’s miles ahead. The government must audit these bodies and enforce accountability. Young players deserve fair shots, not rigged systems. Fans are pushing for reforms, but bureaucracy’s stubborn. Can India’s sports governance change, or will athletes keep paying the price? The system’s broken, and it’s time to fix it.",
        "previewImage": "https://images.unsplash.com/photo-1526378722484-cc5e4d5b2c4d",
        "topics": ["SPORTS", "POLITICS"]
    },
    {
        "title": "Kidambi Srikanth’s Clutch Performances Shine",
        "content": "Kidambi Srikanth’s back in form, winning a thriller at the Japan Open. His defense under pressure—saving three match points—was unreal. X fans are buzzing—#KidambiComeback is trending. His smashes and net play rival the best, but consistency’s his issue. He’s India’s underrated star, often outshone by Sindhu. Fans want him leading India’s charge. Injuries have slowed him, but his grit’s unmatched. Can he reclaim his 2017 glory? His clutch plays fuel hope for a major title. Srikanth’s a fighter—let’s see him soar in 2025.",
        "previewImage": "https://images.unsplash.com/photo-1630524706760-067c1308e27c",
        "topics": ["SPORTS", "BADMINTON"]
    },
    {
        "title": "India’s Growing Sports Culture in Schools",
        "content": "Sports in Indian schools are gaining traction. Badminton’s booming, with kids flocking to local clubs. X is celebrating—#SportsForKids is trending. But schools lack coaches and courts; cricket dominates budgets. Programs like Khelo India are helping, but rural areas get ignored. Urban centers like Delhi have facilities, but access is uneven. Fans want mandatory sports periods and inter-school leagues. Talent’s there—look at Sen—but opportunity isn’t. Can India build a true sports culture? The potential’s huge, but the system needs to prioritize kids over IPL profits.",
        "previewImage": "https://images.unsplash.com/photo-1569172122309-bc25d0109709",
        "topics": ["SPORTS", "INDIA"]
    },
    {
        "title": "Bangalore’s Unpredictable Weather Delays Matches",
        "content": "Bangalore’s weather is chaos—sunny mornings, stormy afternoons. A BWF qualifier was postponed twice last week. X fans are annoyed—#BangaloreWeather is trending. Indoor courts are scarce, and outdoor ones flood easily. The BAI’s dragging its feet on upgrades; cricket gets all the funds. Fans demand retractable roofs or better scheduling. Players lose momentum, and organizers lose money. India’s hosting global events soon—can’t afford this. Can Bangalore fix its venues, or will rain keep winning? The sport’s too big for these setbacks.",
        "previewImage": "https://images.unsplash.com/photo-1519750783825-cb0ca6e83417",
        "topics": ["WEATHER", "INDIA"]
    },
    {
        "title": "Badminton Coaching Shortages in India",
        "content": "India’s badminton boom is stunted by a coaching crisis. Elite coaches are rare; most academies rely on retirees or underqualified staff. X discussions are heated—#MoreCoaches is trending. Talent like Lakshya Sen thrives despite this, but others stall. China’s coaching pipeline produces champions—India’s doesn’t. The BAI must fund training programs and hire international experts. Fans see the gap widening; Denmark’s coaches outclass ours. Without investment, India’s medal hopes fade. Can the system step up, or will talent go to waste? The clock’s ticking for badminton’s future.",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["SPORTS", "BADMINTON"]
    },
    {
        "title": "Indian Women Dominate Global Badminton Scene",
        "content": "Indian women like Sindhu and Saina are ruling badminton. Sindhu’s Malaysia Open title and Malvika Bansod’s upset over a top seed were epic. X is cheering—#WomenInBadminton is trending. Their power and precision stun rivals, but media focuses on male cricketers. The BAI must promote them better; they’re role models. Injuries are a concern—the sport’s brutal. Fans want more sponsorships for women’s events. Can India’s women keep dominating? Their grit’s unmatched, and the world’s taking notice. Let’s amplify their shine.",
        "previewImage": "https://images.unsplash.com/photo-1622270396078-c2db2e252d3b",
        "topics": ["SPORTS", "BADMINTON"]
    },
    {
        "title": "Sports Education Needs Reform in India",
        "content": "India’s school sports programs are a mess. Badminton’s popular, but most schools lack courts or coaches. X parents are vocal—#SportsInSchools is trending. Cricket gets funds, while others scrape by. Khelo India’s a start, but rural schools get nothing. Urban kids have clubs, but costs are high. Fans want mandatory sports hours and free academies. Talent’s everywhere—look at Chirag Shetty—but access isn’t. Can India make sports a right, not a privilege? The potential’s massive, but the system’s failing kids.",
        "previewImage": "https://images.unsplash.com/photo-1569172122309-bc25d0109709",
        "topics": ["SPORTS", "INDIA"]
    },
    {
        "title": "Summer Heat Disrupts Badminton Training",
        "content": "India’s summer heat is killing badminton training. Temperatures hit 42°C, and courts feel like ovens. A player fainted during practice last week. X athletes are frustrated—#CoolCourtsNow is trending. The BAI’s slow to install AC or shift schedules. Hydration breaks aren’t cutting it; health risks are real. Cricket stadiums get upgrades—badminton’s ignored. Fans want action before injuries spike. India’s hosting BWF events; this can’t continue. Can facilities adapt, or will players keep frying? The sport’s growth demands better conditions yesterday.",
        "previewImage": "https://images.unsplash.com/photo-1622310409315-85f92de6b7a6",
        "topics": ["WEATHER", "SPORTS"]
    },
    {
        "title": "Badminton’s Global Appeal Continues to Grow",
        "content": "Badminton’s global rise is unstoppable. Asia dominates, but Europe’s catching up—Denmark’s Axelsen is a beast. X fans love the diversity—#BadmintonWorld is trending. India’s stars like Sindhu keep the flag high, but China’s depth is scary. The sport’s fast, accessible, and thrilling, drawing millions. Prize money’s growing, but still lags tennis. Fans want bigger stages and TV deals. The BWF’s pushing for Olympic hype, but grassroots need love. Can badminton rival football’s popularity? The momentum’s there, and the future’s electric.",
        "previewImage": "https://images.unsplash.com/photo-1630524706760-067c1308e27c",
        "topics": ["SPORTS", "BADMINTON"]
    },
    {
        "title": "Election Promises Fail India’s Sports Scene",
        "content": "Every election, parties promise sports funding, but deliver crumbs. Badminton’s growth—thanks to stars like Sindhu—happens despite them. X fans are fed up—#FundSports is trending. Cricket’s flush, while others beg. The ‘Khelo India’ scheme’s underfunded; rural kids get nothing. Politicians flaunt photo-ops at IPL, ignoring real needs. Fans demand audits and action—where’s the money? Without reform, India’s losing medals. Can leaders prioritize sports over votes? Badminton shows what’s possible with support. It’s time to deliver, not just talk.",
        "previewImage": "https://images.unsplash.com/photo-1526378722484-cc5e4d5b2c4d",
        "topics": ["POLITICS", "INDIA"]
    },
    {
        "title": "Sindhu’s Mental Toughness Inspires a Generation",
        "content": "PV Sindhu’s mental strength is unreal. Her comeback in the BWF Finals, down two games, was epic—pure grit. X is in awe—#SindhuStrong is trending. She trains like a machine, but her focus in clutch moments sets her apart. Young players look up to her, but India’s coaching can’t match her drive. The BAI must hire world-class mentors to nurture talent. Fans want her leading India to gold in 2028. Can she keep inspiring? Her story’s pushing kids to pick up rackets. Sindhu’s a national treasure, and her legacy’s growing.",
        "previewImage": "https://images.unsplash.com/photo-1622270396078-c2db2e252d3b",
        "topics": ["SPORTS", "BADMINTON"]
    },
    {
        "title": "Badminton’s Rise in Rural India",
        "content": "Badminton’s exploding in India’s villages. Kids play on makeshift courts, dreaming of Sindhu’s glory. X is buzzing—#RuralBadminton is trending. But there’s no infrastructure—coaches, gear, or proper courts are rare. Khelo India’s urban-focused, leaving rural talent stranded. Fans want mobile academies and free equipment drives. Success stories like Chirag Shetty show what’s possible, but they’re exceptions. The BAI must prioritize villages to find the next star. Can India tap this potential? The passion’s there, but the system’s failing these kids. Let’s build courts where dreams can soar.",
        "previewImage": "https://images.unsplash.com/photo-1569172122309-bc25d0109709",
        "topics": ["SPORTS", "INDIA"]
    },
    {
        "title": "BWF’s Scheduling Hurts Player Longevity",
        "content": "The BWF’s relentless schedule is brutal. Players like Sindhu play 10 tournaments yearly, risking burnout and injuries. X fans are worried—#ProtectPlayers is trending. Badminton’s physical toll—jumps, dives—is insane, yet rest periods are short. Top stars skip events to recover, but lower-ranked players can’t afford to. The BAI should push for fewer mandatory tournaments. Fans want their heroes healthy, not hobbling. China’s depth lets them rotate players; India can’t. Can the BWF balance revenue and welfare? Players are humans, not machines. Reform’s overdue.",
        "previewImage": "https://images.unsplash.com/photo-1630524706760-067c1308e27c",
        "topics": ["SPORTS", "BADMINTON"]
    }
]

# Send POST requests
for i, post in enumerate(posts, start=1):
    response = requests.post(URL, json=post, headers=HEADERS)
    if response.status_code == 201:
        print(f"[{i}] ✅ Post '{post['title']}' created successfully.")
    else:
        print(f"[{i}] ❌ Failed to create post '{post['title']}': {response.status_code} - {response.text}")
