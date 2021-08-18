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

void remove_topologica(int size, int ord_topologica[], int vertice){
	for(int i = 0; i < size; i++){
		if(ord_topologica[i] == vertice){
			ord_topologica[i] = -1;
			break;
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

void DFS(Grafo grafo, int v, int *tempo, int descoberta[], int processamento[], int cor[], int antecessor[], int ord_topologica[]){
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

	for(int i = grafo->V-1; i >= 0; i--){
		if(ord_topologica[i] == -1){
			ord_topologica[i] = v;
			break;
		}
	}
}

void buscaProfundidade(Grafo grafo){
	int tempo = 0;
	int ord_topologica[grafo->V];
	for(int i = 0; i<grafo->V; i++){
		ord_topologica[i] = -1;
	}
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
	printf("ord %d\n", ord_topologica[0]);
	while(contagem < grafo->V){
		for(int i = 0; i < grafo->V; i++){
			if(ord_topologica[i] != -1 && !grau_vertice(grafo, ord_topologica[i])){
				contagem++;
				remover[aux_cont] = ord_topologica[i];
				aux_cont++;
				printf("%d\n", ord_topologica[i] );
				printf("undit %d\n",unidades_tempo );
				remove_topologica(grafo->V, ord_topologica, ord_topologica[i]);
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