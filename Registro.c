//
// Created by mathe on 5/9/2023.
//

#include "Registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void criarArquivoBinario(int quantidade, char* caminho) {
    Registro registro;
    FILE *arquivo = fopen(caminho, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo binário!\n");
        exit(1);
    }
    for (int i = 0; i < quantidade; i++) {
        registro.chave = i;
        registro.dado1 = i * 10;
        sprintf(registro.dado2, "Dado 2 do registro %d", i);
        sprintf(registro.dado3, "Dado 3 do registro %d", i);
        fwrite(&registro, sizeof(Registro), 1, arquivo);
    }
    fclose(arquivo);
}

void lerArquivoBinario(char* caminho) {
    Registro registro;
    FILE *arquivo = fopen(caminho, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo binário!\n");
        exit(1);
    }
    while (fread(&registro, sizeof(Registro), 1, arquivo)) {
        printf("Chave: %d, Dado 1: %ld, Dado 2: %s, Dado 3: %s\n",
               registro.chave, registro.dado1, registro.dado2, registro.dado3);
    }
    fclose(arquivo);
}