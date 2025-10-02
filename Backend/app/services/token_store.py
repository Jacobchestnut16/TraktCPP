import sqlite3
import json
from app.utils import config
from pathlib import Path

db_path = Path(config.DATABASE_URL.replace("sqlite:///", ""))

class TokenStore:
    def __init__(self):
        db_path.parent.mkdir(parents=True, exist_ok=True)
        self.conn = sqlite3.connect(str(db_path), check_same_thread=False)
        self._init()

    def _init(self):
        cur = self.conn.cursor()
        cur.execute("""CREATE TABLE IF NOT EXISTS tokens (
                       id INTEGER PRIMARY KEY,
                       payload TEXT NOT NULL
                       )""")
        self.conn.commit()

    def save_token(self, payload: dict):
        cur = self.conn.cursor()
        cur.execute("DELETE FROM tokens")
        cur.execute("INSERT INTO tokens(payload) VALUES(?)", (json.dumps(payload),))
        self.conn.commit()

    def get_token(self) -> dict | None:
        cur = self.conn.cursor()
        cur.execute("SELECT payload FROM tokens LIMIT 1")
        row = cur.fetchone()
        if not row:
            return None
        return json.loads(row[0])
