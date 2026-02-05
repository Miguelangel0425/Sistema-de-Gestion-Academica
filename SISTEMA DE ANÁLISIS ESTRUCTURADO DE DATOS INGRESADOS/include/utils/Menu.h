#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "../struct/Cliente.h"
#include "../struct/Producto.h"
#include "../struct/Pedido.h"
#include "../containers/arbolBinario.h"
#include "../containers/Cola.h"
#include "../containers/Lista_enlazada.h"
#include "../containers/Pila.h"
#include "Procesador.h"
#include "Validador.h"
#include "Visualizador.h"

using namespace std;

class Menu{
    private:
    arbolBinario<Cliente>* arbolClientes;
    colaPrioridad<Pedido>* colaPedidos;
    Pila<string>* historial;
    ListaEnlazada<Producto>* listaProductos;
    Procesador* procesador;

    public:

    Menu();

    ~Menu();

    void mostrarMenuPrincipal();

    void ejecutar();

    void ingresarCliente();
    void ingresarProducto();
    void ingresarPedido();
    void procesarPedidos();
    void buscarCliente();
    void verEstadosPedidos();
    void verHistorial();
    void visualizarEstructuras();
    void generarReporte();
    void eliminarCliente();

    void verificarStock();

    void pausar();
    void limpiarPantalla();
    int leerOpcion();
    string leerLinea(const string & msj);
};
#endif