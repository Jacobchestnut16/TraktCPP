import requests
from app.utils import config

BASE_URL = "https://api.themoviedb.org/3"

def get_movie(movie_id: int):
    url = f"{BASE_URL}/movie/{movie_id}"
    params = {"api_key": config.TMDB_API_KEY}
    resp = requests.get(url, params=params)
    resp.raise_for_status()
    return resp.json()
