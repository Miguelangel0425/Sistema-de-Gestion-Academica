#include "../include/utils/Procesador.h"
#include "../include/utils/Visualizador.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Procesador::Procesador(arbolBinario<Cliente>* arbol, colaPrioridad<Pedido>* cola,
            Pila<string>* pila, ListaEnlazada<Producto>* lista)
            :arbolClientes(arbol),colaPedidos(cola),pilaHistorial(pila),listaProductos(lista),
            clientesCont(1000),pedidosCont(0),productosCont(0){}

Cliente Procesador::procesarCliente(const vector<string>& campos){
    int id = generarIdCliente();
    Cliente cliente( id,campos[0],campos[1],campos[2],campos[3]);

    cout << "\n||======================================||" << endl;
    cout << "||  TRANSFORMACIÓN DE DATOS - CLIENTE      ||" << endl;
    cout << "||========================================||" << endl;

    cout << "\n [PASO 1] Datos recibidos: " << endl;
    for(size_t i = 0; i < campos.size(); i++){
        cout << "Campo" << i+1 << ": " << campos[i] << endl; 
    }

    cout << "\n [PASO 2] Generando ID unico: " << endl;
    cout << "ID Generado: " << id << endl;

    cout << "\n [PASO 3] Creacion de la estructura Cliente: " << endl;
    cliente.mostrar();

    cout << "\n [PASO 4] Insertando en el Arbol Binario de Busqueda (BST)...." << endl;
    arbolClientes->insertar(cliente);
    cout << " + Cliente insertado correctamente (estado: Activo)" << endl;

    stringstream ss; //stringstream permite guardar un string complejo 
    ss << "Cliente Registrado - ID: " << id << " - " << cliente.nombre; 
    agregarHistorial(ss.str());//se agrega como ultima accion 

    return cliente;
}

Producto Procesador::procesarProducto(const vector<string>& campos){
    int id = generarIdProducto();
    double precio = stod(campos[1]);
    int cantidad = stoi(campos[2]);

    Producto producto(id, campos[0],precio,cantidad,campos[3]);

    cout << "\n||======================================||" << endl;
    cout << "||  TRANSFORMACION DE DATOS - PRODUCTO    ||" << endl;
    cout << "||========================================||" << endl;

    cout << "\n [PASO 1] Datos recibidos: " << endl;
    for(size_t i = 0; i < campos.size(); i++){
        cout << "Campo" << i+1 << ": " << campos[i] << endl; 
    }

    cout << "\n[PASO 2] Conversion de tipos de datos:" << endl;
    cout << "  Precio (string -> double): " << fixed << setprecision(2) << precio << endl;
    cout << "  Cantidad (string -> int): " << cantidad << endl;
    
    cout << "\n[PASO 3] Generacion de ID unico:" << endl;
    cout << "  ID asignado: " << id << endl;
    
    cout << "\n[PASO 4] Calculo de subtotal:" << endl;
    cout << "  Subtotal = Precio x Cantidad" << endl;
    cout << "  Subtotal = " << precio << " x " << cantidad << " = " << producto.calcularSubtotal() << endl;
    
    cout << "\n[PASO 5] Creacion de estructura Producto:" << endl;
    producto.mostrar();
    
    cout << "\n[PASO 6] Insertando en Lista Enlazada..." << endl;
    listaProductos->insertarFinal(producto);
    cout << " + Producto insertado correctamente." << endl;

    stringstream ss;
    ss << "PRODUCTO REGISTRADO - ID: " << id << " - " << producto.nombre;
    agregarHistorial(ss.str());
    
    return producto;
}

Pedido Procesador::procesarPedido(int idCliente, int prioridad,const vector<Producto>& productos){
    int id = generarIdPedido();
    string fecha  = obtenerFechaActual();
    Pedido pedido(id,idCliente,fecha,prioridad);

    cout << "\n||======================================||" << endl;
    cout << "||        Procesamiento de Pedido         ||" << endl;
    cout << "||========================================||" << endl;

    cout << "\n[PASO 1] Verificando existencia del cliente..." << endl;
    Cliente* cliente = arbolClientes->buscar(idCliente);
    if(cliente == nullptr){
        throw runtime_error("Cliente no encontrado en el sistema.");
    }
    cout << " + Cliente encontrado: " << cliente->nombre << endl;

    cout << "\n[PASO 2] Generando ID de pedido:" << endl;
    cout << "  ID asignado: " << id << endl;
    
    cout << "\n[PASO 3] Asignando fecha actual:" << endl;
    cout << "  Fecha: " << fecha << endl;
    
    cout << "\n[PASO 4] Configurando prioridad:" << endl;
    cout << "  Prioridad: " << pedido.getNombrePrioridad() << endl;

    cout << "\n[PASO 5] Agregando productos al pedido:" << endl;
    for (const auto& prod : productos) {
        pedido.agregarProducto(prod);
        cout << "  + " << prod.nombre << " (x" << prod.cantidad << ") - " 
            << fixed << setprecision(2) << prod.calcularSubtotal() << endl;
    }
    
    cout << "\n[PASO 6] Calculando total del pedido:" << endl;
    cout << "  TOTAL: " << fixed << setprecision(2) << pedido.total << endl;
    
    cout << "\n[PASO 7] Insertando en Cola de Prioridad..." << endl;
    colaPedidos->encolar(pedido, prioridad);
    cout << "  + Pedido encolado segun prioridad" << endl;
    
    stringstream ss;
    ss << "Pedido creado - ID: " << id << " - Cliente: " << cliente->nombre 
    << " - Total: " << fixed << setprecision(2) << pedido.total;
    agregarHistorial(ss.str());
    
    return pedido;
}

void Procesador::procesarSiguientePedido(){
    if(colaPedidos->estaVacio()){
        cout << "\n ! No hay pedidos pendientes en la cola." << endl;
        return;
    }

    cout << "\n||======================================||" << endl;
    cout << "||    Proocesando siguiente pedido        ||" << endl;
    cout << "||========================================||" << endl;

    Pedido pedido = colaPedidos->desencolar();

    
    cout << "\n[PASO 1] Extrayendo pedido de la cola..." << endl;
    cout << "  Pedido #" << pedido.id << " - Prioridad: " << pedido.getNombrePrioridad() << endl;
    
    cout << "\n[PASO 2] Verificando disponibilidad de inventario..." << endl;
    
    bool stockSuficiente = true;
    vector<int> indicesProductos;

    for(const auto& prodPedido : pedido.productos){
        bool encontrado = false;

        for(int i = 0; i < listaProductos->getTam(); i++){
            Producto& prodInventario = listaProductos->obtener(i);

            if(prodInventario.id == prodPedido.id){
                encontrado = true;

                cout << "  - " << prodPedido.nombre << ": ";
                cout << "Solicitado: " << prodPedido.cantidad 
                    << ", Disponible: " << prodInventario.cantidad;
                
                if (prodInventario.cantidad >= prodPedido.cantidad) {
                    cout << " OK" << endl;
                    indicesProductos.push_back(i);
                } else {
                    cout << " INSUFICIENTE" << endl;
                    stockSuficiente = false;
                }
                break;
            }
        }

        if (!encontrado) {
            cout << "  - " << prodPedido.nombre << ": No encontrado en el inventario" << endl;
            stockSuficiente = false;
        }
    }

    if (!stockSuficiente) {
        cout << "\nPedido Cancelado: Stock insuficiente" << endl;
        pedido.estado = "cancelado";
        
        stringstream ss;
        ss << "Pedido Cancelado - ID: " << pedido.id << " - Razon: Stock insuficiente";
        agregarHistorial(ss.str());
        
        pedido.mostrar();
        return;
    }

    cout << "\n[PASO 3] Actualizando inventario..." << endl;
    
    int idx = 0;
    for (const auto& prodPedido : pedido.productos) {
        Producto& prodInventario = listaProductos->obtener(indicesProductos[idx]);
        
        int stockAnterior = prodInventario.cantidad;
        prodInventario.cantidad -= prodPedido.cantidad;
        
        cout << "  - " << prodInventario.nombre << ": "
            << stockAnterior << " -> " << prodInventario.cantidad << " unidades";
        
        if (prodInventario.cantidad == 0) {
            cout << " Agotado" << endl;
        } else if (prodInventario.cantidad < 5) {
            cout << " Stock Bajo" << endl;
        } else {
            cout << " Ok" << endl;
        }
        
        idx++;
    }

    cout << "\n[PASO 4] Cambiando estado a 'procesando'..." << endl;
    pedido.estado = "procesando";
    cout << "  Estado: " << pedido.estado << endl;
    
    cout << "\n[PASO 5] Simulando procesamiento..." << endl;
    cout << "  - Generando factura..." << endl;
    cout << "  - Preparando envio..." << endl;
    cout << "  - Notificando al cliente..." << endl;
    
    cout << "\n[PASO 6] Finalizando pedido..." << endl;
    pedido.estado = "completado";
    cout << "  Estado final: " << pedido.estado << endl;
    
    cout << "\n+ Pedido procesado exitosamente" << endl;
    pedido.mostrar();
    
    stringstream ss;
    ss << "Pedido procesado - ID: " << pedido.id << " - Estado: " << pedido.estado;
    agregarHistorial(ss.str());
}

void Procesador::procesarTodosPedidos(){
    int totalProcesados = 0;

    cout << "\n||======================================||" << endl;
    cout << "||    Procesando Masivo de Pedidos        ||" << endl;
    cout << "||========================================||" << endl;

    while(!colaPedidos->estaVacio()){
        procesarSiguientePedido();
        totalProcesados++;
        cout << "\n-------------------------------------------\n" << endl;
    }

    cout << "\nTotal de pedidos procesados: " << totalProcesados << endl;
}

bool Procesador::clienteTienePedidos(int idCliente){
    return !colaPedidos->estaVacio();
}

bool Procesador::desactivarCliente(int idCliente){
    cout << "\n||========================================||" << endl;
    cout << "||    Desactivacion de Clientes           ||" << endl;
    cout << "||========================================||" << endl;

    cout << "\n[PASO 1] Buscando cliente en el sistema..." << endl;
    Cliente* cliente = arbolClientes->buscar(idCliente);
    if(cliente == nullptr){
        cout << "X Error: Cliente no encontrado en el sistema. " << endl;
        return false;
    }

    if(!cliente->activo){
        cout << "!  El cliente ya está INACTIVO" << endl;
        cout << "\nCliente:" << endl;
        cliente->mostrar();
        cout << "\n¿Desea REACTIVAR este cliente? (s/n): ";
        char respuesta;
        cin >> respuesta;
        if (respuesta == 's' || respuesta == 'S') {
            return reactivarCliente(idCliente);
        }
        return false;
    }

    cout << "+ Cliente encontrado: " << endl;
    cliente->mostrar();

    cout << "\n[PASO 2] Verificando pedidos asociados..." << endl;

    if(clienteTienePedidos(idCliente)){
        cout << "!  ADVERTENCIA: El cliente tiene pedidos pendientes" << endl;
        cout << "\nEl cliente sera desactivado pero sus pedidos pendientes" << endl;
        cout << "se procesaran normalmente. No podrá crear nuevos pedidos." << endl;
        cout << "\n¿Desea continuar? (s/n): ";
        char respuesta;
        cin >> respuesta;
        if (respuesta != 's' && respuesta != 'S') {
            cout << "\nX Operacion cancelada" << endl;
            return false;
        }
    } else {
        cout << "No hay pedidos asociados confirmados" << endl;
    }

    cout << "\n[PASO 3] Confirmacion de desactivacion..." << endl;
    cout << "\n!  El cliente pasara a estado INACTIVO" << endl;
    cout << "Esto significa que:" << endl;
    cout << "  * NO podra crear nuevos pedidos" << endl;
    cout << "  * Permanecerá en el sistema para historial" << endl;
    cout << "  * Sus pedidos actuales se procesaran normalmente" << endl;
    cout << "  * Puede ser reactivado en cualquier momento" << endl;
    cout << "\n¿Esta seguro de desactivar al cliente '" << cliente->nombre << "'? (s/n): ";
    
    char confirmacion;
    cin >> confirmacion;

    if (confirmacion != 's' && confirmacion != 'S') {
        cout << "\nX Operacion cancelada por el usuario" << endl;
        return false;
    }

    cout << "\n[PASO 4] Desactivando cliente..." << endl;

    string nombreCliente = cliente->nombre;
    cliente->desactivar();

    cout << " Cliente desactivado correctamente. " << endl;

    stringstream ss;
    ss << "Cliente desactivado - ID: " << idCliente << " - " << nombreCliente;
    agregarHistorial(ss.str());

    cout << "\n=========================================" << endl;
    cout << "Cliente '" << nombreCliente << "' ha sido DESACTIVADO" << endl;
    cout << "Estado actual:" << endl;
    cliente->mostrar();
    cout << "======================================" << endl;
    return true;
}

bool Procesador::reactivarCliente(int idCliente) {
    cout << "\n||========================================||" << endl;
    cout << "||    Reactivacion de Clientes            ||" << endl;
    cout << "||========================================||" << endl;
    
    Cliente* cliente = arbolClientes->buscar(idCliente);
    
    if (cliente == nullptr) {
        cout << " ERROR: Cliente no encontrado" << endl;
        return false;
    }
    
    if (cliente->activo) {
        cout << "!  El cliente ya esta ACTIVO" << endl;
        cliente->mostrar();
        return false;
    }
    
    cout << "\nCliente a reactivar:" << endl;
    cliente->mostrar();
    
    cout << "\n¿Confirmar reactivacion? (s/n): ";
    char conf;
    cin >> conf;
    
    if (conf == 's' || conf == 'S') {
        cliente->reactivar();
        
        cout << "\n+ Cliente reactivado exitosamente" << endl;
        cout << "\nEl cliente ahora puede:" << endl;
        cout << "  * Crear nuevos pedidos" << endl;
        cout << "  * Realizar todas las operaciones normalmente" << endl;
        
        cout << "\nEstado actual:" << endl;
        cliente->mostrar();
        
        stringstream ss;
        ss << "Cliente reactivado - ID: " << idCliente << " - " << cliente->nombre;
        agregarHistorial(ss.str());
        
        return true;
    }

    return false;
}

void Procesador::listaClientesInactivos(){
    cout << "\n||========================================||" << endl;
    cout << "||         Clientes Inactivos            ||" << endl;
    cout << "||========================================||" << endl;

    if(arbolClientes->estaVacio()){
        cout << "No hay Clientes registrados en el sistema. " << endl;
        return;
    }

    vector<Cliente> todosClientes;
    arbolClientes->obtenerElementos(todosClientes);

    int cantidadInactivos = 0;

    cout << "\nClientes en estado INACTIVO: " << endl;
    cout <<"-----------------------------------------------" << endl;

    for(const auto& cliente : todosClientes){
        if(!cliente.activo){
            cliente.mostrar();
            cantidadInactivos++;
        }
    }

    if(cantidadInactivos == 0){
        cout << "\n + No hay clientes inactivos." << endl;
    } else {
        cout << "\n----------------------------------------------" << endl;
        cout << "Total de clientes inactivos: " << cantidadInactivos << endl;
        cout << "Total de clientes activos: " << (todosClientes.size() - cantidadInactivos) << endl;
    }
}

void Procesador::verificarStockCritico(){
        cout << "\n||=====================================||" << endl;
    cout << "||    ALERTA DE STOCK BAJO/AGOTADO        ||" << endl;
    cout << "||========================================||" << endl;
    
    if (listaProductos->estaVacio()) {
        cout << "\n! No hay productos registrados en el sistema" << endl;
        return;
    }
    
    bool hayAlertas = false;
    int productosAgotados = 0;
    int productosStockBajo = 0;
    
    cout << "\nRevisando inventario..." << endl;
    cout << "--------------------------------------------" << endl;
    
    for (int i = 0; i < listaProductos->getTam(); i++) {
        const Producto& prod = listaProductos->obtener(i);
        
        if (prod.cantidad == 0) {
            cout << "\nX AGOTADO: " << prod.nombre << endl;
            cout << "   ID: " << prod.id << endl;
            cout << "   Accion: Reabastecer INMEDIATAMENTE" << endl;
            hayAlertas = true;
            productosAgotados++;
        }
        else if (prod.cantidad < 5) {
            cout << "\n!  STOCK BAJO: " << prod.nombre << endl;
            cout << "   ID: " << prod.id << endl;
            cout << "   Unidades restantes: " << prod.cantidad << endl;
            cout << "   Accion: Realizar pedido de reabastecimiento" << endl;
            hayAlertas = true;
            productosStockBajo++;
        }
    }
    
    if (!hayAlertas) {
        cout << "\n+ Todos los productos tienen stock adecuado" << endl;
        cout << "   Total de productos: " << listaProductos->getTam() << endl;
    } else {
        cout << "\n--------------------------------------------" << endl;
        cout << "RESUMEN DE ALERTAS:" << endl;
        cout << "  Productos agotados: " << productosAgotados << endl;
        cout << "  Productos con stock bajo: " << productosStockBajo << endl;
        cout << "  Total productos en riesgo: " << (productosAgotados + productosStockBajo) << endl;
    }
}

int Procesador::generarIdCliente(){
    return clientesCont++;
}

int Procesador::generarIdPedido(){
    return pedidosCont++;
}

int Procesador::generarIdProducto(){
    return productosCont++;
}

string Procesador::obtenerFechaActual(){
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
    << setw(2) << (ltm->tm_mon + 1) << "/" <<(1900+ltm->tm_year);
    
    return ss.str();
}

void Procesador::agregarHistorial(const string& operacion){
    string timestamp = obtenerFechaActual();
    string entrada = "[" + timestamp + "] " + operacion;
    pilaHistorial->apilar(entrada);
}

void Procesador::calcularEstadisticas(){
        cout << "\n||=====================================||" << endl;
    cout << "||      Estadisticas del Sistema          ||" << endl;
    cout << "||========================================||" << endl;

    cout << "\nClientes registrados: " << arbolClientes->getTam() << endl;
    cout << "  |- Activos: " << arbolClientes->contarActivos() << " +" << endl;
    cout << "  |- Inactivos: " << arbolClientes->contarInactivos() << " X " << endl;
    cout << "\nProductos en catálogo: " << listaProductos->getTam() << endl;
    cout << "Pedidos pendientes: " << colaPedidos->getTam() << endl;
    cout << "Operaciones en historial: " << pilaHistorial->getTam() << endl;
}