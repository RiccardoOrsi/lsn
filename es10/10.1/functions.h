#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <numeric>
#include <unordered_set>
#include "../../rnd_gen/random.h"
#include <mpi.h>

using namespace std;

const int n_paths = 100; // Numero di cammini per ogni generazione
const int path_size = 34; // Numero di città per ogni cammino
const int best_to_change = 5; // Numero di cammini scambiati tra i vari continenti
const int exchange_time = 12; // Generazioni tra uno scambio e l'altro
const int changes = 12; // Scambi totali

// Legge le posizioni delle città da file
void Cities_Reader(const string &path, vector<vector<double>> &positions);

// Inizializza il generatore di numeri casuali per ogni continente
void Random_Initializer(Random &rnd, int &rank);

// Mischia in maniera casuale i cammini da scambiare tra i continenti
void Shuffler(Random &rnd, vector<vector<int>> &vec);

// Genera le città casualmente su una circonferenza unitaria
vector<vector<double>> Generating_Cities_Circumference(Random &rnd);

// Genera le città casualmente in un quadrato unitario
vector<vector<double>> Generating_Cities_Square(Random &rnd);

// Stampa le posizioni delle città
void Cities_Printer(const string &path, vector<vector<double>> positions);

// Stampa il cammino migliore
void Best_Path_Printer(const string &path, vector<vector<int>> &paths_odd);

// Genera un cammino casuale
vector<int> Generating_Path(Random &rnd);

// Controlla che un cammino rispetti tutti i vincoli
void Check_Operator(vector<int> path, int &n);

// Inizializza una generazione di cammini casuali
void Generation_Creator(Random &rnd, vector<vector<int>> &paths_even, int &generation);

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
// Fa evolvere il sistema per un numero dato di generazioni
void Generation_Evolver(Random &rnd, vector<vector<int>> &paths_even, vector<vector<int>> &paths_odd, vector<vector<double>> positions, int generation, int n_generations);

// Riassegna in maniera casuale i primi 10 cammini di ogni continente
void Best_Paths_Exchange(Random &rnd, vector<vector<int>> &paths, int rank, int size);