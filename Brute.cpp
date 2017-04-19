#include "MyGraph.h"
#include <cstdio>
#include <vector>
#include <queue>

//=====================================================================
// STRUCT DE INSTANCIA DA EXECUCAO DA FILE
//=====================================================================
struct execInstance {
  int act;
  double sum;
  std::vector<bool> visited;
  int path[100];

  // Construtor
  execInstance(int n) {
    sum = 0.0;
    act = 0;

    std::vector<bool> v(n, false);
    visited = v;
  }
};

//------------------------------------------------------------------------------
// BruteForce: solucao usando forca bruta
//------------------------------------------------------------------------------
double BruteForce(MyGraph* g, int* &path) {
  double resp = 10000000.0;
  int size = g->getVertexNum();
  std::queue<execInstance> exec;

  // inicializa a fila de execucao
  exec.push(execInstance(size));
  exec.back().act = 1;
  exec.back().visited[0] = true;
  exec.back().path[0] = 0;

  while(!exec.empty()) {
    execInstance act = exec.front();
    exec.pop();

    if(act.act < size) {
      for(int i = 0 ; i < size; i++) {
        if(act.visited[i] == false) {
          execInstance copy = act;
          double weight =  g->getEdge(i, copy.path[copy.act-1]);
          weight = (weight != -1) ? weight : 0; // checka se existe aresta

          copy.sum = copy.sum + weight;
          copy.visited[i] = true;
          copy.path[copy.act] = i;
          copy.act++;

          exec.push(copy);
        }
      }
    }
    else if((act.sum + g->getEdge(act.path[size-1], 0)) < resp) {
      resp = act.sum + g->getEdge(act.path[size-1], 0);
      path = act.path;
    }
  }

  return resp;
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
