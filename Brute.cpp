#include "MyGraph.h"
#include <cstdio>
#include <vector>
#include <queue>

// REF: https://github.com/samlbest/traveling-salesman
// REF: https://github.com/karepker/little-tsp

//------------------------------------------------------------------------------
// Depth_First_Search: busca em profundidade
//------------------------------------------------------------------------------
double Depth_First_Search(MyGraph*g, int ver, int size, int act, std::vector<bool> visited, int* &path, double &resp, double &sum) {
  visited[ver] = true;
  path[act] = ver;
  if(act != 0 && g->getEdge(path[act-1], ver) != -1) sum = sum + g->getEdge(path[act-1], ver);
  act++;

  //printf("So testando: Sum: %f   Resp: %f\n", sum, resp);
  //printf("Outro Teste, act: %i   ver: %i\n", (act-1), ver);

  if(act >= size)
    if(sum < resp)
      resp = sum;

  for(int i = 1; i < size; i++)
    if(!visited[i]) Depth_First_Search(g, i, size, act, visited, path, resp, sum);

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

  return Depth_First_Search(g, 0, size, act, visited, path, resp, sum);
}

//------------------------------------------------------------------------------
// read_and_construct: metodo para ler entrada e montar o grafo
//------------------------------------------------------------------------------
void read_and_construct(MyGraph* g) {
  int coords[2][100];
  int n;
  scanf("%i", &n);

  for(int i = 0; i < n; i++)
    scanf("%i %i", &coords[0][i], &coords[1][i]);

  g->constructGraph(n, coords);
}

//------------------------------------------------------------------------------
// print: Metodo para mostrar a resposta no formato pedido
//------------------------------------------------------------------------------
void print(MyGraph* g, double resp, int* path) {
  printf("%.2f\n", resp);
  for(int i = 0; i < g->getVertexNum(); i++)
    printf("%d ", (path[i]+1));
  printf("\n");
}

//------------------------------------------------------------------------------
// METODO PRINCIPAL
//------------------------------------------------------------------------------
int main() {
  int* path = new int[100];
  MyGraph* g = new MyGraph();
  read_and_construct(g);

  double resp = BruteForce(g, path);
  print(g, resp, path);

  delete path;
  return 0;
}
