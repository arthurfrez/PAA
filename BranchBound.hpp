/***********************************************************************
*	Arthur Floresta Rezende
* BranchBound.hpp - Metodo de Branch and Bound
*
* Implementacao do metodo de branch and bound para solucao
* do Problema do Caixeiro Viajante (em ingles: TSP)
***********************************************************************/

//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include "MyGraph.hpp"
#include <cstdio>
#include <vector>

//------------------------------------------------------------------------------
// minimal_edge_sum: soma das 2 menores arestas do vertice v
//------------------------------------------------------------------------------
double minimal_edge_sum(double* edges, int n) {
  double min = 100000.0;
  double sec = 100000.0;


  for(int i = 0; i < n; i++) {
    if(edges[i] != -1) {
      if(edges[i] < min) {
        sec = min;
        min = edges[i];
      }
      else if(edges[i] < sec) {
        sec = edges[i];
      }
    }
  }

  return min + sec;
}

//------------------------------------------------------------------------------
// initialBound: calcula o primeiro bound
//------------------------------------------------------------------------------
double initialBound(MyGraph* g) {
  double firstBound = 0.0;
  for(int i = 0; i < g->getVertexNum(); i++) {
    firstBound += minimal_edge_sum(g->get_all_edges(i), g->getVertexNum());
  }

  return firstBound/2;
}

//------------------------------------------------------------------------------
// Depth_First_Search: busca em profundidade
//
// Parametros:
//    Grafo: g
//    Vertice atual: ver
//    Posicao atual do caminho: act
//    Vetor de visitados: visited
//    Caminho atual: tmp_path
//    Caminho final: path
//    Resposta: resp
//    Soma atual: sum
//    Valor do bound atual: bound
//------------------------------------------------------------------------------
void Depth_First_Search(MyGraph* g, int ver, int act,
    std::vector<bool> visited, int* tmp_path, int* &path,
    double &resp, double sum, double &bound) {

  visited[ver] = true;
  tmp_path[act] = ver;
  if(act != 0 && tmp_path[act-1] != ver)
    sum = sum + g->getEdge(tmp_path[act-1], ver);

  // cortando o branch
  if(sum > bound) return;

  act++;

  if(act >= g->getVertexNum()) {
    double fin = sum + g->getEdge(tmp_path[act-1], 0);

    if(fin < resp) {
      resp = fin;
      copyArray(g->getVertexNum(), tmp_path, path);
      bound = resp;
    }
  }

  for(int i = 1; i < g->getVertexNum(); i++)
    if(!visited[i])
      Depth_First_Search(g, i, act, visited, tmp_path, path, resp, sum, bound);
}

//------------------------------------------------------------------------------
// Branch_and_Bound: solucao usando branch and bound
//------------------------------------------------------------------------------
double Branch_and_Bound(MyGraph* g, int* &path) {
  int act = 0;
  double sum = 0.0;
  double resp = 10000000.0;
  std::vector<bool> visited(g->getVertexNum(), false);
  int* tmp_path = new int[g->getVertexNum()];
  double bound = initialBound(g);

  Depth_First_Search(g, 0, act, visited, tmp_path, path, resp, sum, bound);

  delete tmp_path;
  return resp;
}
