//
// Created by mathe on 5/18/2023.
//

#include "ASI.h"
#include "Estatistica.h"
#include <string.h>

#define ITENSPAGINA 4

/**
 * Realiza uma pesquisa sequencial indexada em um arquivo de registros.
 *
 * @param arquivo Ponteiro para o arquivo contendo os registros.
 * @param quantidade Quantidade total de registros no arquivo.
 * @param chave Ponteiro para a chave a ser pesquisada.
 * @param estatistica Ponteiro para a estrutura de estatísticas.
 * @return Retorna 0 se a chave for encontrada e 1 caso contrário.
 */
int pesquisaSequencialIndexado(FILE * arquivo, int quantidade, Registro* chave, Estatistica* estatistica) {
    // Definir o número de páginas
    int n_paginas = quantidade / ITENSPAGINA;

    // Criar tabela de índices
    int tabela_indexes[n_paginas];
    Registro registro;
    for (int i = 0; i < n_paginas; ++i) {
        fseek(arquivo, i * ITENSPAGINA * sizeof(Registro), SEEK_SET);

        // Ler o registro do início da página
        fread(&registro, sizeof(Registro), 1, arquivo);
        incTransf(estatistica);

        tabela_indexes[i] = registro.chave;
    }

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

    fclose(arquivo);
    return 0;
}
