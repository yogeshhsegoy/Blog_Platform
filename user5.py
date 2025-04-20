import requests

# URL and headers
URL = "http://localhost:8082/api/blogs"
HEADERS = {
    "Content-Type": "application/json",
    "Authorization": "Bearer eyJhbGciOiJIUzI1NiJ9.eyJ0b3BpY3MiOlsiRk9PVEJBTEwiLCJTUE9SVFMiLCJVU0EiXSwic3ViIjoicHJpeWFfc2hhcm1hIiwiaWF0IjoxNzQ1MTg0MTYzLCJleHAiOjE3NDUyNzA1NjN9.Lk0DVS-E9oUhxjLWo5r9KszQnJuQGvaWVWI6uebXi5Y"  # Replace with your actual token
}

# List of posts
posts = [
    {
        "title": "USA’s Polarized Politics Hits New Lows",
        "content": "The USA’s political divide is a circus. Congress can’t pass a budget without weeks of bickering, and X is raging—#USPolitics is trending. Partisan media fuels the fire, with each side spinning narratives. Voters are exhausted; independents feel ignored. Recent polls show 60% want a third party, but the system’s rigged for two. Compromise is a dirty word now. Rural and urban divides deepen, and nobody’s listening. Can leaders bridge this gap, or is gridlock permanent? The 2026 midterms will test patience. Americans deserve better than this endless shouting match.",
        "previewImage": "https://images.unsplash.com/photo-1610901491660-0bd5882c8387",
        "topics": ["POLITICS", "USA"]
    },
    {
        "title": "Russia’s Economic Struggles Amid Global Sanctions",
        "content": "Sanctions are squeezing Russia’s economy, and citizens feel the pinch. Gas prices are up 30%, and imports are scarce. X posts are grim—#RussiaEconomy is trending. The government spins resilience, but small businesses are collapsing. Oligarchs dodge the pain, leaving workers to suffer. Energy exports keep things afloat, but Europe’s pivot to renewables hurts. Putin’s doubling down, but cracks are showing. Ordinary Russians deserve relief, not propaganda. Can the Kremlin adapt, or will isolation deepen? The world’s watching, and the stakes are high for stability.",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["POLITICS", "RUSSIA"]
    },
    {
        "title": "India’s Coalition Government Faces Tough Tests",
        "content": "India’s coalition government is wobbling. Regional parties demand more power, stalling key reforms. X is buzzing—#IndiaPolitics is trending. Economic growth is strong, but farmer protests and unemployment spark unrest. The PM’s charisma holds things together, but allies are fickle. Opposition smells blood, pushing divisive narratives. Rural voters feel ignored, while urban elites dominate policy. Transparency’s lacking—where’s the budget going? Can the coalition deliver, or will it fracture before 2029? India’s democracy is vibrant but messy. Leaders must prioritize unity over egos.",
        "previewImage": "https://images.unsplash.com/photo-1526378722484-cc5e4d5b2c4d",
        "topics": ["POLITICS", "INDIA"]
    },
    {
        "title": "Hurricanes Batter USA’s East Coast Again",
        "content": "Hurricane season’s hitting the USA hard. Florida’s reeling from a Category 4 storm, with $10 billion in damages. X is flooded with updates—#Hurricane2025 is trending. Climate change is making storms fiercer, yet infrastructure’s outdated. Evacuations saved lives, but recovery’s slow. Poor communities suffer most, with FEMA stretched thin. Politicians promise aid, but bureaucracy delays it. Coastal cities need better defenses—levees, not speeches. Can the USA adapt to this new normal? Voters want action, not excuses. The weather’s relentless, and time’s running out.",
        "previewImage": "https://images.unsplash.com/photo-1507525428034-b723cf961d3e",
        "topics": ["WEATHER", "USA"]
    },
    {
        "title": "Russia’s Arctic Ambitions Raise Global Tensions",
        "content": "Russia’s pushing hard into the Arctic, eyeing oil and trade routes. Military bases are popping up, alarming NATO. X is tense—#ArcticRace is trending. Melting ice opens new paths, but environmental risks are huge. Russia claims it’s protecting interests, but neighbors see aggression. Energy grabs could reshape geopolitics, yet spills would be catastrophic. Diplomacy’s failing; the UN’s sidelined. Can nations share the Arctic, or is conflict brewing? Russia’s bold, but the stakes are global. The world needs cooperation, not another cold war.",
        "previewImage": "https://images.unsplash.com/photo-1519750783825-cb0ca6e83417",
        "topics": ["POLITICS", "RUSSIA"]
    },
    {
        "title": "India’s Monsoon Crisis Hits Farmers Hard",
        "content": "India’s monsoon was a disaster this year—40% excess rain flooded crops. Farmers in Punjab lost entire harvests, and X is angry—#MonsoonWoes is trending. Government aid is slow, and insurance covers little. Rural debt’s soaring; suicides are up. Climate shifts make rains erratic, yet irrigation projects stall. Urban India’s barely affected, highlighting inequality. Fans demand fast relief and better forecasting. Can the government deliver, or will farmers keep suffering? India’s food security’s at risk, and reforms are urgent. The countryside needs help now.",
        "previewImage": "https://images.unsplash.com/photo-1534274988757-a28bf1a57c17",
        "topics": ["WEATHER", "INDIA"]
    },
    {
        "title": "USA’s Border Policy Sparks Heated Debates",
        "content": "The USA’s border policy is a lightning rod. Stricter enforcement has cut crossings, but X is divided—#BorderCrisis is trending. Humanitarians decry family separations, while others demand tighter controls. Smuggling’s up, exploiting legal gaps. Congress is gridlocked; no reform passes. Local communities bear the cost—schools, hospitals strained. Both sides exaggerate, drowning out reason. Can leaders find a humane, secure solution? Voters want results, not rhetoric. The issue’s complex, but empathy and pragmatism could break the stalemate. America’s identity is at stake.",
        "previewImage": "https://images.unsplash.com/photo-1610901491660-0bd5882c8387",
        "topics": ["POLITICS", "USA"]
    },
    {
        "title": "Russia’s Media Crackdown Stifles Free Speech",
        "content": "Russia’s tightening its grip on media. Independent outlets face fines or shutdowns, and journalists are fleeing. X is vocal—#FreeSpeechRussia is trending. State propaganda dominates, shaping public opinion. Citizens risk arrest for sharing ‘fake news.’ The internet’s censored, but VPNs keep dissent alive. Global condemnation grows, but Putin’s unfazed. Free expression’s dying, and truth’s the casualty. Can Russians reclaim their voice, or is silence permanent? The world’s watching, but sanctions aren’t enough. Courageous reporters deserve support, not exile.",
        "previewImage": "https://images.unsplash.com/photo-1526378722484-cc5e4d5b2c4d",
        "topics": ["POLITICS", "RUSSIA"]
    },
    {
        "title": "India’s Urbanization Strains Water Resources",
        "content": "India’s cities are choking on growth. Bangalore’s water shortage left millions scrambling this summer. X is alarmed—#WaterCrisis is trending. Lakes are drying, and groundwater’s overpumped. Monsoons help, but mismanagement wastes them. Rural areas lose out as cities hoard. The government’s ‘Smart Cities’ plan ignores basics like water infrastructure. Residents queue for tankers, while elites buy private supplies. Can India balance urban boom and sustainability? Policy needs teeth—fast. The crisis is here, and millions are parched.",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["WEATHER", "INDIA"]
    },
    {
        "title": "USA’s Tech Regulation Efforts Face Pushback",
        "content": "The USA’s cracking down on Big Tech, but it’s messy. Antitrust suits against Google and Meta drag on, and X is split—#TechRegulation is trending. Consumers want privacy, but companies cry innovation’s at risk. Lobbyists flood Capitol Hill, slowing progress. Small startups suffer, caught in the crossfire. Europe’s GDPR sets a model, but America’s too divided for bold laws. Can regulators tame tech giants without killing growth? Users deserve control over their data. The fight’s just starting, and the outcome shapes our digital future.",
        "previewImage": "https://images.unsplash.com/photo-1516321318423-f06f85e504b3",
        "topics": ["POLITICS", "USA"]
    },
    {
        "title": "Russia’s Youth Protest Government Policies",
        "content": "Russia’s youth are fed up. Protests against censorship and conscription are growing, despite crackdowns. X is alive with their voices—#RussiaYouth is trending. Students face jail for speaking out, but social media keeps them connected. The regime calls them traitors, but they want freedom, not war. Economic woes fuel their anger; jobs are scarce. Older generations are split—some admire, some condemn. Can this generation shift Russia’s path? Their courage is inspiring, but the risks are real. The world’s rooting for change.",
        "previewImage": "https://images.unsplash.com/photo-1560272564-c83b99b6c9c9",
        "topics": ["POLITICS", "RUSSIA"]
    },
    {
        "title": "India’s Education Reform Faces Resistance",
        "content": "India’s new education policy is ambitious, but teachers and states are pushing back. X is debating—#EducationReform is trending. The focus on skills over rote learning is great, but rural schools lack funds to implement it. Urban elites benefit, widening gaps. Teachers strike over workload, and states want local control. The government’s rushing, ignoring ground realities. Students deserve better—half drop out before 10th grade. Can India overhaul its schools, or will politics stall progress? Education’s the future, but the fight’s messy.",
        "previewImage": "https://images.unsplash.com/photo-1569172122309-bc25d0109709",
        "topics": ["POLITICS", "INDIA"]
    },
    {
        "title": "USA’s Wildfires Highlight Climate Urgency",
        "content": "California’s wildfires are apocalyptic. Over 500,000 acres burned this year, displacing thousands. X is sharing harrowing stories—#WildfireCrisis is trending. Climate change fuels longer, fiercer fire seasons, but prevention lags. Budgets for forest management are tiny, and insurers are bailing. Communities rebuild, only to burn again. Politicians bicker over green policies while homes vanish. Can the USA get serious about climate? Voters demand action—renewables, not promises. The West’s on fire, and time’s running out to adapt.",
        "previewImage": "https://images.unsplash.com/photo-1622310409315-85f92de6b7a6",
        "topics": ["WEATHER", "USA"]
    },
    {
        "title": "Russia’s Energy Leverage Worries Europe",
        "content": "Russia’s gas cuts have Europe scrambling. Prices are up 40%, and winter’s coming. X is nervous—#EnergyCrisis is trending. Moscow’s using energy as a weapon, punishing sanctions. Europe’s diversifying, but LNG imports can’t fill the gap fast. Households face brutal bills, and factories are slowing. Russia’s budget thrives, but long-term losses loom as buyers pivot. Can Europe break this dependency? Diplomacy’s weak, and renewables aren’t ready. The continent’s in a bind, and Russia’s playing hardball.",
        "previewImage": "https://images.unsplash.com/photo-1519750783825-cb0ca6e83417",
        "topics": ["POLITICS", "RUSSIA"]
    },
    {
        "title": "India’s Heatwaves Strain Power Grids",
        "content": "India’s summer heatwaves are relentless. Delhi hit 49°C, triggering blackouts as grids collapsed. X is frustrated—#HeatwaveIndia is trending. Coal plants can’t keep up, and renewables lag. Rural areas suffer most; farmers lose irrigation. The government promises upgrades, but funds vanish into corruption. Urban AC use spikes, worsening shortages. Climate adaptation—solar, storage—is urgent, but policy’s slow. Can India keep the lights on? Citizens demand accountability, not excuses. The heat’s a wake-up call, and action’s overdue.",
        "previewImage": "https://images.unsplash.com/photo-1622310409315-85f92de6b7a6",
        "topics": ["WEATHER", "INDIA"]
    },
    {
        "title": "USA’s Gun Control Debate Rages On",
        "content": "Another mass shooting, another stalemate. The USA’s gun laws are stuck, with 300 incidents this year. X is grieving—#GunControlNow is trending. Proponents want background checks; opponents cling to Second Amendment rights. Both sides dig in, ignoring common ground. Schools drill for shootings, normalizing fear. Rural and urban voters split, paralyzing Congress. Can compromise happen, or is tragedy the norm? Families demand change, but lobbying drowns them out. The issue’s a wound, and America’s bleeding.",
        "previewImage": "https://images.unsplash.com/photo-1610901491660-0bd5882c8387",
        "topics": ["POLITICS", "USA"]
    },
    {
        "title": "Russia’s Military Moves Spark Global Alarm",
        "content": "Russia’s troop buildup near borders is rattling nerves. Satellite images show tanks, and NATO’s on alert. X is anxious—#RussiaTensions is trending. The Kremlin calls it routine, but neighbors fear escalation. Sanctions haven’t deterred; Putin’s playing to domestic hardliners. Diplomacy’s stalled, with talks collapsing. Global markets wobble—oil’s up 5%. Can war be avoided, or is conflict inevitable? The world’s holding its breath, and Russia’s moves dictate the next chapter. Peace feels fragile, and trust is scarce.",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["POLITICS", "RUSSIA"]
    },
    {
        "title": "India’s Startup Boom Faces Policy Hurdles",
        "content": "India’s startups are thriving—unicorns doubled in 2024. But red tape strangles growth. X founders are vocal—#StartupIndia is trending. Tax laws are murky, and funding’s urban-centric. Rural innovators get ignored, despite huge potential. The government’s ‘Digital India’ push helps, but bureaucracy slows approvals. Global investors eye India, but policy clarity’s missing. Can India rival Silicon Valley? The talent’s there, but governance lags. Entrepreneurs need freedom, not forms. The boom’s real, but it’s fragile without reforms.",
        "previewImage": "https://images.unsplash.com/photo-1569172122309-bc25d0109709",
        "topics": ["POLITICS", "INDIA"]
    },
    {
        "title": "USA’s Infrastructure Woes Threaten Growth",
        "content": "The USA’s bridges and roads are crumbling. A recent highway collapse cost millions. X is fed up—#FixOurRoads is trending. Federal funds are stuck in partisan fights, leaving states to scrape by. Public transit’s a joke outside big cities. China’s building high-speed rails while America patches potholes. Climate-proofing—storm drains, levees—is urgent, but budgets are tight. Can Congress prioritize infrastructure, or will decay win? Voters want safe commutes, not excuses. The nation’s backbone needs fixing now.",
        "previewImage": "https://images.unsplash.com/photo-1565118535070-4c3ab6b2c2c2",
        "topics": ["POLITICS", "USA"]
    },
    {
        "title": "India’s Air Pollution Crisis Demands Action",
        "content": "Delhi’s AQI hit 500, choking residents. Schools shut, and hospitals are packed. X is desperate—#CleanAirIndia is trending. Stubble burning and traffic are culprits, but policy’s stuck. Green tech—EVs, filters—exists, but adoption’s slow. Rural farmers need alternatives, not fines. Urban planning’s a mess; green spaces vanish. The government’s ‘Clean India’ rhetoric lacks funds. Can India breathe again, or is smog the future? Citizens demand accountability—health’s at stake. The crisis is now, and solutions can’t wait.",
        "previewImage": "https://images.unsplash.com/photo-1600585154340-be6161a56a0c",
        "topics": ["WEATHER", "INDIA"]
    }
]

# Send POST requests
for i, post in enumerate(posts, start=1):
    response = requests.post(URL, json=post, headers=HEADERS)
    if response.status_code == 201:
        print(f"[{i}] ✅ Post '{post['title']}' created successfully.")
    else:
        print(f"[{i}] ❌ Failed to create post '{post['title']}': {response.status_code} - {response.text}")
