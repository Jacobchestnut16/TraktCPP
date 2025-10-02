import requests
from app.utils import config

BASE_URL = "https://api.trakt.tv"

HEADERS = {
    "Content-Type": "application/json",
    "trakt-api-key": config.TRAKT_CLIENT_ID,
    "trakt-api-version": "2"
}

def get_trending_shows():
    url = f"{BASE_URL}/shows/trending"
    resp = requests.get(url, headers=HEADERS)
    resp.raise_for_status()
    return resp.json()
