#!/bin/bash

PORT=8000
URL="http://localhost:$PORT"

echo "Starting server on $URL..."

# Открыть браузер
if command -v xdg-open >/dev/null 2>&1; then
    xdg-open "$URL"
elif command -v open >/dev/null 2>&1; then
    open "$URL"
fi

python3 -m http.server "$PORT"
