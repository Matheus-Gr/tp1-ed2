//
// Created by mathe on 5/9/2023.
//

#include "Estatistica.h"

void iniciarEstatistica(Estatistica* estatistica) {
    estatistica->transferencias = 0;
    estatistica->comparacoes = 0;
    estatistica->tempoInicio = clock();
}

void finalizarEstatistica(Estatistica* estatistica) {
    estatistica->tempoFim = clock();
}

double calcularTempo(Estatistica* estatistica) {
    return (double)(estatistica->tempoFim - estatistica->tempoInicio) / CLOCKS_PER_SEC;
}