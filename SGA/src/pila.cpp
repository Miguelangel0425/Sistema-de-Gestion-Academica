#include <iostream>
#include "../include/pila.h"

using namespace std;

// Nodo de la pila
struct NodoPila {
	Accion accion;
	NodoPila* siguiente;
	NodoPila(const Accion& a) : accion(a), siguiente(nullptr) {}
};

PilaHistorial::PilaHistorial() : cima(nullptr) {}

PilaHistorial::~PilaHistorial() {
	while (!estaVacia()) {
		pop();
	}
}

void PilaHistorial::push(const Accion& accion) {
	NodoPila* nuevo = new NodoPila(accion);
	nuevo->siguiente = cima;
	cima = nuevo;
}

bool PilaHistorial::estaVacia() const {
	return cima == nullptr;
}

Accion PilaHistorial::top() const {
	if (cima == nullptr) {
		cout << "Historial vacío." << endl;
		return Accion();
	}
	return cima->accion;
}

Accion PilaHistorial::pop() {
	if (cima == nullptr) {
		cout << "No hay acciones para deshacer." << endl;
		return Accion();
	}
	NodoPila* borrar = cima;
	Accion a = borrar->accion;
	cima = cima->siguiente;
	delete borrar;
	return a;
}


