/***********************************************************************
*	Arthur Floresta Rezende
* MYGraph.h - Header da classe MyGraph
*
* Implementacao de um grafo simples para solucao do
* Problema do Caixeiro Viajante (em ingles: TSP)
***********************************************************************/
#ifndef MyGraph_H
#define MyGraph_H

//=====================================================================
// CLASSE GRAFO
//=====================================================================
class MyGraph {
	enum{ MAX_CITY = 100, MAX_COORDENATES = 1000, NULL_VAL = -1 }; // Constantes
	int vertex_n, edge_n; // Numero de vertices e arestas
	double matrix[MAX_CITY][MAX_CITY]; // Matriz de adjacencia

public:
	MyGraph(); // Construtor
	int getVertexNum(); // Get numero de vertices
	int getEdgeNum(); // Get numero de arestas
	void constructGraph(int n, int coor[MAX_CITY][MAX_CITY]); // Constroi o grafo
	void printGraph(); // Imprime o grafo
	double getEdge(int v1, int v2); // Get aresta
	double* get_all_edges(int v); // Get vetor de arestas do vertice

private:
	void nullifyEdge(int v1, int v2); // Reseta a aresta para o valor nulo
	void setVertexNum(int n); // Altera o numeto de vertices
	bool addEdge(int v1, int v2, double weight); // Adiciona uma aresta
	int getDegree(int v); // Get grau do vertice
	void cleanGraph(); // Limpa o grafo
};

#endif // MyGraph_H
