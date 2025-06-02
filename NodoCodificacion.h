#ifndef _NODOCODIFICACION_H_
#define _NODOCODIFICACION_H_

/*
 * Clase que implementa un nodo para el árbol de codificación Huffman.
 * Cada nodo almacena un símbolo, su frecuencia y referencias a sus hijos.
 */
template <class T>
class NodoCodificacion {
    protected:
        T simbolo;                    // Símbolo almacenado en el nodo
        unsigned long frecuencia;     // Frecuencia del símbolo
        NodoCodificacion<T>* hijoIzq; // Puntero al hijo izquierdo
        NodoCodificacion<T>* hijoDer; // Puntero al hijo derecho
        
    public:
        /*
         * Constructor del nodo.
         * Inicializa un nodo con valores por defecto y punteros nulos.
         */
        NodoCodificacion();

        /*
         * Destructor del nodo.
         * Libera la memoria de los hijos recursivamente.
         */
        ~NodoCodificacion();

        /*
         * Obtiene el símbolo almacenado en el nodo.
         * SALIDA: Símbolo almacenado.
         */
        T obtenerSimbolo();

        /*
         * Establece el símbolo del nodo.
         * ENTRADA: Nuevo símbolo a almacenar.
         */
        void fijarSimbolo(T simbolo);

        /*
         * Obtiene la frecuencia del símbolo.
         * SALIDA: Frecuencia almacenada.
         */
        unsigned long obtenerFrecuencia();

        /*
         * Establece la frecuencia del símbolo.
         * ENTRADA: Nueva frecuencia a almacenar.
         */
        void fijarFrecuencia(unsigned long frecuencia);

        /*
         * Establece el hijo izquierdo del nodo.
         * ENTRADA: Puntero al nuevo hijo izquierdo.
         * SALIDA: Puntero al hijo izquierdo establecido.
         */
        NodoCodificacion<T>* fijarHijoIzq(NodoCodificacion<T>* hijoIzq);

        /*
         * Establece el hijo derecho del nodo.
         * ENTRADA: Puntero al nuevo hijo derecho.
         * SALIDA: Puntero al hijo derecho establecido.
         */
        NodoCodificacion<T>* fijarHijoDer(NodoCodificacion<T>* hijoDer);

        /*
         * Obtiene el hijo izquierdo del nodo.
         * SALIDA: Puntero al hijo izquierdo.
         */
        NodoCodificacion<T>* obtenerHijoIzq();

        /*
         * Obtiene el hijo derecho del nodo.
         * SALIDA: Puntero al hijo derecho.
         */
        NodoCodificacion<T>* obtenerHijoDer();

        /*
         * Verifica si el nodo es una hoja.
         * SALIDA: true si el nodo no tiene hijos, false en caso contrario.
         */
        bool esHoja();

        /*
         * Imprime el árbol en orden (para depuración).
         */
        void inOrden();
};

#include "NodoCodificacion.hxx"

#endif //_NODOCODIFICACION_H_