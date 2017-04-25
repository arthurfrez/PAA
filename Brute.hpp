#include "MyGraph.hpp"
#include <cstdio>
#include <vector>

//------------------------------------------------------------------------------
// copyPointer: copia o array
//------------------------------------------------------------------------------
void copyPointer(int size, int* base, int* &p) {
  for(int i = 0; i < size; i++) p[i] = base[i];
}

//------------------------------------------------------------------------------
// Depth_First_Search: busca em profundidade
//------------------------------------------------------------------------------
double Depth_First_Search(MyGraph*g, int ver, int size, int act, std::vector<bool> visited, int* tmp_path, int* &path, double &resp, double sum) {
  visited[ver] = true;
  tmp_path[act] = ver;
  if(act != 0 && tmp_path[act-1] != ver) sum = sum + g->getEdge(tmp_path[act-1], ver);
  act++;

  if(act >= size) {
    double fin = sum + g->getEdge(tmp_path[act-1], 0);
    if(fin < resp) {
      resp = fin;
      copyPointer(size, tmp_path, path);
    }
  }

  for(int i = 1; i < size; i++)
    if(!visited[i]) Depth_First_Search(g, i, size, act, visited, tmp_path, path, resp, sum);

  return resp;
}

//------------------------------------------------------------------------------
// BruteForce: solucao usando forca bruta
//------------------------------------------------------------------------------
double BruteForce(MyGraph* g, int* &path) {
  int act = 0;
  double sum = 0.0;
  double resp = 10000000.0;
  int size = g->getVertexNum();
  std::vector<bool> visited(size, false);
  int* tmp_path = new int[size];

  return Depth_First_Search(g, 0, size, act, visited, tmp_path, path, resp, sum);
}
