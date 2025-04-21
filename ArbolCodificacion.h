#ifndef _ARBOL_CODIFICACION_H_
#define _ARBOL_CODIFICACION_H_

#include "NodoCodificacion.h"
#include <map>

template <class T>
class ArbolCodificacion {
    protected:
        NodoCodificacion<T>* raiz;
    public:
        ArbolCodificacion();
        ~ArbolCodificacion();
        bool esVacio();
        T datoRaiz();
        void fijarRaiz(NodoCodificacion<T>* raiz);
        void construirArbolCodificacion(std::map<T, unsigned long> frecuencias); // Usarlo dentro de codificar y decodificar
        // void codificarImagen(Imagen& imagen, const std::string& nombreArchivo);
        // void guardarArchivoHuff(const Imagen& imagen, const std::map<int, unsigned long>& frecuencias, const std::string& bitsCodificados, const std::string& nombreArchivo);
        // void cargarArchivoHuff(const std::string& nombreArchivo, Imagen& imagen, std::map<int, unsigned long>& frecuencias, std::string& bitsCodificados);
        // bool decodificarImagen(const std::string& nombreArchivo, Imagen& imagen);
        void _imprimirArbol();
};

#include "ArbolCodificacion.hxx"

#endif //_ARBOL_CODIFICACION_H_