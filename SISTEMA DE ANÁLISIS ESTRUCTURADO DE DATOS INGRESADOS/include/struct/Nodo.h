#ifndef NODO_H
#define NODO_H

template <typename T>
// Nodo para lista doblemente enlazada

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



#endif NODO_H
