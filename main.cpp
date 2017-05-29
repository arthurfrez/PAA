#include "MyGraph.hpp"
#include "Brute.hpp"
#include "BranchBound.hpp"
#include "Genetic.hpp"
#include <cstdio>
#include <time.h>

//------------------------------------------------------------------------------
// read_and_construct: metodo para ler entrada e montar o grafo
//------------------------------------------------------------------------------
void read_and_construct(MyGraph* g) {
  double coords[2][100];
  int n;
  scanf("%i", &n);

  for(int i = 0; i < n; i++)
    scanf("%lf %lf", &coords[0][i], &coords[1][i]);

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
  clock_t ex_time = clock(); // tempo do inicio da execucao

  //double resp = BruteForce(g, path);
  //double resp = Branch_and_Bound(g, path);
  double resp = GeneticAlgorithm(g, path);

  ex_time = clock() - ex_time; // tempo gasto para executar

  print(g, resp, path);
  printf("\nExecution time: %0.3fs\n", ((float)ex_time)/CLOCKS_PER_SEC);

  return 0;
}
