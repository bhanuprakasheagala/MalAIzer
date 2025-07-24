import os
import requests

def call_openrouter_mistral(prompt: str) -> str:
    api_key = os.getenv("OPENROUTER_API_KEY")
    # Ensure the API key is set
    if not api_key:
        return "[ERROR] OPENROUTER_API_KEY not set. Skipping OpenRouter call."

    headers = {
        "Authorization": f"Bearer {api_key}",
        "Content-Type": "application/json",
        "HTTP-Referer": "https://github.com/your-username/malalyzer",  # Optional for analytics
        "X-Title": "MalAIzer Malware Assistant"
    }

    body = {
        "model": "mistralai/mistral-7b-instruct",  # or "mistral/mixtral-8x7b"
        "messages": [
            {"role": "system", "content": "You are a malware analysis assistant."},
            {"role": "user", "content": prompt}
        ]
    }

    try:
        res = requests.post("https://openrouter.ai/api/v1/chat/completions", headers=headers, json=body)
        if res.status_code == 200:
            return res.json()["choices"][0]["message"]["content"]
        else:
            return f"[OpenRouter ERROR] {res.status_code}: {res.text}"
    except Exception as e:
        return f"[OpenRouter ERROR] {str(e)}"