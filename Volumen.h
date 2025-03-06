#ifndef VOLUMEN_H
#define VOLUMEN_H

#include <vector>
#include <string>
#include "Imagen.h"

class Volumen { 
    private:
        std::vector<Imagen> imagenes;
        std::string nombreVolumen;
        int numImagenes; // cantidad de imagenes
        int ancho, alto; //dimensiones de las imagenes

    public:
    Volumen(); //Constructor
    
    bool cargarVolumen(const std::string& nombreVolumen, int numImgs);
    void infoVolumen() const;

    Imagen getImagen(int index) const;
    int getNumImagenes() const;
    int getAncho() const;
    int getAlto() const;
    std::string getNombreVolumen() const;
    const std::vector<Imagen>& getImagenes() const;
};

#endif
