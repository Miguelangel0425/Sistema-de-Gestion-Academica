#ifndef PROCESADOR_H
#define PROCESADOR_H

#include <string>
#include <vector>
#include "../struct/Cliente.h"
#include "../struct/Producto.h"
#include "../struct/Pedido.h"
#include "../containers/arbolBinario.h"
#include "../containers/Cola.h"
#include "../containers/Lista_enlazada.h"
#include "../containers/Pila.h"

using namespace std;

class Procesador{
    private:
    arbolBinario<Cliente>* arbolClientes;
    colaPrioridad<Pedido>* colaPedidos;
    Pila<string>* pilaHistorial;
    ListaEnlazada<Producto>* listaProductos;

    int clientesCont;
    int pedidosCont;
    int productosCont;

    public:

    Procesador(arbolBinario<Cliente>* arbol, colaPrioridad<Pedido>* cola,
            Pila<string>* pila, ListaEnlazada<Producto>* lista);
    
    Cliente procesarCliente(const vector<string>& campos);

    Producto procesarProducto(const vector<string>& campos);

    Pedido procesarPedido(int idCliente, int prioridad, const vector<Producto>& productos);

    void procesarSiguientePedido();

    void procesarTodosPedidos();

    bool clienteTienePedidos(int idCliente);

    bool desactivarCliente(int idCliente);

    bool reactivarCliente(int idCliente);

    void listaClientesInactivos();
    
    void verificarStockCritico();

    int generarIdCliente();

    int generarIdPedido();

    int generarIdProducto();

    string obtenerFechaActual(); //formato(DD/MM/AAAA)
    
    //agrega la ulima operacion al historial
    void agregarHistorial(const string& operacion);
    
    void calcularEstadisticas();

    //Obtener contadores(para guardar)
    int getContadorClientes() const { return clientesCont; }
    int getContadorPedidos() const { return pedidosCont; }
    int getContadorProductos() const { return productosCont; }
    
    //  Establecer contadores (para cargar)
    void setContadorClientes(int valor) { clientesCont = valor; }
    void setContadorPedidos(int valor) { pedidosCont = valor; }
    void setContadorProductos(int valor) { productosCont = valor; }
};
#endif