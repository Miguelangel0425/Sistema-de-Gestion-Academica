#ifndef PILA_H
#define PILA_H

#include <string>
#include "estudiante.h"
#include "materia.h"

using namespace std;

// Tipos de acciones para historial
enum TipoAccion {
	AgregarEstudiante,
	EliminarEstudiante,
	AsignarMateriaEstudiante
};

// Acción almacenada en historial (pila)
struct Accion {
	TipoAccion tipo;
	Estudiante estudianteSnapshot;
	Materia<double> materiaSnapshot = Materia<double>("", "", 0, 0.0);

	Accion() : tipo(AgregarEstudiante) {}
	Accion(TipoAccion t, const Estudiante& e) : tipo(t), estudianteSnapshot(e) {}
	Accion(TipoAccion t, const Estudiante& e, const Materia<double>& m) : tipo(t), estudianteSnapshot(e), materiaSnapshot(m) {}
};

// Forward declare del nodo de la pila
struct NodoPila;

// Pila dinámica para historial de acciones (push/pop O(1))
class PilaHistorial {
private:
	NodoPila* cima;

public:
	PilaHistorial();
	~PilaHistorial();

	void push(const Accion& accion);
	bool estaVacia() const;
	Accion top() const;
	Accion pop();
};

#endif
