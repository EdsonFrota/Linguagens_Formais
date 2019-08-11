/*
        Universidade Federal de Goiás
Alunos: Caio Vinicius Pinto  Ziretta
        Celso Gomes Guido Júnior
        Edson Júnior Frota Silva
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define calabouco 6

struct no {
    char info;
    struct no* prox;
};

typedef struct no No;

struct pilha
{
    No* prim;
};

typedef struct pilha Pilha;
//Declaracao das variáveis globais
Pilha *_pil;
char _cadeiaEntrada[255];
int _posAtual = 0;

//Protótipo de Funções
Pilha* Cria (void);
No* InsIni (No* l, char v);
No* RetIni (No* l);
void Push (Pilha* p, char v);
char Pop (Pilha* p);
void Libera (Pilha* p);

//Funções de estados
int Inicio();
int q0();
int q1();
int q2();
int q3();
int q4();
void Calabouco();
void Transicao(char caractere);
void TransicaoC();

//Funcao principal
void main(void)
{

	int estado = 0;
	printf("DIGITE A CADEIA DE ENTRADA:");
	gets(_cadeiaEntrada);
    fflush(stdin);

  	while(estado != calabouco)
    {
    	if(_posAtual == 0)
    		estado = Inicio();

    	switch (estado)
    	{
    		case 1:
    			estado = q1();
    			break;
    		case 2:
    			estado = q2();
    			break;
    		case 3:
    			estado = q3();
    			break;
    		case 4:
    			estado = q4();
    			break;
    		default:
    			estado = calabouco;
    			Calabouco();
		}
	}
}

void Transicao(char caractere)
{
	Push(_pil, caractere);	//Empilha um caractere na pilha
	_posAtual++; 		//Incrementa posição atual da cadeia
}

void TransicaoC()
{
	_posAtual++; 		//Incrementa posição atual da cadeia
	char caractere = Pop(_pil);	//Desempilha um caractere da pilha
	if(caractere == 'c')
		return;
}

int Inicio()
{
	char caractere = _cadeiaEntrada[_posAtual];

	if(caractere == 'a')
	{
		_pil = Cria();		//Cria a pilha
		Transicao('x'); 	//Transição A
		return 1;
	}
	else
		return calabouco;
}


int q1(int PosAtual)
{
	char caractere = _cadeiaEntrada[_posAtual];

	while(caractere == 'a')
	{
		Transicao('x');
		caractere = _cadeiaEntrada[_posAtual];
	}

	if(caractere == 'b')
	{
		Transicao('y');
		return 2;
	}
	else
	{
		return calabouco;
	}
}

int q2(int PosAtual)
{
	char caractere = _cadeiaEntrada[_posAtual];

	while(caractere == 'b')
	{
		Transicao('y');

		caractere = _cadeiaEntrada[_posAtual];
	}

	if(caractere == 'c')
	{
		TransicaoC();
		return 3;
	}
	else
		return calabouco;
}

int q3(int PosAtual)
{
	char caractere = _cadeiaEntrada[_posAtual];

	while(caractere == 'c')
	{
		TransicaoC();

		caractere = _cadeiaEntrada[_posAtual];
	}
	return 4;
}

int q4()
{
	char caractere = _cadeiaEntrada[_posAtual];

	if(caractere == '\0' && Vazia(_pil))
	{
		printf("CADEIA ACEITA\n");
		system("pause");
		return calabouco;
	}
	else
	{
		Calabouco();
		return calabouco;
	}
}

void Calabouco()
{
	printf("CADEIA RECUSADA\n");
	system("pause");
	return;
}

// Função para criação da pilha
Pilha* Cria (void)
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p -> prim = NULL;
    return p;
}

// Função que inserir a pilha no inicio
No* InsIni (No* l, char v)
{
    No* p = (No*) malloc(sizeof(No));
    p -> info = v;
    p -> prox = l;
    return p;
}

// Função auxiliar: retira do inicio da pilha
No* RetIni (No* l)
{
    No* p = l -> prox;
    free(l);
    return p;
}

// Insercao na pilha;
void Push (Pilha* p, char v)
{
    p -> prim = InsIni(p -> prim,v);
}

// Função que remove da pilha
char Pop (Pilha* p)
{
    char v;

    if (Vazia(p))	//Verifica se a pilha está vazia
    {
		Calabouco();
    }

    v = p -> prim -> info;
    p -> prim = RetIni(p -> prim);

    return v;
}

// Função auxiliar q verifica se a pilha esta vazia
int Vazia (Pilha* p)
{
    return (p -> prim == NULL);
}


void Libera (Pilha* p)
{
    No* r = p -> prim;

    while (r != NULL)
    {
        No* t = r -> prox;
        free(r);
        r = t;
    }

    free(p);
}
