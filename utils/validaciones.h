#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
using namespace std;

namespace utils {

	// Elimina espacios al inicio y final
	string trim(const string& s);

	// Retorna true si la cadena no es vacía después de trim
	bool esNoVacio(const string& s);

	// Solo letras y espacios
	bool esAlfaEspacio(const string& s);

	// Letras, números y guiones bajos/medios
	bool esAlfanumericoGuion(const string& s);

	// Número entero o decimal válido
	bool esNumero(const string& s);

	// Valida rango inclusivo [min, max]
	bool enRango(double valor, double minimo, double maximo);

	// Coincidencia contra una expresión regular
	bool coincideRegex(const string& s, const string& patron);
}

#endif
