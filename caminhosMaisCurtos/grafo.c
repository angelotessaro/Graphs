//Angelo Tessaro - 10310551

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "priority_queue.h"
#define INT_MAX   (2147483647)

No criarNo(int vertice, No proximo, int tempo, int custo){
	No a = (No) malloc(sizeof(struct node));
	a->vertice = vertice;
	a->proximo = proximo;
	a->tempo = tempo;
	a->custo = custo;
	return a;
}

Grafo criarGrafo(int V){
	Grafo grafo = (Grafo) malloc(sizeof *grafo);
	grafo->V = 	V;
	grafo->A = 0;
	grafo->adj = malloc(V * sizeof(struct lista_adj));
	for(int i = 0; i < V; i++){
		grafo->adj[i].cabecalho = grafo->adj[i].fim = criarNo(0, NULL, 0, 0); //cabecalho
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

void inserirAresta(Grafo grafo, int v1, int v2, int tempo, int custo){
	if(!existeAresta(grafo, v1, v2)){
		No a = (No) malloc(sizeof(struct node));
		a = grafo->adj[v1].fim;
		a->proximo = criarNo(v2, NULL, tempo, custo);
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

void relax_aresta(Grafo grafo, int v, int tempo[], int custo[], int antecessor[]){
	for(No a = grafo->adj[v].cabecalho->proximo; a!=NULL; a = a->proximo){
		if(tempo[a->vertice] > tempo[v] + a->tempo && (tempo[v] + a->tempo) > 0){
			tempo[a->vertice] = tempo[v] + a->tempo;
			custo[a->vertice] = custo[v] + a->custo;
			antecessor[a->vertice] = v;
		}
	}
}

void caminho_Dijkstra(Grafo grafo, int A, int B){
	int tempo[grafo->V], custo[grafo->V], antecessor[grafo->V], finalizados[grafo->V];
	int contador = 0;
	for(int i = 0; i < grafo->V; i++){ //inicializacao dos vetores
		tempo[i] = INT_MAX;
		custo[i] = INT_MAX;
		antecessor[i] = finalizados[i] = -1;
	}
	tempo[A] = custo[A] = 0;
	Lista_prioridades *fila_PQ = criar_PQ();
	for(int i = 0; i < grafo->V; i++){	//iniciar a lista de prioridades com os valores de tempo de viagem para A
		inserir_PQ(fila_PQ, i, tempo[i]);
	}
	while(fila_PQ->cabecalho->vertice > 0){
		int vertice = remover_PQ(fila_PQ);
		finalizados[contador] = vertice;
		relax_aresta(grafo, vertice, tempo, custo, antecessor);
		contador++;
		atualizar_PQ(fila_PQ, tempo);//atualiza a lista de prioridades com os menores valores de tempo de viagem para cada vértice
	}
	int contagem_paradas = 0;
	int paradas[grafo->V];
	int i = B;
	while(antecessor[i] != -1){		//percorre o caminho dos antecessores de B até A
		paradas[contagem_paradas] = antecessor[i];	//armazena os antecessores num vetor auxiliar
		i = antecessor[i];
		contagem_paradas++;
	}
	for(int i = contagem_paradas-1; i>=0; i--){ //percorre o vetor com as paradas do fim para o inicio 
		printf("%d ", paradas[i]);				//imprime as paradas na ordem de A para B
	}
	printf("%d\n", B);
	printf("%d %d\n", tempo[B], custo[B]);
}	