#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <stdexcept>
#include "../struct/Nodo.h"

using namespace std;

template<typename T>

class colaPrioridad{
    private:
    nodoCola<T>* frente;
    nodoCola<T>* final;
    int tam;
    public:

    colaPrioridad():frente(nullptr),final(nullptr),tam(0){}

    ~colaPrioridad(){
        limpiar();
    }
    // Encolar con prioridad (menor número = mayor prioridad)
    void encolar(const T& dato, int prioridad){
        nodoCola<T>* nuevo = new nodoCola<T>(dato,prioridad);
        //si esta vacia o la nueva es la prioridad
        if(frente == nullptr || prioridad < frente->prioridad){
            nuevo->sig = frente;
            frente = nuevo;
            if(final == nullptr){
                final = nuevo;
            }
        } else { //buscar la pos correcta segun la prioridad
            nodoCola<T>* actual = frente;
            while(actual->sig != nullptr && actual->sig->prioridad <= prioridad){
                actual = actual->sig;
            }

            nuevo->sig = actual->sig;
            actual->sig = nuevo;

            if(nuevo->sig == nullptr){
                final = nuevo;
            }
        }
        tam ++;
    }

    T desencolar(){
        if(estaVacio()){
            throw runtime_error("La cola esta vacia");
        }

        nodoCola<T>* temp = top;
        T dato = frente->dato;
        frente = frente->sig;
        if(frente==nullptr){
            final = nullptr;
        }

        delete temp;
        tam--;
        return dato;
    }

    T& verFrente(){
        if(estaVacio()){
            throw runtime_error("La cola esta vacia");
        }
        return frente->dato;
    }

    bool estaVacio(){
        return frente == nullptr;
    }

    int getTam(){
        return tam;
    }

    void limpiar(){
        while(!estaVacio()){
            desencolar();
        }
    }

    void mostrar() const{
        if(estaVacio()){
            cout << "Cola vacia" << endl;
            return;
        }

        nodoCola<T>* actual = frente;
        int index = 1;
        while (actual != nullptr){
            cout << "[" << index << "] Prioridad: " << actual->prioridad << " -> ";
            actual->dato.mostrar();
            actual = actual->sig;
            index++;
        }
        
    }
};

#endif