#include "../../librerie/librerie.h"
#include "../../rnd_gen/random.h"

using namespace std;

double Nx(double x)
{
    return 0.5*(1+erf(x/sqrt(2)));
}

//Plain vanilla option pricing
//Compute at t=0 via Monte Carlo the european call-option price C[S(0),0]
//and put-option price, P[S(0),0]

int main()
{
    Random rnd;                                     //Variable that allocates the rng methods
    rnd.SetSeed();                                  //Setting the seed of the RNG 
    int const blocks=100, throws=10000;              //Data blocking variables
    //Global variables
    double S0=100, ST=0., STd=0.;
    double T=1.;
    double K=100;
    double r=0.1;
    double sigma=0.25;
    //variables used for the direct sampling
    double C=0., sum_C=0., sum2_C=0.;
    double P=0., sum_P=0., sum2_P=0.;
    //varibales used for the recursive method
    double Cd=0., sum_Cd=0., sum2_Cd=0.;
    double Pd=0., sum_Pd=0., sum2_Pd=0.;
    int steps=100;                                  
    double appo=0.;

    /*double d1=(1./(sigma*sqrt(T))) * (log(S0/K)+(r+(sigma*sigma*T/2.)));
    double d2=d1-sigma*sqrt(T);*/

    ofstream results_direct, results_discrete;
        results_direct.open("direct.out"), results_discrete.open("discrete.out");

    //First part sampling directly S(T) for a GBM(r, sigma^2)

    for(int i=0; i<blocks; i++)
    {
        C=0., P=0., Cd=0., Pd=0.;

        for(int j=0; j<throws; j++)
        {
            double z=rnd.gauss(0., 1.);
            ST = S0*exp((r-0.5*sigma*sigma)*T + sigma*z*sqrt(T));
            C += exp(-r*T)*max(0., ST-K);
            P += exp(-r*T)*(max(0., K-ST));  
            
            STd=S0*exp((r-0.5*sigma*sigma)*(1./steps) + sigma*z*sqrt(1./steps));
            for(int k=1; k<steps; k++)
            {
                //appo=STd;
                double zi=rnd.gauss(0., 1.);;
                STd = STd*exp((r-0.5*sigma*sigma)*(1./steps) + sigma*zi*sqrt(1./steps));
            }
            Cd += exp(-r*T)*max(0., STd-K);
            Pd += exp(-r*T)*(max(0., K-STd)); 
        }
        
        C=C/throws, sum_C += C, sum2_C += C*C;
        P=P/throws, sum_P += P, sum2_P += P*P;

        Cd=Cd/throws, sum_Cd += Cd, sum2_Cd += Cd*Cd;
        Pd=Pd/throws, sum_Pd += Pd, sum2_Pd += Pd*Pd;

        // salvo su file
        if (results_direct.is_open() && results_discrete.is_open())
        {      
            results_direct << i <<" "<< sum_C/(i+1) << "   " << error(sum_C, sum2_C, i) << "   " //
                                   << sum_P/(i+1) << "   " << error(sum_P, sum2_P, i) << "   " << endl;

            results_discrete << i <<" "<< sum_Cd/(i+1) << "   " << error(sum_Cd, sum2_Cd, i) << "   " //
                                   << sum_Pd/(i+1) << "   " << error(sum_Pd, sum2_Pd, i) << "   " << endl;
            
        } else {
            if (!results_direct.is_open()) cerr << "PROBLEM: Unable to open direct.out" << endl;
            if (!results_discrete.is_open()) cerr << "PROBLEM: Unable to open discrete.out" << endl;
        }
    }
    
    results_discrete.close();
    results_direct.close();
    rnd.SaveSeed();
    return 0;
 }   


