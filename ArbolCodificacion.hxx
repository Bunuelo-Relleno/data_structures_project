#ifndef _ARBOLCODIFICACION_HXX_
#define _ARBOLCODIFICACION_HXX_

#include "ArbolCodificacion.h"
#include <map>
#include <queue>
#include <cstddef>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cstdint>

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
NodoCodificacion<T>* ArbolCodificacion<T>::obtenerRaiz() {
    return this->raiz;
}

template <class T>
void ArbolCodificacion<T>::fijarRaiz(NodoCodificacion<T>* raiz) {
    this->raiz = raiz;
}

// Estructura para comparar nodos por frecuencia
template <class T>
struct CompararNodos {
    bool operator()(NodoCodificacion<T>* a, NodoCodificacion<T>* b) {
        return a->obtenerFrecuencia() > b->obtenerFrecuencia();
    }
};

template <class T>
void ArbolCodificacion<T>::construirArbolCodificacion(std::map<T, unsigned long> frecuencias) {
    // Crea una cola de prioridad para almacenar los nodos hoja
    std::priority_queue<NodoCodificacion<T>*, std::vector<NodoCodificacion<T>*>, CompararNodos<T>> colaPrioridad;

    // Llena el heap con los nodos hoja
    for (const auto& it : frecuencias) {
        NodoCodificacion<T>* nodo = new NodoCodificacion<T>();
        nodo->fijarSimbolo(it.first);
        nodo->fijarFrecuencia(it.second);
        colaPrioridad.push(nodo);
    }

    // Construye el árbol combinando los nodos
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

template <class T>
void ArbolCodificacion<T>::recorrerArbol(NodoCodificacion<T>* nodo, const std::string& codigoActual, std::unordered_map<T, std::string>& codigos) {
    if (!nodo) return;

    if (nodo->esHoja()) {
        codigos[nodo->obtenerSimbolo()] = codigoActual;
        return;
    }

    recorrerArbol(nodo->obtenerHijoIzq(), codigoActual + "0", codigos);
    recorrerArbol(nodo->obtenerHijoDer(), codigoActual + "1", codigos);
}

template <class T>
std::unordered_map<T, std::string> ArbolCodificacion<T>::generarCodigos() {
    std::unordered_map<T, std::string> codigos;
    recorrerArbol(this->raiz, "", codigos);
    return codigos;
}

template <class T>
std::string ArbolCodificacion<T>::codificarImagen(const std::vector<std::vector<T>>& imagen) {
    std::string resultado;
    std::unordered_map<T, std::string> codigos = generarCodigos();
    
    for (const auto& fila : imagen) {
        for (T pixel : fila) {
            resultado += codigos.at(pixel);
        }
    }
    return resultado;
}

template <class T>
double ArbolCodificacion<T>::guardarArchivoHUF(const std::string& nombreArchivo, int ancho, int alto, int maxIntensidad, 
                                             const std::vector<unsigned long>& frecuencias, const std::string& bitsCodificados) {
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo .huf para escritura.\n";
        return 0.0;
    }

    // Cuenta cuántas intensidades se usan realmente
    int numIntensidadesUsadas = 0;
    for (int i = 0; i <= maxIntensidad; ++i) {
        if (frecuencias[i] > 0) numIntensidadesUsadas++;
    }

    // Calcula el tamaño original del archivo (asumiendo formato PGM)
    long originalSize = 3 + std::to_string(ancho).length() + std::to_string(alto).length() + 
                       std::to_string(maxIntensidad).length() + 4;
    originalSize += ancho * alto * (std::to_string(maxIntensidad).length() + 1);

    // Escribe W y H (2 bytes cada uno)
    unsigned short w = ancho;
    unsigned short h = alto;
    archivo.write(reinterpret_cast<char*>(&w), sizeof(unsigned short));
    archivo.write(reinterpret_cast<char*>(&h), sizeof(unsigned short));

    // Escribe M (1 byte)
    unsigned char m = static_cast<unsigned char>(maxIntensidad);
    archivo.write(reinterpret_cast<char*>(&m), sizeof(unsigned char));

    // Escribe el número de intensidades usadas (1 byte)
    unsigned char numUsed = static_cast<unsigned char>(numIntensidadesUsadas);
    archivo.write(reinterpret_cast<char*>(&numUsed), sizeof(unsigned char));

    // Escribe solo las frecuencias que se usan, junto con sus valores de intensidad
    for (int i = 0; i <= maxIntensidad; ++i) {
        if (frecuencias[i] > 0) {
            unsigned char intensidad = static_cast<unsigned char>(i);
            archivo.write(reinterpret_cast<char*>(&intensidad), sizeof(unsigned char));
            uint32_t freq = static_cast<uint32_t>(frecuencias[i]);
            archivo.write(reinterpret_cast<char*>(&freq), sizeof(uint32_t));
        }
    }

    // Escribe los bits codificados
    unsigned char byte = 0;
    int bitIndex = 0;

    for (char bit : bitsCodificados) {
        if (bit == '1') byte |= (1 << (7 - bitIndex));
        bitIndex++;

        if (bitIndex == 8) {
            archivo.write(reinterpret_cast<char*>(&byte), 1);
            byte = 0;
            bitIndex = 0;
        }
    }

    if (bitIndex > 0) {
        archivo.write(reinterpret_cast<char*>(&byte), 1);
    }

    // Calcula el tamaño comprimido
    long compressedSize = archivo.tellp();
    archivo.close();

    // Retorna el ratio de compresión (original/comprimido)
    return static_cast<double>(originalSize) / compressedSize;
}

template <class T>
bool ArbolCodificacion<T>::leerArchivoHUF(const std::string& nombreArchivoHUF,
                                        unsigned short& ancho,
                                        unsigned short& alto,
                                        unsigned char& maxIntensidad,
                                        std::map<int, unsigned long>& frecuencias,
                                        std::string& bits) {
    std::ifstream archivo(nombreArchivoHUF, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo .huf para lectura.\n";
        return false;
    }

    archivo.read(reinterpret_cast<char*>(&ancho), sizeof(ancho));
    archivo.read(reinterpret_cast<char*>(&alto), sizeof(alto));
    archivo.read(reinterpret_cast<char*>(&maxIntensidad), sizeof(maxIntensidad));

    unsigned char intensidadesUsadas;
    archivo.read(reinterpret_cast<char*>(&intensidadesUsadas), sizeof(intensidadesUsadas));

    for (int i = 0; i < intensidadesUsadas; ++i) {
        unsigned char intensidad;
        uint32_t frecuencia;
        archivo.read(reinterpret_cast<char*>(&intensidad), sizeof(intensidad));
        archivo.read(reinterpret_cast<char*>(&frecuencia), sizeof(frecuencia));
        frecuencias[(int)intensidad] = frecuencia;
    }

    char byte;
    while (archivo.read(&byte, 1)) {
        for (int i = 7; i >= 0; --i) {
            bits += ((byte >> i) & 1) ? '1' : '0';
        }
    }

    archivo.close();
    return true;
}

template <class T>
bool ArbolCodificacion<T>::decodificarArchivoHUF(const std::string& nombreArchivoHUF, const std::string& nombreSalidaPGM) {
    unsigned short ancho, alto;
    unsigned char maxIntensidad;
    std::map<int, unsigned long> frecuencias;
    std::string bits;

    if (!leerArchivoHUF(nombreArchivoHUF, ancho, alto, maxIntensidad, frecuencias, bits)) {
        return false;
    }

    ArbolCodificacion<int> arbol;
    arbol.construirArbolCodificacion(frecuencias);
    NodoCodificacion<int>* raiz = arbol.obtenerRaiz();

    std::vector<std::vector<int>> imagen(alto, std::vector<int>(ancho));
    int fila = 0, col = 0;
    NodoCodificacion<int>* actual = raiz;
    size_t totalPixeles = ancho * alto;
    size_t pixelesDecodificados = 0;

    for (char bit : bits) {
        actual = (bit == '0') ? actual->obtenerHijoIzq() : actual->obtenerHijoDer();
        if (actual->esHoja()) {
            imagen[fila][col] = actual->obtenerSimbolo();
            pixelesDecodificados++;
            col++;
            if (col == ancho) {
                col = 0;
                fila++;
            }
            if (pixelesDecodificados == totalPixeles) break;
            actual = raiz;
        }
    }

    std::ofstream salida(nombreSalidaPGM);
    if (!salida.is_open()) {
        std::cerr << "No se pudo crear el archivo de salida.\n";
        return false;
    }

    salida << "P2\n" << ancho << " " << alto << "\n" << (int)maxIntensidad << "\n";

    for (size_t i = 0; i < imagen.size(); ++i) {
        for (int valor : imagen[i]) {
            salida << valor << " ";
        }
        if (i != imagen.size() - 1) {
            salida << "\n";
        }
    }

    salida.close();
    return true;
}

template<class T>
void ArbolCodificacion<T>::_imprimirArbol(){
    if (!this->esVacio()){
        (this->raiz)->inOrden();
    }
}

#endif //_ARBOLCODIFICACION_HXX_