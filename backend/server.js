const express = require('express');
const multer = require('multer');
const { exec } = require('child_process');
const path = require('path');
const fs = require('fs');
const cors = require('cors');
const db = require('./database');

const app = express();
app.use(cors());
app.use(express.json());

const upload = multer({ dest: 'uploads/' });

app.post('/api/process', upload.single('file'), (req, res) => {
    const file = req.file;
    const action = req.body.action;

    if (!file) return res.status(400).send('No file uploaded.');

    const inputFile = path.join(__dirname, file.path);
    const ext = action === 'compress' ? '.huff' : '.txt';
    const outputFile = path.join(__dirname, 'uploads', `processed_${file.filename}${ext}`);

    const cppExecutable = path.join(__dirname, '../cpp_core/huffman');

    const command = `${cppExecutable} ${action} ${inputFile} ${outputFile}`;

    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Exec error: ${error}`);
            fs.unlinkSync(inputFile);
            return res.status(500).send('Error processing file.');
        }

        const originalSize = file.size;
        const finalSize = fs.statSync(outputFile).size;

        const stmt = db.prepare(`INSERT INTO compression_history (filename, action, original_size, final_size) VALUES (?, ?, ?, ?)`);
        stmt.run(file.originalname, action, originalSize, finalSize, function(err) {
            res.download(outputFile, `processed_${file.originalname}${ext}`, () => {
                fs.unlinkSync(inputFile);
                fs.unlinkSync(outputFile);
            });
        });
    });
});

app.get('/api/history', (req, res) => {
    db.all(`SELECT * FROM compression_history ORDER BY timestamp DESC LIMIT 10`, [], (err, rows) => {
        if (err) return res.status(500).send(err.message);
        res.json(rows);
    });
});

const PORT = 3000;
app.listen(PORT, () => console.log(`Backend running on http://localhost:${PORT}`));
