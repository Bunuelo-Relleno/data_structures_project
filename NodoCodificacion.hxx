#ifndef _NODOCODIFICACION_HXX_
#define _NODOCODIFICACION_HXX_

#include "NodoCodificacion.h"
#include <cstddef>
#include <iostream>

template <class T>
NodoCodificacion<T>::NodoCodificacion() {
    this->simbolo = -1;
    this->frecuencia = 0;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}

template <class T>
NodoCodificacion<T>::~NodoCodificacion() {
    this->simbolo = -1;
    this->frecuencia = 0;
    if (this->hijoIzq != NULL) {
        delete this->hijoIzq;
    }
    if (this->hijoDer != NULL) {
        delete this->hijoDer;
    }
}

template <class T>
T NodoCodificacion<T>::obtenerSimbolo() {
    return this->simbolo;
}

template <class T>
void NodoCodificacion<T>::fijarSimbolo(T simbolo) {
    this->simbolo = simbolo;
}

template <class T>
unsigned long NodoCodificacion<T>::obtenerFrecuencia() {
    return this->frecuencia;
}

template <class T>
void NodoCodificacion<T>::fijarFrecuencia(unsigned long frecuencia) {
    this->frecuencia = frecuencia;
}

template <class T>
NodoCodificacion<T>* NodoCodificacion<T>::fijarHijoIzq(NodoCodificacion<T>* hijoIzq) {
    this->hijoIzq = hijoIzq;
    return this->hijoIzq;
}

template <class T>
NodoCodificacion<T>* NodoCodificacion<T>::fijarHijoDer(NodoCodificacion<T>* hijoDer) {
    this->hijoDer = hijoDer;
    return this->hijoDer;
}

template <class T>
NodoCodificacion<T>* NodoCodificacion<T>::obtenerHijoIzq() {
    return this->hijoIzq;
}

template <class T>
NodoCodificacion<T>* NodoCodificacion<T>::obtenerHijoDer() {
    return this->hijoDer;
}

template <class T>
bool NodoCodificacion<T>::esHoja() {
    return (this->hijoIzq == NULL && this->hijoDer == NULL);
}

template <class T>
void NodoCodificacion<T>::inOrden() {
    if (this->hijoIzq != NULL) {
        this->hijoIzq->inOrden();
    }
    if(this->simbolo != -1){
        std::cout << "Simbolo: " << this->simbolo << " ";
    }

    std::cout << "Frecuencia: " << this->frecuencia << "\n";

    if (this->hijoDer != NULL) {
        this->hijoDer->inOrden();
    }
}

#endif //_NODOCODIFICACION_HXX_