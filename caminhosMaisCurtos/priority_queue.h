//Angelo Tessaro - 10310551

typedef struct node_PQ{
	int vertice;
	int valor;
	struct node_PQ *proximo;
} *No_PQ;

typedef struct lista_prioridades{
	No_PQ cabecalho, fim;
} Lista_prioridades;

/*typedef struct grafo{
	int V;	//numero de vertices
	int A; 	//numero de arestas
	Lista_adj *adj;
} *Grafo;*/

Lista_prioridades *criar_PQ(void);
void inserir_PQ(Lista_prioridades *lista, int vertice, int valor);
int remover_PQ(Lista_prioridades *lista);
static No_PQ criarNo_PQ(int vertice, int valor, No_PQ proximo);
void exibir_PQ(Lista_prioridades *lista);
void atualizar_PQ(Lista_prioridades* lista, int tempo[]);
int menorValor(Lista_prioridades *lista);