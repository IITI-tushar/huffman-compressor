const sqlite3 = require('sqlite3').verbose();
const path = require('path');

const dbPath = path.resolve(__dirname, 'history.db');
const db = new sqlite3.Database(dbPath, (err) => {
    if (err) console.error("Database connection error:", err.message);
});

db.serialize(() => {
    db.run(`CREATE TABLE IF NOT EXISTS compression_history (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        filename TEXT,
        action TEXT,
        original_size INTEGER,
        final_size INTEGER,
        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
    )`);
});

module.exports = db;
