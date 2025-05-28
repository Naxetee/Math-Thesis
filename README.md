# Trabajo Fin de Grado en Matemáticas

## Uso de haces de protones en medicina

**Autor:** Ignacio Ávila Reyes  
**Curso:** 2024/2025  
**Universidad de Málaga**

---

Este repositorio contiene el código y los datos para el estudio y simulación del poder de frenado y rango de protones en diferentes medios biológicos (agua, tejido óseo cortical y tejido adiposo) usando la ecuación de Bethe-Bloch y aproximaciones analíticas. Incluye scripts para el cálculo, exportación y visualización de resultados, así como comparación con datos de referencia NIST.

## Archivos principales y su uso

### 1. bethe-bloch.cpp
Calcula el poder de frenado (`dE/dx`) usando la ecuación de Bethe-Bloch para distintos materiales y configuraciones de correcciones (sin correcciones, con corrección de densidad, con corrección de capa, o ambas). Exporta los resultados en archivos CSV.

**Uso:**
```bash
g++ bethe-bloch.cpp formulas.cpp variables.cpp -o bethe-bloch
./bethe-bloch
```
Los resultados se guardan en la carpeta `data/Bethe-Bloch/dEdx/`.

---

### 2. dEdx.cpp
Calcula el poder de frenado (`dE/dx`) usando una aproximación analítica para un material seleccionado.

**Uso:**
```bash
g++ dEdx.cpp formulas.cpp variables.cpp -o dEdx
./dEdx water
./dEdx cortical
./dEdx adipose
```
El resultado se guarda en `data/Approximation/dEdx/<material>/dEdx.csv`.

---

### 3. range.cpp
Calcula el rango de protones en un material usando una aproximación analítica.

**Uso:**
```bash
g++ range.cpp formulas.cpp variables.cpp -o range
./range water
./range cortical
./range adipose
```
El resultado se guarda en `data/Approximation/range/<material>/range.csv`.

---

### 4. plot_dEdx.py
Script en Python para graficar y comparar el poder de frenado calculado con la aproximación analítica, la ecuación de Bethe-Bloch y los datos NIST PSTAR.

**Uso:**
```bash
python plot_dEdx.py water
python plot_dEdx.py cortical
python plot_dEdx.py adipose
```
Las gráficas se guardan en `data/Approximation/dEdx/<material>/graphs/`.

---

### 5. plot_range.py
Script en Python para graficar y comparar el rango calculado con la aproximación analítica y los datos NIST PSTAR.

**Uso:**
```bash
python plot_range.py water
python plot_range.py cortical
python plot_range.py adipose
```
Las gráficas se guardan en `data/Approximation/range/<material>/graphs/`.

---

## Requisitos

- Compilador C++ (g++)
- Python 3.x
- Paquetes Python: matplotlib, numpy, scipy

Instalación de dependencias Python:
```bash
pip install matplotlib numpy scipy
```

---
