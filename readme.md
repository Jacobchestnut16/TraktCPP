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
Create a config.json or copy the example-config to config.json file at:`config/config.json`
Add your credentials:
```

{
  "client_id"     : "TraktClientID",
  "client_secret" : "TraktClientSecret",
  "tmdb_bearer"   : "TMDBAPIReadAccessToken"
}
```
* An example-config.json is preloaded as a base template.
* Neither api requires a purchase but Trakt VIP is recommended
    * [trakt website](https://www.trakt.tv)
    * [tmdb website](https://www.themoviedb.org)
___
# Running the App

### Install docker

Docker Desktop:

* [Mac](https://docs.docker.com/desktop/setup/install/mac-install/)
* [Windoes](https://docs.docker.com/desktop/setup/install/windows-install/)
* [Linux](https://docs.docker.com/desktop/setup/install/linux/)

[Docker Engin (For Linux instead of Docker Desktop)](https://docs.docker.com/engine/install/)

### Run docker

From the root of the apps directory there is a `docker-compose` file cd to the direcotry containning this file and run:
```
docker compose up -d
```
older versions of docker
```
docker-compose up -d
```

# configuring the compose file
```
services:
  backend:
    build: ./backend #Backend project dircotry
    container_name: trakt_backend
    ports:
      - "3001:8080" #The backend uses port 8080, 3001 is the port the frontend looks up. recomended to not change
    volumes:
      - ./backend/config:/app/config:ro #The config file
    environment:
      - ENV=production
      - CONFIG_PATH=/app/config/config.json #The location of the configfile for the backend to lookup


  frontend:
    build: ./frontend
    container_name: trakt_frontend
    ports:
      - "3000:80" #NGINX runs 80 for the frontend change 3000 if you need a different port on your host
    depends_on:
      - backend
```

# API endpoints

This app comes with a secondary api that the front end uses, but this api is also exposed to the host. This means you can queary and use the api too.

### Query options
#### Individual option
```
http://localhost:3001/api/[endpoint]/[option]
```
#### All options
```
http://localhost:3001/api/[endpoint]
```

### Endpoints list
```
{
    "/api/most_played":
    {
        "/api/most_played":"both",
        "/api/most_played/movies":"movies",
        "/api/most_played/shows":"shows",
        "name":"most_played"
    },
    "/api/most_watched":
    {
        "/api/most_watched":"both",
        "/api/most_watched/movies":"movies",
        "/api/most_watched/shows":"shows",
        "name":"most_watched"
    },
    "/api/popular":
    {
        "/api/popular":"both",
        "/api/popular/movies":"movies",
        "/api/popular/shows":"shows",
        "name":"popular"
    },
    "/api/top_rated":
    {
        "/api/top_rated":"both",
        "/api/top_rated/movies":"movies",
        "/api/top_rated/shows":"shows",
        "name":"top_rated"
    },
    "/api/upcoming":
    {
        "/api/upcoming":"both",
        "/api/upcoming/in_theaters":in_theaters",
        "/api/upcoming/unreleased":"unreleased",
        "name":"upcoming"
    }
}
```


#### Future endpoints

    // recommended → user-personalized picks.
    // upcoming → unreleased but scheduled.
    // underrated → high ratings but low watch counts.
    // todo: get films watched or get individuals top high rated film
    // todo: use to get recommended and grab high rated films
    // todo: add a threshold if there aren't enough low watch counts with high ratings drop (add to a drop json before dropping)
    // todo: finally if the list is under 10 films re-add random drops to fulfill this list
    // similar → items related to a given movie/show.
    // history → user’s watch log.
    // analytics → aggregated stats like avg rating, completion %, binge patterns.
    // curated → from all watch lists get 3-6 recommendations per film
    // todo: get a combined list of all watchlist' data
    // todo: get 3-6 recommendations per film based on rating 3 no rating 6 highest rating
    // todo: propose: considerations to shorten the list [newest films, most popular, oldest films]