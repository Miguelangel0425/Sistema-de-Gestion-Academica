#include "../include/calificaciones.h"

using namespace std;

// Función recursiva para calcular el promedio general de un estudiante
double promedioGeneralRecursivo(const Estudiante& estudiante, int index) {
	if (estudiante.materias.empty()) return 0.0;
	if ((size_t)index == estudiante.materias.size()) return 0.0;

	double suma = estudiante.materias[index].getCalificacion() +
		promedioGeneralRecursivo(estudiante, index + 1);

	if (index == 0) return suma / estudiante.materias.size();
	return suma;
}

// Función recursiva para contar cuántos estudiantes superan un promedio
int contarSuperanPromedioRecursivo(nodo* cabeza, double promedioObjetivo) {
	if (cabeza == nullptr) return 0; // Caso base: fin de la lista

	int cuenta = 0;
	double promedioEst = promedioGeneralRecursivo(cabeza->estudiante);
	if (promedioEst > promedioObjetivo) {
		cuenta = 1;
	}

	return cuenta + contarSuperanPromedioRecursivo(cabeza->siguiente, promedioObjetivo);
}

// Función recursiva para mostrar los resultados de los estudiantes
void mostrarResultadosRecursivo(nodo* cabeza, double promedioObjetivo) {
	if (cabeza == nullptr) return; // Caso base: fin de la lista

	double promedioEst = promedioGeneralRecursivo(cabeza->estudiante);

	cout << "----------------------------------" << endl;
	cout << "Estudiante: " << cabeza->estudiante.nombre << endl;
	cout << "ID: " << cabeza->estudiante.id << endl;
	cout << "Carrera: " << cabeza->estudiante.carrera << endl;
	cout << "Promedio general: " << promedioEst << endl;
	if (promedioEst > promedioObjetivo) {
		cout << "Estado: Supera el promedio objetivo (" << promedioObjetivo << ")" << endl;
	} else {
		cout << "Estado: No supera el promedio objetivo (" << promedioObjetivo << ")" << endl;
	}
	cout << "----------------------------------" << endl;

	// Llamada recursiva al siguiente estudiante
	mostrarResultadosRecursivo(cabeza->siguiente, promedioObjetivo);
}


