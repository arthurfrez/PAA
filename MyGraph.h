#ifndef MyGraph_H
#define MyGraph_H

//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_CITY 100
#define MAX_COORDENATES 1000

//=====================================================================
// CLASSE GRAFO
//=====================================================================
class MyGraph {
	int vertex_n, edge_n;
	double matrix[MAX_CITY][MAX_CITY];

public:
	MyGraph();
	int getVertexNum();
	int getEdgeNum();
	void constructGraph(int n, int coor[MAX_CITY][MAX_CITY]);
	void printGraph();
	double getEdge(int v1, int v2);

private:
	void nullifyEdge(int v1, int v2);
	void setVertexNum(int n);
	bool addEdge(int v1, int v2, double weight);
	int getDegree(int v);
	void cleanGraph();
};

#endif
