from dotenv import load_dotenv
import os

load_dotenv()

TRAKT_CLIENT_ID = os.getenv("TRAKT_CLIENT_ID")
TRAKT_CLIENT_SECRET = os.getenv("TRAKT_CLIENT_SECRET")
TMDB_API_KEY = os.getenv("TMDB_API_KEY")