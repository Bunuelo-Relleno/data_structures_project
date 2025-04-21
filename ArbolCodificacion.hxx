#ifndef _ARBOLCODIFICACION_HXX_
#define _ARBOLCODIFICACION_HXX_

#include "ArbolCodificacion.h"
#include <map>
#include <queue>

template <class T>
ArbolCodificacion<T>::ArbolCodificacion() {
    this->raiz = NULL;
}

template <class T>
ArbolCodificacion<T>::~ArbolCodificacion() {
    if (this->raiz != NULL) {
        delete this->raiz;
    }
}

template <class T>
bool ArbolCodificacion<T>::esVacio() {
    return this->raiz == NULL;
}

template <class T>
T ArbolCodificacion<T>::datoRaiz() {
    if (this->raiz != NULL) {
        return this->raiz->obtenerSimbolo();
    } else {
        throw std::runtime_error("El árbol está vacío.");
    }
}

template <class T>
void ArbolCodificacion<T>::fijarRaiz(NodoCodificacion<T>* raiz) {
    this->raiz = raiz;
}

template <class T>
struct CompararNodos {
    bool operator()(NodoCodificacion<T>* a, NodoCodificacion<T>* b) {
        return a->obtenerFrecuencia() > b->obtenerFrecuencia();
    }
};

template <class T>
void ArbolCodificacion<T>::construirArbolCodificacion(std::map<T, unsigned long> frecuencias) {
    // Crear una cola de prioridad (min-heap) para almacenar los nodos hoja
    std::priority_queue<NodoCodificacion<T>*, std::vector<NodoCodificacion<T>*>, CompararNodos<T>> colaPrioridad;

    // Se llena el heap con los nodos hoja
    for (const auto& it : frecuencias) {
        NodoCodificacion<T>* nodo = new NodoCodificacion<T>();
        nodo->fijarSimbolo(it.first);
        nodo->fijarFrecuencia(it.second);
        colaPrioridad.push(nodo);
    }

    // Se construye el árbol combinando los nodos
    while (colaPrioridad.size() > 1){
        NodoCodificacion<T>* nodoIzq = colaPrioridad.top();
        colaPrioridad.pop();

        NodoCodificacion<T>* nodoDer = colaPrioridad.top();
        colaPrioridad.pop();

        NodoCodificacion<T>* nodoPadre = new NodoCodificacion<T>();
        nodoPadre->fijarFrecuencia(nodoIzq->obtenerFrecuencia() + nodoDer->obtenerFrecuencia());
        nodoPadre->fijarHijoIzq(nodoIzq);
        nodoPadre->fijarHijoDer(nodoDer);

        colaPrioridad.push(nodoPadre);
    }

    this->raiz = colaPrioridad.top();
    colaPrioridad.pop();
}

template<class T>
void ArbolCodificacion<T>::_imprimirArbol(){
    if (!this->esVacio()){
        (this->raiz)->inOrden();
    }
}

#endif //_ARBOLCODIFICACION_HXX_