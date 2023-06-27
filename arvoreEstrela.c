#include "ArvoreEstrela.h"

void Inicializa (TipoApontadorEstrela *Arvore)
{
    *Arvore = NULL;
}

void pesquisaArvoreEstrela(Registro *x, TipoApontadorEstrela *Ap, Estatistica *est) {
    int i;
    TipoApontadorEstrela Pag;
    Pag = *Ap;
    if ((*Ap)->Pt == Interna) {
        i = 1;
        while (i < Pag->UU.U0.ni && x->chave > Pag->UU.U0.ri[i - 1].chave)  
			i++;
        if (x->chave < Pag->UU.U0.ri[i - 1].chave)
            pesquisaArvoreEstrela(x, &Pag->UU.U0.pi[i - 1],est);
        else
            pesquisaArvoreEstrela(x, &Pag->UU.U0.pi[i],est);
        return;
    }
    i = 1;
    while (i < Pag->UU.U1.ne && x->chave > Pag->UU.U1.re[i - 1].chave) {
        incComp(est);
        i++;
    }//pesquisa na pagina folha

    if (x->chave == Pag->UU.U1.re[i - 1].chave)
    {
        incComp(est);
        *x = Pag->UU.U1.re[i - 1];
        printf("Chave encontrada!\n");
        printf("    Chave: %d.\n", x->chave);
        printf("    Dado1: %.2ld\n", x->dado1);
        printf("    Dado2: %s\n", x->dado2);
        printf("    Dado3: %s.\n", x->dado3);
        return;
    }
    else 
		printf("Chave nao esta presente na arvore\n");
}

void insereNaPaginaArvoreEstrela(TipoApontadorEstrela Ap, Registro Reg, TipoApontadorEstrela ApDir, Estatistica *est)
{//insere registro na pagina (folha ou indice)
    int k;
    int NaoAchouPosicao;

    if(Ap->Pt == Interna){ //se for nó interno(indice) busca na arvore onde o registro será inserido
		k = Ap->UU.U0.ni;
		NaoAchouPosicao = (k > 0);
		while(NaoAchouPosicao) 
		{
			if (Reg.chave >= Ap->UU.U0.ri[k - 1].chave) 
			{
				incComp(est);
				NaoAchouPosicao = 0;
				break;
			}
			Ap->UU.U0.ri[k] = Ap->UU.U0.ri[k - 1];
			Ap->UU.U0.pi[k + 1] = Ap->UU.U0.pi[k];
			k--;
			if (k < 1)
				NaoAchouPosicao = 0;
		}
		Ap->UU.U0.ri[k] = Reg;
		Ap->UU.U0.pi[k + 1] = ApDir;
		Ap->UU.U0.ni++;
		return;
		
	}
        //caso contrario, (nó externo(folha)) busca na pagina onde o registro será inserido
	k = Ap->UU.U1.ne;
	NaoAchouPosicao = (k > 0);

	while (NaoAchouPosicao)
    {
        if (Reg.chave >= Ap->UU.U1.re[k - 1].chave) 
        {
            incComp(est);
            NaoAchouPosicao = 0;
            break;
        }
        Ap->UU.U1.re[k] = Ap->UU.U1.re[k - 1];
        k--;
        if (k < 1)
            NaoAchouPosicao = 0;
    }
    Ap->UU.U1.re[k] = Reg;
    Ap->UU.U1.ne++;
}

void insArvoreEstrela(Registro Reg, TipoApontadorEstrela Ap, int *Cresceu, Registro *RegRetorno, TipoApontadorEstrela *ApRetorno, Estatistica *est)
{
    TipoApontadorEstrela ApTemp,Pag;
    long i=1, j;
    Pag = Ap;
	int n;
	
	if (Ap == NULL) {
		*Cresceu = 1;
		(*RegRetorno) = Reg;
		(*ApRetorno) = NULL;
		return;
	}
	
	//caminhamento em indices
	if (Ap->Pt == Interna){
		while (i < Pag->UU.U0.ni && Reg.chave > Pag->UU.U0.ri[i - 1].chave){
			i++;
			incComp(est);
		}
		if (Reg.chave < Pag->UU.U0.ri[i - 1].chave)
		{
			incComp(est);
			i--;
		}
        insArvoreEstrela(Reg, Pag->UU.U0.pi[i], Cresceu, RegRetorno, ApRetorno, est);
		return;
	
	
		if (!*Cresceu) {
			return;
		}
	
	//Overflow. Página interna (indice) precisa ser dividida (excedeu limite MM)
		ApTemp = (TipoApontadorEstrela) calloc(1, sizeof(TipoPaginaEstrela));
		ApTemp->UU.U0.ni = 0;
		ApTemp->UU.U0.pi[0] = NULL;

		if (i < M + 1){
			Registro RegTemp;
			RegTemp.chave = Ap->UU.U0.ri[MM - 1].chave;
            insereNaPaginaArvoreEstrela(ApTemp, RegTemp, Ap->UU.U0.pi[MM], est);
			Ap->UU.U0.ni--;
            insereNaPaginaArvoreEstrela(Ap, *RegRetorno, *ApRetorno, est);
		} 
		else{
            insereNaPaginaArvoreEstrela(ApTemp, *RegRetorno, *ApRetorno, est);
		}

		for (j = M + 2; j <= MM; j++) {
			Registro RegTemp;
			RegTemp.chave = Ap->UU.U0.ri[j - 1].chave;
            insereNaPaginaArvoreEstrela(ApTemp, RegTemp, Ap->UU.U0.pi[j], est);
		}
		Ap->UU.U0.ni = M;
		ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[M + 1];
		(*RegRetorno).chave = Ap->UU.U0.ri[M].chave;
		*ApRetorno = ApTemp;
	}

    //em paginas folha
	while (i < Pag->UU.U1.ne && Reg.chave > Pag->UU.U1.re[i - 1].chave){
			i++;
			incComp(est);
	}
	
	if (Reg.chave == Pag->UU.U1.re[i - 1].chave)
        {   
            incComp(est);
            //O registro ja esta presente
            //*Cresceu = 0;
            return;
        }
	
	if (Reg.chave < Ap->UU.U1.re[i - 1].chave) {
		i--;
	}

    insArvoreEstrela(Reg, NULL, Cresceu, RegRetorno, ApRetorno, est);
	if (!*Cresceu) {
		return;
	}
	
	if (Pag->UU.U1.ne < MM)
    {
		//Pagina tem espaco 
        incComp(est);
        insereNaPaginaArvoreEstrela(Pag, *RegRetorno, *ApRetorno, est);
        *Cresceu = 0;
        return;
    }
		
    //Overflow. Página externa (folha) precisa ser dividida (excedeu limite MM) 
    ApTemp = (TipoApontadorEstrela) malloc(sizeof(TipoPaginaEstrela));
    ApTemp->Pt = Externa;
	ApTemp->UU.U1.ne = 0;
    if (i <= M + 1)
    {
        insereNaPaginaArvoreEstrela(ApTemp, Ap->UU.U1.re[MM - 1], NULL, est);
        Ap->UU.U1.ne--;
        insereNaPaginaArvoreEstrela(Pag, *RegRetorno, *ApRetorno, est);
    }
    else
        insereNaPaginaArvoreEstrela(ApTemp, *RegRetorno, *ApRetorno, est);
    for (j = M + 2; j <= MM; j++)
        insereNaPaginaArvoreEstrela(ApTemp, Pag->UU.U1.re[j - 1], Ap->UU.U0.pi[j], est);
    Ap->UU.U1.ne = M;
    *RegRetorno = Ap->UU.U1.re[M];
    insereNaPaginaArvoreEstrela(ApTemp, Ap->UU.U1.re[M], NULL, est);
    *ApRetorno = ApTemp;
} 
//insereArvoreEstrela registro na arvore (onde sera inserido sera verificado no insArvoreEstrela)
void insereArvoreEstrela(Registro Reg, TipoApontadorEstrela *Ap, Estatistica *est)
{
    int Cresceu;
    Registro RegRetorno;
    TipoPaginaEstrela *ApRetorno, *ApTemp;

    insArvoreEstrela(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, est);

    if (Cresceu)   // Arvore cresce na altura pela raiz 
    {	
		ApTemp = (TipoPaginaEstrela*) malloc (sizeof(TipoPaginaEstrela));
        if(ApRetorno == NULL){
			ApTemp->Pt = Externa;
			ApTemp->UU.U1.ne = 1;
			ApTemp->UU.U1.re[0] = RegRetorno;
		}
		else{	
			ApTemp->Pt = Interna;
			ApTemp->UU.U0.ni = 1;
			ApTemp->UU.U0.ri[0] = RegRetorno;
			ApTemp->UU.U0.pi[1] = ApRetorno;
			ApTemp->UU.U0.pi[0] = *Ap;
		}
		*Ap = ApTemp;
	}
}
//Inicializa arvore b estrela
void arvoreEstrela(FILE *arq, int chave, Estatistica* est)
{
    TipoApontadorEstrela Ap;
    Registro item;


    Ap=(TipoApontadorEstrela)malloc(sizeof(TipoPaginaEstrela));
    Inicializa (&Ap);
    while (fread(&item, sizeof(Registro), 1, arq) == 1)
    {
        incTransf(est);
        insereArvoreEstrela(item, &Ap, est);
    }
    item.chave=chave;

    pesquisaArvoreEstrela(&item, &Ap,est);
}

