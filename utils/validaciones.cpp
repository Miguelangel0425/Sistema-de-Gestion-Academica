#include "validaciones.h"
#include <regex>
#include <cctype>

using namespace std;

namespace utils {

	string trim(const string& s) {
		size_t inicio = 0;
		while (inicio < s.size() && isspace(static_cast<unsigned char>(s[inicio]))) inicio++;
		if (inicio == s.size()) return "";
		size_t fin = s.size() - 1;
		while (fin > inicio && isspace(static_cast<unsigned char>(s[fin]))) fin--;
		return s.substr(inicio, fin - inicio + 1);
	}

	bool esNoVacio(const string& s) {
		return !trim(s).empty();
	}

	bool esAlfaEspacio(const string& s) {
		if (s.empty()) return false;
		for (char c : s) {
			if (!(isalpha(static_cast<unsigned char>(c)) || isspace(static_cast<unsigned char>(c)))) return false;
		}
		return true;
	}

	bool esAlfanumericoGuion(const string& s) {
		if (s.empty()) return false;
		for (char c : s) {
			if (!(isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-' )) return false;
		}
		return true;
	}

	bool esNumero(const string& s) {
		string t = trim(s);
		if (t.empty()) return false;
		regex re("^[+-]?([0-9]+)(\\.[0-9]+)?$");
		return regex_match(t, re);
	}

	bool enRango(double valor, double minimo, double maximo) {
		return valor >= minimo && valor <= maximo;
	}

	bool coincideRegex(const string& s, const string& patron) {
		regex re(patron);
		return regex_match(s, re);
	}

}
