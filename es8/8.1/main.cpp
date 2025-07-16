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

int main () {

   // Inizializzo il generatore random
   Random rnd;
   rnd.SetSeed();

   // Data blocking
   int N; // Numero di blocchi
   int L; // Lunghezza dei blocchi
   // Parametri per il campionamento
   double rho;
   double sigma[2];
   double mu[2];


   ifstream inputFile("input.dat");
   if (!inputFile) {
      cerr << "Errore nell'aprire il file." << endl;
      return 1;
   }
   
   //Diamo due valori di sigma e mu per fare due prove diverse
   inputFile >> N >> L >> rho >> sigma[0] >> mu[0] >> sigma[1] >> mu[1];
   inputFile.close();
   ofstream output("OUTPUT/output.dat"), posizioni("OUTPUT/position.dat");
   ofstream output_2("OUTPUT/output_2.dat"), posizioni_2("OUTPUT/position_2.dat");

   for(int a=0; a<2; a++){     //ciclo esterno per fare due simulazioni con data set diversi
      // Scelgo una posizione di partenza ed effetuo l'equilibrazione: 100 blocchi da 1000 step l'uno
      double x = 0.0;
      Equilibrate(100, 1000, x, rnd, rho, sigma[a], mu[a]);

      double mean=0;
      double sum_prog=0, sum2_prog=0;
      double acceptance=0;
      vector<double> position;

      position.push_back(x);

      // Faccio evolvere il mio sistema e valuto il valore dell'Hamiltoniana col metodo della Blocking Average
         for (int i=0;i<N;i++) {
            double sum = 0.0;
            double attempted = 0;
            double accepted = 0;
            mean=0;
            acceptance=0.;

            for (int j=0;j<L;j++){
               Step(rnd, x, rho, attempted, accepted, sigma[a], mu[a]);
               sum += ((-0.5*Psi_Second_Derivate(x, sigma[a], mu[a]))/Psi(x, sigma[a], mu[a])) + Potential(x);
               position.push_back(x);
               if(a==0){posizioni << position[j] << endl;}
               else{posizioni_2  << position[j] << endl;}
            }

            mean=(sum/L);
            sum_prog+=mean;
            sum2_prog+=mean*mean;
            acceptance=(accepted/attempted);

            if(a==0){
            // Stampo i valori della prima Hamiltoniana con la rispettiva incertezza in funzione dei blocchi
               output << i << " " << (double)(sum_prog/(i+1))<<" "<<error(sum_prog, sum2_prog, i) << " " << acceptance << endl;
            }
            else if(a==1){
            // Stampo i valori della seconda Hamiltoniana con la rispettiva incertezza in funzione dei blocchi
               output_2 << i << " " << (double)(sum_prog/(i+1))<<" "<<error(sum_prog, sum2_prog, i) << " " << acceptance << endl;
            }
         }
         position.clear();
      }
   
   posizioni.close(), output.close();
   output_2.close(), posizioni_2.close();

   rnd.SaveSeed();
   return 0;
}