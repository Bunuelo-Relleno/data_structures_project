#ifndef SISTEMA_H
#define SISTEMA_H

#include<iostream>
#include<fstream>
#include"Imagen.h"
#include"Volumen.h"
#include "Segmentador.h"
#include <map>
#include <vector>

using namespace std;

class Sistema{
    public:
        Imagen imagenFinal;   //--> Será la imagen donde se guarda la proyeccion y se cargue en el archivo
        Volumen serieImagenes; //--> Será la serie de imagenes donde se guarde el volumen.
        ofstream archivo;        //--> Será el archivo donde se subira la imagen.
        Segmentador segmentador; //--> Objeto para manejar la segmentación de imágenes

        Sistema(){
            Imagen imagenFinal;
            Volumen serieImagenes;
            ifstream archivo;
        }
        bool proyeccion2D_x(string criterio, string nombreArchivo);
        bool proyeccion2D_y(string criterio, string nombreArchivo);
        bool proyeccion2D_z(string criterio, string nombreArchivo);
        bool segmentarImagen(const Imagen& imagen, const vector<Semilla>& semillas, const string& nombreArchivoSalida);
};
#endif //SISTEMA_H