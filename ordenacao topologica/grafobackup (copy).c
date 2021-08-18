//Angelo Tessaro - 10310551

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


No criarNo(int vertice, No proximo){
	No a = (No) malloc(sizeof(struct node));
	a->vertice = vertice;
	a->proximo = proximo;
	return a;
}

Grafo criarGrafo(int V){
	Grafo grafo = (Grafo) malloc(sizeof *grafo);
	grafo->V = 	V;
	grafo->A = 0;
	grafo->adj = malloc(V * sizeof(struct lista_adj));
	for(int i = 0; i < V; i++){
		grafo->adj[i].cabecalho = grafo->adj[i].fim = criarNo(0, NULL); //cabecalho
	}
	return grafo;
}
int existeAresta(Grafo grafo, int v1, int v2){
	for(No a = grafo->adj[v1].cabecalho->proximo; a != NULL; a = a->proximo){ //->cabecalho
		if(a->vertice == v2){
			return 1;
		}
	}
	return 0;
}

void inserirAresta(Grafo grafo, int v1, int v2){
	if(!existeAresta(grafo, v1, v2)){
		No a = (No) malloc(sizeof(struct node));
		a = grafo->adj[v1].fim;
		a->proximo = criarNo(v2, NULL);
		grafo->adj[v1].fim = a->proximo;
		grafo->A++;
	}
	else{
		printf("Aresta %d -> %d ja existe", v1, v2);
	}
}

void removerAresta(Grafo grafo, int v1, int v2){
	No lixo = (No) malloc(sizeof(struct node));
	for(No a = grafo->adj[v1].cabecalho; a != NULL; a = a->proximo){
		lixo = a->proximo;
		if(lixo != NULL && lixo->vertice == v2){
			a->proximo = lixo->proximo;
			if(a->proximo == NULL){
				grafo->adj[v1].fim = a;
			}
			free(lixo);
		}
	}
}

void remove_topologica(lin_lista *ord_topologica, int vertice){
	for(elemento *a = ord_topologica->inicio; a!= NULL; a = a->proximo){
		elemento *lixo = (elemento *) malloc(sizeof(elemento));
		elemento *aux;
		aux = a;
		lixo = a->proximo;
		if(lixo != NULL && lixo->v == vertice){
			if(lixo->proximo !=NULL){
				*a = *(lixo->proximo);
			}
			else{
				a->proximo = NULL;
			}
			printf("ordenacao topologica: ");
			for(lixo = ord_topologica->inicio; lixo!=NULL; lixo = lixo->proximo){
				printf("%d, ", lixo->v);
			}
			free(lixo);
			break;
		}
		else if(a->v == vertice){
			printf("a\n");
			if(lixo!=NULL){
				*a = *lixo;
				printf("ordenacao topologica: ");
				for(lixo = ord_topologica->inicio; lixo!=NULL; lixo = lixo->proximo){
					printf("%d, ", lixo->v);
				}
				free(aux);
				break;
			}
			else{
				a = NULL;
			}
		}
	}
}
void exibirLista(Grafo grafo){
	int i;
	for(i = 0; i < grafo->V; i++){
		printf("%d: ", i);
		for(No a = grafo->adj[i].cabecalho->proximo; a != NULL; a = a->proximo){
			printf("%d ", a->vertice);
		}
		printf("\n");

	}
}

void apagarGrafo(Grafo grafo){
	free(grafo);
}

int grau_vertice(Grafo grafo, int vertice){
	int grau = 0;
	for (int i = 0; i < grafo->V; i++){
		if(existeAresta(grafo, i, vertice)){
			grau++;
		}
	}
	return grau;
}

void eliminar_vertice(Grafo grafo, int vertice){
	for(int i = 0; i < grafo->V; i++){
		if(existeAresta(grafo, vertice, i)){
			removerAresta(grafo, vertice, i);
		}
	}
}

void DFS(Grafo grafo, int v, int *tempo, int descoberta[], int processamento[], int cor[], int antecessor[], lin_lista *ord_topologica){
	cor[v] = 1; // cor do vertice cinza
	(*tempo)++;
	descoberta[v] = *tempo;

	for(No a = grafo->adj[v].cabecalho->proximo; a!=NULL; a = a->proximo){
		if(cor[a->vertice] == 0){
			antecessor[a->vertice] = v;
			DFS(grafo, a->vertice, tempo, descoberta, processamento, cor, antecessor, ord_topologica);
		}
		else if(cor[a->vertice] == 1){
			printf("-1");
			break;
		}
	}
	cor[v] = 2;
	(*tempo)++;
	processamento[v] = *tempo;

	if(ord_topologica->inicio == NULL){
		elemento *aux;
		aux = ord_topologica->inicio;
		ord_topologica->inicio = malloc(sizeof(struct elemento));
		ord_topologica->inicio->v = v;
		ord_topologica->inicio->proximo = aux;
		ord_topologica->fim = aux;
	}
	else{
		elemento *aux;
		aux = ord_topologica->inicio;
		ord_topologica->inicio = malloc(sizeof(struct elemento));
		ord_topologica->inicio->v = v;
		ord_topologica->inicio->proximo = aux;
	}
}

void buscaProfundidade(Grafo grafo){
	int tempo = 0;
	lin_lista *ord_topologica = malloc(grafo->V * sizeof(lin_lista));
	ord_topologica->inicio = NULL;
	ord_topologica->fim = NULL;
	int descoberta[grafo->V], processamento[grafo->V], cor[grafo->V], antecessor[grafo->V];

	for(int v = 0; v < grafo->V; v++){
		cor[v] = 0;
		antecessor[v] = -1;
	}
	for(int v = 0; v < grafo->V; v++){
		if(cor[v] == 0){
			DFS(grafo, v, &tempo, descoberta, processamento, cor, antecessor, ord_topologica);
		}
	}

	int unidades_tempo = 0, contagem = 0, aux_cont = 0, remover[grafo->V];
	exibirLista(grafo);
	while(contagem <= grafo->V){
		for(elemento *a = ord_topologica->inicio; a!=NULL; a = a->proximo){
			if(grau_vertice(grafo, a->v) == 0){
				contagem++;
				remover[aux_cont] = a->v;
				aux_cont++;
				remove_topologica(ord_topologica, a->v);
			}
		}
		for(int i = 0; i < aux_cont; i++){
			eliminar_vertice(grafo, remover[i]);
		}
		aux_cont = 0;
		unidades_tempo++;
	}
	printf("unidades de tempo: %d", unidades_tempo);
}