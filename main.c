#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Registro.h"

#define ARQUIVO "../registros.bin"

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
    switch (metodo) {
        case 1:
            criarArquivoBinario(1000,ARQUIVO);
            lerArquivoBinario(ARQUIVO);
            break;
        default:
            printf("Método inválido. Use um número de 1 a 4.\n");
            return 1;
    }
    return 0;
}