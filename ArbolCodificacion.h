#ifndef _ARBOL_CODIFICACION_H_
#define _ARBOL_CODIFICACION_H_

#include "NodoCodificacion.h"
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

// Clase que implementa un árbol de codificación para el algoritmo de Huffman
template <class T>
class ArbolCodificacion {
    protected:
        NodoCodificacion<T>* raiz;
        
        // Función auxiliar para recorrer el árbol y generar códigos
        void recorrerArbol(NodoCodificacion<T>* nodo, const std::string& codigoActual, std::unordered_map<T, std::string>& codigos);
        
    public:
        /*
         * Constructor del TAD ArbolCodificacion.
         * Inicializa un árbol vacío con raíz nula.
         */
        ArbolCodificacion();

        /*
         * Destructor del TAD ArbolCodificacion.
         * Libera toda la memoria asignada dinámicamente a nodos del árbol.
         */
        ~ArbolCodificacion();

        /*
         * Verifica si el árbol está vacío.
         * SALIDA: true si el árbol no tiene nodos, false en caso contrario.
         */
        bool esVacio();

        /*
         * Obtiene el dato almacenado en la raíz del árbol.
         * SALIDA: Dato almacenado en la raíz.
         * PRECONDICIÓN: El árbol no debe estar vacío.
         */
        T datoRaiz();

        /*
         * Obtiene el nodo raíz del árbol.
         * SALIDA: Puntero al nodo raíz.
         */
        NodoCodificacion<T>* obtenerRaiz();

        /*
         * Establece un nuevo nodo como raíz del árbol.
         * ENTRADA: Puntero al nuevo nodo raíz.
         */
        void fijarRaiz(NodoCodificacion<T>* raiz);
        
        /*
         * Construye el árbol de Huffman dado un conjunto de frecuencias.
         * ENTRADA: mapa con pares <símbolo, frecuencia>
         * SALIDA: árbol Huffman construido.
         * PRECONDICIÓN: El mapa debe tener al menos dos frecuencias diferentes.
         */
        void construirArbolCodificacion(std::map<T, unsigned long> frecuencias);
        
        /*
         * Genera los códigos Huffman para cada símbolo en el árbol.
         * SALIDA: Mapa que asocia cada símbolo con su código Huffman.
         * PRECONDICIÓN: El árbol debe estar construido.
         */
        std::unordered_map<T, std::string> generarCodigos();
        
        /*
         * Codifica una imagen usando los códigos Huffman generados.
         * ENTRADA: Matriz 2D que representa la imagen a codificar.
         * SALIDA: String con la secuencia de bits codificada.
         * PRECONDICIÓN: El árbol debe estar construido y los códigos generados.
         */
        std::string codificarImagen(const std::vector<std::vector<T>>& imagen);
        
        /*
         * Guarda un archivo HUF con la imagen codificada.
         * ENTRADA: nombreArchivo - nombre del archivo de salida
         *         ancho, alto - dimensiones de la imagen
         *         maxIntensidad - valor máximo de intensidad
         *         frecuencias - mapa de frecuencias
         *         bitsCodificados - string con los bits codificados
         * SALIDA: Tasa de compresión alcanzada.
         */
        double guardarArchivoHUF(const std::string& nombreArchivo, int ancho, int alto, int maxIntensidad, 
                               const std::vector<unsigned long>& frecuencias, const std::string& bitsCodificados);
        
        /*
         * Lee un archivo HUF y extrae la información necesaria.
         * ENTRADA: nombreArchivoHUF - nombre del archivo a leer
         * SALIDA: ancho, alto - dimensiones de la imagen
         *         maxIntensidad - valor máximo de intensidad
         *         frecuencias - mapa de frecuencias
         *         bits - string con los bits codificados
         * RETORNO: true si la lectura fue exitosa, false en caso contrario.
         */
        bool leerArchivoHUF(const std::string& nombreArchivoHUF,
                           unsigned short& ancho,
                           unsigned short& alto,
                           unsigned char& maxIntensidad,
                           std::map<int, unsigned long>& frecuencias,
                           std::string& bits);
        
        /*
         * Decodifica un archivo HUF y guarda la imagen resultante en formato PGM.
         * ENTRADA: nombreArchivoHUF - archivo HUF a decodificar
         *         nombreSalidaPGM - nombre del archivo PGM de salida
         * RETORNO: true si la decodificación fue exitosa, false en caso contrario.
         */
        bool decodificarArchivoHUF(const std::string& nombreArchivoHUF, const std::string& nombreSalidaPGM);
        
        /*
         * Imprime el árbol en orden (para depuración).
         */
        void _imprimirArbol();
};

#include "ArbolCodificacion.hxx"

#endif //_ARBOL_CODIFICACION_H_