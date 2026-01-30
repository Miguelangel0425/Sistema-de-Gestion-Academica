#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <iostream>
#include <string>
#include <vector>
#include "materia.h" 

using namespace std;

// Creaci�n de alias de tipo 
typedef string nombreEstudiante;
typedef string codigoEstudiante;
typedef string carreraEstudiante;
typedef double promedioEstudiante;

// Creamos la estructura del TDA
struct Estudiante {
    nombreEstudiante nombre;
    codigoEstudiante id;
    carreraEstudiante carrera;
    promedioEstudiante promedio;
    vector<Materia<double>> materias;  // Lista de materias actualizado de version 1 (9/11/25)

};

// Sobrecarga de operadores para Estudiante basada en el promedio (O(1))
inline bool operator>(const Estudiante& a, const Estudiante& b) {
	return a.promedio > b.promedio;
}

inline bool operator<(const Estudiante& a, const Estudiante& b) {
	return a.promedio < b.promedio;
}

// Operador + para combinar registros: promedios combinados y materias concatenadas (O(n))
inline Estudiante operator+(const Estudiante& a, const Estudiante& b) {
	Estudiante c = a;
	// Combinar nombre/carrera de forma ilustrativa
	c.nombre = a.nombre + " & " + b.nombre;
	// Mantener id del primero para simplicidad
	// Concatenar materias
	for (const auto& m : b.materias) {
		c.materias.push_back(m);
	}
	// Recalcular promedio general usando calificaciones de materias si existen
	double suma = 0.0;
	int cuenta = 0;
	for (const auto& m : c.materias) {
		suma += m.getCalificacion();
		cuenta++;
	}
	if (cuenta > 0) {
		c.promedio = suma / cuenta;
	} else {
		// si no hay materias, promedio como media de ambos
		c.promedio = (a.promedio + b.promedio) / 2.0;
	}
	return c;
}

#endif
