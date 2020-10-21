//Angelo Tessaro - 10310551

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

No_PQ criarNo_PQ(int vertice, int valor, No_PQ proximo){
	No_PQ a = (No_PQ) malloc(sizeof(struct node_PQ));
	a->vertice = vertice;
	a->proximo = proximo;
	a->valor = valor;
	return a;
}

Lista_prioridades *criar_PQ(void){
	Lista_prioridades *PQ = malloc(sizeof(Lista_prioridades));
		PQ->cabecalho = PQ->fim = criarNo_PQ(0, 0, NULL); //cabecalho
	return PQ;
}

void inserir_PQ(Lista_prioridades *lista, int vertice, int valor){
		No_PQ a = (No_PQ) malloc(sizeof(struct node_PQ));
		a = lista->fim;
		a->proximo = criarNo_PQ(vertice, valor, NULL);
		lista->fim = a->proximo;
		lista->cabecalho->vertice++;
}
int menorValor(Lista_prioridades *lista){	//Encontra o vertice com menor valor da lista de prioridades
	int menor = lista->cabecalho->proximo->valor;
	int menor_vertice = lista->cabecalho->proximo->vertice;
	for(No_PQ a = lista->cabecalho->proximo; a != NULL; a = a->proximo){
		if(a->valor < menor){
			menor = a->valor;
			menor_vertice = a->vertice;
		}
	}
	return menor_vertice;
}

int remover_PQ(Lista_prioridades *lista){ //retira o menor valor da lista de prioridades
	No_PQ lixo = (No_PQ) malloc(sizeof(struct node_PQ));
	int menor_vertice = menorValor(lista);
	for(No_PQ a = lista->cabecalho; a != NULL; a = a->proximo){
		lixo = a->proximo;
		if(lixo != NULL && lixo->vertice == menor_vertice){
			a->proximo = lixo->proximo;
			if(a->proximo == NULL){
				lista->fim = a;
			}
			free(lixo);
			lista->cabecalho->vertice--;
			return menor_vertice;
		}
	}
/*	lista->cabecalho->vertice--;
	}
	return vertice;*/
}

void exibir_PQ(Lista_prioridades *lista){
	int i;
	for(No_PQ a = lista->cabecalho->proximo; a != NULL; a = a->proximo){
		printf("%d ", a->vertice);
	}
	printf("\n");
}

void atualizar_PQ(Lista_prioridades *lista, int tempo[]){ //atualiza a lista de prioridades com os menores valores de tempo de viagem para cada vértice
	for(No_PQ a = lista->cabecalho->proximo; a != NULL; a = a->proximo){
		a->valor = tempo[a->vertice];
	}
}