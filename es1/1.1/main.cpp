
#include "../../librerie/librerie.h"
#include "../../rnd_gen/random.h"

using namespace std;

double error(double somma, double somma2, int n);

 
int main (int argc, char *argv[]){

   Random rnd;
   rnd.SetSeed();

   int const blocks=100;               //Number of blocks
   int const throws=10000;             //Total number of throws and so pseudo random number generated
   double ev, var;                     //Integral's expected value and variance for each block
   double ev_sum=0., ev2_sum=0., var_sum=0., var2_sum=0.;
   int l=throws/blocks;                // Number of throws for each block

   //saving the results on an external file
   ofstream ev_results;
   	ev_results.open("ev_results.out"); 
	ofstream var_results;
   	var_results.open("var_results.out"); 

   //1.1.1 and 1.1.2: CALCULATING THE INTEGRAL'S EXPECTED VALUE AND VARIANCE
   //Main cicle: 
   for(int i=0; i<blocks; i++)
   {
      ev=0.0, var=0.0;

      for(int j=0; j<l; j++)
      {
         double r=rnd.Rannyu();
         ev += r;
         var += pow(r-0.5, 2);
      }

      ev=ev/l, ev_sum+=ev, ev2_sum+=(ev*ev);              //calculating the expected value and ev^2
      var=var/l, var_sum+=var, var2_sum+=(var*var);       //calculating the variance and var^2

      ev_results<<i<<"  "<<(double)(ev_sum/(i+1))<<"  "<<error(ev_sum, ev2_sum, i)<<endl;
      var_results<<i<<"  "<<(double)(var_sum/(i+1))<<"  "<<error(var_sum, var2_sum, i)<<endl;
   }

   ev_results.close();
   var_results.close();
   rnd.SaveSeed();

   //1.1.3: chi^2 test

   double chi2;                           //chi2 test value
   int const N_tests=100;                 //number of times we do this test
   int count[blocks];
   ofstream chiresults;
      chiresults.open("chiresults.out");
   
   //we want to calculate 100 times the chi^2 test
   for(int tests=0; tests<N_tests; tests++)
   {
      chi2=0.;

      for(int i=0; i<blocks; i++) {count[i]=0;}

    
      for(int j=0; j<throws; j++)
      {
         double r=rnd.Rannyu();
         int which_block=(int)(r*blocks);
         count[which_block]++;
      }
         
      for(int k=0; k<blocks; k++)
      {
         chi2+=pow(count[k]-l, 2) / l;
      }

      chiresults<<chi2<<endl;

   }

   chiresults.close();
   return 0;
}
