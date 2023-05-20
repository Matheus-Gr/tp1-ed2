#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Registro.h"
#include "Estatistica.h"
#include "ASI.h"

#define ARQUIVO "dados_100_1.bin"

int main(int argc, char *argv[]) {
    int metodo, quantidade, situacao, chave, mostrar_pesquisa = 0;
    if (argc < 5 || argc > 6) {
        printf("Uso: pesquisa <metodo> <quantidade> <situacao> <chave> [-P]\n");
        return 1;
    }
    metodo = atoi(argv[1]);
    quantidade = atoi(argv[2]);
    situacao = atoi(argv[3]);
    chave = atoi(argv[4]);
    if (argc == 6 && strcmp(argv[5], "-P") == 0) {
        mostrar_pesquisa = 1;
    }

    //Definição da chave que ser buscada
    Registro* reg = malloc(sizeof(Registro));
    reg->chave = chave;

    //criação de estatistica
    Estatistica* est = malloc(sizeof(Estatistica));

    //tempoarariamente para garantir que não tera arquivos corrompidos
    criarArquivoBinario(100,"dados",1);
    if(mostrar_pesquisa){
        lerArquivoBinario(ARQUIVO);
    }

    switch (metodo) {
        case 1:
            zerarEstatistica(est);
            if (!pesquisaSequencialIndexado(ARQUIVO,quantidade,reg,est)) {
                finalizarEstatistica(est);
                printf("Registro %d\n Dado 1:%d\n Dado 2:%s\n Dado 3:%s\n", reg->chave, reg->dado1, reg->dado2,
                       reg->dado3);
                printf("Estatisticas\n Numero de transferencias: %d\n Numero de comparacoes: %d\n Tempo %.4f\n",
                       est->transferencias, est->comparacoes, calcularTempo(est));
            }
            else
                printf("Item nao encontrado");
            break;
        default:
            printf("Método inválido. Use um número de 1 a 4.\n");
            return 1;
    }
    return 0;
}