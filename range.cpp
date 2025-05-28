/*  IMPORTACIÓN DE LIBRERÍAS */
#include <iostream>
#include <cmath>
#include "formulas.h"
#include "variables.h"
using namespace std;

int main(const int argc, const char *argv[]) {
    string material;
    if (argc > 1) {
        material = argv[1];

        int material_code = -1;
        if (material == "water") material_code = 0;
        else if (material == "cortical") material_code = 1;
        else if (material == "adipose") material_code = 2;

        switch (material_code) {
            case 0:
            cout << "Calculando rango para: AGUA" << endl;
            return range("water/range.csv", I_water, N_water, density_water);
            case 1:
            cout << "Calculando rango para: CORTICAL" << endl;
            return range("cortical/range.csv", I_cortical, N_cortical, density_cortical);
            case 2:
            cout << "Calculando rango para: ADIPOSO" << endl;
            return range("adipose/range.csv", I_adipose, N_adipose, density_adipose);
            default:
            cout << "Material no reconocido. Por favor, use 'water' o 'cortical'." << endl;
            return 1;
        }
    } else {
        cout << "Por favor, introduzca el nombre del material como argumento." << endl;
        return 1;
    }

}
