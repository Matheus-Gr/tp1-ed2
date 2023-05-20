//
// Created by mathe on 5/9/2023.
//

#ifndef TP1_REGISTRO_H
#define TP1_REGISTRO_H

#define MAX_DADO2_SIZE 1000
#define MAX_DADO3_SIZE 5000

typedef struct {
    int chave;
    long dado1;
    char dado2[MAX_DADO2_SIZE];
    char dado3[MAX_DADO3_SIZE];
} Registro;

void criarArquivoBinario(int quantidade, char* caminho, int ordem);
void lerArquivoBinario(char* caminho);

#endif //TP1_REGISTRO_H
