import matplotlib.pyplot as plt
import csv
from scipy.interpolate import interp1d
import numpy as np
import os

# Leer los archivo CSV
X_None = []
Y_None = []

X_SC = []
Y_SC = []

X_Den = []
Y_Den = []

X_All = []
Y_All = []

X_NIST = []
Y_NIST = []

MATERIAL = 'water'
PATH = f"./data/Bethe-Bloch/dEdx/{MATERIAL}/graphs/"
BB_PATH = f"./data/Bethe-Bloch/dEdx/"
NIST_PATH = f"./data/NIST/dEdx/"

def readMaterial():

    files_to_read = {
        "no_corrections.csv": (X_None, Y_None, BB_PATH),
        "shell_corrections.csv": (X_SC, Y_SC, BB_PATH),
        "density_corrections.csv": (X_Den, Y_Den, BB_PATH),
        "all_corrections.csv": (X_All, Y_All, BB_PATH),
        "nist_pstar.csv": (X_NIST, Y_NIST, NIST_PATH),
    }

    for filename, (x_list, y_list, path) in files_to_read.items():
        file_path = os.path.join(f"{path}{MATERIAL}/", filename)
        if os.path.exists(file_path):
            with open(file_path, 'r') as file:
                reader = csv.reader(file)
                for row in reader:
                    x_list.append(float(row[0]))
                    y_list.append(float(row[1]))


def plot_corrections(plot_no_corrections=True, plot_shell_correction=True, plot_density_correction=True, plot_all_corrections=True, plot_nist=True):
    plt.figure(figsize=(10, 6))
    
    if plot_no_corrections:
        plt.plot(X_None, Y_None, label=f"Protones en '{MATERIAL}' sin correcciones", color='blue')
    if plot_shell_correction:
        plt.plot(X_SC, Y_SC, label=f"Protones en '{MATERIAL}' con corrección de capa", color='red')
    if plot_density_correction:
        plt.plot(X_Den, Y_Den, label=f"Protones en '{MATERIAL}' con corrección de densidad", color='green')
    if plot_all_corrections:
        plt.plot(X_All, Y_All, label=f"Protones en '{MATERIAL}' con correcciones de capa y densidad", color='orange')
    if plot_nist:
        plt.plot(X_NIST, Y_NIST, label='Datos NIST PSTAR', color='purple', linestyle='dashed')

    plt.title(f"Poder de Frenado en '{MATERIAL}' en función de la energía con correcciones de capa y densidad (Bethe-Bloch)")
    plt.xlabel('Energía (MeV)')
    plt.ylabel('Poder de Frenado (MeV/cm)')
    plt.legend()
    plt.grid(True)
    plt.xscale('log')
    plt.yscale('log')

    if plot_no_corrections:
        plt.savefig(PATH + 'fig_no_corrections.png', dpi=300)
    if plot_shell_correction:
        plt.savefig(PATH + 'fig_shell_correction.png', dpi=300)
    if plot_density_correction:
        plt.savefig(PATH + 'fig_density_correction.png', dpi=300)
    if plot_all_corrections:
        plt.savefig(PATH + 'fig_all_corrections.png', dpi=300)
    if plot_nist:
        plt.savefig(PATH + 'fig_nist.png', dpi=300)
    # Mostrar el gráfico
    plt.show()

def subplots_corrections():
    fig, axs = plt.subplots(2, 2, figsize=(15, 10))

    # Protones en {MATERIAL} sin correcciones
    axs[0, 0].plot(X_None, Y_None, label=f"Protones en '{MATERIAL}' sin correcciones", color='blue')
    axs[0, 0].set_title(f"Protones en '{MATERIAL}' sin correcciones")
    axs[0, 0].set_xlabel('Energía (MeV)')
    axs[0, 0].set_ylabel('Poder de Frenado (MeV/cm)')
    axs[0, 0].legend()
    axs[0, 0].grid(True)
    axs[0, 0].set_xscale('log')
    axs[0, 0].set_yscale('log')

    # Protones en Agua sin correcciones + Protones en {MATERIAL} con corrección de capa
    axs[0, 1].plot(X_None, Y_None, label=f"Protones en '{MATERIAL}' sin correcciones", color='blue')
    axs[0, 1].plot(X_SC, Y_SC, label=f"Protones en '{MATERIAL}' con corrección de capa", color='red')
    axs[0, 1].set_title(f"Protones en '{MATERIAL}' sin correcciones + corrección de capa")
    axs[0, 1].set_xlabel('Energía (MeV)')
    axs[0, 1].set_ylabel('Poder de Frenado (MeV/cm)')
    axs[0, 1].legend()
    axs[0, 1].grid(True)
    axs[0, 1].set_xscale('log')
    axs[0, 1].set_yscale('log')

    # Protones en {MATERIAL} sin correcciones + Protones en {MATERIAL} con corrección de densidad
    axs[1, 0].plot(X_None, Y_None, label=f"Protones en '{MATERIAL}' sin correcciones", color='blue')
    axs[1, 0].plot(X_Den, Y_Den, label=f"Protones en '{MATERIAL}' con corrección de densidad", color='green')
    axs[1, 0].set_title(f"Protones en '{MATERIAL}' sin correcciones + corrección de densidad")
    axs[1, 0].set_xlabel('Energía (MeV)')
    axs[1, 0].set_ylabel('Poder de Frenado (MeV/cm)')
    axs[1, 0].legend()
    axs[1, 0].grid(True)
    axs[1, 0].set_xscale('log')
    axs[1, 0].set_yscale('log')

    # Protones en {MATERIAL} sin correcciones + Protones en {MATERIAL} con corrección de capa y densidad
    axs[1, 1].plot(X_None, Y_None, label=f"Protones en '{MATERIAL}' sin correcciones", color='blue')
    axs[1, 1].plot(X_All, Y_All, label=f"Protones en '{MATERIAL}' con corrección de capa y densidad", color='orange')
    axs[1, 1].set_title(f"Protones en '{MATERIAL}' sin correcciones + corrección de capa y densidad")
    axs[1, 1].set_xlabel('Energía (MeV)')
    axs[1, 1].set_ylabel('Poder de Frenado (MeV/cm)')
    axs[1, 1].legend()
    axs[1, 1].grid(True)
    axs[1, 1].set_xscale('log')
    axs[1, 1].set_yscale('log')

    plt.tight_layout()
    plt.savefig(PATH + 'fig_comparing_all_graphs.png', dpi=300)
    plt.show()

def compare_with_nist(corrections : str = 'all'):

    if corrections == 'all':
        X = X_All
        Y = Y_All
    elif corrections == 'density':
        X = X_Den
        Y = Y_Den
    elif corrections == 'shell':
        X = X_SC
        Y = Y_SC
    elif corrections == 'none':
        X = X_None
        Y = Y_None
    else:
        raise ValueError("Corrections argument must be 'all', 'density', 'shell', or 'none'.")

    # Convertir X_NIST a un array de NumPy si no lo es
    X_NIST_np = np.array(X_NIST)

    # Interpolación para comparar los valores de X_All con X_NIST
    interp_func = interp1d(X, Y, kind='linear', bounds_error=False, fill_value="extrapolate")
    Y_interp = interp_func(X_NIST)

    # Error relativo porcentual (valor absoluto)
    relative_error = np.abs((Y_interp - Y_NIST) / Y_NIST) * 100

    # Definimos los tramos de energía
    ranges = [(0, 50), (50, 250), (250, 300)]
    mean_errors = []

    for rmin, rmax in ranges:
        mask = (X_NIST_np >= rmin) & (X_NIST_np < rmax)
        if np.any(mask):
            mean_err = np.mean(relative_error[mask])
        else:
            mean_err = np.nan
        mean_errors.append(mean_err)

    # Gráfica principal
    fig, ax1 = plt.subplots(figsize=(10, 6))

    # Poder de frenado
    ax1.plot(X, Y, label=f"{corrections} Corrections", color='orange')
    ax1.plot(X_NIST, Y_NIST, label='Datos NIST PSTAR', color='purple', linestyle='dashed')
    ax1.set_xlabel('Energía (MeV)')
    ax1.set_ylabel("Poder de Frenado (MeV/cm) en ")
    ax1.set_xscale('log')
    ax1.set_yscale('log')
    ax1.legend(loc='upper right')
    ax1.grid(True)

    # Eje secundario para el error relativo
    ax2 = ax1.twinx()
    ax2.plot(X_NIST, relative_error, label='Error relativo (%)', color='red', linewidth=1.5, alpha=0.7)
    ax2.set_ylabel('Error relativo (%)', color='red')
    ax2.tick_params(axis='y', labelcolor='red')

    # Añadir los errores medios en los tramos
    y_pos = 0.80  # posición vertical inicial para los textos
    x_pos = 0.95  # posición horizontal para los textos
    for i, (r, err) in enumerate(zip(ranges, mean_errors)):
        ax2.text(
            x_pos, y_pos - i*0.07,
            f'Error medio [{r[0]}-{r[1]}] MeV: {err:.2f}%',
            transform=ax2.transAxes,
            color='red',
            fontsize=11,
            horizontalalignment='right',
            bbox=dict(facecolor='white', alpha=0.7, edgecolor='red')
        )

    plt.title(f"Comparación de Poder de Frenado en {MATERIAL.upper()} con Correcciones {corrections.upper()} con Datos NIST PSTAR")
    fig.tight_layout()
    # plt.savefig(PATH + f"fig_{MATERIAL.upper()}_comparing_{corrections.upper()}_corrections_with_nist.png", dpi=300)
    plt.show()

    return relative_error, mean_errors


readMaterial()

# plot_corrections()
# subplots_corrections()
compare_with_nist(corrections = 'all')
compare_with_nist(corrections = 'density')
compare_with_nist(corrections = 'shell')
compare_with_nist(corrections = 'none')
