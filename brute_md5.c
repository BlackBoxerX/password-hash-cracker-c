#include <stdio.h>
#include <string.h>
#include <time.h>
#include "md5.h"

// Tenta todas as combinações de até 4 letras minúsculas
int brute_md5(const char *target_hash, char *result) {
    char charset[] = "abcdefghijklmnopqrstuvwxyz";
    int len, i, j, k, l;
    char tentativa[5] = {0};
    char hash[33];
    unsigned long tentativas = 0;

    // Tamanho 1
    for (i=0; i<26; i++) {
        tentativa[0] = charset[i]; tentativa[1]=0;
        md5_string(tentativa, hash);
        tentativas++;
        if (strcmp(hash, target_hash)==0) { strcpy(result, tentativa); return tentativas; }
    }
    // Tamanho 2
    for (i=0; i<26; i++) for (j=0; j<26; j++) {
        tentativa[0] = charset[i]; tentativa[1]=charset[j]; tentativa[2]=0;
        md5_string(tentativa, hash);
        tentativas++;
        if (strcmp(hash, target_hash)==0) { strcpy(result, tentativa); return tentativas; }
    }
    // Tamanho 3
    for (i=0; i<26; i++) for (j=0; j<26; j++) for (k=0; k<26; k++) {
        tentativa[0]=charset[i]; tentativa[1]=charset[j]; tentativa[2]=charset[k]; tentativa[3]=0;
        md5_string(tentativa, hash);
        tentativas++;
        if (strcmp(hash, target_hash)==0) { strcpy(result, tentativa); return tentativas; }
    }
    // Tamanho 4
    for (i=0; i<26; i++) for (j=0; j<26; j++) for (k=0; k<26; k++) for (l=0; l<26; l++) {
        tentativa[0]=charset[i]; tentativa[1]=charset[j]; tentativa[2]=charset[k]; tentativa[3]=charset[l]; tentativa[4]=0;
        md5_string(tentativa, hash);
        tentativas++;
        if (strcmp(hash, target_hash)==0) { strcpy(result, tentativa); return tentativas; }
    }
    return 0; // Não achou
}

int main() {
    char hash[33];
    char senha[5];
    printf("Digite o hash MD5 para brute force: ");
    scanf("%32s", hash);

    clock_t start = clock();
    unsigned long tentativas = brute_md5(hash, senha);
    double tempo = (double)(clock() - start) / CLOCKS_PER_SEC;

    if (tentativas) {
        printf("\nSenha encontrada: %s\nTentativas: %lu\nTempo: %.2f segundos\n", senha, tentativas, tempo);
    } else {
        printf("\nSenha NÃO encontrada (até 4 letras minúsculas)\n");
    }
    return 0;
}
