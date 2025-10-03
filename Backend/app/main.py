from fastapi import FastAPI
from app.routes import auth, media, user, sync

def create_app():
    app = FastAPI(title="Film Finder", version="0.1")

    # include routes
    app.include_router(auth.router, prefix="/auth", tags=["Auth"])
    app.include_router(media.router, prefix="/media", tags=["Media"])
    app.include_router(sync.router, prefix="/sync", tags=["Sync"])

    app.include_router(user.router, prefix="/user", tags=["User"])

    return app

app = create_app()
