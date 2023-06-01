//
// Created by mathe on 5/30/2023.
//

#include "ArvoreBinaria.h"
#include "Registro.h"


void criarArvoreBinaria(FILE *arquivo, int quantidade) {
    Registro registro;
    NodeBinario* nodes = (NodeBinario*) malloc(quantidade * sizeof(NodeBinario));

    int pos = 0;
    while (fread(&registro, sizeof(Registro),1,arquivo)){
//        printf("chave: %d\n",registro.chave);
        NodeBinario node;
        node.esquerda = -1;
        node.direita = -1;
        node.registro = registro;
        node.posicao = pos;

        nodes[pos] = node;

        int pos_atual = 0;
        while (pos_atual != -1 && pos != 0){
//            printf("pos %d: %d < %d\n",pos, registro.chave,nodes[pos_atual].registro.chave);
            if(registro.chave < nodes[pos_atual].registro.chave){
//                printf("sim!\n");
                if(nodes[pos_atual].esquerda == -1){
//                    printf("escrito!\n");
                    nodes[pos_atual].esquerda = pos;
                    pos_atual = -1;
                }else{
//                    printf("pulando para pos %d!\n",pos_atual);
                    pos_atual = nodes[pos_atual].esquerda;
                }
            }else{
//                printf("nao!\n");
                if(nodes[pos_atual].direita == -1){
//                    printf("escrito!\n");
                    nodes[pos_atual].direita = pos;
                    pos_atual = -1;
                }else{
//                    printf("pulando para pos %d!\n",pos_atual);
                    pos_atual = nodes[pos_atual].direita;
                }
            }
        }
        pos ++;
    }

    FILE* arvore_binaria = fopen("../arvorebin.bin", "wb");
    if (arvore_binaria == NULL) {
        printf("Erro ao criar arvore!\n");
        free(nodes);
        exit(1);
    }

    for(int i = 0; i < quantidade; i++){
        fwrite(&nodes[i], sizeof(NodeBinario), 1, arvore_binaria);
    }

    fclose(arvore_binaria);
    free(nodes);
}

Registro buscaArvoreBinaria(FILE *arvore_binaria, int chave, Estatistica* est) {
    NodeBinario node;
    fread(&node, sizeof(NodeBinario), 1, arvore_binaria);
    incTransf(est);

    if (node.registro.chave == chave) {
        incComp(est);
        return node.registro;
    } else if (chave > node.registro.chave && node.direita != -1) {
        incComp(est);
        fseek(arvore_binaria,(int) ( node.direita * sizeof(NodeBinario)),SEEK_SET);
        return (buscaArvoreBinaria(arvore_binaria, chave, est));
    } else if (chave < node.registro.chave && node.esquerda != -1) {
        incComp(est);
        fseek(arvore_binaria,(int) (node.esquerda * sizeof(NodeBinario)),SEEK_SET);
        return (buscaArvoreBinaria(arvore_binaria, chave, est));
    }

    return node.registro;
}
