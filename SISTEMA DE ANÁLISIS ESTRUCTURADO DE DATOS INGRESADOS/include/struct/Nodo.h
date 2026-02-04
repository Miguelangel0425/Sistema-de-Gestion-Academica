#ifndef NODO_H
#define NODO_H

template <typename T>
struct nodoArbol {
	T dato;
	nodoArbol<T> *izq;
	nodoArbol<T> *der;

    nodoArbol(T _dato) : dato(_dato),izq(nullptr),der(nullptr) {};
};

template <typename T>
struct nodoSimple{
    T dato;
    nodoSimple<T> *siguiente;

    nodoSimple(T _dato): dato(_dato), siguiente(nullptr){};
};

template <typename T>
struct nodoDoble{
	T dato;
	nodoDoble<T> *izq;
	nodoDoble<T> *der;

    nodoDoble(T _dato) : dato(_dato),izq(nullptr),der(nullptr) {};
};

template <typename T>

struct nodoPila{
    T dato;
    nodoPila<T>* sig;

    nodoPila(T _dato):dato(_dato),sig(nullptr){};
};

template <typename T>

struct nodoCola{
    T dato;
    int prioridad;
    nodoCola<T>* sig;

    nodoCola(T _dato, int _prioridad):dato(_dato),prioridad(_prioridad),sig(nullptr){};
};



#endif 
