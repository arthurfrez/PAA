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
#define POPULATION_SIZE 50
#define EVOLUTION_NUM 100
#define TOURNAMENT_SIZE 5

// REF: http://www.theprojectspot.com/tutorial-post/applying-a-genetic-algorithm-to-the-travelling-salesman-problem/5
// REF: https://www.vivaolinux.com.br/script/Um-algoritmo-genetico-para-o-TSP-(Travel-Salesman-Problem)
// REF: https://github.com/parano/GeneticAlgorithm-TSP
// REF: http://user.ceng.metu.edu.tr/~ucoluk/research/publications/tspnew.pdf
// REF: http://stackoverflow.com/questions/1544055/%D0%A1rossover-operation-in-genetic-algorithm-for-tsp
// HEADER: http://www.umich.edu/~eecs381/handouts/CppHeaderFileGuidelines.pdf

int* generate_random_path(int); // prototipo da funcao
MyGraph* graph;

//=====================================================================
// STRUCT DO INDIVIDUO
//=====================================================================
struct individual {
  int size; // tamanho do caminho
  int path[MAX_CITY]; // caminho
  double fitness; // aptdao do individuo
  void calculate_fitness();

  individual();
  individual(individual*);
  //~individual();
};

// boo
void individual::calculate_fitness() {
  fitness = 0.0;
  for(int i = 1; i < size; i++)
    fitness += graph->getEdge(path[i], path[i-1]);
  fitness += graph->getEdge(path[size-1], 0);
}
individual::individual() {  }
individual::individual(individual * ind) {
  size = ind->size;
  fitness = ind->fitness;
  for(int i = 0; i < size; i++)
    path[i] = ind->path[i];
}
//individual::~individual() { delete path; }

//------------------------------------------------------------------------------
// random_to_one: gera um numero pseudo aleatorio entre 0 e 1
//------------------------------------------------------------------------------
double random_to_one() { return rand() / (RAND_MAX + 1.0); }

//------------------------------------------------------------------------------
// generate_random_path: gera um caminho aleatorio
//------------------------------------------------------------------------------
void generate_random_path(int size, int path[MAX_CITY]) {
  std::vector<int> tmp(size);

  for(int i = 0; i < size; i++) tmp[i] = i; // gerando array sequencial
  std::random_shuffle(tmp.begin()+1, tmp.end()); //embaralhando

  // copiando vetor para array
  for(int i = 0; i < size; i++)
    path[i] = tmp[i];
}

//------------------------------------------------------------------------------
// generate_pop: gera uma populacao
//------------------------------------------------------------------------------
individual* generate_pop(int size, int p_size) {
  individual* population = new individual[p_size];

  for(int i = 0; i < p_size; i++) {
    population[i].size = size;
    generate_random_path(size, population[i].path);
    population[i].calculate_fitness();
  }

  return population;
}

//------------------------------------------------------------------------------
// getFittest: acha a posicao do individuo mais adaptado
//------------------------------------------------------------------------------
int getFittest(individual* pop, int p_size) {
  double fit = 1000000.0;
  int pos = -1;

  for(int i = 0; i < p_size; i++) {
    if(pop[i].fitness < fit) {
      fit = pop[i].fitness;
      pos = i;
    }
  }

  return pos;
}

//------------------------------------------------------------------------------
// crossover: mescla os parentes
//------------------------------------------------------------------------------
individual crossover(individual parent1, individual parent2) { // ERRADO
  individual child;
  int init_pos = (rand() % (parent1.size-1)) + 1;
  int fin_pos = (rand() % (parent1.size-1)) + 1;

  if(init_pos > fin_pos) {
    int aux = fin_pos;
    fin_pos = init_pos;
    init_pos = aux;
  }

  child.size = parent1.size;

  // parte to parente 1
  for(int i = init_pos; i < fin_pos; i++)
    child.path[i] = parent1.path[i];

  // parte do parente 2
  for(int i = 0; i < init_pos; i++)
    child.path[i] = parent2.path[i];
  for(int i = fin_pos; i < child.size; i++)
    child.path[i] = parent2.path[i];

  child.calculate_fitness();
  return child;
}

//------------------------------------------------------------------------------
// mutate: gera mutacoes na populacao
//------------------------------------------------------------------------------
void mutate(individual &ind) {
  double mutation_rate = 0.015; // frequencia da mutacao

  for(int i = 1; i < ind.size; i++) {
    // indice de mutacao
    if(random_to_one() < mutation_rate) {
      int pos = rand() % ind.size;

      // swap
      int aux = ind.path[pos];
      ind.path[pos] = ind.path[i];
      ind.path[i] = aux;
    }
  }

  ind.calculate_fitness();
}

//------------------------------------------------------------------------------
// tournamentSelection: seleciona individual usando selecao por torneio
//------------------------------------------------------------------------------
individual* tournamentSelection(individual* pop, int p_size) {
  individual* tournament = new individual[TOURNAMENT_SIZE];
  for(int i = 0; i < TOURNAMENT_SIZE; i++)
    tournament[i] = pop[rand() % p_size];

  return &tournament[getFittest(tournament, TOURNAMENT_SIZE)];
}

//------------------------------------------------------------------------------
// evolve_pop: evolui a populacao, elitismo de 1 individuo
//------------------------------------------------------------------------------
individual* evolve_pop(individual* oldPop, int size, int p_size) {
  individual* newPop = new individual[p_size];
  newPop[0] = oldPop[getFittest(oldPop, p_size)]; // elitism
  newPop[1] = individual(newPop[0]);

  for(int i = 2; i < p_size; i++) {
    individual parent1 = individual(tournamentSelection(oldPop, p_size));
    individual parent2 = individual(tournamentSelection(oldPop, p_size));
    individual child = individual(crossover(parent1, parent2));
    newPop[i] = child;
  }

  for(int i = 1; i < p_size; i++) mutate(newPop[i]);

  return newPop;
}

//------------------------------------------------------------------------------
// GeneticAlgorithm: solucao usando algoritmo genetico
//------------------------------------------------------------------------------
double GeneticAlgorithm(MyGraph* g, int* &path) {
  srand(time(0)); // seed para aleatoriedade
  int size = g->getVertexNum();
  int p_size = POPULATION_SIZE;
  graph = g;

  individual* pop = generate_pop(size, p_size);
  for(int i = 0; i < EVOLUTION_NUM; i++)
    evolve_pop(pop, size, p_size);

  individual ind = pop[getFittest(pop, p_size)];
  double resp = ind.fitness;

  path = new int[MAX_CITY];
  for(int i = 0; i < size; i++)path[i] = ind.path[i];

  delete pop;
  return resp;
}
