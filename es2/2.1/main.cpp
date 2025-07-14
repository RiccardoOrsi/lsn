
#include "../../librerie/librerie.h"
#include "../../rnd_gen/random.h"

double function(double x)
//it returns the integrand function
{
    return (M_PI/2.)*cos(M_PI*x/2.);
}

double importance (double x) 
//function that does importance sampling from the p(x)=-2x+2
//we use this p(x) as it's normalized and positive on [0,1]
{
    return 1-sqrt(1-x);         //we suppose that x is uniformly distributed value
}


using namespace std;

int main()
{
    Random rnd;                                     //Variable that allocates the rng methods
    rnd.SetSeed();                                  //Setting the seed of the RNG  

    int const blocks=100;                   //Blocks used for data blocking
    int const throws=10000;                 //Throws taken for eaxh block
    double int_mean, int_sample;             //Variable that allocates the value of the integral
    double mean_sum=0., mean2_sum=0.;       //variables used for the error evaluation with the data blocking method
    double sample_sum=0., sample2_sum=0.;

    ofstream results_mean, results_importance;
    results_mean.open("results_mean.out"), results_importance.open("results_importance.out");

    for(int i=0; i<blocks; i++) //external cycle for error's evaluation
    {
        int_mean=0., int_sample=0;

        for(int j=0; j<throws; j++) //Inner cycle used for integral's evaluation
        {
            double x=rnd.Rannyu();
            int_mean += function(x);

            double x_linear = importance(x);
            double fx=function(x_linear);
            double px=-2.*x_linear+2.;
            int_sample += (fx/px);
        }

        int_mean=(double)int_mean/throws;
        mean_sum += int_mean, mean2_sum += (int_mean*int_mean);
        results_mean<<i<<"  "<<(double)(mean_sum/(i+1))<<"  "<<error(mean_sum, mean2_sum, i)<<endl;

        int_sample=(double)int_sample/throws;
        sample_sum += int_sample, sample2_sum += (int_sample*int_sample);
        results_importance<<i<<"  "<<(double)(sample_sum/(i+1))<<"  "<<error(sample_sum, sample2_sum, i)<<endl;

        
    }

    results_mean.close(), results_importance.close();
    rnd.SaveSeed();
    return 0;


}