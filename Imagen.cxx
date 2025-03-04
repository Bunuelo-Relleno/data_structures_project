#include "Imagen.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor por defecto
Imagen::Imagen() : nombre(""), ancho(0), alto(0), intensidadMaxima(0) {}

// Getters y Setters
std::string Imagen::nombre() const { return nombre; }
void Imagen::nombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }

int Imagen::ancho() const { return ancho; }
void Imagen::ancho(int nuevoAncho) { ancho = nuevoAncho; }

int Imagen::alto() const { return alto; }
void Imagen::alto(int nuevoAlto) { alto = nuevoAlto; }

int Imagen::intensidadMaxima() const { return intensidadMaxima; }
void Imagen::intensidadMaxima(int nuevaIntensidadMaxima) { intensidadMaxima = nuevaIntensidadMaxima; }

std::vector<std::vector<int>> Imagen::pixeles() const { return pixeles; }
void Imagen::pixeles(const std::vector<std::vector<int>>& nuevaMatriz) { pixeles = nuevaMatriz; }

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
    if (ancho <= 0 || alto <= 0 || intensidadMaxima <= 0 || intensidadMaxima > 255) {
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