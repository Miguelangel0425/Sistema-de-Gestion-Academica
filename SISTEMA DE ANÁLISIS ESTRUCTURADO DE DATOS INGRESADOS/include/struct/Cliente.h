#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>

using namespace std;

struct Cliente{
    int id;
    string nombre;
    string email;    
    string telefono;
    string direccion;
    bool activo;


    Cliente() : id(0),nombre(""),email(""),telefono(""),direccion(""),activo(true){};


    Cliente(int _id, string _nombre, string _email, string _telefono, string _direccion):
    id(_id),nombre(_nombre),email(_email),telefono(_telefono),direccion(_direccion),activo(true){};

    Cliente(int _id, string _nombre, string _email, string _telefono, string _direccion,bool _activo)://para cargar los archivos
    id(_id),nombre(_nombre),email(_email),telefono(_telefono),direccion(_direccion),activo(_activo){};
    
    bool operator>(const Cliente& otro) const {
        return id > otro.id;
    }

    bool operator<(const Cliente& otro) const {
        return id < otro.id;
    }

    bool operator==(const Cliente& otro) const{
        return id == otro.id;
    }

    void desactivar(){
        activo = false;
    }

    void reactivar(){
        activo = true;
    }

    bool estaActivo() const{
        return activo;

    }

    void mostrar() const {
        cout << "ID: " << id << "| Nombre: " << nombre
            << "| Email: " << email << "| Telf: " << telefono
            << "| Dir: " << direccion;

            if(!activo){
                cout << " | X INACTIVO";
            }

            cout << endl;
    }
};

#endif 