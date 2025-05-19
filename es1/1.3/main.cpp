
#include "../../librerie/librerie.h"
#include "../../rnd_gen/random.h"

using namespace std;

 
int main (int argc, char *argv[]){

   Random rnd;
   rnd.SetSeed();
   int const blocks=100;                        //Number of Pi extimations that the programm does
   int Throws;                                  // Throws=number of throws

   double l=1., d=3.;                           //l=needle lenghth, d= distance between stripes (must be d>l)
   int hits=0;                                  //Number of times that the needle hits the stripe
   double pi=0;                                //Pi estimation
   double pi_sum=0., pi2_sum=0;
   ofstream results;
      results.open("piresults.out");            

   cout<<endl<<"how many throws do you want to take? ";
   cin>>Throws;

   for(int i=0; i<blocks; i++)
   {
      hits=0;
      for(int j=0; j<Throws; j++)
      {
         double distance = rnd.Rannyu(0., d / 2.0);         //distance between the needle's centre and the closest line
         double theta = rnd.Rannyu(0., M_PI);        //angolo tra ago e righe

            if ((l / 2.0) * sin(theta) >= distance) 
            {hits++;}

      }
      pi=(2.*l*Throws)/(hits*d);
      pi_sum+=pi, pi2_sum+=(pi*pi);
      results<<i<<"  "<<(double)(pi_sum/(i+1))<<"  "<<error(pi_sum, pi2_sum, i)<<endl;
   }


   results.close();   
   rnd.SaveSeed();
   return 0;

}

