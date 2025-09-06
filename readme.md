# Trakt Plus
Trakt Plus is an extension app designed to improve the Trakt experience by enhancing recommendations and analytics. It integrates TMDB to counterbalance Trakt’s tendency to deliver repetitive or poorly rated recommendations. Instead of the common "flat curve" where the same shows or movies are repeated, Trakt Plus diversifies and personalizes content discovery.

## Features
* Recommended → Personalized picks tailored to the user.
* Upcoming → Movies and shows scheduled but not yet released.
* Underrated → Highly rated titles with low watch counts.
* Similar → Content related to a given movie or show.
* History → Full watch log tracking.
* Analytics → Aggregated statistics (average ratings, completion %, * binge patterns).
* Curated → Pulls recommendations across all watchlists (3–6 per film * based on ratings).
## Planned Enhancements
* Fetch top-rated films for each user.
* Improved recommendation filters with rating and watch-count thresholds.
* Fallback logic for short lists (random drops if <10 items).
* Combined multi-watchlist recommendations with rating-based prioritization.
* Considerations for list shortening (e.g., newest, most popular, oldest).
* Docker setup to simplify configuration and deployment.
___
# Setup
Create a config.json or copy the example-config to config.json file at:`traktplus/backend/config/config.json`
Add your credentials:
```

{
  "client_id"     : "TraktClientID",
  "client_secret" : "TraktClientSecret",
  "tmdb_bearer"   : "TMDBAPIReadAccessToken",
  "host"          : "0.0.0.0",
  "port"          : 8080
}
```
* Use 0.0.0.0 for both internal and external access.
* Default port is 8080. Changing it requires extra frontend setup.
* An example-config.json is preloaded as a base template.
* Neither api requires a purchase but Trakt VIP is recommended
    * [trakt website](https://www.trakt.tv)
    * [tmdb website](https://www.themoviedb.org)
___
# Running the App
### Backend (C++)
Build and run the C++ backend from the `traktplus/backend` directory.
### Frontend (React + Vite)
From the `traktplus/frontend` directory:
```
npm run dev
```
This will start the frontend in development mode.