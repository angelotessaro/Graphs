//Angelo Tessaro - 10310551

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "priority_queue.h"

int main(int argc, char *argv[]) {
		
	int n, m;	
	int  c1, c2, tempo, custo;
	scanf("%i", &n);
	scanf("%i", &m);
	Grafo grafo = criarGrafo(n);
	while(m > 0){
		scanf("%i %i %i %i", &c1, &c2, &tempo, &custo);
		inserirAresta(grafo, c1, c2, tempo, custo);
		m--;
	}
	int A, B;
	scanf("%i %i", &A, &B);
	caminho_Dijkstra(grafo, A, B);

	return 0;
}
