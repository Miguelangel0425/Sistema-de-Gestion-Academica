#ifndef NODO_H
#define NODO_H

#include "estudiante.h"

// Nodo para lista doblemente enlazada
struct nodo {
	Estudiante estudiante;
	nodo* siguiente;
	nodo* anterior;

	nodo() : siguiente(nullptr), anterior(nullptr) {}
};

#endif

