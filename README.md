# Password Hash Cracker (C)

A simple hash cracker simulator (MD5, SHA-1, SHA-256) using wordlists in C, powered by OpenSSL.  
Educational project for security studies and low-level programming practice.

---

## 🔧 How to Use

1. **Compile:**
    ```bash
    gcc wordlist_hash.c -o wordlist_hash.exe -lssl -lcrypto
    ```

2. **Run:**
    ```bash
    ./wordlist_hash.exe [wordlist.txt] [hash] [algorithm]
    ```
    - `wordlist.txt`: File with possible passwords (one per line)
    - `hash`: The hash string to crack
    - `algorithm`: `md5`, `sha1`, or `sha256`

    **Example:**
    ```bash
    ./wordlist_hash.exe rockyou.txt 5d41402abc4b2a76b9719d911017c592 md5
    ```

---

## 📄 License

MIT License — free for educational and personal use.

---

> For security research and learning purposes only. Never use for illegal activities.
