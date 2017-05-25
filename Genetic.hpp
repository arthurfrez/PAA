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

//=====================================================================
// CONSTANTES
//=====================================================================
#define MAX_CITY 100
#define POPULATION_SIZE 50
#define EVOLUTION_NUM 100
#define TOURNAMENT_SIZE 5
MyGraph* graph;

//------------------------------------------------------------------------------
// generate_random_path: gera um caminho aleatorio
//------------------------------------------------------------------------------
void generate_random_path(int size, int (&path)[MAX_CITY]) {
  std::vector<int> tmp(size);

  for(int i = 0; i < size; i++) tmp[i] = i; // gerando array sequencial
  std::random_shuffle(tmp.begin()+1, tmp.end()); //embaralhando

  // copiando vetor para array
  for(int i = 0; i < size; i++)
    path[i] = tmp[i];
}

//=====================================================================
// STRUCT DO INDIVIDUO
//=====================================================================
struct individual {
  int size; // tamanho do caminho
  int path[MAX_CITY]; // caminho
  double fitness; // aptdao do individuo

  //----------------------------------------------------------------------------
  // Construtor padrao
  //----------------------------------------------------------------------------
  individual() {
    size = -1;
    fitness = -1.0;
  }

  //----------------------------------------------------------------------------
  // Construtor copiando de outro objeto
  //----------------------------------------------------------------------------
  individual(individual*) {
    size = ind->size;
    fitness = ind->fitness;
    for(int i = 0; i < size; i++)
      path[i] = ind->path[i];
  }

  //----------------------------------------------------------------------------
  // calculate_fitness: calcula o valor do caminho
  //----------------------------------------------------------------------------
  void calculate_fitness() {
    fitness = 0.0;
    for(int i = 1; i < size; i++)
      fitness += graph->getEdge(path[i], path[i-1]);
    fitness += graph->getEdge(path[size-1], 0);
  }
}; // fim da struct individuo

//------------------------------------------------------------------------------
// random_to_one: gera um numero pseudo aleatorio entre 0 e 1
//------------------------------------------------------------------------------
double random_to_one() { return rand() / (RAND_MAX + 1.0); }

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
// getSecond: acha a posicao do segundo individuo mais adaptado
//------------------------------------------------------------------------------
int getSecond(individual* pop, int p_size, int fittest_pos) {
  double fit = 1000000.0;
  int pos = -1;

  for(int i = 0; i < p_size; i++) {
    if(pop[i].fitness < fit && i != fittest_pos) {
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
  int init_pos = (rand() % (parent1.size-1)) + 1; // posicao aleatoria inicial
  int fin_pos = (rand() % (parent1.size-1)) + 1; // posicao aleatoria final

  // colocando o menor e o maior dos numeros em ordem
  if(init_pos > fin_pos) {
    int aux = fin_pos;
    fin_pos = init_pos;
    init_pos = aux;
  }

  child.size = parent1.size;

  // vetor para saber quais vertices ja estao no individuo filho
  bool* hasIt = new bool[child.size];
  for(int i = 0; i < child.size; i++)
    hasIt[i] = false;

  // parte to parente 1
  for(int i = init_pos; i < fin_pos; i++) {
    child.path[i] = parent1.path[i];

    // Ja colocado o vertice no caminho
    hasIt[parent1.path[i]] = true;
  }

  // posicao no vetor do parente a ser copiado
  int a_pos = 0;

  // parte do parente 2: antes da posicao inicial do parente 1
  for(int i = 0; i < init_pos; i++) {
    while(hasIt[parent2.path[a_pos]])
          a_pos += 1;

    child.path[i] = parent2.path[a_pos++];
  }

  // parte do parente 2: dopois da posicao final do parente 1
  for(int i = fin_pos; i < child.size; i++) {
    while(hasIt[parent2.path[a_pos]])
          a_pos += 1;

    child.path[i] = parent2.path[a_pos++];
  }

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
      int pos = (rand() % (ind.size-1)) + 1;

      // swap
      int aux = ind.path[pos];
      ind.path[pos] = ind.path[i];
      ind.path[i] = aux;
    }
  }

  ind.calculate_fitness();
}

//------------------------------------------------------------------------------
// tournamentSelection: seleciona os parentes usando selecao por torneio
//------------------------------------------------------------------------------
void tournamentSelection(individual* pop, int p_size,
  individual &p1, individual &p2) {

  individual* tournament = new individual[TOURNAMENT_SIZE];
  for(int i = 0; i < TOURNAMENT_SIZE; i++)
    tournament[i] = pop[(rand() % (p_size-1))+1];

  int fit = getFittest(tournament, TOURNAMENT_SIZE);
  int sec = getSecond(tournament, TOURNAMENT_SIZE, fit);
  p1 = individual(tournament[fit]);
  p2 = individual(tournament[sec]);
}

//------------------------------------------------------------------------------
// evolve_pop: evolui a populacao, elitismo de 1 individuo
//------------------------------------------------------------------------------
individual* evolve_pop(individual* oldPop, int size, int p_size) {
  individual* newPop = new individual[p_size];
  newPop[0] = oldPop[getFittest(oldPop, p_size)]; // elitism

  // gerando filhos por crossover
  for(int i = 1; i < p_size; i++) {
    individual parent1, parent2;
    tournamentSelection(oldPop, p_size, parent1, parent2);
    individual child = individual(crossover(parent1, parent2));
    newPop[i] = child;
  }

  // mutando a partir do segundo individuo para manter o elitismo
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
    pop = evolve_pop(pop, size, p_size);

  individual ind = pop[getFittest(pop, p_size)];
  double resp = ind.fitness;

  path = new int[MAX_CITY];
  for(int i = 0; i < size; i++)path[i] = ind.path[i];

  delete [] pop;
  return resp;
}
