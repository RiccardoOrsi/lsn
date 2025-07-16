#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>

#include "../../rnd_gen/random.h"

using namespace std;

// Genera le città casualmente su una circonferenza unitaria
vector<vector<double>> Generating_Cities_Circumference(Random &rnd);

// Genera le città casualmente in un quadrato unitario
vector<vector<double>> Generating_Cities_Square(Random &rnd);

// Genera un cammino casuale
vector<int> Generating_Path(Random &rnd);

// Controlla che un cammino rispetti tutti i vincoli
void Check_Operator(vector<int> path, int &n);

// Misura la metrica di un cammino
double Metric(vector<int> path, vector<vector<double>> positions);

// Ordina i cammini di una generazione in ordine crescente di metrica
void Sorting_Generation(vector<vector<int>> &paths, vector<vector<double>> positions);

// Seleziona un cammino da una generazione scegliendo con maggiore probabilità i migliori
int Selection_Operator(Random &rnd);

// Rispetta le condizioni periodiche al contorno
int pbc(int i);

// Effettua una permutazione di una coppia di città casuali
void Pair_Permutation(vector<int> &path, Random &rnd);

// Effettua uno shifting casuale di un blocco di città
void Shifting(vector<int> &path, Random &rnd);

// Effettua una permutazione casuale all'interno di un blocco di città
void Permutation(vector<int> &path, Random &rnd);

// Inverte l'ordine delle città all'interno di un blocco
void Order_Inversion(vector<int> &path, Random &rnd);

// Effettua il crossover tra due cammini genitori
void Crossover(vector<int> &path1, vector<int> &path2, Random &rnd);

// Fa avvenire le varie mutazioni con una data probabilità
bool Calling_probability(Random &rnd, double p);

// Fa evolvere il sistema generando una generazione dispari
void Odd_Generation_Generator(Random &rnd, vector<vector<int>> &paths_even, vector<vector<int>> &paths_odd, vector<vector<double>> positions, int generation);

// Fa evolvere il sistema generando una generazione pari
void Even_Generation_Generator(Random &rnd, vector<vector<int>> &paths_even, vector<vector<int>> &paths_odd, vector<vector<double>> positions, int generation);