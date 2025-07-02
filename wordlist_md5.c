#include <stdio.h>
#include <string.h>
#include "md5.h"

int main() {
    char hash[33];
    char linha[128];
    char tentativa_hash[33];
    int achou = 0;
    unsigned long tentativas = 0;

    printf("Digite o hash MD5 para ataque por wordlist: ");
    scanf("%32s", hash);

    FILE *fp = fopen("senhas.txt", "r");
    if (!fp) {
        printf("Não foi possível abrir o arquivo senhas.txt!\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), fp)) {
        // Remove quebra de linha
        linha[strcspn(linha, "\r\n")] = 0;
        md5_string(linha, tentativa_hash);
        tentativas++;
        if (strcmp(tentativa_hash, hash) == 0) {
            printf("\nSenha encontrada: %s\nTentativas: %lu\n", linha, tentativas);
            achou = 1;
            break;
        }
    }
    fclose(fp);

    if (!achou) {
        printf("\nSenha NÃO encontrada no wordlist.\n");
    }
    return 0;
}
