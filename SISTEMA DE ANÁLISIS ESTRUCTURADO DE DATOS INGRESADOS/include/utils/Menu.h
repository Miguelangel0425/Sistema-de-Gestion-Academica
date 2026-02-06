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
#include "GestorArchivos.h"

using namespace std;

class Menu{
    private:
    arbolBinario<Cliente>* arbolClientes;
    colaPrioridad<Pedido>* colaPedidos;
    Pila<string>* pilaHistorial;
    ListaEnlazada<Producto>* listaProductos;
    Procesador* procesador;
    GestorArchivos* gestorArchivos;

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

    void gestionarCliente();
    void desactivarCliente();
    void reactivarCliente();
    void verClientesInactivo();
    void mostrarClientesActivos();
    void mostrarTodosClientes();

    void verificarStock();

    void guardarDatos();
    void cargarDatos();

    void pausar();
    void limpiarPantalla();
    int leerOpcion();
    string leerLinea(const string & msj);
};
#endif