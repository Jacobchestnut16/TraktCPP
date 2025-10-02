from fastapi import APIRouter
from app.services import trakt_api

router = APIRouter()

@router.get("/details")
def user_details():
    return trakt_api.retrieve_settings()

