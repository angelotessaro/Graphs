//Angelo Tessaro - 10310551

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(int argc, char *argv[]) {
	
	int n, m;	
	int o1, a1, a2;
	scanf("%i", &n);
	scanf("%i", &m);
	Grafo grafo = criarGrafo(n);
	
	while(m > 0){
		scanf("%i %i", &a1, &a2);
		inserirAresta(grafo, a1, a2);
		m--;
	}
	buscaProfundidade(grafo);
	return 0;
}
