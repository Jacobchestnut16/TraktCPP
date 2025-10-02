from fastapi import APIRouter
from app.services import trakt_api, tmdb_api

router = APIRouter()

@router.get("/history")
def sync_history():
    return trakt_api.sync_history()
