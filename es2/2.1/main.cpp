
#include "../../librerie/librerie.h"
#include "../../rnd_gen/random.h"

double function(double x)
{
    return (M_PI/2.)*cos(M_PI*x/2.);
}

using namespace std;

int main()
{
    Random rnd;                                     //Variable that allocates the rng methods
    rnd.SetSeed();                                  //Setting the seed of the RNG  

    int const blocks=100;                           //Blocks used for data blocking
    int const throws=10000;                         //Throws taken for eaxh block
    double integral;                                //Variable that allocates the value of the integral
    double integral_sum=0., integral2_sum=0.;             //variables used for the error evaluation with the data blocking method

    ofstream results;
    results.open("results.out");

    for(int i=0; i<blocks; i++) //external cycle for error's evaluation
    {
        integral=0.;

        for(int j=0; j<throws; j++) //Inner cycle used for integral's evaluation
        {
            double x=rnd.Rannyu();
            integral += function(x);

        }

        integral=(double)integral/throws;
        integral_sum += integral, integral2_sum += (integral*integral);
        results<<i<<"  "<<(double)(integral_sum/(i+1))<<"  "<<error(integral_sum, integral2_sum, i)<<endl;
    }

    results.close();
    rnd.SaveSeed();
    return 0;


}