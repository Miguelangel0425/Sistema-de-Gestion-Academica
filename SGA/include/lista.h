#ifndef LISTA_H
#define LISTA_H


#include "nodo.h"
#include <string>
using namespace std;

class listaEstudiantes {
private:
    nodo* cabeza;
    nodo* cola;

public:
	// Constructor y destructor
    listaEstudiantes();
	~listaEstudiantes();

	// Operaciones principales
    void registrarEstudiante(nombreEstudiante nombre, codigoEstudiante id, carreraEstudiante carrera, promedioEstudiante promedio);
    void mostrarEstudiantes();
	nodo* buscarPorId(const string& id) const;
	void buscarPorNombre(const string& nombre) const;
    void eliminarEstudiante(codigoEstudiante id);
    void asignarMateria(const char* id, const char* nombreMat, const char* codigoMat, int creditos, double calificacion);
    double recalcularPromedio(const string& id);
	// Accesores
    nodo* getCabeza() const;
	void limpiar();
};


#endif
