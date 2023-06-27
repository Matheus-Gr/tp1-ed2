#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Registro.h"
#include "Estatistica.h"
#include "ArvoreBinaria.h"
#include "ASI.h"
#include "arvoreB.h"
#include "arvoreEstrela.h"

#define ARQUIVO "../Dados/dados_100_3.bin"

int main(int argc, char *argv[]) {
    int metodo, quantidade, ordem, chave, mostrar_pesquisa = 0;
    if (argc < 5 || argc > 6) {
        printf("Uso: pesquisa <metodo> <quantidade> <ordem> <chave> [-P]\n");
        return 1;
    }
    metodo = atoi(argv[1]);
    quantidade = atoi(argv[2]);
    ordem = atoi(argv[3]);
    chave = atoi(argv[4]);
    if (argc == 6 && strcmp(argv[5], "-P") == 0) {
        mostrar_pesquisa = 1;
    }

    //Definição da chave que ser buscada
    Registro* reg = malloc(sizeof(Registro));
    reg->chave = chave;

    //Criação de estatistica
    Estatistica* est = malloc(sizeof(Estatistica));

    //Tempoarariamente para garantir que não tera arquivos corrompidos
    criarArquivoBinario(100, "../Dados/dados", ordem);
    if(mostrar_pesquisa){
        lerArquivoBinario(ARQUIVO);
    }

    //abrindo arquivo a ser manipulado
    FILE* arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo binário!\n");
        exit(1);
    }


    switch (metodo) {
        case 1:
            zerarEstatistica(est);
            pesquisaSequencialIndexado(arquivo,quantidade,reg,est);
            finalizarEstatistica(est);
            printf("Registro %d\n"
                   "    Dado 1:%ld\n"
                   "    Dado 2:%s\n"
                   "    Dado 3:%s\n",
                   reg->chave, reg->dado1,
                   reg->dado2, reg->dado3);
            break;
        case 2:
            criarArvoreBinaria(arquivo,quantidade);
            FILE * arvore_binaria = fopen("../arvorebin.bin", "rb");

            zerarEstatistica(est);
            *reg = buscaArvoreBinaria(arvore_binaria, chave,est);
            finalizarEstatistica(est);
            printf("Registro %d\n"
                   "    Dado 1:%ld\n"
                   "    Dado 2:%s\n"
                   "    Dado 3:%s\n",
                   reg->chave, reg->dado1,
                   reg->dado2, reg->dado3);
            break;
        case 3:
            zerarEstatistica(est);
            arvoreB(arquivo, chave, est);
            finalizarEstatistica(est);
            break;
        case 4:
            zerarEstatistica(est);
            arvoreEstrela(arquivo, chave, est);
            finalizarEstatistica(est);
            break;

        default:
            printf("Metodo invalido. Use um numero de 1 a 4.\n");
            return 1;
    }

    printf("Estatisticas\n"
           "    Numero de transferencias: %d\n"
           "    Numero de comparacoes: %d\n"
           "    Tempo: %fs\n",
           est->transferencias, est->comparacoes,
           calcularTempo(est));

    fclose(arquivo);
    return 0;
}