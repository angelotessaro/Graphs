//Angelo Tessaro - 10310551

typedef struct node{
	int vertice;
	int tempo;
	int custo;
	struct node *proximo;
} *No;

typedef struct lista_adj{
	No cabecalho, fim;
} Lista_adj;

typedef struct grafo{
	int V;	//numero de vertices
	int A; 	//numero de arestas
	Lista_adj *adj;
} *Grafo;

static No criarNo(int vertice, No proximo, int tempo, int custo);
Grafo criarGrafo(int V);
void DFS(Grafo grafo, int v, int *tempo, int descoberta[], int processamento[], int cor[], int antecessor[], int ord_topologica[]);
void buscaProfundidade(Grafo grafo);
int existeAresta(Grafo grafo, int v1, int v2);
void inserirAresta(Grafo grafo, int v1, int v2, int tempo, int custo);
void removerAresta(Grafo grafo, int v1, int v2);
void exibirLista(Grafo grafo);
void apagarGrafo(Grafo grafo);
int grau_vertice(Grafo grafo, int vertice);
void eliminar_vertice(Grafo grafo, int vertice);
void remove_topologica(int size, int ord_topologica[], int vertice);
void relax_aresta(Grafo grafo, int v, int tempo[], int custo[], int antecessor[]);
void caminho_Dijkstra(Grafo grafo, int A, int B);
int menor_valor(int vetor[], int tamanho);
