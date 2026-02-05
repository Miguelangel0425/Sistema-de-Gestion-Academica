#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <stdexcept>
#include "../struct/Nodo.h"

using namespace std;

template<typename T>
class Pila{
    private:
    nodoPila<T>* top;
    int tam;
    public:

    Pila():top(nullptr),tam(0){}

    ~Pila(){
        limpiar();
    }

    void apilar(const T& dato){
        nodoPila<T>* nuevo = new nodoPila<T>(dato);
        nuevo->sig = top;
        top = nuevo;
        tam++;
    }

    T desapilar(){
        if(estavacio()){
            throw runtime_error("La pila esta vacia");
        }

        nodoPila<T>* temp = top;
        T dato = top->dato;
        top = top->sig;
        delete top;
        tam--;

        return dato;
    }

    T& verTope(){
        if(estaVacio()){
            throw runtime_error("La pila esta vacia");
        }
        return top->dato;
    }

    bool estaVacio() const{
        return top == nullptr;
    }

    int getTam() const {
        return tam;
    }

    void limpiar(){
        while(!estaVacio()){
            desapilar();
        }
    }

    void mostrarHistorial() const{
        if(estaVacio()){
            cout << "Historial vacio" << endl;
            return;
        }

        cout << "\n||=======================================||" << endl;
        cout << "||          HISTORIAL DE OPCIONES     ||" << endl;
        cout << "||========================================||" << endl;

        nodoPila<T>* actual = top;
        int index = 1;
        while(actual != nullptr){
            cout <<"\n[" << index <<"] ";
            cout << actual->dato << endl;
            actual = actual->sig;
            index++;
        }
    }
};

#endif 