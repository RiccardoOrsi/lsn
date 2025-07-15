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
#include "system.h"

using namespace std;

int main (int argc, char *argv[]){
  if(argc!=2 and (argv[1]!="solid" or argv[1]!="liquid" or argv[1]!="gas" or argv[1]!="tgas" or argv[1]!="tliquid" or argv[1]!="tsolid")){
    cerr<<"ERRORE: digitare uno fra <gas/liquid/solid> all'avvio";
    exit(-1);
  }

  
  int nconf = 1;
  string state=string(argv[1]);
  System SYS;
  SYS.initialize(state);
  SYS.initialize_properties(state);
  SYS.block_reset(0, state);

  for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
      SYS.step();
      SYS.measure();
      if(j%10 == 0){
//        SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
        nconf++;
      }
    }
    SYS.averages(i+1, state);
    SYS.block_reset(i+1, state);
  }
  SYS.finalize(state );

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
