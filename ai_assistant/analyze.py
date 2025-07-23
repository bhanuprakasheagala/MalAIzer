import os
import sys
import json
import re
import argparse
from datetime import datetime
from prompt_builder import build_prompt_from_artifacts

# Model selector
def select_model(model_name):
    if model_name == "ollama":
        from ollama_client import call_llama3 as call_ai
    elif model_name == "openrouter":
        from openrouter_client import call_openrouter_mistral as call_ai
    else:
        print(f"[ERROR] Unsupported model: {model_name}")
        sys.exit(1)
    return call_ai

def postprocess_summary(text: str) -> str:
    text = re.sub(r'\*\*(.*?)\*\*', r'\1', text)
    text = re.sub(r'(?i)^([A-Za-z ]+):\s*$', r'\1:\n' + '-' * 40, text, flags=re.MULTILINE)
    return text.strip()

# --- CLI Argument Parsing ---
parser = argparse.ArgumentParser(description="Analyze PE artifacts using GenAI")
parser.add_argument("json_path", help="Path to PE artifact JSON")
parser.add_argument("--model", choices=["ollama", "openrouter"], default="ollama", help="LLM backend")
parser.add_argument("--print", action="store_true", help="Also print summary to console")

args = parser.parse_args()

# Load JSON
with open(args.json_path, 'r') as f:
    data = json.load(f)

# Generate prompt
prompt = build_prompt_from_artifacts(data)

# Choose and call model
call_ai = select_model(args.model)
response = call_ai(prompt)
cleaned_summary = postprocess_summary(response)

# Generate timestamped output filename
timestamp = datetime.now().strftime("%Y-%m-%dT%H-%M-%S")
base_filename = os.path.splitext(os.path.basename(args.json_path))[0]
summary_path = os.path.join("responses", f"{base_filename}_summary_{timestamp}.txt")
os.makedirs("responses", exist_ok=True)

# Save summary to file
with open(summary_path, 'w') as f:
    f.write(cleaned_summary)

# if args.print:
#     print("\n== AI Summary ==\n")
#     print(cleaned_summary)

print(f"✔ AI summary saved to: {summary_path}")
