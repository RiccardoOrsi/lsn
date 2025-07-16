#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include "functions.h"
#include "../../librerie/librerie.h"

using namespace std;

int main ( int argc, char** argv ) {

   // Inizializzo il generatore random
   Random rnd;
   rnd.SetSeed();
   // Inizializzo le variabili necessarie e le leggo dal file di input
   int N; // Numero di blocchi
   int L; // Lunghezza dei blocchi
   double rho; // Parametri per il campionamento
   double sigma;
   double mu;
   double T; // Temperatura di partenza

   ifstream inputFile("input.dat");

   if (!inputFile) {
      cerr << "Errore nell'aprire il file." << endl;
      return 1;
   }
   
   inputFile >> N >> L >> rho >> sigma >> mu >> T;

   // Definisco i paramteri necessari all'ottimizzazione dei parametri
   double beta = 1/T;
   double energy = 1.;
   double currentEnergy = energy;
   double currentError = 0.;
   double bestEnergy = energy;
   double bestParameters[2] = {sigma, mu};

   double x = 0.0;

   ofstream output_opt("OUTPUT/optimization.dat");
   ofstream output_par("OUTPUT/parameters.dat");

   // Ciclo sulla temperatura
   while (T>=0.01) {

      double old_sigma = sigma;
      double old_mu = mu;

      // Faccio evolvere i parametri
      sigma = abs(old_sigma + rnd.Rannyu(-1, 1) * .25 * T);
      mu = abs(old_mu + rnd.Rannyu(-1, 1) * .5 * T);

      // Eseguo l'equilibrazione e calcolo il valore dell'Hamiltoniana
      Equilibrate(N, L, x, rnd, rho, sigma, mu);

      double mean=0;
      double sum_prog=0, sum2_prog=0;
      double acceptance=0;

      for (int i=0;i<N;i++) {
         double sum = 0.0;
         double attempted = 0.0;
         double accepted = 0.0;
         mean=0;
         acceptance=0.;

         for (int j=0;j<L;j++){
            Step(rnd, x, rho, attempted, accepted, sigma, mu);
            sum += ((-0.5*Psi_Second_Derivate(x, sigma, mu))/Psi(x, sigma, mu)) + Potential(x);
         }
         mean=(sum/L);
         sum_prog+=mean;
         sum2_prog+=mean*mean;
         acceptance=(accepted/attempted);
      }

      currentEnergy = sum_prog/(N-1);
      currentError = error(sum_prog, sum2_prog, N-1);

      double A = min(1., (exp(- beta * (currentEnergy - energy))));
      double p = rnd.Rannyu();

      // Aggiorno l'energia e i paramteri con una certa probabilità
      if (A > p)
         energy = currentEnergy;
      else{
         mu = old_mu;
         sigma = old_sigma;
      }

      output_opt << T << " " << energy << " " << currentError << endl;
      output_par << T << " " << sigma << " " << mu << endl;

      T = T * 0.997;
      beta = 1/T;

      // Salvo i parametri migliori
      if (bestEnergy > energy) {
         bestEnergy = energy;
         bestParameters[0] = sigma;
         bestParameters[1] = mu;
      }
   }

   output_opt.close();
   output_par.close();

   // Stampo i paramteri best
   sigma = bestParameters[0];
   mu = bestParameters[1];

   ofstream output_best_par("OUTPUT/best_parameters.dat");

   output_best_par << sigma << " " << mu << endl;
   
   output_best_par.close();

   // Rieseguo la simulazione da zero coi parametri ottimali
   x = 0.0;

   Equilibrate(N, L, x, rnd, rho, sigma, mu);

   double mean=0;
   double sum_prog=0, sum2_prog=0;
   double acceptance=0;
   vector<double> position;
   ofstream output("OUTPUT/output.dat");
   ofstream posizioni("OUTPUT/position.dat");

   position.push_back(x);

   for (int i=0;i<N;i++) {
      double sum = 0.0;
      double attempted = 0.0;
      double accepted = 0.0;
      mean=0;
      acceptance=0.;

      for (int j=0;j<L;j++){
         Step(rnd, x, rho, attempted, accepted, sigma, mu);
         sum += ((-0.5*Psi_Second_Derivate(x, sigma, mu))/Psi(x, sigma, mu)) + Potential(x);
         position.push_back(x);
         posizioni << position[j] << endl;
      }
      mean=(sum/L);
      sum_prog+=mean;
      sum2_prog+=mean*mean;
      acceptance=(accepted/attempted);

      output << (double)(sum_prog/(i+1)) << " " << error(sum_prog, sum2_prog, i) << " " << acceptance << endl;

   }

   output.close();
   posizioni.close();
   
   rnd.SaveSeed();
   return 0;
}