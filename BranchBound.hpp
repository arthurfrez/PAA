#include "MyGraph.hpp"
#include <cstdio>
#include <vector>
#include <queue>

// REF: http://www.geeksforgeeks.org/branch-bound-set-5-traveling-salesman-problem/
// REF: http://stackoverflow.com/questions/22985590/calculating-the-held-karp-lower-bound-for-the-traveling-salesmantsp
// REF: http://lcm.csa.iisc.ernet.in/dsa/node187.html
// REF: https://github.com/karepker/little-tsp

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

/*void buscaEmLargura(MyGraph* g, int init, std::vector<bool> visited) {
	queue<vector<int>> q;

  while (!q.empty()) {

    q.pop();
  }
}*/

//------------------------------------------------------------------------------
// Branch_and_BoundÇ solucao usando branch and bound
//------------------------------------------------------------------------------
double Branch_and_Bound(MyGraph* g, int* &path) {
  double resp = 10000000.0;
  double bound = initialBound(g);
  int size = g->getVertexNum();

  //for();

  return resp;
}
