#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Producto.h"

using namespace std;

struct Pedido{
    int id;
    int idCliente;
    vector<Producto> productos;
    string fecha;
    int prioridad;
    string estado;
    double total;

    Pedido() : id(0), idCliente(0), fecha(""), prioridad(2), estado("pendiente"), total(0.0) {}
    
    Pedido(int _id, int _idCliente, string _fecha, int _prioridad)
        : id(_id), idCliente(_idCliente), fecha(_fecha), prioridad(_prioridad), 
        estado("pendiente"), total(0.0) {}

    void calcularTotal(){
        total = 0.0;
        for(const auto& prod : productos){
            total += prod.calcularSubtotal();
        }
    }
    void agregarProducto(const Producto& prod){
        productos.push_back(prod);
        calcularTotal();
    }

    string getNombrePrioridad() const {
        switch(prioridad){
            case 1: return "URGENTE";
            case 2: return "NORMAL";
            case 3: return "BAJA";
            default: return "DESCONOCIDA";
        }
    }

    void mostrar() const{
        cout <<"\n||=====================================||"<<endl;
        cout <<"||      PEDIDO #" << setw(4) << setfill('0') << id << "||" << endl;
        cout <<"||=====================================||" << endl;
        cout << setfill(' ');
        cout << "Cliente ID: " << idCliente << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Prioridad: " << getNombrePrioridad() << endl;
        cout << "Estado: " << estado << endl;
        cout << "\nProductos:" << endl;
        cout << "----------------------------------------" << endl;
        for(const auto& prod : productos){
            prod.mostrar();
        }
        cout << "----------------------------------------" << endl;
        cout << fixed << setprecision(2);
        cout << "TOTAL: " << total << endl;

    }

    // Operadores de comparación para la cola de prioridad
    bool operator<(const Pedido& otro) const {
        return prioridad < otro.prioridad;  // Menor numero = mayor prioridad
    }
    
    bool operator>(const Pedido& otro) const {
        return prioridad > otro.prioridad;
    }
};

#endif