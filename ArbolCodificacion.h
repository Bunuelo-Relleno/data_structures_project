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
        ArbolCodificacion();
        ~ArbolCodificacion();
        bool esVacio();
        T datoRaiz();
        NodoCodificacion<T>* obtenerRaiz();
        void fijarRaiz(NodoCodificacion<T>* raiz);
        
        // Construye el árbol de codificación a partir de las frecuencias
        void construirArbolCodificacion(std::map<T, unsigned long> frecuencias);
        
        // Genera los códigos Huffman para cada símbolo
        std::unordered_map<T, std::string> generarCodigos();
        
        // Codifica una imagen usando los códigos generados
        std::string codificarImagen(const std::vector<std::vector<T>>& imagen);
        
        // Guarda un archivo HUF con la imagen codificada
        double guardarArchivoHUF(const std::string& nombreArchivo, int ancho, int alto, int maxIntensidad, 
                               const std::vector<unsigned long>& frecuencias, const std::string& bitsCodificados);
        
        // Lee un archivo HUF y extrae la información necesaria
        bool leerArchivoHUF(const std::string& nombreArchivoHUF,
                           unsigned short& ancho,
                           unsigned short& alto,
                           unsigned char& maxIntensidad,
                           std::map<int, unsigned long>& frecuencias,
                           std::string& bits);
        
        // Decodifica un archivo HUF y guarda la imagen resultante
        bool decodificarArchivoHUF(const std::string& nombreArchivoHUF, const std::string& nombreSalidaPGM);
        
        // Imprime el árbol en orden
        void _imprimirArbol();
};

#include "ArbolCodificacion.hxx"

#endif //_ARBOL_CODIFICACION_H_