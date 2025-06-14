#include "Imagen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

// Constructor por defecto
Imagen::Imagen() : nombre(""), ancho(0), alto(0), intensidadMaxima(0) {}

// Getters y Setters
std::string Imagen::getNombre() const { return nombre; }
void Imagen::setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }

int Imagen::getAncho() const { return ancho; }
void Imagen::setAncho(int nuevoAncho) { ancho = nuevoAncho; }

int Imagen::getAlto() const { return alto; }
void Imagen::setAlto(int nuevoAlto) { alto = nuevoAlto; }

int Imagen::getIntensidadMaxima() const { return intensidadMaxima; }
void Imagen::setIntensidadMaxima(int nuevaIntensidadMaxima) { intensidadMaxima = nuevaIntensidadMaxima; }

std::vector<std::vector<int>>& Imagen::getPixeles() { return pixeles; }
const std::vector<std::vector<int>>& Imagen::getPixeles() const { return pixeles; }
void Imagen::setPixeles(const std::vector<std::vector<int>>& nuevaMatriz) { pixeles = nuevaMatriz; }

// Método para cargar una imagen desde un archivo PGM (P2)
bool Imagen::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return false;
    }

    std::string tipo;
    archivo >> tipo;
    if (tipo != "P2") {
        std::cerr << "Error: Formato de archivo no válido (se esperaba P2)" << std::endl;
        return false;
    }

    // Ignorar comentarios
    std::string linea;
    while (archivo.peek() == '#') {
        std::getline(archivo, linea);
    }

    // Leer dimensiones y máxima intensidad
    archivo >> ancho >> alto >> intensidadMaxima;

    // Validaciones
    if (ancho <= 0 || alto <= 0 || intensidadMaxima < 0 || intensidadMaxima > 255) {
        std::cerr << "Error: Valores inválidos en la cabecera del archivo" << std::endl;
        return false;
    }

    // Leer la matriz de píxeles
    pixeles.assign(alto, std::vector<int>(ancho));
    for (int i = 0; i < alto; ++i) { 
        for (int j = 0; j < ancho; ++j) {   
            if (!(archivo >> pixeles[i][j]) || pixeles[i][j] < 0 || pixeles[i][j] > intensidadMaxima) {
                std::cerr << "Error: Valores de píxeles fuera de rango" << std::endl;
                return false;
            }
        }
    }

    nombre = nombreArchivo;
    std::cout << "La imagen " << nombreArchivo << " ha sido cargada correctamente." << std::endl;
    return true;
}

// Método para guardar una imagen en un archivo PGM (P2)
bool Imagen::guardarEnArchivo(const std::string& nombreArchivo) const {
    if (!esValida()) {
        std::cerr << "Error: No hay una imagen válida para guardar" << std::endl;
        return false;
    }

    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
        return false;
    }

    // Escribir cabecera PGM
    archivo << "P2\n";
    archivo << "# Imagen guardada por el programa\n";
    archivo << ancho << " " << alto << "\n";
    archivo << intensidadMaxima << "\n";

    // Escribir matriz de píxeles
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            archivo << pixeles[i][j];
            if (j < ancho - 1) archivo << " ";
        }
        archivo << "\n";
    }
    archivo.close();
    std::cout << "La imagen ha sido guardada correctamente en " << nombreArchivo << std::endl;
    return true;
}

// Método para mostrar información de la imagen cargada
void Imagen::infoImagen() const {
    if (nombre.empty()) {
        std::cerr << "No hay una imagen cargada en memoria." << std::endl;
    } else {
        std::cout << "Imagen cargada en memoria: " << nombre
                  << ", ancho: " << ancho
                  << ", alto: " << alto << std::endl;
    }
}

// Validación de imagen cargada
bool Imagen::esValida() const {
    return !nombre.empty() && ancho > 0 && alto > 0 && intensidadMaxima > 0 && !pixeles.empty();
}

// Cuenta el número de veces que se repite la intensidad de un pixel dentro de la imagen. Usarla para codificar la imagen.
std::map<int, unsigned long> Imagen::calcular_frecuencias() {
    std::map<int, unsigned long> frecuencias;
    
    for (int i = 0; i < this->alto; i++) {
        for (int j = 0; j < this->ancho; j++) {
            unsigned char pixel = this->pixeles[i][j];
            frecuencias[pixel]++;
        }
    }
    return frecuencias;
}