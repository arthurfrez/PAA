/***********************************************************************
*	Arthur Floresta Rezende
* Genetic.hpp - Metodo de Algoritmo Genetico
*
* Implementacao do metodo de algoritimo genetico para solucao
* do Problema do Caixeiro Viajante (em ingles: TSP)
***********************************************************************/

//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include "MyGraph.hpp"
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

// REF: http://www.theprojectspot.com/tutorial-post/applying-a-genetic-algorithm-to-the-travelling-salesman-problem/5

int* generate_random_path(int size); //foward declaration

struct Population {
  int pos;
  int qnt_p;
  double fittest_weight;
  int** tours;

  void get_fittest() {

  }

  Population(int size, int p_size) {
    qnt_p = size;
    tours = new int*[qnt_p];
    for(int i = 0; i < qnt_p; i++) tours[i] = generate_random_path(p_size);
    get_fittest();
  }

  ~Population() {
    for(int i = 0; i < qnt_p; i++) delete tours[i];
    delete tours;
  }
};

//------------------------------------------------------------------------------
// generate_random_path: gera um caminho aleatorio
//------------------------------------------------------------------------------
int* generate_random_path(int size) {
  int* resp = new int[size];
  std::vector<int> tmp(size);

  for(int i = 0; i < size; i++) tmp[i] = i; // gerando array sequencial
  srand(time(0)); // mudando a seed inicial para gerar aleatoriedade
  std::random_shuffle(tmp.begin()+1, tmp.end()); //embaralhando

  // copiando vetor para array
  for(int i = 0; i < size; i++)
    resp[i] = tmp[i];

  return resp;
}

//------------------------------------------------------------------------------
// GeneticAlgorithm: solucao usando algoritmo genetico
//------------------------------------------------------------------------------
double GeneticAlgorithm(MyGraph* g, int* &path) {
  int size = g->getVertexNum();
  int* tmp_path = generate_random_path(size);

  delete tmp_path;
  return 0.0;
}
