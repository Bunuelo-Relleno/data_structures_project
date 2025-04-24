#include "CodificadorHuffman.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <map>
#include "ArbolCodificacion.h"

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

double guardarArchivoHUF(const string& nombreArchivo, int ancho, int alto, int maxIntensidad, 
                        const vector<unsigned long>& frecuencias, const string& bitsCodificados) {
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo .huf para escritura.\n";
        return 0.0;
    }

    // Count how many intensities are actually used
    int numIntensidadesUsadas = 0;
    for (int i = 0; i <= maxIntensidad; ++i) {
        if (frecuencias[i] > 0) numIntensidadesUsadas++;
    }

    // Calculate original file size (assuming PGM format)
    // Header: P2\n + dimensions + max value + spaces and newlines
    long originalSize = 3 + to_string(ancho).length() + to_string(alto).length() + 
                       to_string(maxIntensidad).length() + 4;
    // Data: each pixel value + spaces/newlines
    originalSize += ancho * alto * (to_string(maxIntensidad).length() + 1);

    // Escribir W y H (2 bytes cada uno)
    unsigned short w = ancho;
    unsigned short h = alto;
    archivo.write(reinterpret_cast<char*>(&w), sizeof(unsigned short));
    archivo.write(reinterpret_cast<char*>(&h), sizeof(unsigned short));

    // Escribir M (1 byte)
    unsigned char m = static_cast<unsigned char>(maxIntensidad);
    archivo.write(reinterpret_cast<char*>(&m), sizeof(unsigned char));

    // Write number of used intensities (1 byte)
    unsigned char numUsed = static_cast<unsigned char>(numIntensidadesUsadas);
    archivo.write(reinterpret_cast<char*>(&numUsed), sizeof(unsigned char));

    // Write only the frequencies that are used, along with their intensity values
    for (int i = 0; i <= maxIntensidad; ++i) {
        if (frecuencias[i] > 0) {
            // Write the intensity value (1 byte)
            unsigned char intensidad = static_cast<unsigned char>(i);
            archivo.write(reinterpret_cast<char*>(&intensidad), sizeof(unsigned char));
            // Write its frequency (4 bytes is enough for a small image)
            uint32_t freq = static_cast<uint32_t>(frecuencias[i]);
            archivo.write(reinterpret_cast<char*>(&freq), sizeof(uint32_t));
        }
    }

    // Write the encoded bits
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

    // Calculate compressed size
    long compressedSize = archivo.tellp();
    archivo.close();

    // Return compression ratio (original/compressed)
    return static_cast<double>(originalSize) / compressedSize;
}

bool decodificarArchivoHUF(const std::string& nombreArchivoHUF, const std::string& nombreSalidaPGM) {
    std::ifstream archivo(nombreArchivoHUF, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo .huf para lectura.\n";
        return false;
    }

    //Leer encabezado: ancho, alto, max intensidad
    unsigned short ancho, alto;
    unsigned char maxIntensidad;
    archivo.read(reinterpret_cast<char*>(&ancho), sizeof(ancho));
    archivo.read(reinterpret_cast<char*>(&alto), sizeof(alto));
    archivo.read(reinterpret_cast<char*>(&maxIntensidad), sizeof(maxIntensidad));

    //Leer cantidad de intensidades usadas
    unsigned char intensidadesUsadas;
    archivo.read(reinterpret_cast<char*>(&intensidadesUsadas), sizeof(intensidadesUsadas));

    //Leer frecuencias
    std::map<int, unsigned long> frecuencias;
    for (int i = 0; i < intensidadesUsadas; ++i) {
        unsigned char intensidad;
        uint32_t frecuencia;
        archivo.read(reinterpret_cast<char*>(&intensidad), sizeof(intensidad));
        archivo.read(reinterpret_cast<char*>(&frecuencia), sizeof(frecuencia));
        frecuencias[(int)intensidad] = frecuencia;
    }

    //Construir arbol
    ArbolCodificacion<int> arbol;
    arbol.construirArbolCodificacion(frecuencias);
    NodoCodificacion<int>* raiz = arbol.obtenerRaiz();

    //Leer bits 
    std::string bits;
    char byte;
    while (archivo.read(&byte, 1)) {
        for (int i = 7; i >= 0; --i) {
            bits += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    archivo.close();

    //Decodificar bits usando el árbol
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

    // Guardar imagen decodificada en formato PGM
    std::ofstream salida(nombreSalidaPGM);
    if (!salida.is_open()) {
        std::cerr << "No se pudo crear el archivo de salida.\n";
        return false;
    }

    salida << "P2\n";
    //salida << "# Imagen decodificada desde Huffman\n";
    salida << ancho << " " << alto << "\n";
    salida << (int)maxIntensidad << "\n";

    for (size_t i = 0; i < imagen.size(); ++i) {
        for (int valor : imagen[i]) {
            salida << valor << " ";
        }
        if (i != imagen.size() - 1) {//para que no sea añada una linea vacia al final uwu
            salida << "\n";
        }
    }    

    salida.close();
    return true;
}


// Explicit template instantiations
template void recorrerArbol<int>(NodoCodificacion<int>*, const string&, unordered_map<int, string>&);
template unordered_map<int, string> generarCodigos<int>(NodoCodificacion<int>*);
template string codificarImagen<int>(const vector<vector<int>>&, const unordered_map<int, string>&);
