from dotenv import load_dotenv
import os


load_dotenv()

TRAKT_CLIENT_ID = os.getenv("TRAKT_CLIENT_ID")
TRAKT_CLIENT_SECRET = os.getenv("TRAKT_CLIENT_SECRET")
TMDB_API_KEY = os.getenv("TMDB_API_KEY")
APP_HOST = os.getenv("APP_HOST")

print("INFO: Config loaded, OK"
      if
      TRAKT_CLIENT_SECRET
      and TRAKT_CLIENT_ID
      and TMDB_API_KEY
      and APP_HOST
      else
      "ERROR: Failed to load Config")