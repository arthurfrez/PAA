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

#define MAX_CITY 100

// REF: http://www.theprojectspot.com/tutorial-post/applying-a-genetic-algorithm-to-the-travelling-salesman-problem/5
// REF: https://www.vivaolinux.com.br/script/Um-algoritmo-genetico-para-o-TSP-(Travel-Salesman-Problem)

int* generate_random_path(int size); //foward declaration

//=====================================================================
// STRUCT DO INDIVIDUO
//=====================================================================
struct individual {
  int p_size; // tamanho do caminho
  int path[MAX_CITY]; // caminho
  double finess; // aptdao do individuo
  bool state; // estado atual (modificado ou nao na populacao atual)
};

//------------------------------------------------------------------------------
// random_to_one: gera um numero pseudo aleatorio entre 0 e 1
//------------------------------------------------------------------------------
double random_to_one() { return rand() / (RAND_MAX + 1.0); }

//------------------------------------------------------------------------------
// generate_random_path: gera um caminho aleatorio
//------------------------------------------------------------------------------
int* generate_random_path(int size) {
  int* resp = new int[size];
  std::vector<int> tmp(size);

  for(int i = 0; i < size; i++) tmp[i] = i; // gerando array sequencial
  std::random_shuffle(tmp.begin()+1, tmp.end()); //embaralhando

  // copiando vetor para array
  for(int i = 0; i < size; i++)
    resp[i] = tmp[i];

  return resp;
}

//------------------------------------------------------------------------------
// crossover: mescla os parentes
//------------------------------------------------------------------------------
individual crossover(individual parent1, individual parent2) {
  individual child;
  int init_pos = (rand() % (parent1.p_size-1)) + 1;
  int fin_pos = (rand() % (parent1.p_size-1)) + 1;

  if(init_pos > fin_pos) {
    int aux = fin_pos;
    fin_pos = init_pos;
    init_pos = aux;
  }

  child.p_size = parent1.p_size;

  // parte to parente 1
  for(int i = init_pos; i < fin_pos; i++)
    child.path[i] = parent1.path[i];

  // parte do parente 2
  for(int i = 0; i < init_pos; i++)
    child.path[i] = parent2.path[i];
  for(int i = fin_pos; i < child.p_size; i++)
    child.path[i] = parent2.path[i];
}

//------------------------------------------------------------------------------
// mutate: gera mutacoes na populacao
//------------------------------------------------------------------------------
void mutate(individual ind) {
  double mutation_rate = 0.015; // frequencia da mutacao

  for(int i = 1; i < ind.p_size; i++) {
    // indice de mutacao
    if(random_to_one() < mutation_rate) {
      int pos = rand() % ind.p_size;

      // swap
      int aux = ind.path[pos];
      ind.path[pos] = ind.path[i];
      ind.path[i] = aux;
    }
  }
}

//------------------------------------------------------------------------------
// GeneticAlgorithm: solucao usando algoritmo genetico
//------------------------------------------------------------------------------
double GeneticAlgorithm(MyGraph* g, int* &path) {
  srand(time(0));
  int size = g->getVertexNum();
  int* tmp_path = generate_random_path(size);

  delete tmp_path;
  return 0.0;
}
