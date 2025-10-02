import time
import requests
from typing import Optional
from app.utils import config
from app.services.token_store import TokenStore

BASE = "https://api.trakt.tv"
AUTH_URL = "https://trakt.tv/oauth/authorize"

store = TokenStore()

def build_auth_url(state: str):
    redirect = f"{config.APP_HOST}/auth/callback"
    return (f"{AUTH_URL}?response_type=code&client_id={config.TRAKT_CLIENT_ID}"
            f"&redirect_uri={redirect}&state={state}")

def exchange_code_for_token(code: str) -> dict:
    url = f"{BASE}/oauth/token"
    payload = {
        "code": code,
        "client_id": config.TRAKT_CLIENT_ID,
        "client_secret": config.TRAKT_CLIENT_SECRET,
        "redirect_uri": f"{config.APP_HOST}/auth/callback",
        "grant_type": "authorization_code"
    }
    resp = requests.post(url, json=payload, timeout=10)
    resp.raise_for_status()
    data = resp.json()
    data["obtained_at"] = int(time.time())
    store.save_token(data)
    return data

def refresh_token_if_needed() -> dict:
    token = store.get_token()
    if not token:
        raise RuntimeError("no token")
    expires_in = token.get("expires_in", 0)
    obtained = token.get("obtained_at", 0)
    if int(time.time()) < obtained + expires_in - 60:
        return token
    # refresh
    url = f"{BASE}/oauth/token"
    payload = {
        "refresh_token": token["refresh_token"],
        "client_id": config.TRAKT_CLIENT_ID,
        "client_secret": config.TRAKT_CLIENT_SECRET,
        "redirect_uri": f"{config.APP_HOST}/auth/callback",
        "grant_type": "refresh_token"
    }
    resp = requests.post(url, json=payload, timeout=10)
    resp.raise_for_status()
    data = resp.json()
    data["obtained_at"] = int(time.time())
    store.save_token(data)
    return data
