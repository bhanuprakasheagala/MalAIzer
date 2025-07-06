# 🧠 MalAIzer

> Combine traditional binary analysis with Generative AI to automate and assist malware reverse engineering.

---

## 🔍 What is MalAIzer?

**MalAIzer** is a modular tool that helps malware analysts and reverse engineers extract static artifacts from Windows PE binaries using **C++**, and then **summarize and interpret** those artifacts using **Generative AI (LLMs like GPT-4 or Mistral)**.

---

## 🎯 Key Features

- 📦 Extracts from PE files:
  - ASCII strings
  - Imports and API usage
  - Section information
  - Entry point metadata
- 🤖 GenAI Analysis:
  - Summarizes potential behavior
  - Flags suspicious activity patterns
  - Suggests malware family and RE next steps
- 🔌 Extensible architecture: Add new formats, prompt styles, and even sandbox hooks

---

## 📂 Project Structure
```
MalAIzer/
├── extractor/                     # C++ component: Artifact extraction
│   ├── include/                   # Header files
│   │   ├── pe_parser.hpp          # PE parsing class/functions
│   │   └── utils.hpp              # Helper functions (entropy, string cleaning, etc.)
│   │
│   ├── src/                       # Source files
│   │   ├── main.cpp               # Entry point: parse args, call extractor, save output
│   │   ├── pe_parser.cpp          # Implements PE parsing (imports, sections, strings)
│   │   └── utils.cpp              # Common utility functions
│   │
│   ├── samples/                   # Test binaries (safe PE files or hashes)
│   ├── outputs/                   # Extracted data files (artifacts.txt / artifacts.json)
│   └── CMakeLists.txt             # CMake project setup
│
├── ai_assistant/                 # Python component: GenAI-powered analysis
│   ├── analyze.py                 # Main script: reads artifact, builds prompt, calls LLM
│   ├── prompt_templates.py        # Stores prompt formats and examples
│   ├── config.py                  # Model settings (OpenAI key, model name, etc.)
│   ├── example_outputs/           # Sample AI responses (for testing/debugging)
│   └── requirements.txt           # Python dependencies
│
├── integration/                  # C++ ↔ Python communication helpers
│   ├── run_pipeline.sh            # Bash script to run extractor → analyzer end-to-end
│   └── interface_notes.md         # Design notes on CLI/file/pipe integration
│
├── data/                         # Sample data (non-malicious for development)
│   ├── benign_notepad.txt         # Example artifact extract (benign)
│   └── trojan_generic.txt         # Example artifact extract (malware-like)
│
├── docs/                         # Documentation
│   ├── architecture.md            # High-level system design
│   ├── prompts.md                 # Prompt crafting guidelines & versions
│   ├── roadmap.md                 # Future scope and planned features
│   └── screenshots/               # CLI screenshots or flow diagrams
│
├── tests/                        # Future unit and integration tests
│   ├── test_pe_parser.cpp         # PE parser test suite
│   └── test_prompt_logic.py       # Prompt formatting/unit tests
│
├── .env.example                  # Template for OpenAI API keys
├── .gitignore                    # Ignore build, outputs, secrets, etc.
├── LICENSE                       # Open-source license (MIT recommended)
├── README.md                     # Project overview, usage, install guide
└── setup.md                      # Initial setup guide (CMake, Python venv, API keys)
```
