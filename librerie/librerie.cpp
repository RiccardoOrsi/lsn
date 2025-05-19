#include "librerie.h"

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
    else {return b;}
};

double max(double a, double b)
{
    if(a>b) {return a;}
    else {return b;}
};

using namespace std;