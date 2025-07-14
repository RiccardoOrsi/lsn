#include "../../librerie/librerie.h"
#include "../../rnd_gen/random.h"

using namespace std;

int main()
{
    Random rnd;                                     //Variable that allocates the rng methods
    rnd.SetSeed();                                  //Setting the seed of the RNG  

    int const blocks=100;                           //Blocks used for data blocking
    int const throws=10000;                         //Throws taken for eaxh block
    int walks_number = throws/blocks;               //RW for each block
    int steps= 100;                                 //Step taken in a random walk
    vector <double> pos_disc(3, 0.);                //vector in which we save the progressive pos_discition of the RW
    vector <double> pos_cont(3, 0.);
    vector<vector<double>> r2_disc(steps, vector<double>(blocks, 0.));      
    vector<vector<double>> r2_cont(steps, vector<double>(blocks, 0.));
    double length=1.;

    ofstream results_dis, results_cont;
        results_dis.open("results_discrete.out");
        results_cont.open("results_continous.out");

    //Cosa bisogna fare: in 100 blocchi bisogna fare 100 valutazioni della pos_discizione di r^2 per blocco!
    //esempio primo blocco: faccio uno step, valuto r, faccio un secondo step, valuto r dopo due step
    //faccio n step. valuto r dopo n step. Questo valore viene raccolto da r_sum e r2_disc_sum
    //Con questi poi si fa l'analisi dati

    for(int i=0; i<blocks; i++)
    {

        for(int j=0; j<walks_number; j++)
        {
            pos_disc[0]=0., pos_disc[1]=0., pos_disc[2]=0.;
            pos_cont[0]=0., pos_cont[1]=0., pos_cont[2]=0.;

            for(int k=0; k<steps; k++)     //We evaluate r step after step, and we start from the second value as the first will be 0
            {
            //discrete random walk
            double sort= rnd.Rannyu(-1., 1.);
            pos_disc=disc_walk(length, sort, pos_disc);
            r2_disc [k] [i] += (double) (pos_disc[0]*pos_disc[0] + pos_disc[1]*pos_disc[1] + pos_disc[2]*pos_disc[2]) / walks_number;

            //continous random walk
            double theta=rnd.Rannyu(0., M_PI);
            double phi=rnd.Rannyu(0., 2*M_PI);
            pos_cont=cont_walk(length, theta, phi, pos_cont);
            r2_cont [k] [i] += (double) (pos_cont[0]*pos_cont[0]+pos_cont[1]*pos_cont[1]+pos_cont[2]*pos_cont[2]) / walks_number;
            }

        }


    }


    double ave_r2_disc[steps]={0.}, ave2_r2_disc[steps]={0.};
    double ave_r2_cont[steps]={0.}, ave2_r2_cont[steps]={0.};


    if (results_dis.is_open() && results_cont.is_open()){
        results_dis<<0.<<" "<<0.<<" "<<0.<<endl;
        results_cont<<0.<<" "<<0.<<" "<<0.<<endl;

            for (int i = 0; i < steps; i++)
            {
                // fissato lo step i-esimo calcolo media e media quadratica sui blocchi
                for (int j = 0; j < blocks; j++)
                {
                    double appo = r2_disc[i][j];
                    ave_r2_disc[i] += appo/blocks;
                    ave2_r2_disc[i] += appo*appo/blocks;

                    double appo_cont = r2_cont[i][j];
                    ave_r2_cont[i] += appo_cont/blocks;
                    ave2_r2_cont[i] += appo_cont*appo_cont/blocks;
                
                }
                
                double err = 0;
                if(i == 0) results_dis <<i+1<<" "<< sqrt(ave_r2_disc[i]) << " " << 0 << endl;
                else
                {
                    // propagazione errore: normalizzo per 1/2\sqrt{ave}
                    err = error(ave_r2_disc[i], ave2_r2_disc[i], blocks) / (2*sqrt(ave_r2_disc[i]));
                    results_dis <<i+1<<" "<< sqrt(ave_r2_disc[i]) << " " << err << endl;
                }
                
                if(i == 0) results_cont<<i+1<<" " << sqrt(ave_r2_cont[i]) << " " << 0 << endl;
                else
                {
                    // propagazione errore: normalizzo per 1/(2*sqrt{ave})
                    err = error(ave_r2_cont[i], ave2_r2_cont[i], blocks)/(2*sqrt(ave_r2_cont[i]));
                    results_cont <<i+1<<" "<< sqrt(ave_r2_cont[i]) << " " << err << endl;
                }

            }

        } else {
            if (!results_dis.is_open()) cerr << "PROBLEM: Unable to open discrete.out" << endl;
            if (!results_cont.is_open()) cerr << "PROBLEM: Unable to open continuous.out" << endl;
        }
    
    results_dis.close();
    results_cont.close();
    rnd.SaveSeed();
    return 0;
}