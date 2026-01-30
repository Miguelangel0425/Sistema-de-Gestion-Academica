#include <iostream>
#include "../include/cola.h"

using namespace std;

ColaSolicitudes::ColaSolicitudes() : frente(nullptr), fondo(nullptr) {}

ColaSolicitudes::~ColaSolicitudes() {
	while (!estaVacia()) {
		dequeue();
	}
}

void ColaSolicitudes::enqueue(const Solicitud& s) {
	NodoCola* nuevo = new NodoCola(s);
	if (fondo == nullptr) {
		frente = fondo = nuevo;
	} else {
		fondo->siguiente = nuevo;
		fondo = nuevo;
	}
	cout << "Solicitud registrada: [" << s.tipo << "] " << s.descripcion << endl;
}

bool ColaSolicitudes::estaVacia() const {
	return frente == nullptr;
}

Solicitud ColaSolicitudes::front() const {
	if (frente == nullptr) {
		cout << "No hay solicitudes pendientes." << endl;
		return Solicitud();
	}
	return frente->solicitud;
}

Solicitud ColaSolicitudes::dequeue() {
	if (frente == nullptr) {
		cout << "No hay solicitudes para atender." << endl;
		return Solicitud();
	}
	NodoCola* borrar = frente;
	Solicitud s = borrar->solicitud;
	frente = frente->siguiente;
	if (frente == nullptr) {
		fondo = nullptr;
	}
	delete borrar;
	cout << "Solicitud atendida: [" << s.tipo << "] " << s.descripcion << endl;
	return s;
}

void ColaSolicitudes::mostrar() const {
	if (frente == nullptr) {
		cout << "No hay solicitudes en la cola." << endl;
		return;
	}
	NodoCola* actual = frente;
	cout << "Solicitudes en espera:" << endl;
	while (actual != nullptr) {
		cout << "- [" << actual->solicitud.tipo << "] " << actual->solicitud.descripcion << endl;
		actual = actual->siguiente;
	}
}


