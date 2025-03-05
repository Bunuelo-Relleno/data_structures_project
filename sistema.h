#ifndef SISTEMA_H
#define SISTEMA_H

#include<iostream>
#include<fstream>
#include"Imagen.h"
#include"volumen.h"

using namespace std;

class Sistema{
    public:
        Imagen imagenFinal;   //--> Será la imagen donde se guarda la proyeccion y se cargue en el archivo
        Volumen serieImagenes; //--> Será la serie de imagenes donde se guarde el volumen.
        ofstream archivo;        //--> Será el archivo donde se subira la imagen.

        Sistema(){
            Imagen imagenFinal;
            Volumen serieImagenes;
            ifstream archivo;
        }
        bool proyeccion2D_x(string criterio, string nombreArchivo);
        bool proyeccion2D_y(string criterio, string nombreArchivo);
        bool proyeccion2D_z(string criterio, string nombreArchivo);
};
#endif //SISTEMA_H