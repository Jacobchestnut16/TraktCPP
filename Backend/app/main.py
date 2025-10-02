from fastapi import FastAPI
from app.routes import auth, media

def create_app():
    app = FastAPI(title="Trakt Backend", version="0.1")

    # include routes
    app.include_router(auth.router, prefix="/auth", tags=["auth"])
    app.include_router(media.router, prefix="/media", tags=["media"])

    return app

app = create_app()
