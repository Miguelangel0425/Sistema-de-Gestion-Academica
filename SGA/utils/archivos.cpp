#include "archivos.h"
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

namespace utils {

	bool escribirTexto(const string& ruta, const string& texto, bool append) {
		ofstream out;
		if (append) {
			out.open(ruta, ios::out | ios::app);
		} else {
			out.open(ruta, ios::out | ios::trunc);
		}
		if (!out.is_open()) return false;
		out << texto;
		out.close();
		return true;
	}

	bool escribirLineas(const string& ruta, const vector<string>& lineas, bool append) {
		ofstream out;
		if (append) {
			out.open(ruta, ios::out | ios::app);
		} else {
			out.open(ruta, ios::out | ios::trunc);
		}
		if (!out.is_open()) return false;
		for (const auto& l : lineas) {
			out << l << "\n";
		}
		out.close();
		return true;
	}

	bool leerLineas(const string& ruta, vector<string>& outLineas) {
		ifstream in(ruta);
		if (!in.is_open()) return false;
		string linea;
		outLineas.clear();
		while (getline(in, linea)) {
			outLineas.push_back(linea);
		}
		in.close();
		return true;
	}

	bool existeArchivo(const string& ruta) {
		ifstream in(ruta);
		return in.good();
	}

	string fechaHoraActual() {
		time_t t = time(nullptr);
		tm* lt = localtime(&t);
		char buffer[20];
		// YYYY-MM-DD HH:MM:SS
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", lt);
		return string(buffer);
	}

	string construirRuta(const string& directorio, const string& nombreArchivo) {
		if (directorio.empty()) return nombreArchivo;
		char sep = '/';
		if (directorio.back() == '/' || directorio.back() == '\\') {
			return directorio + nombreArchivo;
		}
		return directorio + string(1, sep) + nombreArchivo;
	}

}

