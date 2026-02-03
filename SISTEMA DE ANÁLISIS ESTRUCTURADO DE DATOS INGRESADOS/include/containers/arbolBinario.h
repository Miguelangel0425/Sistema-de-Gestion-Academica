#ifndef ARBOL_H
#define ARBOL_H

#include "../struct/Nodo.h"

template <typename T>

class arbolBinario{
    private:
    nodoArbol<T> *raiz;
    int tam;

    public:

    void insertarNodo(nodoArbol<T> *arbol, const T& dato){
        if(arbol==Null){
            nodoArbol *nuevo_nodo=crearNodo(dato);
            arbol=nuevo_nodo;
        }else{
            raiz=arbol->dato;
            if(dato<raiz){
                insertar(arbol->izq,dato);
            }else{
                insertar(arbol->der,dato)
            }
        }
    }

    void mostrarArbol(nodoArbol<T> arbol, int contador){
        if(arbol==nullptr){
            return;
        }else{
            mostrarArbol(arbol->der,contador+1);
            for(int i=0; i < contador, i++){
                cout<<" ";
                cout<<arbol->dato<<endl;
                mostrarArbol(arbol->izq, contador+1);
            }
            
        }
    }

    bool busquedaArbol(nodoArbol<T> arbol, int n){
        if(arbol==nulptr){
            return false
        }else if(arbol->dato==n){
            return true;
        }else if(n < arbol->dato){
            busquedaArbol(arbol->izq,n);
        }else{
            return busquedaArbol(arbol->der,n);
        }
    }

    void preOrden(nodoArbol<T> arbol){
        if(arbol==nullptr){
            return;
        }else{
            cout<<arbol->dato<<"- ";
            preOrden(arbol->izq);
            preOrden(arbol->izq);
        }
    }

    void inOrden(nodoArbol<T> arbol){
        if(arbol==nullptr){
            return;
        }else{
            inOrden(arbol->izq);
            cout<<arbol->dato<<"- ";
            inOrden(arbol->izq);
        }
    }

    void postOrden(nodoArbol<T> arbol){
        if(arbol==nullptr){
            return;
        }else{
            postOrden(arbol->izq);
            postOrden(arbol->der);
            cout<<arbol->dato<<"- ";
        }
    }
};

#endif

#endif
