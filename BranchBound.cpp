#include "MyGraph.h"
#include <ctdio>

// REF: http://www.geeksforgeeks.org/branch-bound-set-5-traveling-salesman-problem/
// REF: http://stackoverflow.com/questions/22985590/calculating-the-held-karp-lower-bound-for-the-traveling-salesmantsp

int findLower() {
  return 0;
}
double Branch_and_Bound(MyGraph* g, int* &path) {
  return 0.0;
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
