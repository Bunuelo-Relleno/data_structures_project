#include "Volumen.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>


Volumen::Volumen() : nombreVolumen(""), numImagenes(0), ancho(0), alto(0) {}

bool Volumen::cargarVolumen(const std::string& nombreBase, int numImgs) {
    if (numImgs <= 0 || numImgs > 99) {
        std::cerr << "Error: La cantidad de imágenes debe estar entre 1 y 99." << std::endl;
        return false;
    }

    this->nombreVolumen = nombreBase;
    this->numImagenes = numImgs;
    this->imagenes.clear();

    int expectedWidth = -1, expectedHeight = -1;
    
    for (int i = 1; i <= numImgs; i++) {
        std::ostringstream nombreArchivo;
        nombreArchivo << nombreBase << std::setw(2) << std::setfill('0') << i << ".pgm";

        std::ifstream file(nombreArchivo.str());
        if (!file) {
            std::cerr << "Error: Archivo " << nombreArchivo.str() << " no encontrado." << std::endl;
            return false;
        }

        Imagen img;
        if (!img.cargarDesdeArchivo(nombreArchivo.str())) {
            std::cerr << "Error: No se pudo cargar la imagen " << nombreArchivo.str() << std::endl;
            return false;
        }

        if (expectedWidth == -1 && expectedHeight == -1) {
            expectedWidth = img.getAncho();
            expectedHeight = img.getAlto();
        } else if (img.getAncho() != expectedWidth || img.getAlto() != expectedHeight) {
            std::cerr << "Error: La imagen " << nombreArchivo.str() << " tiene dimensiones diferentes a las anteriores." << std::endl;
            return false;
        }

        imagenes.push_back(img);
    }

    if (!imagenes.empty()) {
        ancho = imagenes[0].getAncho();
        alto = imagenes[0].getAlto();
    }

    std::cout << "El volumen " << nombreBase << " ha sido cargado correctamente con " << numImgs << " imágenes." << std::endl;
    return true;
}

void Volumen::infoVolumen() const {
    if (imagenes.empty()) {
        std::cerr << "No hay un volumen cargado en memoria." << std::endl;
    } else {
        std::cout << "Volumen cargado en memoria: " << nombreVolumen
                  << ", cantidad de imágenes: " << numImagenes
                  << ", ancho: " << ancho
                  << ", alto: " << alto << std::endl;
    }
}

int Volumen::getAlto() const { 
    return alto;
}

int Volumen::getAncho() const { 
    return ancho;
}

std::string Volumen::getNombreVolumen() const {
    return nombreVolumen;
}

const std::vector<Imagen>& Volumen::getImagenes() const {
    return imagenes;
}

Imagen Volumen::getImagen(int index) const {
    if (index < 0 || index >= numImagenes) {
        std::cerr << "Error: Índice de imagen fuera de rango." << std::endl;
        return Imagen(); // retornar una imagen vacía
    }
    return imagenes[index];
}

int Volumen::getNumImagenes() const {
    return numImagenes;
}