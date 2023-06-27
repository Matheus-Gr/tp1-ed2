#include "arvoreB.h"
#include "Registro.h"
#include "Estatistica.h"
#include "stdlib.h"

void inicializaArvoreB (TipoApontador *Arvore)
{
    *Arvore = NULL;
}
 
void arvoreB(FILE *arq, int chave, Estatistica *est)
{
    TipoApontador Ap;
    Registro item;
    
    Ap= (TipoApontador)malloc(sizeof(TipoPagina));
    inicializaArvoreB(&Ap);
    while (fread(&item, sizeof(Registro), 1, arq) == 1)
    {
        incTransf(est);
        insereArvoreB(item, &Ap, est);
    }
    item.chave=chave;

    pesquisaArvoreB(&item ,Ap, est);
}

int pesquisaArvoreB(Registro *x, TipoApontador Ap, Estatistica *est)
{
    long i = 1;
    
    if (Ap == NULL)
    {
        printf("Registro nao esta presente na arvore\n");
        return 0;
    }
    while (i < Ap->n && x->chave > Ap->r[i-1].chave)
    { 
        incComp(est);
        i++;
    }

    if (x->chave == Ap->r[i-1].chave)
    { 
        incComp(est);
        *x = Ap->r[i-1];
        printf("Chave encontrada!\n");
        printf("Chave: %d\n", x->chave);
        printf("   Dado1: %.2ld\n", x->dado1);
        printf("   Dado2: %s\n", x->dado2);
        printf("   Dado3: %s\n", x->dado3);
        return 1;
    }
    if (x->chave < Ap->r[i-1].chave)
    {
        incComp(est);
        pesquisaArvoreB(x, Ap->p[i - 1], est);
    }
    else
    {
        incComp(est);
        pesquisaArvoreB(x, Ap->p[i], est);
    }
}
void insereNaPaginaArvoreB(TipoApontador Ap, Registro Reg, TipoApontador ApDir, Estatistica *est)
{
    int k;
    int NaoAchouPosicao;

    k = Ap->n;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao)
    {
        if (Reg.chave >= Ap->r[k - 1].chave)
        {
            incComp(est);
            NaoAchouPosicao = 0;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1)
            NaoAchouPosicao = 0;
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void insArvoreB(Registro Reg, TipoApontador Ap, short *Cresceu, Registro *RegRetorno, TipoApontador *ApRetorno, Estatistica *est)
{
    TipoApontador ApTemp;
    long i=1, j;
    
    if (Ap == NULL)
    {
        incComp(est);
        *Cresceu = 1;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;

        return;
    }

    while (i < Ap->n && Reg.chave > Ap->r[i - 1].chave)
        i++;

    if (Reg.chave == Ap->r[i - 1].chave)
    {   
        incComp(est);
        //printf("O registro ja esta presente.\n");
        *Cresceu = 0;
        return;
    }

    if (Reg.chave < Ap->r[i - 1].chave)
    {
        incComp(est);
        i--;
    }
    insArvoreB(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno, est);
    if (!*Cresceu)
        return;
    if (Ap->n < MM)
    {
        incComp(est);
        //Pagina tem espaco 
        insereNaPaginaArvoreB(Ap, *RegRetorno, *ApRetorno, est);
        *Cresceu = 0;
        return;
    }
    // Overflow: Pagina tem que ser dividida 
    ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    if (i <= M + 1)
    {
        insereNaPaginaArvoreB(ApTemp, Ap->r[MM - 1], Ap->p[MM], est);
        Ap->n--;
        insereNaPaginaArvoreB(Ap, *RegRetorno, *ApRetorno, est);
    }
    else
        insereNaPaginaArvoreB(ApTemp, *RegRetorno, *ApRetorno, est);
    for (j = M + 2; j <= MM; j++)
        insereNaPaginaArvoreB(ApTemp, Ap->r[j - 1], Ap->p[j], est);
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
} 

void insereArvoreB(Registro Reg, TipoApontador *Ap, Estatistica *est)
{
    int Cresceu;
    Registro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    insArvoreB(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, est);

    if (Cresceu)   // Arvore cresce na altura pela raiz 
    {
        incComp(est);
        ApTemp=(TipoPagina*)malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = (*Ap);
        *Ap = ApTemp;
    }
 }

