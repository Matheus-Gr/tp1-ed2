#ifndef ARVOREESTRELA_H
#define ARVOREESTRELA_H

#include <stddef.h>
#include "stdio.h"
#include "Registro.h"
#include "Estatistica.h"

#define M 10
#define MM 20
#define FALSE 0
#define TRUE 1

typedef enum {
  Interna, Externa
} TipoIntExt;

typedef struct TipoPaginaEstrela *TipoApontadorEstrela;

typedef struct TipoPaginaEstrela {
  TipoIntExt Pt;
  union {
    struct {
      int ni;
      Registro ri[MM];
      TipoApontadorEstrela pi[MM + 1];
    } U0;
    struct {
      int ne;
      Registro re[MM];
    } U1;
  } UU;
} TipoPaginaEstrela;

void arvoreEstrela(FILE *arq, int chave, Estatistica* est);
void pesquisaArvoreEstrela(Registro *x, TipoApontadorEstrela *Ap,Estatistica *est);
void insereNaPaginaArvoreEstrela(TipoApontadorEstrela Ap, Registro Reg, TipoApontadorEstrela ApDir, Estatistica *est);
void insereArvoreEstrela(Registro Reg, TipoApontadorEstrela *Ap, Estatistica *est);
void insArvoreEstrela(Registro Reg, TipoApontadorEstrela Ap, int *Cresceu, Registro *RegRetorno, TipoApontadorEstrela *ApRetorno, Estatistica *est);


#endif