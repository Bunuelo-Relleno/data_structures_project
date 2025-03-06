#include "Volumen.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Volumen::Volumen() : nombreVolumen(""), numImagenes(0), ancho(0), alto(0) {}

bool Volumen::cargarVolumen(const std::string& nombreBase, int numImgs) { 
    this->nombreVolumen = nombreBase;
    this->numImagenes = numImgs;
    this->imagenes.clear();

    for (int i = 1; i <= numImgs; i++) { 
        std::ostringstream nombreArchivo;
        nombreArchivo << nombreBase << std::setw(2) << std::setfill('0') << i << ".pgm";

        Imagen img;
        if (!img.cargarDesdeArchivo(nombreArchivo.str())) {
            std::cerr << "Error: No se pudo cargar la imagen " << nombreArchivo.str() << std::endl;
            return false;
        }
        imagenes.push_back(img);
    }

    if (!imagenes.empty()) { 
        ancho = imagenes[0].ancho;
        alto = imagenes[0].alto;
    }

    std::cout << "El volumen " << nombreBase << "ha sido cargado." << std::endl;
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
