let currentAction = 'compress';

const fileInput = document.getElementById('fileInput');
const fileName = document.getElementById('fileName');
const uploadForm = document.getElementById('uploadForm');
const statusSection = document.getElementById('statusSection');
const statusText = document.getElementById('statusText');
const historyTable = document.querySelector('#historyTable tbody');

fileInput.addEventListener('change', (e) => {
    if (e.target.files.length > 0) {
        fileName.textContent = e.target.files[0].name;
        fileName.style.color = '#27ae60';
    } else {
        fileName.textContent = 'No file selected';
        fileName.style.color = '#7f8c8d';
    }
});

function setAction(action) {
    currentAction = action;
}

uploadForm.addEventListener('submit', async (e) => {
    e.preventDefault();

    const files = fileInput.files;
    if (files.length === 0) {
        alert('Please select a file');
        return;
    }

    const formData = new FormData();
    formData.append('file', files[0]);
    formData.append('action', currentAction);

    statusSection.style.display = 'block';
    statusText.textContent = currentAction === 'compress'
        ? '📦 Compressing your file...'
        : '📂 Decompressing your file...';

    try {
        const response = await fetch('http://localhost:3000/api/process', {
            method: 'POST',
            body: formData
        });

        if (response.ok) {
            const blob = await response.blob();
            const url = window.URL.createObjectURL(blob);
            const a = document.createElement('a');
            a.href = url;
            a.download = `processed_${files[0].name}${currentAction === 'compress' ? '.huff' : '.txt'}`;
            document.body.appendChild(a);
            a.click();
            window.URL.revokeObjectURL(url);
            document.body.removeChild(a);

            statusText.textContent = '✅ File processed successfully!';
            setTimeout(() => {
                statusSection.style.display = 'none';
                fileInput.value = '';
                fileName.textContent = 'No file selected';
                fileName.style.color = '#7f8c8d';
            }, 2000);

            await loadHistory();
        } else {
            statusText.textContent = '❌ Error processing file. Please try again.';
            statusText.style.color = '#e74c3c';
            setTimeout(() => {
                statusSection.style.display = 'none';
            }, 3000);
        }
    } catch (err) {
        console.error(err);
        statusText.textContent = '❌ Connection error. Make sure the backend is running on http://localhost:3000';
        statusText.style.color = '#e74c3c';
        setTimeout(() => {
            statusSection.style.display = 'none';
        }, 3000);
    }
});

async function loadHistory() {
    try {
        const res = await fetch('http://localhost:3000/api/history');
        const history = await res.json();

        historyTable.innerHTML = '';

        if (history.length === 0) {
            historyTable.innerHTML = '<tr class="empty-row"><td colspan="5">No compression history yet</td></tr>';
            return;
        }

        history.forEach(row => {
            const tr = document.createElement('tr');
            let ratio = 'N/A';
            let ratioClass = '';

            if (row.action === 'compress') {
                const reduction = ((1 - row.final_size / row.original_size) * 100).toFixed(2);
                ratio = `${reduction}%`;
                ratioClass = reduction > 0 ? 'positive' : 'negative';
            }

            const originalSizeStr = formatSize(row.original_size);
            const finalSizeStr = formatSize(row.final_size);

            tr.innerHTML = `
                <td>${truncateFilename(row.filename)}</td>
                <td>${row.action.toUpperCase()}</td>
                <td>${originalSizeStr}</td>
                <td>${finalSizeStr}</td>
                <td class="${ratioClass}">${ratio}</td>
            `;
            historyTable.appendChild(tr);
        });
    } catch (err) {
        console.error('Failed to load history:', err);
    }
}

function formatSize(bytes) {
    if (bytes === 0) return '0 B';
    const k = 1024;
    const sizes = ['B', 'KB', 'MB', 'GB'];
    const i = Math.floor(Math.log(bytes) / Math.log(k));
    return Math.round((bytes / Math.pow(k, i)) * 100) / 100 + ' ' + sizes[i];
}

function truncateFilename(filename, maxLength = 25) {
    if (filename.length > maxLength) {
        return filename.substring(0, maxLength - 3) + '...';
    }
    return filename;
}

loadHistory();
setInterval(loadHistory, 5000);
