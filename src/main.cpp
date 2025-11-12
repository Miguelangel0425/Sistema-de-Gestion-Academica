#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "../include/estudiante.h"
#include "../include/materia.h"
#include "../include/lista.h"
#include "../include/calificaciones.h"
#include "../include/pila.h"
#include "../include/cola.h"
#include "../utils/validaciones.h"
#include "../utils/archivos.h"

using namespace std;

void menuPrincipal()
{
	system("cls");
	cout << "\n=== Sistema de Gestion Academica ===\n";
	cout << "1. Estudiantes (lista dinamica)\n";
	cout << "2. Materias (asignar a estudiante)\n";
	cout << "3. Calificaciones (recursividad)\n";
	cout << "4. Historial (pila, deshacer)\n";
	cout << "5. Solicitudes (cola FIFO)\n";
	cout << "6. Exportar datos a TXT\n";
	cout << "7. Importar datos desde TXT\n";
	cout << "8. Salir\n";
	cout << "Seleccione una opcion: ";
}

void menuEstudiantes()
{
	system("cls");
	cout << "\n-- Modulo Estudiantes --\n";
	cout << "1. Registrar estudiante\n";
	cout << "2. Mostrar estudiantes\n";
	cout << "3. Buscar por ID\n";
	cout << "4. Buscar por nombre\n";
	cout << "5. Eliminar estudiante\n";
	cout << "6. Volver\n";
	cout << "Opcion: ";
}

void menuMaterias()
{
	system("cls");
	cout << "\n-- Modulo Materias --\n";
	cout << "1. Asignar materia a estudiante\n";
	cout << "2. Volver\n";
	cout << "Opcion: ";
}

void menuCalificaciones()
{
	system("cls");
	cout << "\n-- Modulo Calificaciones (Recursivo) --\n";
	cout << "1. Promedio general de un estudiante\n";
	cout << "2. Contar estudiantes que superan un promedio\n";
	cout << "3. Mostrar resultados contra promedio objetivo\n";
	cout << "4. Volver\n";
	cout << "Opcion: ";
}

void menuHistorial()
{
	system("cls");
	cout << "\n-- Historial --\n";
	cout << "1. Deshacer ultima accion\n";
	cout << "2. Volver\n";
	cout << "Opcion: ";
}

void menuSolicitudes()
{
	system("cls");
	cout << "\n-- Solicitudes --\n";
	cout << "1. Registrar solicitud\n";
	cout << "2. Atender siguiente solicitud\n";
	cout << "3. Ver solicitudes en espera\n";
	cout << "4. Volver\n";
	cout << "Opcion: ";
}

string formatearDouble(double valor)
{
	ostringstream os;
	os << fixed << setprecision(2) << valor;
	return os.str();
}

void presioneEnter()
{
	cout << "\nPresione Enter para continuar...";
	cin.get();
}

void exportarDatosTXT(const listaEstudiantes &lista)
{
	system("cls");
	cout << "-- Exportar datos a TXT --" << endl;
	string nombreArchivo;
	cout << "Nombre de archivo (ejemplo reporte.txt). Dejar vacio para generar uno automaticamente: ";
	getline(cin, nombreArchivo);
	if (!utils::esNoVacio(nombreArchivo))
	{
		nombreArchivo = "reporte_sga_" + utils::fechaHoraActual();
		for (auto &c : nombreArchivo)
		{
			if (c == ' ' || c == ':')
				c = '_';
		}
		nombreArchivo += ".txt";
	}

	vector<string> lineas;
	lineas.push_back("Sistema de Gestion Academica - Exportacion");
	lineas.push_back("Generado: " + utils::fechaHoraActual());
	lineas.push_back("");

	nodo *actual = lista.getCabeza();
	if (actual == nullptr)
	{
		lineas.push_back("No hay estudiantes registrados.");
	}
	else
	{
		while (actual != nullptr)
		{
			lineas.push_back("Estudiante: " + actual->estudiante.nombre);
			lineas.push_back("ID: " + actual->estudiante.id + " | Carrera: " + actual->estudiante.carrera);
			lineas.push_back("Promedio general: " + formatearDouble(actual->estudiante.promedio));
			if (actual->estudiante.materias.empty())
			{
				lineas.push_back("  Sin materias registradas.");
			}
			else
			{
				int idx = 1;
				for (const auto &mat : actual->estudiante.materias)
				{
					lineas.push_back("  Materia " + to_string(idx) + ": " + mat.getNombre() + " (" + mat.getCodigo() + ")");
					lineas.push_back("    Creditos: " + to_string(mat.getCreditos()) + " | Calificacion: " + formatearDouble(mat.getCalificacion()));
					idx++;
				}
			}
			lineas.push_back("----------------------------------------");
			actual = actual->siguiente;
		}
	}

	bool exito = utils::escribirLineas(nombreArchivo, lineas, false);
	if (exito)
	{
		cout << "Datos exportados correctamente en el archivo: " << nombreArchivo << endl;
	}
	else
	{
		cout << "No se pudo escribir el archivo: " << nombreArchivo << endl;
	}
	presioneEnter();
}

void importarDatosTXT(listaEstudiantes &lista, PilaHistorial &historial)
{
	system("cls");
	cout << "-- Importar datos desde TXT --" << endl;
	string nombreArchivo;
	cout << "Nombre del archivo a importar: ";
	getline(cin, nombreArchivo);

	if (!utils::esNoVacio(nombreArchivo))
	{
		cout << "Nombre de archivo no puede estar vacio." << endl;
		presioneEnter();
		return;
	}

	if (!utils::existeArchivo(nombreArchivo))
	{
		cout << "El archivo no existe: " << nombreArchivo << endl;
		presioneEnter();
		return;
	}

	vector<string> lineas;
	if (!utils::leerLineas(nombreArchivo, lineas))
	{
		cout << "Error al leer el archivo: " << nombreArchivo << endl;
		presioneEnter();
		return;
	}

	int importados = 0;
	int actualizados = 0;
	string nombre, id, carrera;
	double promedio = 0.0;
	vector<Materia<double>> materiasTemp;
	bool enEstudiante = false;

	for (size_t i = 0; i < lineas.size(); i++)
	{
		string linea = utils::trim(lineas[i]);

		if (linea.empty() || linea.find("Sistema de Gestion") != string::npos ||
			linea.find("Generado:") != string::npos ||
			linea.find("---") != string::npos)
		{
			continue;
		}

		if (linea.find("Estudiante:") == 0)
		{
			if (enEstudiante && !id.empty())
			{
				// Verificar si el estudiante ya existe

				if (!materiasTemp.empty())
				{
					double sumaCalif = 0.0;
					for (const auto &m : materiasTemp)
					{
						sumaCalif += m.getCalificacion();
					}
					promedio = sumaCalif / materiasTemp.size();
				}
				else
				{
					promedio = 0.0; // Sin materias, promedio en 0
				}

				nodo *existente = lista.buscarPorId(id);
				if (existente != nullptr)
				{
					// Actualizar estudiante existente
					existente->estudiante.nombre = nombre;
					existente->estudiante.carrera = carrera;
					existente->estudiante.promedio = promedio;
					// Limpiar materias existentes y agregar las nuevas
					existente->estudiante.materias.clear();
					for (const auto &m : materiasTemp)
					{
						existente->estudiante.materias.push_back(m);
					}
					actualizados++;
				}
				else
				{
					// Agregar nuevo estudiante
					lista.registrarEstudiante(nombre, id, carrera, promedio);
					for (const auto &m : materiasTemp)
					{
						lista.asignarMateria(id.c_str(), m.getNombre().c_str(), m.getCodigo().c_str(), m.getCreditos(), m.getCalificacion());
					}
					Estudiante snap;
					snap.nombre = nombre;
					snap.id = id;
					snap.carrera = carrera;
					snap.promedio = promedio;
					snap.materias = materiasTemp;
					historial.push(Accion(AgregarEstudiante, snap));
					importados++;
				}
			}
			nombre = linea.substr(11);
			nombre = utils::trim(nombre);
			id = "";
			carrera = "";
			promedio = 0.0;
			materiasTemp.clear();
			enEstudiante = true;
		}
		else if (linea.find("ID:") == 0)
		{
			size_t posPipe = linea.find("|");
			if (posPipe != string::npos)
			{
				string idParte = linea.substr(3, posPipe - 3);
				id = utils::trim(idParte);
				string carreraParte = linea.substr(posPipe + 1);
				size_t posCarrera = carreraParte.find("Carrera:");
				if (posCarrera != string::npos)
				{
					carrera = carreraParte.substr(posCarrera + 8);
					carrera = utils::trim(carrera);
				}
			}
		}
		else if (linea.find("Promedio general:") == 0)
		{
			string promStr = linea.substr(16);
			promStr = utils::trim(promStr);
			if (utils::esNumero(promStr))
			{
				promedio = stod(promStr);
			}
		}
		else if (linea.find("Materia") == 0)
		{
			size_t posNombre = linea.find(":");
			if (posNombre != string::npos)
			{
				string resto = linea.substr(posNombre + 1);
				size_t posParentesis = resto.find("(");
				if (posParentesis != string::npos)
				{
					string nomMat = utils::trim(resto.substr(0, posParentesis));
					string codMat = resto.substr(posParentesis + 1);
					codMat = codMat.substr(0, codMat.find(")"));
					codMat = utils::trim(codMat);

					if (i + 1 < lineas.size())
					{
						string lineaCreditos = utils::trim(lineas[i + 1]);
						if (lineaCreditos.find("Creditos:") == 0)
						{
							size_t posPipe = lineaCreditos.find("|");
							if (posPipe != string::npos)
							{
								string creditosStr = lineaCreditos.substr(9, posPipe - 9);
								creditosStr = utils::trim(creditosStr);
								int creditos = 0;
								if (utils::esNumero(creditosStr))
								{
									creditos = stoi(creditosStr);
								}

								string califStr = lineaCreditos.substr(posPipe + 1);
								size_t posCalif = califStr.find("Calificacion:");
								if (posCalif != string::npos)
								{
									califStr = califStr.substr(posCalif + 13);
									califStr = utils::trim(califStr);
									double calif = 0.0;
									if (utils::esNumero(califStr))
									{
										calif = stod(califStr);
									}
									materiasTemp.push_back(Materia<double>(nomMat, codMat, creditos, calif));
								}
							}
						}
					}
				}
			}
		}
	}

	if (enEstudiante && !id.empty())
	{

		if (!materiasTemp.empty())
		{
			double sumaCalif = 0.0;
			for (const auto &m : materiasTemp)
			{
				sumaCalif += m.getCalificacion();
			}
			promedio = sumaCalif / materiasTemp.size();
		}
		else
		{
			promedio = 0.0; // Sin materias, promedio en 0
		}

		// Verificar si el estudiante ya existe
		nodo *existente = lista.buscarPorId(id);
		if (existente != nullptr)
		{
			// Actualizar estudiante existente
			existente->estudiante.nombre = nombre;
			existente->estudiante.carrera = carrera;
			existente->estudiante.promedio = promedio;
			// Limpiar materias existentes y agregar las nuevas
			existente->estudiante.materias.clear();
			for (const auto &m : materiasTemp)
			{
				existente->estudiante.materias.push_back(m);
			}
			actualizados++;
		}
		else
		{
			// Agregar nuevo estudiante
			lista.registrarEstudiante(nombre, id, carrera, promedio);
			for (const auto &m : materiasTemp)
			{
				lista.asignarMateria(id.c_str(), m.getNombre().c_str(), m.getCodigo().c_str(), m.getCreditos(), m.getCalificacion());
			}
			Estudiante snap;
			snap.nombre = nombre;
			snap.id = id;
			snap.carrera = carrera;
			snap.promedio = promedio;
			snap.materias = materiasTemp;
			historial.push(Accion(AgregarEstudiante, snap));
			importados++;
		}
	}

	cout << "Importacion completada. Estudiantes nuevos: " << importados << ", actualizados: " << actualizados << endl;
	presioneEnter();
}

int main()
{
	listaEstudiantes lista;
	PilaHistorial historial;
	ColaSolicitudes cola;

	int opcion = 0;
	do
	{
		menuPrincipal();
		cin >> opcion;
		cin.ignore();

		switch (opcion)
		{
		case 1:
		{
			int opE = 0;
			do
			{
				menuEstudiantes();
				cin >> opE;
				cin.ignore();

				switch (opE)
				{
				case 1:
				{
					string nombre, id, carrera, promedioStr;
					double promedio = 0.0;
					bool idValido = false;
					do
					{
						cout << "Nombre: ";
						getline(cin, nombre);
					} while (!utils::esNoVacio(nombre));
					do
					{
						cout << "ID: ";
						getline(cin, id);

						// Verificar que no esté vacío
						if (!utils::esNoVacio(id))
						{
							cout << "El ID no puede estar vacío." << endl;
							continue;
						}

						// Verificar que no exista ya en el sistema
						nodo *existente = lista.buscarPorId(id);
						if (existente != nullptr)
						{
							cout << "ERROR: Ya existe un estudiante con el ID '" << id << "'." << endl;
							cout << "Estudiante registrado: " << existente->estudiante.nombre << endl;
							cout << "Por favor, ingrese un ID diferente." << endl;
						}
						else
						{
							idValido = true;
						}
					} while (!idValido);
					do
					{
						cout << "Carrera: ";
						getline(cin, carrera);
					} while (!utils::esNoVacio(carrera));
					cout << "Promedio inicial: 0.0 (se calculara al asignar materias)" << endl;
					lista.registrarEstudiante(nombre, id, carrera, promedio);
					Estudiante snap;
					snap.nombre = nombre;
					snap.id = id;
					snap.carrera = carrera;
					snap.promedio = promedio;
					historial.push(Accion(AgregarEstudiante, snap));
					presioneEnter();
					break;
				}
				case 2:
					lista.mostrarEstudiantes();
					presioneEnter();
					break;
				case 3:
				{
					string id;
					cout << "ID a buscar: ";
					getline(cin, id);
					nodo *n = lista.buscarPorId(id);
					if (n)
					{
						cout << "Hallado: " << n->estudiante.nombre << " | " << n->estudiante.carrera << " | Promedio: " << n->estudiante.promedio << endl;
					}
					else
					{
						cout << "No se encontro estudiante con ID " << id << endl;
					}
					presioneEnter();
					break;
				}
				case 4:
				{
					string nombre;
					cout << "Nombre a buscar: ";
					getline(cin, nombre);
					lista.buscarPorNombre(nombre);
					presioneEnter();
					break;
				}
				case 5:
				{
					string id;
					cout << "ID a eliminar: ";
					getline(cin, id);
					nodo *n = lista.buscarPorId(id);
					if (n)
					{
						Estudiante snap = n->estudiante;
						lista.eliminarEstudiante(id);
						historial.push(Accion(EliminarEstudiante, snap));
					}
					else
					{
						cout << "No se encontro estudiante con ID " << id << endl;
					}
					presioneEnter();
					break;
				}
				case 6:
					break;
				default:
					cout << "Opcion invalida." << endl;
					presioneEnter();
					break;
				}
			} while (opE != 6);
			break;
		}
		case 2:
		{
			int opM = 0;
			do
			{
				menuMaterias();
				cin >> opM;
				cin.ignore();

				switch (opM)
				{
				case 1:
				{
					string id, nombreMat, codMat, creditosStr, califStr;
					int creditos = 0;
					double calif = 0.0;
					do
					{
						cout << "ID del estudiante: ";
						getline(cin, id);
					} while (!utils::esNoVacio(id));
					do
					{
						cout << "Nombre de materia: ";
						getline(cin, nombreMat);
					} while (!utils::esNoVacio(nombreMat));
					do
					{
						cout << "Codigo de materia: ";
						getline(cin, codMat);
					} while (!utils::esNoVacio(codMat));
					do
					{
						cout << "Creditos (1-30): ";
						getline(cin, creditosStr);
					} while (!utils::esNumero(creditosStr) || !(utils::enRango(stod(utils::trim(creditosStr)), 1.0, 30.0)));
					creditos = static_cast<int>(stod(utils::trim(creditosStr)));
					do
					{
						cout << "Calificacion (0-100): ";
						getline(cin, califStr);
					} while (!utils::esNumero(califStr) || !(utils::enRango(stod(utils::trim(califStr)), 0.0, 100.0)));
					calif = stod(utils::trim(califStr));
					lista.asignarMateria(id.c_str(), nombreMat.c_str(), codMat.c_str(), creditos, calif);
					Estudiante eSnap;
					nodo *n = lista.buscarPorId(id);
					if (n)
						eSnap = n->estudiante;
					historial.push(Accion(AsignarMateriaEstudiante, eSnap, Materia<double>(nombreMat, codMat, creditos, calif)));
					presioneEnter();
					break;
				}
				case 2:
					break;
				default:
					cout << "Opcion invalida." << endl;
					presioneEnter();
					break;
				}
			} while (opM != 2);
			break;
		}
		case 3:
		{
			int opC = 0;
			do
			{
				menuCalificaciones();
				cin >> opC;
				cin.ignore();

				switch (opC)
				{
				case 1:
				{
					string id;
					cout << "ID del estudiante: ";
					getline(cin, id);
					nodo *n = lista.buscarPorId(id);
					if (n)
					{
						double p = promedioGeneralRecursivo(n->estudiante);
						cout << "Promedio general (recursivo) de " << n->estudiante.nombre << ": " << p << endl;
					}
					else
					{
						cout << "No se encontro estudiante." << endl;
					}
					presioneEnter();
					break;
				}
				case 2:
				{
					double objetivo;
					cout << "Promedio objetivo: ";
					cin >> objetivo;
					cin.ignore();
					int c = contarSuperanPromedioRecursivo(lista.getCabeza(), objetivo);
					cout << "Estudiantes que superan " << objetivo << ": " << c << endl;
					presioneEnter();
					break;
				}
				case 3:
				{
					double objetivo;
					cout << "Promedio objetivo: ";
					cin >> objetivo;
					cin.ignore();
					mostrarResultadosRecursivo(lista.getCabeza(), objetivo);
					presioneEnter();
					break;
				}
				case 4:
					break;
				default:
					cout << "Opcion invalida." << endl;
					presioneEnter();
					break;
				}
			} while (opC != 4);
			break;
		}
		case 4:
		{
			int opH = 0;
			do
			{
				menuHistorial();
				cin >> opH;
				cin.ignore();

				switch (opH)
				{
				case 1:
					if (historial.estaVacia())
					{
						cout << "No hay acciones para deshacer." << endl;
					}
					else
					{
						Accion a = historial.pop();
						switch (a.tipo)
						{
						case AgregarEstudiante:
							lista.eliminarEstudiante(a.estudianteSnapshot.id);
							cout << "Se deshizo el registro de " << a.estudianteSnapshot.nombre << endl;
							break;
						case EliminarEstudiante:
							lista.registrarEstudiante(a.estudianteSnapshot.nombre, a.estudianteSnapshot.id, a.estudianteSnapshot.carrera, a.estudianteSnapshot.promedio);
							for (const auto &m : a.estudianteSnapshot.materias)
							{
								lista.asignarMateria(a.estudianteSnapshot.id.c_str(), m.getNombre().c_str(), m.getCodigo().c_str(), m.getCreditos(), m.getCalificacion());
							}
							cout << "Se restauro el estudiante " << a.estudianteSnapshot.nombre << endl;
							break;
						case AsignarMateriaEstudiante:
						{
							nodo *n = lista.buscarPorId(a.estudianteSnapshot.id);
							if (n)
							{
								auto &v = n->estudiante.materias;
								for (int i = (int)v.size() - 1; i >= 0; --i)
								{
									if (v[i].getCodigo() == a.materiaSnapshot.getCodigo())
									{
										v.erase(v.begin() + i);
										break;
									}
								}
								cout << "Se deshizo la asignacion de materia " << a.materiaSnapshot.getNombre() << " al estudiante " << a.estudianteSnapshot.nombre << endl;
							}
							break;
						}
						}
					}
					presioneEnter();
					break;
				case 2:
					break;
				default:
					cout << "Opcion invalida." << endl;
					presioneEnter();
					break;
				}
			} while (opH != 2);
			break;
		}
		case 5:
		{
			int opQ = 0;
			do
			{
				menuSolicitudes();
				cin >> opQ;
				cin.ignore();

				switch (opQ)
				{
				case 1:
				{
					string tipo, desc;
					cout << "Tipo de solicitud: ";
					getline(cin, tipo);
					cout << "Descripcion: ";
					getline(cin, desc);
					cola.enqueue(Solicitud(tipo, desc));
					presioneEnter();
					break;
				}
				case 2:
					cola.dequeue();
					presioneEnter();
					break;
				case 3:
					cola.mostrar();
					presioneEnter();
					break;
				case 4:
					break;
				default:
					cout << "Opcion invalida." << endl;
					presioneEnter();
					break;
				}
			} while (opQ != 4);
			break;
		}
		case 6:
			exportarDatosTXT(lista);
			break;
		case 7:
			importarDatosTXT(lista, historial);
			break;
		case 8:
			break;
		default:
			cout << "Opcion invalida." << endl;
			presioneEnter();
			break;
		}
	} while (opcion != 8);

	// Liberación de memoria con confirmación
	cout << "Liberando memoria de estudiantes..." << endl;
	lista.limpiar();
	cout << "Liberando memoria del historial..." << endl;
	// historial se libera en su destructor
	cout << "Liberando memoria de solicitudes..." << endl;
	// cola se libera en su destructor
	cout << "Memoria liberada correctamente. Saliendo del programa. " << endl;
	return 0;
}
