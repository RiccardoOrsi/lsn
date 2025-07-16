#include "librerie.h"
#include <errno.h>

using namespace std;

double error(double somma, double somma2, int n)
//somma:=sommatoria delle n medie, somma2=:sommatoria di (somma*somma), n=: n-esimo blocco valutato
{
    if(n==0) 
        {return 0;}
    else{
    return sqrt( (double)( (somma2/(n+1)) - (pow(somma/(n+1), 2)) ) / n );}
};

double min(double a, double b)
{
    if(a<b) {return a;}
    else if(a>b) {return b;}
    else {return 0;}
};

double max(double a, double b)
{
    if(a>b) {return a;}
    else if(a<b) {return b;}
    else {return 0;}
};

vector <double>  disc_walk (double length, double sort, vector<double> v)
{
   if(sort<(-2./3.) and sort>=-1.)                 //event: -length on x
      { v[0] -= length; }
   else if(sort>=(-2./3.) and sort<(-1./3.))       //event -length on y       
      { v[1] -= length; }
   else if(sort>=(-1./3.) and sort<(0))            //event: -length on z
      { v[2] -= length; }
   else if(sort>(0) and sort<=(1./3.))             //event: +lenth on x
      { v[0] += length; }
   else if(sort>=(1./3.) and sort<=(2./3.))        //event: +length on y
      { v[1] += length; }
   else if(sort>(2/3.) and sort<=(1))              //event: +length on z            
      { v[2] += length; }  
    return v;

}

vector<double> cont_walk(double rho, double theta, double phi, vector<double> pos)
{
   pos[0]+=rho*sin(theta)*cos(phi);           //x value
   pos[1]+=rho*sin(theta)*sin(phi);           //y value
   pos[2]+=rho*cos(theta);                    //z value

   return pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////
                        /*LIBRERIE PER CREAZIONE DIRECTORIES*/
////////////////////////////////////////////////////////////////////////////////////////////////

bool directoryExists(const string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        // Errore nel chiamare stat: presumiamo che la directory non esista
        return false;
    } else if (info.st_mode & S_IFDIR) {
        // Esiste ed è una directory
        return true;
    } else {
        // Esiste ma non è una directory
        return false;
    }
}

bool createDirectory(const string& path) {
    if (mkdir(path.c_str(), 0755) == 0) {
        cout << "Directory creata: " << path << endl;
        return true;
    } else {
        cerr << "Errore nella creazione della directory: " << strerror(errno) << endl;
        return false;
    }
}