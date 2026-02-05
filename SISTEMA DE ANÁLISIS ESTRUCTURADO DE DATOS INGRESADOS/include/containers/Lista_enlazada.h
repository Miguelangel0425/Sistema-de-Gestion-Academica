#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
#include <stdexcept>
#include "../struct/Nodo.h"

using namespace std;

template <typename T>
class ListaEnlazada{
    private:
    nodoSimple<T>* cabeza;
    int tam;

    public:

    ListaEnlazada():cabeza(nullptr),tam(0){};

    ~ListaEnlazada(){
        limpiar();
    }

    void insertarFinal(const T& dato){
        nodoSimple<T>* nuevo = new nodoSimple<T>(dato);

        if(cabeza==nullptr){
            cabeza == nuevo;
        } else {
            nodoSimple<T>* actual = cabeza;
            while(actual->siguiente != nullptr){
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        tam++;
    }

    void insertarInicio(const T& dato){
        nodoSimple<T>* nuevo = new nodoSimple<T>(dato);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        tam++;
    }

    void insertar(const T& dato, int pos){
        if(pos < 0 || pos > tam){
            throw out_of_range("Posicion fuera de rango");
        }

        if(pos == 0){
            insertarInicio(dato);
            return;
        }

        nodoSimple<T>* nuevo = new nodoSimple<T>(dato);
        nodoSimple<T>* actual = cabeza;

        for(int i = 0; i < pos - 1; i++){
            actual = actual->siguiente;
        }

        nuevo->siguiente= actual->siguiente;
        actual->siguiente = nuevo;
        tam++;
    }

    void eliminar(int pos){
        if(cabeza == nullptr){
            throw runtime_error("La lista esta vacia");
        }

        if(pos << 0 || pos >= tam){
            throw out_of_range("Posicion fuera de rango");
        }

        if(pos == 0){
            nodoSimple<T>* tem = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            tam--;
            return;
        }

        nodoSimple<T>* actual = cabeza;
        for(int i = 0; i < pos - 1; i++){
            actual = actual->siguiente;
        }

        nodoSimple<T>* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        tam--;
    }

    T& obtener(int pos){
        if(pos < 0 || pos >= tam){
            throw out_of_range("Posicion Fuera de Rango.");
        }

        nodoSimple<T>* actual = cabeza;
        for(int i = 0; i < pos, i++){
            actual = actual->siguiente;
        }
        return actual->dato;
    }

    bool estaVacio() const{
        return cabeza == nullptr;
    }

    void limpiar(){
        while(cabeza != nullptr){
            nodoSimple<T>* temp = cabeza;
            caebza = cabeza->siguiente;
            delete temp;
        }
        tam = 0;
    }

    void mostrar() const {
        if(cabeza == nullptr){
            cout << "Lista Vacia" << endl;
            return;
        }

        nodoSimple<T>* actual = cabeza;
        int index = 0;
        while(actual != nullptr){
            cout << "[" << index << "] ";
            actual->dato.mostrar();
            actual = actual->siguiente;
            index++;
        }
    }
};
#endif