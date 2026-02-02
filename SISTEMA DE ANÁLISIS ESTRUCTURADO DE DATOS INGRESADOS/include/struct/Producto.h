#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

struct Producto{
    int id;
    string nombre;
    double precio;
    int cantidad;
    string categoria;

    Producto(): id(0), nombre(""),precio(0.0),cantidad(0),categoria(""){}

    Producto(int _id, string _nombre, double _precio,int _cantidad,string _categoria){
        id = _id;
        nombre = _nombre;
        precio = _precio;
        cantidad = _cantidad;
        categoria = _categoria;
    }

    double calcularSubtotal() const{
        return precio * cantidad;
    }

    bool hayStocke() const{
        return cantidad > 0;
    }

    void mostrar() const{
        cout << fixed << setprecision(2);
        cout << "ID: " << id << "| Producto: " << nombre
            << "| Precio: " << precio << "| Cant: " << cantidad
            << "| Categoria: " << categoria
            << "| Subtotal: " << calcularSubtotal() << endl;
    }
};
#endif