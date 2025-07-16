#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include "../rnd_gen/random.h"

using namespace std;

double error(double, double, int );

double min (double, double);

double max(double, double);

//Method to compute a step of a RW
vector <double> disc_walk (double, double, vector<double>);

//Converts spherical coordinates into x-y-z, used for the continuous RW
vector <double> cont_walk (double, double, double, vector<double>);

bool directoryExists(const string& path);

bool createDirectory(const string& path);

