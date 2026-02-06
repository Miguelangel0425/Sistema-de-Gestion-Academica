#include "../include/utils/Visualizador.h"

void Visualizador::mostrarArbolClientes(arbolBinario<Cliente>& arbol) {
    mostrarEncabezado("ESTRUCTURA: ARBOL BINARIO DE BUSQUEDA - CLIENTES");
    
    if (arbol.estaVacio()) {
        cout << "\n! No hay clientes registrados" << endl;
        return;
    }
    
    
    cout << "\n[RECORRIDO IN-ORDEN] Clientes ACTIVOS (ordenados por ID):" << endl;
    mostrarSeparador();
    
    if (arbol.contarActivos() == 0) {
        cout << "! No hay clientes activos registrados" << endl;
    } else {
        arbol.inordenActivos();
    }
    
    cout << "\n\n[REPRESENTACION GRAFICA DEL ARBOL]:" << endl;
    cout << "(Mostrando estructura completa - inactivos marcados con X)" << endl;
    mostrarSeparador();
    arbol.imprimirArbol();
    
    cout << "\n\nEstadisticas:" << endl;
    cout << "  Total de clientes: " << arbol.getTam() << endl;
    cout << "  ├─ Activos: " << arbol.contarActivos() << " +" << endl;
    cout << "  └─ Inactivos: " << arbol.contarInactivos() << "X" << endl;
    
    if (arbol.contarInactivos() > 0) {
        cout << "\nNOTA: Los clientes inactivos no se muestran en el listado." << endl;
        cout << "Use 'Gestionar clientes > Ver clientes inactivos' para verlos." << endl;
    }
}

void Visualizador::mostrarColaPedidos(colaPrioridad<Pedido>& cola) {
    mostrarEncabezado("ESTRUCTURA: COLA DE PRIORIDAD - PEDIDOS");
    
    if (cola.estaVacio()) {
        cout << "\n! No hay pedidos en cola" << endl;
        return;
    }
    
    cout << "\n[PEDIDOS ORDENADOS POR PRIORIDAD]:" << endl;
    cout << "(1=Urgente, 2=Normal, 3=Baja)" << endl;
    mostrarSeparador();
    cola.mostrar();
    
    cout << "\n\nTotal de pedidos en cola: " << cola.getTam() << endl;
}

void Visualizador::mostrarHistorial(Pila<string>& pila) {
    mostrarEncabezado("ESTRUCTURA: PILA - HISTORIAL DE OPERACIONES");
    
    if (pila.estaVacio()) {
        cout << "\n! No hay operaciones en el historial" << endl;
        return;
    }
    
    cout << "\n[ÚLTIMAS OPERACIONES] (Más reciente primero):" << endl;
    mostrarSeparador();
    pila.mostrarHistorial();
    
    cout << "\n\nTotal de operaciones: " << pila.getTam() << endl;
}

void Visualizador::mostrarListaProductos(ListaEnlazada<Producto>& lista) {
    mostrarEncabezado("ESTRUCTURA: LISTA ENLAZADA - PRODUCTOS");
    
    if (lista.estaVacio()) {
        cout << "\n! No hay productos registrados" << endl;
        return;
    }
    
    cout << "\n[CATÁLOGO DE PRODUCTOS]:" << endl;
    mostrarSeparador();
    lista.mostrar();
    
    cout << "\n\nTotal de productos: " << lista.getTam() << endl;
}

void Visualizador::mostrarTodasEstructuras(arbolBinario<Cliente>& arbol,colaPrioridad<Pedido>& cola,
                                        Pila<string>& pila,ListaEnlazada<Producto>& lista) {

    mostrarEncabezado("VISUALIZACIÓN COMPLETA DE ESTRUCTURAS DE DATOS");
    
    cout << "\n\n";
    mostrarArbolClientes(arbol);
    
    cout << "\n\n";
    mostrarColaPedidos(cola);
    
    cout << "\n\n";
    mostrarListaProductos(lista);
    
    cout << "\n\n";
    mostrarHistorial(pila);
}

void Visualizador::menuVisualizacion() {
    cout << "\n||=======================================||" << endl;
    cout << "||     MENÚ DE VISUALIZACIÓN              ||" << endl;
    cout << "||========================================||" << endl;
    cout << "\n1. Ver Arbol de Clientes (BST)" << endl;
    cout << "2. Ver Cola de Pedidos (Prioridad)" << endl;
    cout << "3. Ver Lista de Productos (Enlazada)" << endl;
    cout << "4. Ver Historial (Pila)" << endl;
    cout << "5. Ver todas las estructuras" << endl;
    cout << "0. Volver al menú principal" << endl;
    cout << "\nOpción: ";
}

void Visualizador::mostrarEncabezado(const string& titulo) {
    int ancho = 60;
    int padding = (ancho - titulo.length() - 2) / 2;
    
    cout << "\n||";
    for (int i = 0; i < ancho; i++) cout << "=";
    cout << "||" << endl;
    
    cout << "||";
    for (int i = 0; i < padding; i++) cout << " ";
    cout << titulo;
    for (int i = 0; i < ancho - padding - titulo.length(); i++) cout << " ";
    cout << "||" << endl;
    
    cout << "||";
    for (int i = 0; i < ancho; i++) cout << "=";
    cout << "||" << endl;
}

void Visualizador::mostrarSeparador() {
    cout << "---------------------------------------------------------------------" << endl;
}

void Visualizador::mostrarExito(const string& mensaje) {
    cout << "\n+ " << mensaje << endl;
}

void Visualizador::mostrarError(const string& mensaje) {
    cout << "\nX ERROR: " << mensaje << endl;
}

void Visualizador::mostrarAdvertencia(const string& mensaje) {
    cout << "\n! ADVERTENCIA: " << mensaje << endl;
}

void Visualizador::mostrarPaso(int numero, const string& descripcion) {
    cout << "\n[PASO " << numero << "] " << descripcion << endl;
}
