#ifndef FORMULAS_H
#define FORMULAS_H
#include <string>

int Bethe_Bloch(std::string filename, double I, double Z, double N, bool densityCorrection, bool shellCorrection);
int dEdx(std::string filename,  double I, double N, double density);
int range(std::string filename, double I, double N, double density);


#endif