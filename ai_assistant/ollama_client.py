import requests

def call_llama3(prompt):
    try:
        response = requests.post("http://localhost:11434/api/generate", json={
            "model": "llama3",
            "prompt": prompt,
            "stream": False
        })

        if response.status_code == 200:
            return response.json()["response"]
        else:
            return f"[ERROR] Ollama returned: {response.status_code} {response.text}"

    except Exception as e:
        return f"[ERROR] Could not connect to Ollama: {str(e)}"