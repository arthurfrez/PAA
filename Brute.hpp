/***********************************************************************
*	Arthur Floresta Rezende
* Brute.hpp - Metodo de forca bruta
*
* Implementacao do metodo de forca bruta para solucao
* do Problema do Caixeiro Viajante (em ingles: TSP)
***********************************************************************/

//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include "MyGraph.hpp"
#include <cstdio>
#include <vector>

//------------------------------------------------------------------------------
// copyArray: copia o array base no array final
//------------------------------------------------------------------------------
void copyArray(int size, int* base, int* &p) {
  for(int i = 0; i < size; i++) p[i] = base[i];
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
//------------------------------------------------------------------------------
void Depth_First_Search(MyGraph* g, int ver, int act,
    std::vector<bool> visited, int* tmp_path, int* &path,
    double &resp, double sum) {

  visited[ver] = true;
  tmp_path[act] = ver;
  if(act != 0 && tmp_path[act-1] != ver)
    sum = sum + g->getEdge(tmp_path[act-1], ver);

  act++;

  if(act >= g->getVertexNum()) {
    double fin = sum + g->getEdge(tmp_path[act-1], 0);
    if(fin < resp) {
      resp = fin;
      copyArray(g->getVertexNum(), tmp_path, path);
    }
  }

  for(int i = 1; i < g->getVertexNum(); i++)
    if(!visited[i])
      Depth_First_Search(g, i, act, visited, tmp_path, path, resp, sum);
}

//------------------------------------------------------------------------------
// BruteForce: solucao usando forca bruta
//------------------------------------------------------------------------------
double BruteForce(MyGraph* g, int path[100]) {
  int act = 0;
  double sum = 0.0;
  double resp = 10000000.0;
  std::vector<bool> visited(g->getVertexNum(), false);
  int* tmp_path = new int[g->getVertexNum()];

  Depth_First_Search(g, 0, act, visited, tmp_path, path, resp, sum);

  delete tmp_path;
  return resp;
}
