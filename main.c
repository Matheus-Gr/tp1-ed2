#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Registro.h"
#include "Estatistica.h"
#include "ASI.h"

#define ARQUIVO "../Dados/dados_100_1.bin"

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
    Estatistica* est;

    criarArquivoBinario(100,"../Dados/dados",1);
    if(mostrar_pesquisa){
        lerArquivoBinario(ARQUIVO);
    }
    switch (metodo) {
        case 1:
            iniciarEstatistica(est);
            Registro* reg = malloc(sizeof(Registro));
            reg->chave = chave;
            if (!pesquisaSequencialIndexado(ARQUIVO,quantidade,reg,est))
                printf("Registro %d\n dado 1:%d\n, dado 2:%s\n, dado 3:%s\n",reg->chave,reg->dado1, reg->dado2, reg->dado3);
            else
                printf("Item nao encontrado");
            finalizarEstatistica(est);
            break;
        default:
            printf("Método inválido. Use um número de 1 a 4.\n");
            return 1;
    }
    return 0;
}