from fastapi import APIRouter
from app.services import trakt_api, tmdb_api

router = APIRouter()

@router.get("/trending")
def trending_shows():
    return trakt_api.get_trending_shows()

@router.get("/movie/{tmdb_id}")
def movie_info(tmdb_id: int):
    return tmdb_api.get_movie(tmdb_id)
