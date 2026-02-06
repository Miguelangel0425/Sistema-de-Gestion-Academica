#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include <string>
#include <fstream>
#include "../struct/Cliente.h"
#include "../struct/Producto.h"
#include "../struct/Pedido.h"
#include "../containers/arbolBinario.h"
#include "../containers/Cola.h"
#include "../containers/Lista_enlazada.h"
#include "../containers/Pila.h"

using namespace std;

class GestorArchivos{
    private:
    string rutaClientes;
    string rutaProductos;
    string rutaPedidos;
    string rutaHistorial;
    string rutaContadores;

    public:

    GestorArchivos();

    //Guardar datos
    bool guardarClientes(arbolBinario<Cliente>& arbol);
    bool guardarProductos(ListaEnlazada<Producto>& lista);
    bool guardarPedidos(colaPrioridad<Pedido>& cola);
    bool guardarHistorial(Pila<string>& pila);
    bool guardarContadores(int clientes, int productos, int pedidos);
    bool guardarTodo(arbolBinario<Cliente>& arbol,ListaEnlazada<Producto>& lista,colaPrioridad<Pedido>& cola,
        Pila<string>& pila,int contClientes, int contProductos, int contPedidos);
    
    // Cargar datos
    bool cargarClientes(arbolBinario<Cliente>& arbol);
    bool cargarProductos(ListaEnlazada<Producto>& lista);
    bool cargarPedidos(colaPrioridad<Pedido>& cola);
    bool cargarHistorial(Pila<string>& pila);
    bool cargarContadores(int& clientes, int& productos, int& pedidos);
    bool cargarTodo(arbolBinario<Cliente>& arbol,ListaEnlazada<Producto>& lista,colaPrioridad<Pedido>& cola,
        Pila<string>& pila,int& contClientes, int& contProductos, int& contPedidos);
    
    // Verificar si existen archivos guardados
    bool existenDatosGuardados();
    
    // Limpiar archivos
    bool limpiarArchivos();
};

#endif