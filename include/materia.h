#ifndef MATERIA_H
#define MATERIA_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Definimos los typedef
typedef string nombreMateria;
typedef string codigoMateria;
typedef int creditosMateria;

// Clase plantilla Materia 
template <typename T>
class Materia{
	private:
		nombreMateria nombre;
		codigoMateria codigo;
		creditosMateria creditos;
		T calificacion;
	
	public:
		
		Materia(nombreMateria nombre, codigoMateria codigo, creditosMateria creditos, T calificacion) {
			this->nombre = nombre;
			this->codigo = codigo;
			this->creditos = creditos;
			this->calificacion = calificacion;
		}
	
	// Getters y Setters
	nombreMateria getNombre() const {
		return nombre;
	}
	
	codigoMateria getCodigo() const { 
		return codigo; 
	}
	
	creditosMateria getCreditos() const { 
		return creditos; 
	}
	
	T getCalificacion() const { 
		return calificacion;
	}
	
	void setCalificacion(T nuevaCalif) { 
		calificacion = nuevaCalif; 
	}
	
	// Metodo para mostrar los datos 
	void mostrarInfo() const {
		cout << "Materia: " << nombre << ": " << codigo << endl;
		cout << "Creditos: " << creditos << " - Calificacion: " << calificacion << endl;
	}

	// Operadores de comparación por calificación (O(1))
	bool operator>(const Materia<T>& otra) const {
		return calificacion > otra.calificacion;
	}

	bool operator<(const Materia<T>& otra) const {
		return calificacion < otra.calificacion;
	}
};

#endif

