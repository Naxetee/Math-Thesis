import matplotlib.pyplot as plt
import csv
from scipy.interpolate import interp1d
import numpy as np
import os
import sys

X, Y = [], []
X_NIST, Y_NIST = [], []
X_BB, Y_BB = [], []

def readMaterial():

    files_to_read = {
        "dEdx.csv": (X, Y, DEDX_PATH),
        "nist_pstar.csv": (X_NIST, Y_NIST, NIST_PATH),
        'all_corrections.csv' if MATERIAL == 'water' else "shell_corrections.csv": (X_BB, Y_BB, BB_PATH),
    }

    for filename, (x_list, y_list, path) in files_to_read.items():
        file_path = os.path.join(f"{path}{MATERIAL}/", filename)
        print(f"Reading file: {file_path}")
        if os.path.exists(file_path):
            with open(file_path, 'r') as file:
                reader = csv.reader(file)
                for row in reader:
                    x_list.append(float(row[0]))
                    y_list.append(float(row[1]))

def compare_with_nist():
    X_np = np.array(X)
    Y_np = np.array(Y)
    X_NIST_np = np.array(X_NIST)
    Y_NIST_np = np.array(Y_NIST)

    # Interpolación de NIST a los puntos de X
    interp_nist = interp1d(X_NIST_np, Y_NIST_np, kind='linear', bounds_error=False, fill_value="extrapolate")
    Y_NIST_interp = interp_nist(X_np)

    # Error relativo porcentual (valor absoluto) SOLO en X
    relative_error = np.abs((Y_np - Y_NIST_interp) / Y_NIST_interp) * 100

    # Gráfica principal
    fig, ax1 = plt.subplots(figsize=(10, 6))
    ax1.plot(X_NIST, Y_NIST, label='Datos NIST PSTAR', color='purple', linestyle='dashed', linewidth=1.5)
    ax1.plot(X, Y, label=f"Aproximación Analítica", color='orange', linewidth=3)
    ax1.plot(X_BB, Y_BB, label=f"Ecuación Bethe-Bloch con correcciónes", color='skyblue', linewidth=1.5)
    ax1.set_xlabel(r"Energía ($MeV$)", fontsize=12, labelpad=10)
    ax1.set_ylabel(r"Poder de Frenado [$\mathrm{MeV\,cm^2/g}$]", fontsize=12, labelpad=10)
    ax1.set_xscale('log')
    ax1.set_yscale('log')
    ax1.grid(True)

    # Colorear el área bajo X, Y en 1 <= x <= 300
    mask = (relative_error <= 5)
    ax1.fill_between(X_np[mask], Y_np[mask], color='red', alpha=0.1)

    # Imprimir y mostrar los límites izquierdo y derecho de la máscara en la gráfica
    left_limit = X_np[mask][0]
    right_limit = X_np[mask][-1]
    # Mostrar los límites en la gráfica
    ax1.axvline(left_limit, color='red', linewidth=0.3, label='Límite izquierdo y derecho: Error < 5%')
    # Añadir texto en la gráfica
    ax1.text(left_limit, ax1.get_ylim()[1]*0.5, f"{left_limit:.2f}", color='red', rotation=90, va='center', ha='right', fontsize=9)
    # Actualizar leyenda para mostrar los nuevos labels
    handles, labels = ax1.get_legend_handles_labels()
    ax1.axvline(right_limit, color='red', linewidth=0.3, label='Límite derecho (5%)')
    ax1.legend(handles, labels, loc='lower left', fontsize='small')
    ax1.text(right_limit, ax1.get_ylim()[1]*0.5, f"{right_limit:.2f}", color='red', rotation=90, va='center', ha='right', fontsize=9)


    # Eje secundario para el error relativo SOLO en X
    ax2 = ax1.twinx()
    ax2.plot(X, relative_error, label='Error relativo respecto a los datos NIST (%)', color='red', linewidth=1.0, alpha=0.7)
    ax2.set_ylabel(r"Error relativo respecto a NIST ($\%$)", color='red')
    ax2.tick_params(axis='y', labelcolor='red')

    plt.title(f"Comparación de Poder de Frenado en {MATERIAL.upper()} con Datos NIST PSTAR")
    # Comprobar si el directorio existe, si no, crearlo
    if not os.path.exists(GRAPH_PATH):
        os.makedirs(GRAPH_PATH)
    plt.savefig(f"{GRAPH_PATH}fig_{MATERIAL}_comparing_dEdx_with_NIST.png")
    fig.tight_layout()
    plt.show()

    return relative_error

if __name__ == "__main__":
    if len(sys.argv) > 1:
        MATERIAL = sys.argv[1].lower()
        if MATERIAL not in ['water', 'cortical', 'adipose']:
            print("Material no soportado. Usa 'cortical', 'adipose' o 'water'.")
            sys.exit(1)

        GRAPH_PATH = f"./data/Approximation/dEdx/{MATERIAL}/graphs/"
        DEDX_PATH = f"./data/Approximation/dEdx/"
        BB_PATH = f"./data/Bethe-Bloch/dEdx/"
        NIST_PATH = f"./data/NIST/dEdx/"
        
    readMaterial()
    compare_with_nist()