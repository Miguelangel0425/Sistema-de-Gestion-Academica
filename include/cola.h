#ifndef COLA_H
#define COLA_H

#include <string>
using namespace std;

// Solicitud a gestionar en cola (FIFO)
struct Solicitud {
	string tipo;       // "Inscripcion", "RevisionNotas", etc.
	string descripcion;
	Solicitud() {}
	Solicitud(const string& t, const string& d) : tipo(t), descripcion(d) {}
};

// Nodo de la cola
struct NodoCola {
	Solicitud solicitud;
	NodoCola* siguiente;
	NodoCola(const Solicitud& s) : solicitud(s), siguiente(nullptr) {}
};

// Cola dinámica (enqueue/dequeue O(1))
class ColaSolicitudes {
private:
	NodoCola* frente;
	NodoCola* fondo;

public:
	ColaSolicitudes();
	~ColaSolicitudes();

	void enqueue(const Solicitud& s);
	bool estaVacia() const;
	Solicitud front() const;
	Solicitud dequeue();
	void mostrar() const;
};

#endif
