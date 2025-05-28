/*  IMPORTACIÓN DE LIBRERÍAS */
#include <iostream>
#include <cmath>
#include "formulas.h"
#include "variables.h"
using namespace std;

int main() {
    
    /* CÁLCULO DE LA CONSTANTE DE IONIZACIÓN */
    double I_water = 75.0; // eV
    double Z_water = 9.0; // Número atómico del medio (agua)
    double N_water = 3.34e29; // Número de electrones por m^3 del medio (agua)

    double I_cortical = 112.0; // eV
    double Z_cortical = 96; // Número atómico del medio (cortical)
    double N_cortical = 3.2e29; // Número de electrones por m^3 del medio (cortical)

    double I_adipose = 64.8; // eV
    double Z_adipose = 66; // Número atómico del medio (adiposo)
    double N_adipose = 3.0e29; // Número de electrones por m^3 del medio (adiposo)

    // cout << "Ionization constant: " << I << " MeV" << endl;
    int a = Bethe_Bloch("water/no_corrections.csv", I_water, Z_water, N_water, false, false);
    int b = Bethe_Bloch("water/density_corrections.csv", I_water, Z_water, N_water, true, false);
    int c = Bethe_Bloch("water/shell_corrections.csv", I_water, Z_water, N_water, false, true);
    int d = Bethe_Bloch("water/all_corrections.csv", I_water, Z_water, N_water, true, true);

    int e = Bethe_Bloch("cortical/no_corrections.csv", I_cortical, Z_cortical, N_cortical, false, false);
    // int f = Bethe_Bloch("cortical/density_corrections.csv", I_cortical, Z_cortical, N_cortical, true, false);
    int g = Bethe_Bloch("cortical/shell_corrections.csv", I_cortical, Z_cortical, N_cortical, false, true);
    // int h = Bethe_Bloch("cortical/all_corrections.csv", I_cortical, Z_cortical, N_cortical, true, true);

    int i = Bethe_Bloch("adipose/no_corrections.csv", I_adipose, Z_adipose, N_adipose, false, false);
    // int j = Bethe_Bloch("adipose/density_corrections.csv", I_adipose, Z_adipose, N_adipose, true, false);
    int k = Bethe_Bloch("adipose/shell_corrections.csv", I_adipose, Z_adipose, N_adipose, false, true);
    // int l = Bethe_Bloch("adipose/all_corrections.csv", I_adipose, Z_adipose, N_adipose, true, true);

    return 0;
}
