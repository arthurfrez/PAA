#include "MyGraph.h"
#include <cstdio>
#include <vector>
#include <queue>

int* path;

// instancia de execucao da pilha
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
// BruteForce: solucao usando forca bruta
//------------------------------------------------------------------------------
double BruteForce(MyGraph* g) {
  double resp = -1.0;
  int size = g->getVertexNum();
  std::queue<execInstance> exec;

  // inicializa a fila de execucao
  for(int i = 0; i < size; i++) {
    exec.push(execInstance(size));
    exec.back().act = 1;
    exec.back().visited[i] = true;
    exec.back().path[0] = i;
  }

  while(!exec.empty()) {
    execInstance act = exec.front();
    exec.pop();

    if(act.act < size) {
      for(int i = 0 ; i < size; i++) {
        if(i != act.path[act.act-1] && act.visited[i] == false) {
          execInstance copy = act;
          copy.sum = g->getEdge(i, copy.path[copy.act-1]);
          copy.visited[i] = true;
          copy.path[copy.act] = i;
          copy.act++;

          exec.push(copy);
        }
      }
    }
    else if(act.sum > resp) {
      resp = act.sum;
      path = act.path;
    }
  }

  return resp;
}

//------------------------------------------------------------------------------
// print: Metodo para mostrar a resposta no formato pedido
//------------------------------------------------------------------------------
void print(MyGraph* g, double resp) {
  printf("%.2f\n", resp);
  for(int i = 0; i < g->getVertexNum(); i++)
    printf("%d ", path[i]);
  printf("\n");
}

//------------------------------------------------------------------------------
// METODO PRINCIPAL
//------------------------------------------------------------------------------
int main() {
  path = new int[100];
  MyGraph* g = new MyGraph();
  read_and_construct(g);

  double resp = BruteForce(g);
  print(g, resp);

  delete path;
  return 0;
}
