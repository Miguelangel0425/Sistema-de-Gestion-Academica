#include "../include/utils/Menu.h"
#include <limits>

Menu::Menu(){
    arbolClientes = new arbolBinario<Cliente>();
    colaPedidos = new colaPrioridad<Pedido>();
    pilaHistorial = new Pila<string>();
    listaProductos = new ListaEnlazada<Producto>();
    procesador = new Procesador(arbolClientes, colaPedidos, pilaHistorial, listaProductos);
    gestorArchivos = new GestorArchivos();
}

Menu::~Menu() {

    delete arbolClientes;
    delete colaPedidos;
    delete pilaHistorial;
    delete listaProductos;
    delete procesador;
    delete gestorArchivos;
}

void Menu::mostrarMenuPrincipal() {
    cout << "\n||=====================================================||" << endl;
    cout << "||   SISTEMA DE ANALISIS ESTRUCTURADO DE DATOS        ||" << endl;
    cout << "||         Sistema de Gestion de Pedidos              ||" << endl;
    cout << "||====================================================||" << endl;
    cout << "\n------------------------------------------------------" << endl;
    cout << "|  GESTION DE DATOS                                  |" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "  1. Ingresar nuevo cliente" << endl;
    cout << "  2. Ingresar nuevo producto" << endl;
    cout << "  3. Crear nuevo pedido" << endl;
    cout << "  4. Gestionar clientes (desactivar/reactivar)" << endl;
    cout << "\n------------------------------------------------------" << endl;
    cout << "|  PROCESAMIENTO                                     |" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "  5. Procesar siguiente pedido (por prioridad)" << endl;
    cout << "  6. Procesar todos los pedidos" << endl;
    cout << "\n------------------------------------------------------" << endl;
    cout << "|  CONSULTAS                                         |" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "  7. Buscar cliente por ID" << endl;
    cout << "  8. Ver estado de pedidos" << endl;
    cout << "  9. Ver historial de operaciones" << endl;
    cout << " 10. Verificar alertas de stock" << endl;
    cout << "\n------------------------------------------------------" << endl;
    cout << "|  VISUALIZACION Y REPORTES                          |" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << " 11. Visualizar estructuras de datos" << endl;
    cout << " 12. Generar reporte estadistico" << endl;
    cout << "\n  0. Salir del sistema" << endl;
    cout << "\n------------------------------------------------------" << endl;
    cout << "Opcion: ";
}

void Menu::ejecutar() {
    cargarDatos();
    int opcion;
    
    do {
        limpiarPantalla();
        mostrarMenuPrincipal();
        opcion = leerOpcion();
        
        try {
            switch (opcion) {
                case 1:
                    ingresarCliente();
                    guardarDatos();
                    break;
                case 2:
                    ingresarProducto();
                    guardarDatos();
                    break;
                case 3:
                    ingresarPedido();
                    guardarDatos();
                    break;
                case 4:
                    gestionarCliente();
                    guardarDatos();
                    break;
                case 5:
                    procesarPedidos();
                    guardarDatos();
                    break;
                case 6:
                    procesador->procesarTodosPedidos();
                    guardarDatos();
                    break;
                case 7:
                    buscarCliente();
                    break;
                case 8:
                    verEstadosPedidos();
                    break;
                case 9:
                    verHistorial();
                    break;
                case 10:
                    verificarStock();
                    break;
                case 11:
                    visualizarEstructuras();
                    break;
                case 12:
                    generarReporte();
                    break;
                case 0:
                    cout << "\n¡Gracias por usar el sistema!" << endl;
                    break;
                default:
                    Visualizador::mostrarError("Opcion invalida");
            }
            
            if (opcion != 0) {
                pausar();
            }
        } catch (const exception& e) {
            Visualizador::mostrarError(e.what());
            pausar();
        }
        
    } while (opcion != 0);
}

void Menu::ingresarCliente() {
    Visualizador::mostrarEncabezado("INGRESO DE NUEVO CLIENTE");
    
    cout << "\nFormato: Nombre,Email,Telefono,Direccion" << endl;
    cout << "Ejemplo: Juan Perez,juan@mail.com,0999123456,Av. Principal 123" << endl;
    cout << "\nIngrese los datos del cliente: ";
    
    string entrada;
    // Limpiar el buffer solo si hay algo pendiente
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, entrada);
    
    vector<string> campos;
    if (Validador::validarCliente(entrada, campos)) {
        Cliente cliente = procesador->procesarCliente(campos);
        Visualizador::mostrarExito("Cliente registrado exitosamente");
        
        cout << "\n¿Desea ingresar otro cliente? (s/n): ";
        char respuesta;
        cin >> respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (respuesta == 's' || respuesta == 'S') {
            ingresarCliente();
        }
    }
}

void Menu::ingresarProducto() {
    Visualizador::mostrarEncabezado("INGRESO DE NUEVO PRODUCTO");
    
    cout << "\nFormato: Nombre,Precio,Cantidad,Categoria" << endl;
    cout << "Ejemplo: Laptop HP,899.99,10,Electronica" << endl;
    cout << "\nIngrese los datos del producto: ";
    
    string entrada;
    // Limpiar el buffer solo si hay algo pendiente
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, entrada);
    
    vector<string> campos;
    if (Validador::validarProducto(entrada, campos)) {
        Producto producto = procesador->procesarProducto(campos);
        Visualizador::mostrarExito("Producto registrado exitosamente");
        
        cout << "\n¿Desea ingresar otro producto? (s/n): ";
        char respuesta;
        cin >> respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (respuesta == 's' || respuesta == 'S') {
            ingresarProducto();
        }
    }
}

void Menu::ingresarPedido() {
    Visualizador::mostrarEncabezado("CREACION DE NUEVO PEDIDO");
    
    if (arbolClientes->estaVacio()) {
        Visualizador::mostrarError("No hay clientes registrados. Registre un cliente primero.");
        return;
    }
    
    if (listaProductos->estaVacio()) {
        Visualizador::mostrarError("No hay productos registrados. Registre productos primero.");
        return;
    }
    
    cout << "\nIngrese el ID del cliente: ";
    int idCliente;
    cin >> idCliente;
    
    Cliente* cliente = arbolClientes->buscar(idCliente);
    if (cliente == nullptr) {
        Visualizador::mostrarError("Cliente no encontrado");
        return;
    }
    
    if (!cliente->activo) {
        Visualizador::mostrarError("El cliente esta INACTIVO");
        cout << "\nEste cliente no puede realizar nuevos pedidos." << endl;
        cout << "Para permitirle crear pedidos, debe reactivar su cuenta." << endl;
        cout << "\n¿Desea reactivar al cliente ahora? (s/n): ";
        char respuesta;
        cin >> respuesta;
        if (respuesta == 's' || respuesta == 'S') {
            if (procesador->reactivarCliente(idCliente)) {
                cout << "\nCliente reactivado. Ahora puede continuar con el pedido." << endl;
                pausar();
            } else {
                return;
            }
        } else {
            return;
        }
    }
    
    cout << "Cliente encontrado: " << cliente->nombre << " ✓ ACTIVO" << endl;
    
    cout << "\nPrioridad del pedido:" << endl;
    cout << "  1 - Urgente" << endl;
    cout << "  2 - Normal" << endl;
    cout << "  3 - Baja" << endl;
    cout << "Seleccione (1-3): ";
    int prioridad;
    cin >> prioridad;
    
    if (prioridad < 1 || prioridad > 3) {
        Visualizador::mostrarError("Prioridad invalida");
        return;
    }
    
    vector<Producto> productosSeleccionados;
    char agregarMas;
    
    do {
        cout << "\n--- PRODUCTOS DISPONIBLES ---" << endl;
        listaProductos->mostrar();
        
        cout << "\nIngrese el ID del producto: ";
        int idProducto;
        cin >> idProducto;
        
        bool encontrado = false;
        for (int i = 0; i < listaProductos->getTam(); i++) {
            Producto prod = listaProductos->obtener(i);
            if (prod.id == idProducto) {
                encontrado = true;
                
                if (prod.cantidad == 0) {
                    Visualizador::mostrarError("Producto agotado");
                    break;
                }
                
                cout << "Producto: " << prod.nombre << endl;
                cout << "Disponibles: " << prod.cantidad << " unidades" << endl;
                cout << "Precio: " << prod.precio << endl;
                cout << "Cantidad a pedir: ";
                int cantidad;
                cin >> cantidad;
                
                if (cantidad <= 0 || cantidad > prod.cantidad) {
                    Visualizador::mostrarError("Cantidad invalida");
                    break;
                }
                
                Producto prodPedido = prod;
                prodPedido.cantidad = cantidad;
                productosSeleccionados.push_back(prodPedido);
                
                cout << "+ Producto agregado al pedido" << endl;
                break;
            }
        }
        
        if (!encontrado) {
            Visualizador::mostrarError("Producto no encontrado");
        }
        
        cout << "\n¿Agregar otro producto? (s/n): ";
        cin >> agregarMas;
        
    } while (agregarMas == 's' || agregarMas == 'S');
    
    if (productosSeleccionados.empty()) {
        Visualizador::mostrarError("No se agregaron productos al pedido");
        return;
    }
    
    Pedido pedido = procesador->procesarPedido(idCliente, prioridad, productosSeleccionados);
    Visualizador::mostrarExito("Pedido creado exitosamente");
    pedido.mostrar();
}

void Menu::procesarPedidos() {
    procesador->procesarSiguientePedido();
}

void Menu::buscarCliente() {
    Visualizador::mostrarEncabezado("BUSQUEDA DE CLIENTE");
    
    if (arbolClientes->estaVacio()) {
        Visualizador::mostrarAdvertencia("No hay clientes registrados");
        return;
    }
    
    cout << "\nIngrese el ID del cliente a buscar: ";
    int id;
    cin >> id;
    
    cout << "\n[PROCESO DE BUSQUEDA EN BST]" << endl;
    cout << "Buscando ID: " << id << endl;
    cout << "Estructura: Arbol Binario de Busqueda" << endl;
    cout << "Complejidad: O(log n) en promedio" << endl;
    cout << "----------------------------------------" << endl;
    
    Cliente* cliente = arbolClientes->buscar(id);
    
    if (cliente != nullptr) {
        Visualizador::mostrarExito("Cliente encontrado");
        cout << "\nDatos del cliente:" << endl;
        cout << "----------------------------------------" << endl;
        cliente->mostrar();
    } else {
        Visualizador::mostrarError("Cliente no encontrado en el sistema");
    }
}

void Menu::verEstadosPedidos() {
    Visualizador::mostrarEncabezado("ESTADO DE PEDIDOS");
    
    if (colaPedidos->estaVacio()) {
        cout << "\n! No hay pedidos pendientes" << endl;
        return;
    }
    
    cout << "\nPEDIDOS EN COLA (ordenados por prioridad):" << endl;
    cout << "----------------------------------------" << endl;
    colaPedidos->mostrar();
    
    cout << "\n----------------------------------------" << endl;
    cout << "Total de pedidos pendientes: " << colaPedidos->getTam() << endl;
}

void Menu::verHistorial() {
    pilaHistorial->mostrarHistorial();
}

void Menu::visualizarEstructuras() {
    int opcion;
    
    do {
        limpiarPantalla();
        Visualizador::menuVisualizacion();
        opcion = leerOpcion();
        
        try {
            switch (opcion) {
                case 1:
                    Visualizador::mostrarArbolClientes(*arbolClientes);
                    pausar();
                    break;
                case 2:
                    Visualizador::mostrarColaPedidos(*colaPedidos);
                    pausar();
                    break;
                case 3:
                    Visualizador::mostrarListaProductos(*listaProductos);
                    pausar();
                    break;
                case 4:
                    Visualizador::mostrarHistorial(*pilaHistorial);
                    pausar();
                    break;
                case 5:
                    Visualizador::mostrarTodasEstructuras(*arbolClientes, *colaPedidos, 
                                                         *pilaHistorial, *listaProductos);
                    pausar();
                    break;
                case 0:
                    break;
                default:
                    Visualizador::mostrarError("Opcion invalida");
                    pausar();
            }
        } catch (const exception& e) {
            Visualizador::mostrarError(e.what());
            pausar();
        }
        
    } while (opcion != 0);
}

void Menu::generarReporte() {
    procesador->calcularEstadisticas();
}

void Menu::gestionarCliente() {
    int opcion;
    
    do {
        limpiarPantalla();
        Visualizador::mostrarEncabezado("GESTION DE CLIENTES");
    
        cout << "\n1. Desactivar cliente" << endl;
        cout << "2. Reactivar cliente" << endl;
        cout << "3. Ver clientes ACTIVOS" << endl;
        cout << "4. Ver clientes INACTIVOS" << endl;
        cout << "5. Ver TODOS los clientes" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "\nOpcion: ";
        
        opcion = leerOpcion();
        
        try {
            switch (opcion) {
                case 1:
                    desactivarCliente();
                    pausar();
                    break;
                case 2:
                    reactivarCliente();
                    pausar();
                    break;
                case 3:
                    mostrarClientesActivos();
                    pausar();
                    break;
                case 4:
                    verClientesInactivo();
                    pausar();
                    break;
                case 5:
                    mostrarTodosClientes();
                    pausar();
                    break;
                case 0:
                    break;
                default:
                    Visualizador::mostrarError("Opción inválida");
                    pausar();
            }
        } catch (const exception& e) {
            Visualizador::mostrarError(e.what());
            pausar();
        }
        
    } while (opcion != 0);
}


void Menu::desactivarCliente() {
    Visualizador::mostrarEncabezado("DESACTIVACION DE CLIENTE");
    
    if (arbolClientes->estaVacio()) {
        Visualizador::mostrarAdvertencia("No hay clientes registrados");
        return;
    }
    
    cout << "\nClientes ACTIVOS:" << endl;
    cout << "----------------------------------------------" << endl;
    
    vector<Cliente> todosClientes;
    arbolClientes->obtenerElementos(todosClientes);
    
    bool hayActivos = false;
    for (const auto& cliente : todosClientes) {
        if (cliente.activo) {
            cliente.mostrar();
            hayActivos = true;
        }
    }
    
    if (!hayActivos) {
        cout << "\n! No hay clientes activos para desactivar" << endl;
        return;
    }
    
    cout << "\n\nIngrese el ID del cliente a desactivar: ";
    int id;
    cin >> id;
    
    procesador->desactivarCliente(id);
}

void Menu::reactivarCliente() {
    Visualizador::mostrarEncabezado("REACTIVACION DE CLIENTE");
    
    if (arbolClientes->estaVacio()) {
        Visualizador::mostrarAdvertencia("No hay clientes registrados");
        return;
    }
    
    cout << "\nClientes INACTIVOS:" << endl;
    cout << "--------------------------------------------" << endl;
    
    vector<Cliente> todosClientes;
    arbolClientes->obtenerElementos(todosClientes);
    
    bool hayInactivos = false;
    for (const auto& cliente : todosClientes) {
        if (!cliente.activo) {
            cliente.mostrar();
            hayInactivos = true;
        }
    }
    
    if (!hayInactivos) {
        cout << "\n! No hay clientes inactivos para reactivar" << endl;
        return;
    }
    
    cout << "\n\nIngrese el ID del cliente a reactivar: ";
    int id;
    cin >> id;
    
    procesador->reactivarCliente(id);
}

void Menu::verClientesInactivo() {
    procesador->listaClientesInactivos();
}

void Menu::mostrarClientesActivos() {
    Visualizador::mostrarEncabezado("CLIENTES ACTIVOS");
    
    if (arbolClientes->estaVacio()) {
        cout << "\n! No hay clientes registrados" << endl;
        return;
    }
    
    if (arbolClientes->contarActivos() == 0) {
        cout << "\n! No hay clientes activos" << endl;
        return;
    }
    
    cout << "\nClientes en estado ACTIVO:" << endl;
    cout << "-----------------------------------------------" << endl;
    arbolClientes->inordenActivos();
    
    cout << "\n---------------------------------------------" << endl;
    cout << "Total: " << arbolClientes->contarActivos() << " clientes activos" << endl;
}

void Menu::mostrarTodosClientes() {
    Visualizador::mostrarEncabezado("TODOS LOS CLIENTES");
    
    if (arbolClientes->estaVacio()) {
        cout << "\n! No hay clientes registrados" << endl;
        return;
    }
    
    cout << "\nTODOS los clientes (activos e inactivos):" << endl;
    cout << "------------------------------------------------" << endl;
    arbolClientes->inordenTodos();
    
    cout << "\n-----------------------------------------------" << endl;
    cout << "Total: " << arbolClientes->getTam() << " clientes" << endl;
    cout << "  |- Activos: " << arbolClientes->contarActivos() << " +" << endl;
    cout << "  |-- Inactivos: " << arbolClientes->contarInactivos() << " X" << endl;
}

void Menu::pausar() {
    cout << "\n\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Menu::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int Menu::leerOpcion() {
    int opcion;
    while (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Intente nuevamente: ";
    }
    return opcion;
}

string Menu::leerLinea(const string& mensaje) {
    cout << mensaje;
    cin.ignore();
    string linea;
    getline(cin, linea);
    return linea;
}


void Menu::guardarDatos() {
    gestorArchivos->guardarTodo(*arbolClientes, *listaProductos, *colaPedidos, *pilaHistorial,
    procesador->getContadorClientes(),procesador->getContadorProductos(),procesador->getContadorPedidos());
}


void Menu::cargarDatos() {
    if (!gestorArchivos->existenDatosGuardados()) {
        Visualizador::mostrarAdvertencia("No hay datos guardados para cargar");
        return;
    }
    
    cout << "\n!  ADVERTENCIA: Esto sobrescribira los datos actuales en memoria" << endl;
    cout << "¿Esta seguro de que desea cargar los datos guardados? (s/n): ";
    char opcion;
    cin >> opcion;
    
    if (opcion == 's' || opcion == 'S') {
        // Limpiar datos actuales
        delete arbolClientes;
        delete colaPedidos;
        delete pilaHistorial;
        delete listaProductos;
        delete procesador; // IMPORTANTE: también eliminar el procesador
        
        // Recrear estructuras vacías
        arbolClientes = new arbolBinario<Cliente>();
        colaPedidos = new colaPrioridad<Pedido>();
        pilaHistorial = new Pila<string>();
        listaProductos = new ListaEnlazada<Producto>();
        
        // CORRECCIÓN: Recrear el procesador con las nuevas estructuras
        procesador = new Procesador(arbolClientes, colaPedidos, pilaHistorial, listaProductos);
        
        // Cargar datos
        int contClientes, contProductos, contPedidos;
        if (gestorArchivos->cargarTodo(*arbolClientes, *listaProductos, *colaPedidos, *pilaHistorial,
        contClientes, contProductos, contPedidos)) {
            procesador->setContadorClientes(contClientes);
            procesador->setContadorProductos(contProductos);
            procesador->setContadorPedidos(contPedidos);
            
            Visualizador::mostrarExito("Datos cargados exitosamente");
        }
    }
}

void Menu::verificarStock() {
    procesador->verificarStockCritico();
}