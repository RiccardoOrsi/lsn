
#include "../../librerie/librerie.h"
#include "../../rnd_gen/random.h"

using namespace std;

int main (int argc, char *argv[]){

   Random rnd;
   rnd.SetSeed();

   ofstream exp, unif, lorentz;
   exp.open("exp.out"), unif.open("unif.out"), lorentz.open("lorentz.out");      //Opening files
   double sum_exp=0., sum_unif=0., sum_lorentz=0.;
  
   
   for(int n=0; n<4; n++)        //external for cycle written in order to make the switch-case work
   {

   for(int i=0; i<10000; i++)
   {
      sum_exp=0., sum_unif=0., sum_lorentz=0.;

      switch (n)        //
      {
      case 0:
         exp<<rnd.exp(1.)<<endl;
         unif<<rnd.Rannyu()<<endl;
         lorentz<<rnd.Lorentz(1., 0.)<<endl;
         break;
      
      case 1:
      for(int a=0; a<2; a++)
      {sum_exp+=rnd.exp(1.0), sum_unif+=rnd.Rannyu(), sum_lorentz+=rnd.Lorentz(1., 0.); }
         
         exp<< sum_exp/2.0 <<endl;
         unif<< sum_unif/2.0 <<endl;
         lorentz<< sum_lorentz/2.0 <<endl;

         break;

      case 2:
      for(int a=0; a<10; a++)
      {sum_exp+=rnd.exp(1.0), sum_unif+=rnd.Rannyu(), sum_lorentz+=rnd.Lorentz(1., 0.); }
         
         exp<< sum_exp/10.0 <<endl;
         unif<< sum_unif/10.0 <<endl;
         lorentz<< sum_lorentz/10.0 <<endl;

         break;

      case 3:
      for(int a=0; a<100; a++)
      {sum_exp+=rnd.exp(1.0), sum_unif+=rnd.Rannyu(), sum_lorentz+=rnd.Lorentz(1., 0.); }
         
         exp<< sum_exp/100.0 <<endl;
         unif<< sum_unif/100.0 <<endl;
         lorentz<< sum_lorentz/100.0 <<endl;

         break;
      

      }
   }
   }

   rnd.SaveSeed();
   exp.close(), unif.close(); lorentz.close();        //Closing files
   return 0;
   

}