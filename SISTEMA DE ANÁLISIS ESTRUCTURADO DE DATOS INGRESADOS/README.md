DOCUMENTACIÓN COMPLETA DEL PROYECTO

📋 ¿QUÉ ES EL PROYECTO?
Nombre del Sistema
Sistema de Análisis Estructurado de Datos - Gestión de Pedidos E-commerce
Descripción General
Es un sistema de gestión de pedidos que simula un entorno de e-commerce, donde se:

Registran clientes que realizan compras
Catalogan productos disponibles para la venta
Crean pedidos con diferentes niveles de prioridad
Procesan pedidos según su urgencia
Mantienen historial de todas las operaciones realizadas

Propósito Académico
Demostrar el uso práctico de 4 estructuras de datos fundamentales:

Árbol Binario de Búsqueda (BST) - Para clientes
Cola de Prioridad - Para pedidos
Lista Enlazada - Para productos
Pila - Para historial de operaciones


🎯 OBJETIVOS DEL PROYECTO
Objetivos Principales

✅ Validar datos estructurados antes de procesarlos
✅ Transformar datos de entrada a estructuras internas
✅ Procesar datos paso a paso con lógica clara
✅ Visualizar estructuras de datos de forma comprensible
✅ Manejar múltiples entradas en una sola ejecución
✅ Detectar errores y mostrar mensajes claros
✅ Organizar código de forma modular

Objetivos Técnicos

Implementar estructuras de datos desde cero (sin STL completo)
Aplicar patrones de diseño y buenas prácticas
Demostrar complejidad algorítmica O(log n), O(1), O(n)
Validación robusta con manejo de excepciones


🏗️ ESTRUCTURA COMPLETA DE CARPETAS
ProyectoEstructuraDatos/
│
├── 📁 src/                           # Código fuente (.cpp)
│   ├── main.cpp                      # Punto de entrada del programa
│   ├── Menu.cpp                      # Implementación del sistema de menús
│   ├── Validador.cpp                 # Lógica de validación de datos
│   ├── Procesador.cpp                # Procesamiento paso a paso
│   └── Visualizador.cpp              # Visualización de estructuras
│
├── 📁 include/                       # Archivos de encabezado (.h)
│   │
│   ├── 📁 estructuras/               # Estructuras de datos básicas
│   │   ├── Cliente.h                 # Definición de Cliente
│   │   ├── Producto.h                # Definición de Producto
│   │   ├── Pedido.h                  # Definición de Pedido
│   │   └── Nodo.h                    # Nodos para todas las estructuras
│   │
│   ├── 📁 contenedores/              # Implementación de EDAs
│   │   ├── Cola.h                    # Cola de prioridad (template)
│   │   ├── Pila.h                    # Pila (template)
│   │   ├── ListaEnlazada.h          # Lista enlazada simple (template)
│   │   └── ArbolBinario.h           # Árbol binario de búsqueda (template)
│   │
│   └── 📁 utilidades/                # Clases auxiliares
│       ├── Menu.h                    # Interfaz de usuario
│       ├── Validador.h               # Validación de entradas
│       ├── Procesador.h              # Lógica de negocio
│       └── Visualizador.h            # Presentación de datos
│
├── 📁 obj/                           # Archivos objeto compilados (.o)
│   └── (generado automáticamente)
│
├── 📁 bin/                           # Ejecutable final
│   └── sistema_pedidos               # Programa compilado
│
├── 📁 docs/                          # Documentación del proyecto
│   ├── Manual_Usuario.md             # Guía para el usuario
│   ├── Manual_Tecnico.md             # Documentación técnica
│   ├── Diagramas.pdf                 # Diagramas UML/flujo
│   └── Presentacion.pptx             # Diapositivas para exposición
│
├── 📁 data/                          # Datos de prueba (opcional)
│   ├── clientes_ejemplo.txt
│   ├── productos_ejemplo.txt
│   └── resultados.txt
│
├── 📁 tests/                         # Casos de prueba (opcional)
│   ├── test_validacion.cpp
│   ├── test_estructuras.cpp
│   └── test_procesamiento.cpp
│
├── Makefile                          # Automatización de compilación
├── README.md                         # Descripción general del proyecto
└── .gitignore                        # Archivos a ignorar en Git
