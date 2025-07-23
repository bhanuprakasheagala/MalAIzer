def build_prompt_from_artifacts(data):
    parts = []

    info = data.get("file_info", {})
    parts.append(f"Filename: {info.get('filename')}")
    parts.append(f"File type: {info.get('file_type')}")
    parts.append(f"File size: {info.get('file_size')} bytes")
    parts.append(f"Hashes: MD5={info.get('hashes', {}).get('md5')}, SHA256={info.get('hashes', {}).get('sha256')}")

    imports = data.get("imports", [])
    if imports:
        parts.append("\n== IMPORTS ==")
        for imp in imports[:25]:  # limit to 25
            parts.append(f"{imp['dll']} : {imp['function']}")

    sections = data.get("sections", [])
    if sections:
        parts.append("\n== SECTIONS ==")
        for sec in sections:
            parts.append(f"{sec['name']} | VSize: {sec['virtualSize']} | RawSize: {sec['rawSize']}")

    strings = data.get("strings", [])
    if strings:
        parts.append("\n== STRINGS (top 30) ==")
        parts.extend(strings[:30])

    full_prompt = (
        "You are a malware analysis assistant. "
        "Given the following extracted PE file artifacts, identify potentially suspicious behaviors, "
        "malware families, or actions (e.g., API injection, network beacons, persistence). "
        "Summarize what an analyst should know:\n\n" +
        "\n".join(parts)
    )

    return full_prompt
