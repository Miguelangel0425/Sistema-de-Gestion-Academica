#ifndef VISUALIZADOR_H
#define VISUALIZADOR_H

#include <iostream>
#include <iomanip>
#include "../struct/Cliente.h"
#include "../struct/Producto.h"
#include "../struct/Pedido.h"
#include "../containers/arbolBinario.h"
#include "../containers/Cola.h"
#include "../containers/Lista_enlazada.h"
#include "../containers/Pila.h"

using namespace std;

class Visualizador{
    public:

    static void mostrarArbolClientes(arbolBinario<Cliente>& arbol);

    static void mostrarColaPedidos(colaPrioridad<Pedido>& cola);

    static void mostrarHistorial(Pila<string>& pila);

    static void mostrarListaProductos(ListaEnlazada<Producto>& lista);

    static void mostrarTodasEstructuras(arbolBinario<Cliente>& arbol,
    colaPrioridad<Pedido>& cola,Pila<string>& pila,ListaEnlazada<Producto>& lista);

    static void menuVisualizacion();

    static void mostrarEncabezado(const string& titulo);

    static void mostrarSeparador();

    static void mostrarExito(const string& mensaje);

    static void mostrarError(const string& mensaje);

    static void mostrarAdvertencia(const string& mensaje);

    static void mostrarPaso(int numero, const string& descripcion);
};

#endif 