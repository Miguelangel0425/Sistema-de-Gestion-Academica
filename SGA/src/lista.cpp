#include <iostream>
#include <string>
#include <iomanip>
#include "../include/estudiante.h"
#include "../include/materia.h"
#include "../include/nodo.h"
#include "../include/lista.h"

using namespace std;

// Constructor: inicializa lista vacía. Inserción al final O(1)
listaEstudiantes::listaEstudiantes() {
	cabeza = nullptr;
	cola = nullptr;
}

// Destructor: libera todos los nodos O(n)
listaEstudiantes::~listaEstudiantes() {
	limpiar();
}

void listaEstudiantes::registrarEstudiante(nombreEstudiante nombre, codigoEstudiante id, carreraEstudiante carrera, promedioEstudiante promedio) {
	Estudiante estudianteNuevo;
	estudianteNuevo.nombre = nombre;
	estudianteNuevo.id = id;
	estudianteNuevo.carrera = carrera;
	estudianteNuevo.promedio = promedio;

	nodo* nuevoNodo = new nodo;
	nuevoNodo->estudiante = estudianteNuevo;
	nuevoNodo->siguiente = nullptr;
	nuevoNodo->anterior = nullptr;

	if (cabeza == nullptr) {
		cabeza = nuevoNodo;
		cola = nuevoNodo;
	} else {
		cola->siguiente = nuevoNodo;
		nuevoNodo->anterior = cola;
		cola = nuevoNodo;
	}
	cout << "El estudiante fue registrado de forma exitosa" << endl;
}

void listaEstudiantes::mostrarEstudiantes() {
	if (cabeza == nullptr) {
		cout << "No hay estudiantes registrados en el sistema: " << endl;
		return;
	}

	nodo* actual = cabeza;
	cout << "\nLista de estudiantes registrados\n" << endl;
	while (actual != nullptr) {
		cout << "Nombre del estudiante: " << actual->estudiante.nombre << endl;
		cout << "Codigo del estudiante: " << actual->estudiante.id << endl;
		cout << "Carrera que sigue el estudiante: " << actual->estudiante.carrera << endl;
		cout << "Promedio del estudiante: " << actual->estudiante.promedio << endl;
		cout << "Materias asignadas:" << endl;
		for (const auto& mat : actual->estudiante.materias) {
			mat.mostrarInfo();
		}
		cout << endl;
		actual = actual->siguiente;
	}
}

// Buscar por ID: O(n)
nodo* listaEstudiantes::buscarPorId(const string& id) const {
	nodo* actual = cabeza;
	while (actual != nullptr) {
		if (actual->estudiante.id == id) return actual;
		actual = actual->siguiente;
	}
	return nullptr;
}

// Buscar por nombre: O(n). Puede devolver múltiples coincidencias.
namespace {
	// Función helper para convertir a minúsculas
	string aMinusculas(const string& str) {
		string resultado = str;
		for (auto& c : resultado) {
			c = tolower(static_cast<unsigned char>(c));
		}
		return resultado;
	}
}

void listaEstudiantes::buscarPorNombre(const string& nombre) const {
	// Verificar lista vacía
	if (cabeza == nullptr) {
		cout << "No hay estudiantes registrados en el sistema." << endl;
		return;
	}

	// Preparar búsqueda: trim + minúsculas
	string nombreBusqueda = aMinusculas(nombre);
	// Eliminar espacios del inicio y final (usar utils::trim si está disponible)
	size_t inicio = nombreBusqueda.find_first_not_of(" \t");
	size_t fin = nombreBusqueda.find_last_not_of(" \t");
	if (inicio == string::npos) {
		cout << "Nombre de busqueda vacio." << endl;
		return;
	}
	nombreBusqueda = nombreBusqueda.substr(inicio, fin - inicio + 1);

	bool encontrado = false;
	nodo* actual = cabeza;
	int contador = 0;
	
	cout << "\n=== Resultados de Busqueda ===" << endl;
	cout << "Buscando: \"" << nombre << "\"" << endl;
	cout << "================================" << endl;
	
	while (actual != nullptr) {
		string nombreEstudiante = aMinusculas(actual->estudiante.nombre);
		
		// Búsqueda parcial (contiene)
		if (nombreEstudiante.find(nombreBusqueda) != string::npos) {
			contador++;
			cout << "\n[Resultado #" << contador << "]" << endl;
			cout << "Nombre completo: " << actual->estudiante.nombre << endl;
			cout << "ID: " << actual->estudiante.id << endl;
			cout << "Carrera: " << actual->estudiante.carrera << endl;
			cout << "Promedio: " << fixed << setprecision(2)
			<< actual->estudiante.promedio << endl;
			cout << "Materias registradas: " << actual->estudiante.materias.size() << endl;
			
			cout << "--------------------------------" << endl;
			encontrado = true;
		}
		actual = actual->siguiente;
	}
	
	if (!encontrado) {
		cout << "\nNo se encontraron coincidencias para: \"" << nombre << "\"" << endl;
		cout << "\nSugerencias:" << endl;
		cout << "  -> Verifique la ortografia" << endl;
		cout << "  -> Intente con solo el primer nombre" << endl;
		cout << "  -> Use menos caracteres para busqueda mas amplia" << endl;
	} else {
		cout << "\n Total de coincidencias encontradas: " << contador << endl;
	}
}

void listaEstudiantes::eliminarEstudiante(codigoEstudiante id) {
	if (cabeza == nullptr) {
		cout << "No hay estudiantes en el sistema: " << endl;
		return;
	}

	nodo* actual = cabeza;
	while (actual != nullptr && actual->estudiante.id != id) {
		actual = actual->siguiente;
	}

	if (actual == nullptr) {
		cout << "No se encontro el estudiante con ID: " << id << endl;
		return;
	}

	if (actual == cabeza) {
		cabeza = actual->siguiente;
		if (cabeza != nullptr) {
			cabeza->anterior = nullptr;
		}
	} else if (actual == cola) {
		cola = actual->anterior;
		cola->siguiente = nullptr;
	} else {
		actual->anterior->siguiente = actual->siguiente;
		actual->siguiente->anterior = actual->anterior;
	}

	delete actual;
	cout << "Estudiante eliminado de forma correcta." << endl;
}
double listaEstudiantes::recalcularPromedio(const string& id){
	nodo* actual = buscarPorId(id);
	if(actual == nullptr){
		return 0;
	}
	if(actual->estudiante.materias.empty()){
		actual->estudiante.promedio = 0.0;
	} else {
		double suma = 0.0;
			for (const auto& mat : actual->estudiante.materias) {
			suma += mat.getCalificacion();
		}
		actual->estudiante.promedio = suma/actual->estudiante.materias.size();
	}
}
// Método para asignar materia 
void listaEstudiantes::asignarMateria(const char* id, const char* nombreMat, const char* codigoMat, int creditos, double calificacion) {
	string idStr = id;
	nodo* actual = cabeza;
	while (actual != nullptr && actual->estudiante.id != idStr) {
		actual = actual->siguiente;
	}

	if (actual == nullptr) {
		cout << "No se encontro el estudiante con ID: " << id << endl;
		return;
	}

	// Crear una nueva materia y agregarla al vector del estudiante
	Materia<double> nuevaMateria(string(nombreMat), string(codigoMat), creditos, calificacion);
	actual->estudiante.materias.push_back(nuevaMateria);
	//recalcular el promedio
	actual->estudiante.promedio = recalcularPromedio(id);
	cout << "Materia asignada exitosamente al estudiante " << actual->estudiante.nombre << endl;
}

// Metodo para obtener la cabeza de la lista (10/11/2025)
nodo* listaEstudiantes::getCabeza() const {
	return cabeza;
}

// Limpia toda la lista y libera memoria O(n)
void listaEstudiantes::limpiar() {
	nodo* actual = cabeza;
	while (actual != nullptr) {
		nodo* borrar = actual;
		actual = actual->siguiente;
		delete borrar;
	}
	cabeza = nullptr;
	cola = nullptr;
}


