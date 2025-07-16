/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "system.h"

using namespace std;

int main (int argc, char *argv[]){
  if(argc<2 or argc>3){
    cerr<<"ERRORE: digitare uno fra <GIBBS/METRO> all'avvio";
    exit(-1);
  }

  int nconf = 1;
  string in = string(argv[1]);      //scelta del file di input (es: input.GIBBS)
  string out = string(argv[2])+"/"+string(argv[1]);     //directory di output (es in+)
  System SYS;


  SYS.initialize(in, out);
  SYS.initialize_properties(out);
  SYS.block_reset(0, out);

  for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
      SYS.step();
      SYS.measure();
      if(j%10 == 0){
//        SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
        nconf++;
      }
    }
    SYS.averages(i+1, out);
    SYS.block_reset(i+1, out);
  }
  SYS.finalize(out);

  return 0;
}


/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
