//
// Created by mathe on 5/18/2023.
//

#include "ASI.h"
#include "Estatistica.h"
#include <string.h>

#define ITENSPAGINA 4

int pesquisaSequencialIndexado(FILE * arquivo, int quantidade, Registro* chave, Estatistica* estatistica) {
    //definir numero de paginas
    int n_paginas = quantidade / ITENSPAGINA;

    //criar tabela de index
    int tabela_indexes[n_paginas];
    Registro registro;
    for (int i = 0; i < n_paginas; ++i) {
        fseek(arquivo, i * ITENSPAGINA * sizeof(Registro), SEEK_SET);

        // Ler o registro do início da página
        fread(&registro, sizeof(Registro), 1, arquivo);
        incTransf(estatistica);

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
        incComp(estatistica);
        if (tabela_indexes[i] <= chave->chave && (i == n_paginas - 1 || tabela_indexes[i + 1] > chave->chave)) {
            incComp(estatistica);
            fseek(arquivo, i * ITENSPAGINA * sizeof(Registro), SEEK_SET);
            fread(pagina, sizeof(Registro), ITENSPAGINA, arquivo);
            incTransf(estatistica);
            paginaEncontrada = i;
            break;
        }
    }

    if (paginaEncontrada != -1) {
        // Realizar a busca dentro da página encontrada
        for (int i = 0; i < ITENSPAGINA; ++i) {
            incComp(estatistica);
            if (pagina[i].chave == chave->chave) {
                incComp(estatistica);
                // Chave encontrada
                chave->dado1 = pagina[i].dado1;
                strcpy(chave->dado2, pagina[i].dado2);
                strcpy(chave->dado3, pagina[i].dado3);
                break;
            }
        }
    } else {
        return 1;
    }
//    printf("Registro %d\n Dado 1:%d\n Dado 2:%s\n Dado 3:%s\n",chave->chave,chave->dado1, chave->dado2, chave->dado3);

    fclose(arquivo);
    return 0;
}
