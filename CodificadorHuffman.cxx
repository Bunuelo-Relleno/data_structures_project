#include "CodificadorHuffman.h"
#include <fstream>
#include <iostream>

template <class T>
void recorrerArbol(NodoCodificacion<T>* nodo, const string& codigoActual, unordered_map<T, string>& codigos) {
    if (!nodo) return;

    if (nodo->esHoja()) {
        codigos[nodo->obtenerSimbolo()] = codigoActual;
        return;
    }

    recorrerArbol(nodo->obtenerHijoIzq(), codigoActual + "0", codigos);
    recorrerArbol(nodo->obtenerHijoDer(), codigoActual + "1", codigos);
}

template <class T>
unordered_map<T, string> generarCodigos(NodoCodificacion<T>* raiz) {
    unordered_map<T, string> codigos;
    recorrerArbol(raiz, "", codigos);
    return codigos;
}

template <class T>
string codificarImagen(const vector<vector<T>>& imagen, const unordered_map<T, string>& codigos) {
    string resultado;
    for (const auto& fila : imagen) {
        for (T pixel : fila) {
            resultado += codigos.at(pixel);
        }
    }
    return resultado;
}

void guardarArchivoHUF(const string& nombreArchivo, int ancho, int alto, int maxIntensidad, 
                        const vector<unsigned long>& frecuencias, const string& bitsCodificados) {
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo .huf para escritura.\n";
        return;
    }

    // Escribir W y H (2 bytes cada uno)
    unsigned short w = ancho;
    unsigned short h = alto;
    archivo.write(reinterpret_cast<char*>(&w), sizeof(unsigned short));
    archivo.write(reinterpret_cast<char*>(&h), sizeof(unsigned short));

    // Escribir M (1 byte)
    unsigned char m = static_cast<unsigned char>(maxIntensidad);
    archivo.write(reinterpret_cast<char*>(&m), sizeof(unsigned char));

    // Escribir frecuencias (cada una 8 bytes)
    for (int i = 0; i <= maxIntensidad; ++i) {
        archivo.write(reinterpret_cast<const char*>(&frecuencias[i]), sizeof(unsigned long));
    }

    // Escribir los bits codificados agrupados por byte
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

    archivo.close();
}

// Explicit template instantiations
template void recorrerArbol<int>(NodoCodificacion<int>*, const string&, unordered_map<int, string>&);
template unordered_map<int, string> generarCodigos<int>(NodoCodificacion<int>*);
template string codificarImagen<int>(const vector<vector<int>>&, const unordered_map<int, string>&);
