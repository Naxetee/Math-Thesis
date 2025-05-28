#include "formulas.h"
#include "variables.h"
#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;

const string DATA_BB_PATH = "./data/Bethe-Bloch/dEdx/";
const string DATA_APPR_PATH = "./data/Approximation/dEdx/";
const string DATA_APPR_RANGE_PATH = "./data/Approximation/range/";

/**
 * * @brief Función que calcula el poder de frenado de Bethe-Bloch para un protón que penetra en un medio.
 * * @param filename Nombre del archivo donde se guardarán los resultados.
 * * @param I Constante de ionización del medio.
 * * @param Z Número atómico del medio.
 * * @param N Número de electrones por m^3 del medio.
 * * @param densityCorrection Si se aplica la corrección de densidad.
 * * @param shellCorrection Si se aplica la corrección de capa.
 * * @return 0 si la función se ejecuta correctamente.
 */
int Bethe_Bloch(std::string filename, double I, double Z, double N, bool densityCorrection, bool shellCorrection)
{

    ofstream file(DATA_BB_PATH + filename);

    if (file.is_open())
    {
        double BG, SC = 0, delta = 0, x;
        int i = 0;

        const double const_general = 4 * PI * // Constante K de la ecuación del poder de frenado.
                                     pow(electron_charge, 4) * pow(coulomb_const, 2) / (electron_energy_J * electron_charge * 1.0e8);

        for (double k = 0.05; k < 30; k = k + 0.05)
        {
            v_proton_energy[i] = proton_energy_MeV_I * (10 * (k + 0.05)) * 1.0e6; // Convertimos a eV

            /* Cálculos */
            v_beta[i] = sqrt(v_proton_energy[i] * (v_proton_energy[i] + (2 * proton_energy_eV))) / (v_proton_energy[i] + proton_energy_eV);

            /* Corrección de capa*/
            if (shellCorrection || densityCorrection)
            {
                BG = v_beta[i] * 1 / sqrt(1 - pow(v_beta[i], 2));
                if (shellCorrection)
                {
                    SC = (0.422377 * pow(BG, -2) + 0.0304043 * pow(BG, -4) - 0.00038106 * pow(BG, -6)) / 1.0e6 * pow((I), 2) +
                         (3.850190 * pow(BG, -2) - 0.1667989 * pow(BG, -4) + 0.00157955 * pow(BG, -6)) / 1.0e9 * pow((I), 3);
                }
                if (densityCorrection)
                {
                    x = 2 * log10(BG);
                    if (x >= x1)
                    {
                        delta = 2 * log(10) * x - c;
                    }
                    else if (x < x1 && x >= x0)
                    {
                        delta = 2 * log(10) * x - c + a * pow(x1 - x, m);
                    }
                }
            }
            /* Poder de Frenado según ecuación de Bethe-Bloch*/
            v_de_dx[i] = ((const_general * pow(z_proton, 2) * N) / pow(v_beta[i], 2)) *
                         (log((2 * electron_energy_eV * pow(v_beta[i], 2)) / I) -
                          log(1 - pow(v_beta[i], 2)) - pow(v_beta[i], 2) - 2 * (SC / Z) - delta);

            /* Escritura en el archivo .csv */
            file << (v_proton_energy[i] / 1.0e6) << "," << v_de_dx[i] << "\n";
            i++;
        }
    }
    cout << "Datos exportados a: " << (DATA_BB_PATH + filename) << endl;
    return 0;
}

/**
 * * @brief Función que calcula el poder de frenado de un protón al ser absorbido por un medio.
 * * @param filename Nombre del archivo donde se guardarán los resultados.
 * * @param I Potecial de ionización del medio [eV]
 * * @param N Número de electrones por m^3 del medio [m^-3]
 * * @param density Densidad del medio [g/cm^3]
 * * @return 0 si la función se ejecuta correctamente.
 */
int dEdx(std::string filename, double I, double N, double density)
{
    ofstream file(DATA_APPR_PATH + filename);
    if (file.is_open())
    {
        double c = speed_of_light;                                                                  // Velocidad de la luz en m/s
        double mp = proton_mass;                                                                    // Masa del protón en kg
        double me = electron_mass;                                                                  // Masa del electrón en kg
        double e = electron_charge;                                                                 // Carga del electrón en coulombs
        double B = 2 * me / (I * e);                                                                // B [s^2/m^2]
        double A = (4 * PI * N * pow(z_proton, 2)) / (me * mp) * pow(e, 4) * pow(coulomb_const, 2); // A [m^3/s^4]

        for (int E_MeV = 0.0; E_MeV <= 302.0; ++E_MeV)
        {
            for (int i = 1; i <= 2; ++i)
            {
                // Convertimos E_MeV a J
                double E_J = (E_MeV + 0.5*i) * 1.0e6 * e;

                // 1. Obtenemos gamma y u0 de la ecuación de energía relativista E=mpc^2(gamma-1)
                double gamma = 1.0 + E_J / (mp * pow(c, 2));
                double beta = sqrt(1.0 - 1.0 / pow(gamma, 2));
                double u0 = beta * c; // en m/s

                // 2. b y ε adimensionales, B [s^2/m^2]
                double b = B * pow(u0, 2);
                double ε = u0 / c;
                double uu = 1.0;
                double lnbu2 = log(b * pow(uu, 2));

                // 3. dEdx

                double dxdu = 0.0;
                double term0 = -pow(uu, 3) / lnbu2;
                dxdu += term0;

                double term2 = -pow(ε, 2) * (3 * pow(uu, 5)) / (2 * lnbu2);
                dxdu += term2;

                double term4 = -pow(ε, 4) * (pow(uu, 7) / lnbu2) * (15 / 8 - 1 / (2 * lnbu2));
                dxdu += term4;

                double term6 = -pow(ε, 6) * (pow(uu, 9) / lnbu2) * (35 / 16 - 13 / (12 * lnbu2));
                dxdu += term6;

                double dEdx = mp * pow(gamma, 3) * A / (dxdu * pow(u0, 2)); // [Kg m/s^2 = J/m]

                // Conversión a MeV/m
                dEdx = dEdx * 1.0e-6 / e; // [MeV/m]

                // 4. Conversión a MeV/cm
                dEdx = dEdx * 1.0e-2; // [MeV/cm]

                // 5. Usamos la densidad del para convertir a MeV cm^2/g
                dEdx = dEdx / density; // [MeV cm^2/g]

                // Escribimos los resultados en el archivo .csv
                file << (E_MeV + 0.5*i) << "," << -dEdx << "\n";
            }
        }
    }
    cout << "Datos exportados a: " << (DATA_APPR_PATH + filename) << endl;
    return 0;
}

/**
 * * @brief Función que calcula el rango de un protón al ser absorbido por un medio.
 * * @param filename Nombre del archivo donde se guardarán los resultados.
 * * @param I Potecial de ionización del medio.
 * * @param Z Número atómico del medio.
 * * @param N Número de electrones por m^3 del medio.
 * * @param density Densidad del medio g/cm^3.
 * * @return 0 si la función se ejecuta correctamente.
 */
int range(std::string filename, double I, double N, double density)
{
    ofstream file(DATA_APPR_RANGE_PATH + filename);
    if (file.is_open())
    {
        double c = speed_of_light;                                                                  // Velocidad de la luz en m/s
        double mp = proton_mass;                                                                    // Masa del protón en kg
        double me = electron_mass;                                                                  // Masa del electrón en kg
        double e = electron_charge;                                                                 // Carga del electrón en coulombs
        double B = 2 * me / (I * e);                                                                // B [s^2/m^2] (valor aproximado)
        double A = (4 * PI * N * pow(z_proton, 2)) / (me * mp) * pow(e, 4) * pow(coulomb_const, 2); // A [m^3/s^4]

        for (int E_MeV = 1.0; E_MeV <= 300.0; ++E_MeV)
        {
            // Convertimos E_MeV a J
            double E_J = E_MeV * 1.0e6 * e;

            // 1. Obtenemos gamma y u0 de la ecuación de energía relativista E=mpc^2(gamma-1)
            double gamma = 1.0 + E_J / (mp * pow(c, 2));
            double beta = sqrt(1.0 - 1.0 / pow(gamma, 2));
            double u0 = beta * c; // en m/s

            // 2. b y ε adimensionales, B [s^2/m^2]

            double b = B * pow(u0, 2);
            double ε = u0 / c;

            // 3. Rango
            double range = 0.0;
            double lnb = log(b);
            double ln2b = pow(log(b), 2);
            double ln3b = pow(log(b), 3);

            double term0 = (2 * ln2b + lnb - 1) / (8 * ln3b);
            range += term0;

            double term2 = pow(ε, 2) * (9 * ln2b - 3 * lnb + 2) / (36 * ln3b);
            range += term2;

            double term4 = pow(ε, 4) * (120 * ln2b - 2 * lnb - 1) / (512 * ln3b);
            range += term4;

            double term6 = -31 * pow(ε, 6) * (25 * ln2b + 5 * lnb + 2) / (2400 * ln3b);
            range += term6;

            // Deshacemos la normalización del Rango [m]
            range = range * pow(u0, 4) / A;

            // 4. Conversión a cm
            range = range * 100;

            // 5. usamos la densidad del agua para convertir a g/cm^2
            range = range * density;

            // Escribimos los resultados en el archivo .csv
            file << E_MeV << "," << range << "\n";
        }
    }
    cout << "Datos exportados a: " << (DATA_APPR_RANGE_PATH + filename) << endl;
    return 0;
}