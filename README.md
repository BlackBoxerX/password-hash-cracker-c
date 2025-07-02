# Password Hash Cracker (C)

Um simulador de quebra de hash (MD5, SHA-1, SHA-256) via wordlist em C, usando OpenSSL.
Projeto educacional para estudo de segurança e programação em baixo nível.

## Como usar

1. Compile:
   ```sh
   gcc wordlist_hash.c -o wordlist_hash.exe -lssl -lcrypto
