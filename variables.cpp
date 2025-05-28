#include <cmath>
#include "variables.h"

// Definición de constantes
const double electron_charge = 1.602176634e-19; // Carga del electrón [Coulombs]
const double electron_mass = 9.10938356e-31;    // Masa del electrón en [Kg]
const double speed_of_light = 299792458.0;      // Velocidad de la luz en [m/s]
const double proton_energy_MeV_I = 1.0;         // Energía del protón en [MeV]
const double proton_mass = 1.6726219e-27;       // Masa del protón en [Kg]
const double vaccuum_permittivity = 8.854187817e-12;                // Permitividad del vacío [F/m]
const double coulomb_const = 1 / (4 * PI * vaccuum_permittivity);   // Constante de Coulomb [N*m^2/C^2]
const double z_proton = 1.0;                    // Número atómico del protón
const double PI = 3.14159265358979323846;       // Número PI

// Parámetros asociados a un medio concreto
/* Agua */
extern const double I_water = 75.0;      // Potencial de excitación del agua [eV]
extern const double N_water = 3.34e29;   // Densidad de electrones del agua (agua) [m^-3]
extern const double density_water = 1.0; // Densidad del agua [g/cm^3]

/* Cortical */
extern const double I_cortical = 112.00000;         // Potencial de excitación del tejido cortical [eV]
extern const double N_cortical = 5.74e29;           // Densidad de electrones del tejido cortical (cortical) [m^-3]
extern const double density_cortical = 1.92000E+00; // Densidad del tejido cortical [g/cm^3]

/* Adiposo */
extern const double I_adipose = 64.8000000;         // Potencial de excitación del tejido adipop [eV]
extern const double N_adipose = 3.18e29;            // Densidad de electrones del tejido adiposo [m^-3]
extern const double density_adipose = 9.50000E-01;  // Densidad del tejido adiposo [g/cm^3]

// Parámetros del término correctivo Delta
double a = 0.09116;
double x0 = 0.24;
double x1 = 2.8004;
double c = 3.5017;
double m = 3.4773;

// Inicialización de arrays
double v_beta[1000] = {};          // Beta
double v_de_dx[1000] = {};         // Poder de frenado
double v_proton_energy[1000] = {}; // Energía del protón

// Cálculos de energía en reposo
/* Energía del protón en reposo [eV] */
const double proton_energy_eV = proton_mass * pow(speed_of_light, 2) / electron_charge; 
/* Energía del electrón en reposo [J] */
const double electron_energy_J = electron_mass * pow(speed_of_light, 2);  
/* Energía del electrón en reposo [eV] */               
const double electron_energy_eV = electron_energy_J / electron_charge;                  
