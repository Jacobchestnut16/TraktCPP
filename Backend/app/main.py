from fastapi import FastAPI
from app.routes import auth, media, user, sync

def create_app():
    app = FastAPI(title="Trakt Backend", version="0.1")

    # include routes
    app.include_router(auth.router, prefix="/auth", tags=["auth"])
    app.include_router(media.router, prefix="/media", tags=["media"])
    app.include_router(sync.router, prefix="/sync", tags=["sync"])

    app.include_router(user.router, prefix="/user", tags=["user"])

    return app

app = create_app()
