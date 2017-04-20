#include "MyGraph.h"
#include <cstdio>
#include <vector>
#include <queue>

// REF: http://www.geeksforgeeks.org/branch-bound-set-5-traveling-salesman-problem/
// REF: http://stackoverflow.com/questions/22985590/calculating-the-held-karp-lower-bound-for-the-traveling-salesmantsp
// REF: http://lcm.csa.iisc.ernet.in/dsa/node187.html

//=====================================================================
// STRUCT DE INSTANCIA DA EXECUCAO DA FILA
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
// minimal_edge_sum: soma das 2 menores arestas do vertice v
//------------------------------------------------------------------------------
double minimal_edge_sum(double* edges, int n) {
  double min, sec = 10000;

  for(int i = 0; i < n; i++) {
    if(edges[i] < min) {
      sec = min;
      min = edges[i];
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
// Branch_and_BoundÇ solucao usando branch and bound
//------------------------------------------------------------------------------
double Branch_and_Bound(MyGraph* g, int* &path) {
  double resp = 10000000.0;
  double bound = initialBound(g);
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



int main() {
  int* path = new int[100];
  MyGraph* g = new MyGraph();
  read_and_construct(g);

  double resp = Branch_and_Bound(g, path);
  print(g, resp, path);

  delete path;
  return 0;
}
