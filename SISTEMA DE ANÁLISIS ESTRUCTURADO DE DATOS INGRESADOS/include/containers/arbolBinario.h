#ifndef ARBOL_H
#define ARBOL_H

#include "../struct/Nodo.h"
#include <iostream>
#include<stdexcept>
#include <vector>

using namespace std;

template <typename T>
class arbolBinario {
private:
    nodoArbol<T>* raiz;
    int tam;

    // ================= INSERTAR =================
    nodoArbol<T>* insertarRecursivo(nodoArbol<T>* nodo, const T& dato) {
        if (nodo == nullptr) {
            tam++;
            return new nodoArbol<T>(dato);
        }

        if (dato.id < nodo->dato.id) {
            nodo->izq = insertarRecursivo(nodo->izq, dato);
        } else if (dato.id > nodo->dato.id) {
            nodo->der = insertarRecursivo(nodo->der, dato);
        }

        return nodo;
    }

    // ================= BUSCAR =================
    nodoArbol<T>* buscarRecursivo(nodoArbol<T>* nodo, int id) const {
        if (nodo == nullptr) {
            return nullptr;
        }

        if (id == nodo->dato.id) {
            return nodo;
        } else if (id < nodo->dato.id) {
            return buscarRecursivo(nodo->izq, id);
        } else {
            return buscarRecursivo(nodo->der, id);
        }
    }

    // ================= MÍNIMO =================
    nodoArbol<T>* encontrarMinimo(nodoArbol<T>* nodo) {
        while (nodo && nodo->izq != nullptr) {
            nodo = nodo->izq;
        }
        return nodo;
    }

    // ================= ELIMINAR =================
    nodoArbol<T>* eliminarRecursivo(nodoArbol<T>* nodo, int id, bool& eliminado) {
        if (nodo == nullptr) {
            eliminado = false;
            return nullptr;
        }

        if (id < nodo->dato.id) {
            nodo->izq = eliminarRecursivo(nodo->izq, id, eliminado);
        } 
        else if (id > nodo->dato.id) {
            nodo->der = eliminarRecursivo(nodo->der, id, eliminado);
        } 
        else {
            eliminado = true;

            // Caso 1: sin hijos
            if (nodo->izq == nullptr && nodo->der == nullptr) {
                delete nodo;
                tam--;
                return nullptr;
            }
            // Caso 2: un hijo
            else if (nodo->izq == nullptr) {
                nodoArbol<T>* temp = nodo->der;
                delete nodo;
                tam--;
                return temp;
            } 
            else if (nodo->der == nullptr) {
                nodoArbol<T>* temp = nodo->izq;
                delete nodo;
                tam--;
                return temp;
            }
            // Caso 3: dos hijos
            else {
                nodoArbol<T>* sucesor = encontrarMinimo(nodo->der);
                nodo->dato = sucesor->dato;
                nodo->der = eliminarRecursivo(nodo->der, sucesor->dato.id, eliminado);
            }
        }
        return nodo;
    }

    // ================= DESTRUIR =================
    void destruirRecursivo(nodoArbol<T>* nodo) {
        if (nodo != nullptr) {
            destruirRecursivo(nodo->izq);
            destruirRecursivo(nodo->der);
            delete nodo;
        }
    }

    // ================= RECORRIDOS =================
    void inOrdenRec(nodoArbol<T>* nodo) const{
        if (nodo != nullptr) {
            inOrdenRec(nodo->izq);
            nodo->dato.mostrar();
            inOrdenRec(nodo->der);
        }
    }

    void preOrdenRec(nodoArbol<T>* nodo) const{
        if (nodo != nullptr) {
            nodo->dato.mostrar();
            preOrdenRec(nodo->izq);
            preOrdenRec(nodo->der);
        }
    }

    void postOrdenRec(nodoArbol<T>* nodo) const{
        if (nodo != nullptr) {
            postOrdenRec(nodo->izq);
            postOrdenRec(nodo->der);
            nodo->dato.mostrar();
        }
    }

    void inordenActivosRecursivo(nodoArbol<T>* nodo) const {
        if (nodo != nullptr) {
            inordenActivosRecursivo(nodo->izq);

            if(nodo->dato.activo){
                nodo->dato.mostrar();
            }
            inordenActivosRecursivo(nodo->der);
        }
    }
    
    int contarActivosRecursivo(nodoArbol<T>* nodo) const {
        if (nodo == nullptr ) return 0;

        int count = nodo->dato.activo ? 1 : 0;
        count += contarActivosRecursivo(nodo->izq);
        count += contarActivosRecursivo(nodo->der);

        return count;
    }

    void obtenerElementosRecursivo(nodoArbol<T>* nodo, vector<T>& elementos) const{
        if(nodo != nullptr){
            obtenerElementosRecursivo(nodo->izq, elementos);
            elementos.push_back(nodo->dato);
            obtenerElementosRecursivo(nodo->der,elementos);
        }
    }

    // ================= IMPRIMIR ÁRBOL =================
    void imprimirArbolRec(nodoArbol<T>* nodo, std::string prefijo, bool esIzq) const {
        if (nodo != nullptr) {
            std::cout << prefijo
                    << (esIzq ? "|-- " : "`-- ");
            if (!nodo->dato.activo) {
                cout << " X ID: " << nodo->dato.id << " (" << nodo->dato.nombre << ") [INACTIVO]" << endl;
            } else {
                cout << " + ID: " << nodo->dato.id << " (" << nodo->dato.nombre << ")" << endl;
            }

            std::string nuevoPrefijo = prefijo + (esIzq ? "|   " : "    ");
            imprimirArbolRec(nodo->izq, nuevoPrefijo, true);
            imprimirArbolRec(nodo->der, nuevoPrefijo, false);
        }
    }

public:
    // ================= CONSTRUCTOR / DESTRUCTOR =================
    arbolBinario() : raiz(nullptr), tam(0) {}

    ~arbolBinario() {
        destruirRecursivo(raiz);
    }

    // ================= INTERFAZ PÚBLICA =================
    void insertar(const T& dato) {
        raiz = insertarRecursivo(raiz, dato);
    }

    T* buscar(int id) {
        nodoArbol<T>* nodo = buscarRecursivo(raiz, id);
        return (nodo != nullptr) ? &nodo->dato : nullptr;
    }

    bool eliminar(int id) {
        bool eliminado = false;
        raiz = eliminarRecursivo(raiz, id, eliminado);
        return eliminado;
    }

    bool estaVacio() const {
        return raiz == nullptr;
    }

    int getTam() const {
        return tam;
    }

    int contarActivos() const {
        return contarActivosRecursivo(raiz);
    }

    int contarInactivos() const {
        return tam - contarActivos();
    }

    void inordenActivos() const{
        if(estaVacio()){
            cout << "Arbol Vacio " << endl;
            return;
        }

        if(contarActivos() == 0){
            cout << "No hay clientes activos " << endl;
            return;
        }

        inordenActivosRecursivo(raiz);
    }

    void inOrden() {
        if (estaVacio()) {
            std::cout << "Arbol vacio\n";
            return;
        }
        inOrdenRec(raiz);
    }

    void preOrden() {
        if (estaVacio()) {
            std::cout << "Arbol vacio\n";
            return;
        }
        preOrdenRec(raiz);
    }

    void postOrden() {
        if (estaVacio()) {
            std::cout << "Arbol vacio\n";
            return;
        }
        postOrdenRec(raiz);
    }

        void inordenTodos() const {
        if (estaVacio()) {
            cout << "Arbol vacio" << endl;
            return;
        }
        inOrdenRec(raiz);
    }

    void obtenerElementos(vector<T>& elementos){
        elementos.clear();
        obtenerElementosRecursivo(raiz,elementos);
    }

    void imprimirArbol() const {
        if (estaVacio()) {
            std::cout << "Arbol vacio\n";
            return;
        }
        string estadoRaiz = raiz->dato.activo ? "" : "[INACTIVO]";
        cout << "Raiz -> ID: " << raiz->dato.id 
        << " (" << raiz->dato.nombre <<") "<<estadoRaiz << "\n";
        if(raiz->izq != nullptr){
        imprimirArbolRec(raiz->izq, "", true);
        }
        if (raiz->der != nullptr){
        imprimirArbolRec(raiz->der, "", false);
        }
    }
};

#endif
