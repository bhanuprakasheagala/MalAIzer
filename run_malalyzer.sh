#!/bin/bash

set -e

# --- Input Validation ---
if [ $# -lt 1 ]; then
  echo "Usage: $0 <path_to_PE_file> [--model ollama|openrouter]"
  exit 1
fi

PE_FILE="$1"
MODEL="ollama"  # Default

# Optional: Check for model argument
if [[ "$2" == "--model" && -n "$3" ]]; then
  MODEL="$3"
  if [[ "$MODEL" != "ollama" && "$MODEL" != "openrouter" ]]; then
    echo "[ERROR] Invalid model: $MODEL"
    echo "Supported models: ollama, openrouter"
    exit 1
  fi
fi

# --- Step 1: Build the C++ tool ---
echo "[+] Building extractor..."
./build_cpp.sh

# --- Step 2: Extract artifacts ---
OUTPUT_DIR="extractor/build/outputs"
mkdir -p "$OUTPUT_DIR"

echo "[+] Extracting PE artifacts from: $PE_FILE"
./extractor/build/malalyzer "$PE_FILE"

# --- Step 3: Prepare input for AI assistant ---
BASENAME=$(basename "$PE_FILE" | cut -d. -f1)
JSON_FILE="$OUTPUT_DIR/${BASENAME}_artifacts.json"

if [[ ! -f "$JSON_FILE" ]]; then
  echo "[ERROR] JSON output not found: $JSON_FILE"
  exit 1
fi

# --- Step 4: Run AI assistant ---
echo "[+] Running AI Assistant using model: $MODEL"
python3 ai_assistant/analyze.py "$JSON_FILE" --model "$MODEL"
