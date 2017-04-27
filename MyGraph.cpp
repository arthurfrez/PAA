/***********************************************************************
*	Arthur Floresta Rezende
* MYGraph.cpp - Implementacao da classe MyGraph
*
* Implementacao de um grafo simples para solucao do
* Problema do Caixeiro Viajante (em ingles: TSP)
***********************************************************************/

//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include "MyGraph.hpp"
#include <cstdio>
#include <cmath>


//------------------------------------------------------------------------------
// calculateDistance: calcula a distancia entre dois pontos
//------------------------------------------------------------------------------
double calculateDistance(double v1c1, double v1c2, double v2c1, double v2c2) {
  return sqrt(pow((v2c1-v1c1), 2.0) + pow((v2c2-v1c2), 2.0));
}

//------------------------------------------------------------------------------
// MyGraph: Construtor padrao
//------------------------------------------------------------------------------
MyGraph::MyGraph(){
  vertex_n = 0;
  edge_n = 0;
}

//------------------------------------------------------------------------------
// gets: Metodos para acessar o valor das variaveis privadas
//------------------------------------------------------------------------------
int MyGraph::getVertexNum() { return vertex_n; }
int MyGraph::getEdgeNum() { return edge_n; }

//------------------------------------------------------------------------------
// addEdge: Metodo para inserir aresta
//------------------------------------------------------------------------------
bool MyGraph::addEdge(int v1, int v2, double weight){
  if(v1 >= MAX_CITY || v1 >= vertex_n)
    return false;
  if(v2 >= MAX_CITY || v2 >= vertex_n)
    return false;

  matrix[v1][v2] = weight;
  matrix[v2][v1] = weight;

  edge_n++;
  return true;
}

//------------------------------------------------------------------------------
// setVertexNum: Muda o numero de vertices do grafo quando o mesmo esta vasio
//------------------------------------------------------------------------------
void MyGraph::setVertexNum(int n) { if(vertex_n == 0) vertex_n = n; }

//------------------------------------------------------------------------------
// getEdge: Retorna a aresta que liga os dois vertices
//------------------------------------------------------------------------------
double MyGraph::getEdge(int v1, int v2) {
  return matrix[v1][v2];
}

//------------------------------------------------------------------------------
// get_all_edges: retorna o vetor com todas a arestas do vertice
//------------------------------------------------------------------------------
double* MyGraph::get_all_edges(int v) {
  return matrix[v];
}

//------------------------------------------------------------------------------
// getDegree: Calcula o grau do vertice
//------------------------------------------------------------------------------
int MyGraph::getDegree(int v) {
  int resp = 0;
  for(int i = 0; i < vertex_n; i++) if(getEdge(v, i) != NULL_VAL) resp++;
  return resp;
}


//------------------------------------------------------------------------------
//  addEdge: Metodo para inserir aresta
//------------------------------------------------------------------------------
void MyGraph::cleanGraph() {
  vertex_n = 0;
  edge_n = 0;
}

//------------------------------------------------------------------------------
// nullifyEdge: coloca aresta nula
//------------------------------------------------------------------------------
void MyGraph::nullifyEdge(int v1, int v2) { matrix[v1][v2] = NULL_VAL; }

//------------------------------------------------------------------------------
//  constructGraph: constroi o grafo
//------------------------------------------------------------------------------
void MyGraph::constructGraph(int n, double coor[][MAX_CITY]) {
  vertex_n = n;
  for(int i = 0; i < n; i++) {
    nullifyEdge(i, i);

    for(int j = i+1; j < n; j++) {
      double dist =
        calculateDistance(coor[0][i], coor[1][i], coor[0][j], coor[1][j]);
      addEdge(i, j, dist);
    }
  }
}

//------------------------------------------------------------------------------
//  printGraph: mostra o grafo
//------------------------------------------------------------------------------
void MyGraph::printGraph() {
  for(int i = 0; i < vertex_n; i++) {
    for(int j = 0; j < vertex_n; j++) {
      if(getEdge(i, j) != NULL_VAL) printf("%0.2f\t", getEdge(i, j));
      else printf("-\t");
    }
    printf("\n");
  }
}
