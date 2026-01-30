#ifndef CALIFICACIONES_H
#define CALIFICACIONES_H

#include "estudiante.h"
#include "nodo.h"
#include <vector>
#include <iostream>
using namespace std;

// Declaraciones
double promedioGeneralRecursivo(const Estudiante& estudiante, int index = 0);
int contarSuperanPromedioRecursivo(nodo* cabeza, double promedioObjetivo);
void mostrarResultadosRecursivo(nodo* cabeza, double promedioObjetivo);

#endif
