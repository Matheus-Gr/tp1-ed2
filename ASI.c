//
// Created by mathe on 5/18/2023.
//

#include "ASI.h"
#include "Estatistica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITENSPAGINA 4

int pesquisaSequencialIndexado(char* caminhoArquivo, int quantidade, Registro* chave, Estatistica* estatistica) {
    FILE* arquivo = fopen(caminhoArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo binário!\n");
        exit(1);
    }
    //definir numero de paginas
    int n_paginas = quantidade / ITENSPAGINA;

    //criar tabela de index
    int tabela_indexes[n_paginas];
    for (int i = 0; i < n_paginas; ++i) {
        fseek(arquivo, i * ITENSPAGINA * sizeof(Registro), SEEK_SET);

        // Ler o registro no início da página
        Registro registro;
        fread(&registro, sizeof(Registro), 1, arquivo);

        tabela_indexes[i] = registro.chave;
    }

//    visualizar a tabela de indexes
//    for (int i = 0; i < n_paginas; ++i) {
//        printf("Pagina[%d]: %d\n", i +1, tabela_indexes[i]);
//    }

    // Fazer busca
    Registro pagina[ITENSPAGINA];
    int paginaEncontrada = -1;
    for (int i = 0; i < n_paginas; ++i) {
        if (tabela_indexes[i] <= chave->chave && (i == n_paginas - 1 || tabela_indexes[i + 1] > chave->chave)) {
            fseek(arquivo, i * ITENSPAGINA * sizeof(Registro), SEEK_SET);
            fread(pagina, sizeof(Registro), ITENSPAGINA, arquivo);
            paginaEncontrada = i;
            break;
        }
    }
    printf("dado1: %d\n",pagina[0].dado1);
    printf("dado1: %d\n",pagina[1].dado1);
    printf("dado1: %d\n",pagina[2].dado1);
    printf("dado1: %d\n",pagina[3].dado1);

    if (paginaEncontrada != -1) {
        // Realizar a busca dentro da página encontrada
        for (int i = 0; i < ITENSPAGINA; ++i) {
            if (pagina[i].chave == chave->chave) {
                // Chave encontrada
                chave->dado1 = pagina[i].dado1;
                strcpy(chave->dado2, pagina[i].dado2);
                strcpy(chave->dado3, pagina[i].dado3);
                break;
            }
        }
    } else {
        // Página não encontrada
        printf("Pagina nao encontrada!\n");
        return 1;
    }
//    printf("Registro %d\n Dado 1:%d\n Dado 2:%s\n Dado 3:%s\n",chave->chave,chave->dado1, chave->dado2, chave->dado3);

    fclose(arquivo);
    return 0;
}
