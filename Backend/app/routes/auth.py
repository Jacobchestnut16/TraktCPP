from fastapi import APIRouter, Request, HTTPException
from fastapi.responses import RedirectResponse
from app.services import trakt_oauth

router = APIRouter()

@router.get("/login")
def login(state: str = "state"):
    url = trakt_oauth.build_auth_url(state)
    return RedirectResponse(url)

@router.get("/callback")
def callback(request: Request, code: str = None, state: str = None):
    if not code:
        raise HTTPException(status_code=400, detail="missing code")
    token = trakt_oauth.exchange_code_for_token(code)
    return {"status": "ok", "token": {"access_token": token.get("access_token"), "expires_in": token.get("expires_in")}}

@router.get("/token")
def token():
    token = trakt_oauth.refresh_token_if_needed()
    return token
