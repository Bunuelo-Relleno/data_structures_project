#ifndef _NODOCODIFICACION_H_
#define _NODOCODIFICACION_H_

template <class T>
class NodoCodificacion {
    protected:
        T simbolo;
        unsigned long frecuencia;
        NodoCodificacion<T>* hijoIzq;
        NodoCodificacion<T>* hijoDer; 
    public:
        NodoCodificacion();
        ~NodoCodificacion();
        T obtenerSimbolo();
        void fijarSimbolo(T simbolo);
        unsigned long obtenerFrecuencia();
        void fijarFrecuencia(unsigned long frecuencia);
        NodoCodificacion<T>* fijarHijoIzq(NodoCodificacion<T>* hijoIzq);
        NodoCodificacion<T>* fijarHijoDer(NodoCodificacion<T>* hijoDer);
        NodoCodificacion<T>* obtenerHijoIzq();
        NodoCodificacion<T>* obtenerHijoDer();
        bool esHoja();
        void inOrden();
};

#include "NodoCodificacion.hxx"

#endif //_NODOCODIFICACION_H_