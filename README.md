# MalAIzer: GenAI-Powered Malware Artifact Analyzer

<img width="1024" height="1024" alt="image" src="https://github.com/user-attachments/assets/62e71f6b-7733-40c7-96f1-8b3939c44308" />


---

## 🧠 Overview

**MalAIzer** is an automated malware analysis pipeline that:

* 🗃️ Extracts static artifacts from PE files (.exe/.dll)
* 🧠 Feeds them into LLMs (local or cloud)
* 📝 Outputs an AI-generated malware summary with key insights

It combines **C++ PE parsing**, **ASCII string extraction**, and **GenAI inference** (via LLaMA 3 or Mistral) to help researchers, malware analysts, or security engineers get faster assessments.

---

## 📦 Features

```
+------------------+     +----------------------+     +---------------------------+
|   PE File Input  | --> |   C++ Artifact       | --> |   Python AI Assistant     |
|  (.exe, .dll)    |     |   Extractor (PE)     |     |   (Ollama / OpenRouter)   |
+------------------+     +----------------------+     +---------------------------+
                                                  \
                                                   +--> Markdown/Text Summary
```

* 🧠 LLM analysis via **Ollama (local)** or **OpenRouter (cloud)**
* ✅ Supports **macOS/Linux**, no Windows required
* 📎 Generates output in JSON + formatted text
* 📝 Auto-names response files with timestamps
* 🛠️ No external dependencies like OpenSSL required
* 🧪 Easily extendable with VirusTotal or dynamic sandbox integration

---

## 🔧 Requirements

* CMake (>=3.10)
* C++17 compiler (g++/clang)
* Python 3.8+
* Python dependencies: `requests`, `python-dotenv` *(optional for cloud)*
* **Ollama** (for LLaMA 3 local inference)

---

## 📂 Project Structure

```bash
MalAIzer/
├── extractor/                  # C++ Artifact Extractor
│   ├── src/                   # Main, utils, PE parsing
│   ├── include/               # Headers and helpers
│   └── build/                 # Auto-generated
├── ai_assistant/              # Python AI Summary Assistant
│   ├── analyze.py             # Main entry point
│   ├── prompt_builder.py      # Prompt formatting
│   ├── ollama_client.py       # Local LLaMA 3
│   ├── openrouter_client.py   # Cloud Mistral/Mixtral
│           
├── outputs/                   # Artifact JSON files
├── responses/                 # Final AI summaries (flat)
├── build_cpp.sh               # Builds C++ extractor
├── run_malalyzer.sh           # One-shot full analysis pipeline
└── responses/                 # AI output summaries
└── README.md                  # This file
```

---

## 🚀 Quick Start

### 1. Build the C++ Extractor

```bash
./build_cpp.sh
```

### 2. Run the full pipeline on any PE file:

```bash
./run_malalyzer.sh path/to/malware.exe --model ollama
./run_malalyzer.sh path/to/suspicious.dll --model openrouter
```

> Output goes to:
>
> * Extracted artifacts: `outputs/*.json`
> * AI summaries: `responses/*_summary_YYYY-MM-DDTHH-MM-SS.txt`

---

## 🧠 AI Model Support

| Model   | Type  | Setup Notes                                       |
| ------- | ----- | ------------------------------------------------- |
| LLaMA 3 | Local | Requires [Ollama](https://ollama.com)             |
| Mistral | Cloud | Free tier via [OpenRouter](https://openrouter.ai) |

### 🌐 OpenRouter Setup

```bash
# Get your free API key from openrouter.ai
export OPENROUTER_API_KEY="sk-or-xxxxxxxxxxxx"
```

Or save to `.env`:

```dotenv
OPENROUTER_API_KEY=sk-or-xxxxxxxxxxxx
```

> You can select models via:
>
> ```bash
> ./run_malalyzer.sh sample.exe --model ollama
> ./run_malalyzer.sh sample.exe --model openrouter
> ```

---

## 📄 Output Examples

### 🧩 Extracted JSON:

```json
{
  "file_info": {
    "filename": "sample.exe",
    "file_type": ".exe",
    "file_size": 1048576,
    "hashes": { "md5": "...", "sha256": "..." }
  },
  "imports": [...],
  "sections": [...],
  "strings": [...]
}
```

### 🧠 AI Summary Output (TXT)

```
Suspicious Behaviors:
---------------------
1. API injection: Calls to GetProcAddress and LoadLibrary...
2. Beaconing hints: String patterns resemble C2 beaconing...

Malware Family:
---------------
Potential Trojan or Backdoor

Next Steps:
-----------
- Run dynamic analysis
- Cross-check hash on VirusTotal
```

---

## 🧪 Optional Enhancements

* [ ] Add VirusTotal hash lookup module
* [ ] Export Markdown reports (`.md`)
* [ ] Multi-file batch mode
* [ ] Section entropy scoring
* [ ] Add lightweight GUI wrapper (Tk or Flask)

---

## 🤖 Credits & Acknowledgements

* [pe-parse](https://github.com/trailofbits/pe-parse)
* [Ollama](https://ollama.com/) for local GenAI
* [OpenRouter](https://openrouter.ai/) for cloud-based model access

---

## 📜 License

MIT License. For research, educational, and security testing use only.

---

## 🛡 Disclaimer

This project does not upload or submit files anywhere. Ensure you have authorization before analyzing unknown binaries. This tool is provided as-is, without any warranty or liability.

---

## 👋 Feedback & Contributions

Suggestions welcome! Fork the repo, create issues, or submit a PR. Let's make malware analysis smarter together.
