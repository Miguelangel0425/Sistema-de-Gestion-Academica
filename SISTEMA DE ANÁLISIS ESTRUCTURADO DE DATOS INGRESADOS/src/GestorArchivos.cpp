// src/GestorArchivos.cpp
#include "../include/utils/GestorArchivos.h"
#include "../include/utils/Visualizador.h"
#include <sstream>
#include <vector>
#include <sys/stat.h>

// Constructor
GestorArchivos::GestorArchivos() {
    rutaClientes = "data/clientes.txt";
    rutaProductos = "data/productos.txt";
    rutaPedidos = "data/pedidos.txt";
    rutaHistorial = "data/historial.txt";
    rutaContadores = "data/contadores.txt";
}

// ========================================
// GUARDAR CLIENTES
// ========================================
bool GestorArchivos::guardarClientes(arbolBinario<Cliente>& arbol) {
    if (arbol.estaVacio()) {
        return true;
    }
    
    ofstream archivo(rutaClientes);
    if (!archivo.is_open()) {
        return false;
    }
    
    vector<Cliente> clientes;
    arbol.obtenerElementos(clientes);
    
    // Formato: ID|Nombre|Email|Telefono|Direccion|Activo
    for (const auto& cliente : clientes) {
        archivo << cliente.id << "|"
                << cliente.nombre << "|"
                << cliente.email << "|"
                << cliente.telefono << "|"
                << cliente.direccion << "|"
                << (cliente.activo ? "1" : "0") << endl;
    }
    
    archivo.close();
    return true;
}

// ========================================
// CARGAR CLIENTES
// ========================================
bool GestorArchivos::cargarClientes(arbolBinario<Cliente>& arbol) {
    ifstream archivo(rutaClientes);
    if (!archivo.is_open()) {
        return false;
    }
    
    string linea;
    int contador = 0;
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        vector<string> campos;
        
        while (getline(ss, campo, '|')) {
            campos.push_back(campo);
        }
        
        if (campos.size() == 6) {
            int id = stoi(campos[0]);
            string nombre = campos[1];
            string email = campos[2];
            string telefono = campos[3];
            string direccion = campos[4];
            bool activo = (campos[5] == "1");
            
            Cliente cliente(id, nombre, email, telefono, direccion, activo);
            arbol.insertar(cliente);
            contador++;
        }
    }
    
    archivo.close();
    
    if (contador > 0) {
        cout << "  Cargados " << contador << " clientes" << endl;
    }
    
    return true;
}

// ========================================
// GUARDAR PRODUCTOS
// ========================================
bool GestorArchivos::guardarProductos(ListaEnlazada<Producto>& lista) {
    if (lista.estaVacio()) {
        return true;
    }
    
    ofstream archivo(rutaProductos);
    if (!archivo.is_open()) {
        return false;
    }
    
    // Formato: ID|Nombre|Precio|Cantidad|Categoria
    for (int i = 0; i < lista.getTam(); i++) {
        Producto prod = lista.obtener(i);
        archivo << prod.id << "|"
                << prod.nombre << "|"
                << prod.precio << "|"
                << prod.cantidad << "|"
                << prod.categoria << endl;
    }
    
    archivo.close();
    return true;
}

// ========================================
// CARGAR PRODUCTOS
// ========================================
bool GestorArchivos::cargarProductos(ListaEnlazada<Producto>& lista) {
    ifstream archivo(rutaProductos);
    if (!archivo.is_open()) {
        return false;
    }
    
    string linea;
    int contador = 0;
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        vector<string> campos;
        
        while (getline(ss, campo, '|')) {
            campos.push_back(campo);
        }
        
        if (campos.size() == 5) {
            int id = stoi(campos[0]);
            string nombre = campos[1];
            double precio = stod(campos[2]);
            int cantidad = stoi(campos[3]);
            string categoria = campos[4];
            
            Producto prod(id, nombre, precio, cantidad, categoria);
            lista.insertarFinal(prod);
            contador++;
        }
    }
    
    archivo.close();
    
    if (contador > 0) {
        cout << "  Cargados " << contador << " productos" << endl;
    }
    
    return true;
}

// ========================================
// GUARDAR PEDIDOS
// ========================================
bool GestorArchivos::guardarPedidos(colaPrioridad<Pedido>& cola) {
    if (cola.estaVacio()) {
        return true;
    }
    
    ofstream archivo(rutaPedidos);
    if (!archivo.is_open()) {
        return false;
    }
    
    vector<pair<Pedido, int>> pedidos;
    cola.obtenerElemento(pedidos);
    
    // Formato: ID|IDCliente|Fecha|Prioridad|Estado|Total|Productos
    // Productos: idProd1:cant1;idProd2:cant2
    for (const auto& par : pedidos) {
        const Pedido& ped = par.first;
        archivo << ped.id << "|"
                << ped.idCliente << "|"
                << ped.fecha << "|"
                << ped.prioridad << "|"
                << ped.estado << "|"
                << ped.total << "|";
        
        // Guardar productos del pedido
        for (size_t i = 0; i < ped.productos.size(); i++) {
            const Producto& prod = ped.productos[i];
            archivo << prod.id << ":" << prod.cantidad;
            if (i < ped.productos.size() - 1) {
                archivo << ";";
            }
        }
        archivo << endl;
    }
    
    archivo.close();
    return true;
}

// ========================================
// CARGAR PEDIDOS (simplificado)
// ========================================
bool GestorArchivos::cargarPedidos(colaPrioridad<Pedido>& cola) {
    ifstream archivo(rutaPedidos);
    if (!archivo.is_open()) {
        return false;
    }
    
    string linea;
    int contador = 0;
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        vector<string> campos;
        
        while (getline(ss, campo, '|')) {
            campos.push_back(campo);
        }
        
        if (campos.size() >= 6) {
            int id = stoi(campos[0]);
            int idCliente = stoi(campos[1]);
            string fecha = campos[2];
            int prioridad = stoi(campos[3]);
            string estado = campos[4];
            double total = stod(campos[5]);
            
            Pedido pedido(id, idCliente, fecha, prioridad);
            pedido.estado = estado;
            pedido.total = total;
            
            // Nota: Los productos no se reconstruyen completamente
            // En producción, necesitarías buscar cada producto en el inventario
            
            cola.encolar(pedido, prioridad);
            contador++;
        }
    }
    
    archivo.close();
    
    if (contador > 0) {
        cout << "  Cargados " << contador << " pedidos" << endl;
    }
    
    return true;
}

// ========================================
// GUARDAR HISTORIAL
// ========================================
bool GestorArchivos::guardarHistorial(Pila<string>& pila) {
    if (pila.estaVacio()) {
        return true;
    }
    
    ofstream archivo(rutaHistorial);
    if (!archivo.is_open()) {
        return false;
    }
    
    vector<string> entradas;
    pila.obtenerElementos(entradas);
    
    // Guardar cada entrada (están en orden inverso en la pila)
    for (const auto& entrada : entradas) {
        archivo << entrada << endl;
    }
    
    archivo.close();
    return true;
}

// ========================================
// CARGAR HISTORIAL
// ========================================
bool GestorArchivos::cargarHistorial(Pila<string>& pila) {
    ifstream archivo(rutaHistorial);
    if (!archivo.is_open()) {
        return false;
    }
    
    vector<string> lineas;
    string linea;
    
    while (getline(archivo, linea)) {
        lineas.push_back(linea);
    }
    
    // Apilar en orden inverso para mantener el orden original
    for (int i = lineas.size() - 1; i >= 0; i--) {
        pila.apilar(lineas[i]);
    }
    
    archivo.close();
    
    if (!lineas.empty()) {
        cout << "  Cargadas " << lineas.size() << " operaciones" << endl;
    }
    
    return true;
}

// ========================================
// GUARDAR CONTADORES
// ========================================
bool GestorArchivos::guardarContadores(int clientes, int productos, int pedidos) {
    ofstream archivo(rutaContadores);
    if (!archivo.is_open()) {
        return false;
    }
    
    archivo << clientes << endl;
    archivo << productos << endl;
    archivo << pedidos << endl;
    
    archivo.close();
    return true;
}

// ========================================
// CARGAR CONTADORES
// ========================================
bool GestorArchivos::cargarContadores(int& clientes, int& productos, int& pedidos) {
    ifstream archivo(rutaContadores);
    if (!archivo.is_open()) {
        return false;
    }
    
    archivo >> clientes;
    archivo >> productos;
    archivo >> pedidos;
    
    archivo.close();
    
    cout << "  Contadores restaurados" << endl;
    return true;
}

// ========================================
// GUARDAR TODO
// ========================================
bool GestorArchivos::guardarTodo(arbolBinario<Cliente>& arbol,ListaEnlazada<Producto>& lista,
    colaPrioridad<Pedido>& cola,Pila<string>& pila,int contClientes, int contProductos, int contPedidos) {
    cout << "\n||========================================||" << endl;
    cout << "||      GUARDANDO DATOS EN ARCHIVOS       ||" << endl;
    cout << "||========================================||" << endl;
    
    bool exito = true;
    
    cout << "\n[1/5] Guardando clientes..." << endl;
    if (guardarClientes(arbol)) {
        cout << "  + " << arbol.getTam() << " clientes guardados" << endl;
    } else {
        cout << "  X Error al guardar clientes" << endl;
        exito = false;
    }
    
    cout << "\n[2/5] Guardando productos..." << endl;
    if (guardarProductos(lista)) {
        cout << "  + " << lista.getTam() << " productos guardados" << endl;
    } else {
        cout << "  X Error al guardar productos" << endl;
        exito = false;
    }
    
    cout << "\n[3/5] Guardando pedidos..." << endl;
    if (guardarPedidos(cola)) {
        cout << "  + " << cola.getTam() << " pedidos guardados" << endl;
    } else {
        cout << "  X Error al guardar pedidos" << endl;
        exito = false;
    }
    
    cout << "\n[4/5] Guardando historial..." << endl;
    if (guardarHistorial(pila)) {
        cout << "  + " << pila.getTam() << " operaciones guardadas" << endl;
    } else {
        cout << " x Error al guardar historial" << endl;
        exito = false;
    }
    
    cout << "\n[5/5] Guardando contadores..." << endl;
    if (guardarContadores(contClientes, contProductos, contPedidos)) {
        cout << "  ✓ Contadores guardados" << endl;
    } else {
        cout << "  ❌ Error al guardar contadores" << endl;
        exito = false;
    }
    
    if (exito) {
        cout << "\n=========================================" << endl;
        cout << "✓ Todos los datos guardados exitosamente" << endl;
        cout << "  Ubicación: carpeta 'data/'" << endl;
        cout << "=========================================" << endl;
    }
    
    return exito;
}

// ========================================
// CARGAR TODO
// ========================================
bool GestorArchivos::cargarTodo(arbolBinario<Cliente>& arbol,
                                ListaEnlazada<Producto>& lista,
                                colaPrioridad<Pedido>& cola,
                                Pila<string>& pila,
                                int& contClientes, int& contProductos, int& contPedidos) {
    if (!existenDatosGuardados()) {
        return false;
    }
    
    cout << "\n||========================================||" << endl;
    cout << "||         CARGANDO DATOS GUARDADOS       ||" << endl;
    cout << "||========================================||" << endl;
    
    cout << "\n[1/5] Cargando clientes..." << endl;
    cargarClientes(arbol);
    
    cout << "\n[2/5] Cargando productos..." << endl;
    cargarProductos(lista);
    
    cout << "\n[3/5] Cargando pedidos..." << endl;
    cargarPedidos(cola);
    
    cout << "\n[4/5] Cargando historial..." << endl;
    cargarHistorial(pila);
    
    cout << "\n[5/5] Cargando contadores..." << endl;
    cargarContadores(contClientes, contProductos, contPedidos);
    
    cout << "\n========================================" << endl;
    cout << "++ Datos cargados exitosamente" << endl;
    cout << "==========================================" << endl;
    
    return true;
}

bool GestorArchivos::existenDatosGuardados() {
    struct stat buffer;
    return (stat(rutaClientes.c_str(), &buffer) == 0 ||
            stat(rutaProductos.c_str(), &buffer) == 0);
}

bool GestorArchivos::limpiarArchivos() {
    remove(rutaClientes.c_str());
    remove(rutaProductos.c_str());
    remove(rutaPedidos.c_str());
    remove(rutaHistorial.c_str());
    remove(rutaContadores.c_str());
    
    cout << "✓ Archivos de datos eliminados" << endl;
    return true;
}