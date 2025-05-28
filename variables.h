#ifndef VARIABLES_H
#define VARIABLES_H

// Definición de constantes
extern const double electron_charge;     // Carga del electrón en coulombs
extern const double electron_mass;     // Masa del electrón en kg
extern const double speed_of_light;      // Velocidad de la luz en m/s
extern const double proton_energy_MeV_I; // Energía del protón en MeV
extern const double proton_mass;       // Masa del protón en kg
extern const double coulomb_const;       // Constante de Coulomb
extern const double z_proton;            // Número atómico del protón
extern const double PI;                  // Número PI

// Parámetros asociados a un medio concreto
// Agua
extern const double I_water;            // Potencial de excitación del agua [eV]
extern const double N_water;            // Número de electrones por m^3 del agua (agua) [m^-3]
extern const double density_water;      // Densidad del agua [g/cm^3]

// Tejido óseo cortical
extern const double I_cortical;         // Potencial de excitación del tejido óseo cortical [eV]
extern const double N_cortical;         // Número de electrones por m^3 del tejido óseo cortical (cortical) [m^-3]
extern const double density_cortical;   // Densidad del tejido óseo cortical [g/cm^3]

// Tejido adiposo
extern const double I_adipose;          // Potencial de excitación del tejido adipop [eV]
extern const double N_adipose;          // Número de electrones por m^3 del tejido adiposo [m^-3]
extern const double density_adipose;    // Densidad del tejido adiposo [g/cm^3]

// Parámetros del término correctivo Delta
extern double a;
extern double x0;
extern double x1;
extern double c;
extern double m;

// Inicialización de arrays
extern double v_proton_energy_MeV[1000]; // Energía del protón en MeV
extern double v_beta[1000];              // Beta
extern double v_de_dx[1000];             // Poder de frenado
extern double v_proton_energy[1000];     // Energía del protón

// Cálculos de energía en reposo
extern const double proton_energy_eV;      // Energía del protón en reposo, en eV
extern const double electron_energy_J; // Energía del electrón en reposo, en J
extern const double electron_energy_eV; // Energía del electrón en reposo, en eV

#endif
