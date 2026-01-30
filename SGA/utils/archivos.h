#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <string>
#include <vector>
using namespace std;

namespace utils {

	// Escribe texto al archivo. Si append=true agrega al final.
	bool escribirTexto(const string& ruta, const string& texto, bool append = false);

	// Escribe múltiples líneas. Si append=true agrega al final.
	bool escribirLineas(const string& ruta, const vector<string>& lineas, bool append = false);

	// Lee todas las líneas del archivo a outLineas.
	bool leerLineas(const string& ruta, vector<string>& outLineas);

	// Verifica existencia de archivo
	bool existeArchivo(const string& ruta);

	// Fecha y hora local en formato "YYYY-MM-DD HH:MM:SS"
	string fechaHoraActual();

	// Construye una ruta simple dir/nombre (sin validar existencia)
	string construirRuta(const string& directorio, const string& nombreArchivo);
}

#endif

