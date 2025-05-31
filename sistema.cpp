#include <iostream>
#include <algorithm>
#include "sistema.h"
#include "Imagen.h"
#include "Volumen.h"
#include <map>

using namespace std;

// Definición de colores para las lineas de comando
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

bool Sistema::proyeccion2D_y(string criterio, string nombreArchivo){
    if(serieImagenes.getImagenes().empty()){
        cout << RED << "Error: Volumen no cargado, use el comando para cargar uno antes de ejecutar este" << RESET << endl;
        return false; 
    }
    
    // Inicializar la imagen final
    imagenFinal = Imagen();
    imagenFinal.setNombre(nombreArchivo);
    imagenFinal.setAlto(serieImagenes.getAlto());
    imagenFinal.setAncho(serieImagenes.getNumImagenes());
    
    // Inicializar la matriz de píxeles con el tamaño correcto
    imagenFinal.getPixeles().resize(imagenFinal.getAlto());
    for(int i = 0; i < imagenFinal.getAlto(); i++){
        imagenFinal.getPixeles()[i].resize(imagenFinal.getAncho());
    }
    
    imagenFinal.setIntensidadMaxima(1);
    
    if(criterio == "minimo"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int j = 0; j < serieImagenes.getImagenes()[i].getAlto(); j++){
                int min = 256;
                for(int k = 0; k < serieImagenes.getImagenes()[i].getAncho(); k++){
                    if(serieImagenes.getImagenes()[i].getPixeles()[j][k] < min){
                        min = serieImagenes.getImagenes()[i].getPixeles()[j][k];
                    }
                }
                imagenFinal.getPixeles()[j][i] = min;
            }
        }
    }
    else if(criterio == "maximo"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int j = 0; j < serieImagenes.getImagenes()[i].getAlto(); j++){
                int max = -1;
                for(int k = 0; k < serieImagenes.getImagenes()[i].getAncho(); k++){
                    if (serieImagenes.getImagenes()[i].getPixeles()[j][k] > max){
                        max = serieImagenes.getImagenes()[i].getPixeles()[j][k];
                    }
                }
                imagenFinal.getPixeles()[j][i] = max;
            }
        }
    }
    else if(criterio == "promedio"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int j = 0; j < serieImagenes.getImagenes()[i].getAlto(); j++){
                int prom = 0, cont = 0;
                for(int k = 0; k < serieImagenes.getImagenes()[i].getAncho(); k++){
                    prom += serieImagenes.getImagenes()[i].getPixeles()[j][k];
                    cont++;
                }
                prom /= cont;
                imagenFinal.getPixeles()[j][i] = prom;
            }
        }
    }
    else if(criterio == "mediana"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int j = 0; j < serieImagenes.getImagenes()[i].getAlto(); j++){
                vector<int> orden;
                for(int k = 0; k < serieImagenes.getImagenes()[i].getAncho(); k++){
                    orden.push_back(serieImagenes.getImagenes()[i].getPixeles()[j][k]);
                }

                sort(orden.begin(), orden.end());

                int med;
                if(orden.size() % 2 == 0){
                    med = (orden[orden.size()/2] + orden[(orden.size()/2) - 1]) / 2;
                }
                else{
                    med = orden[orden.size()/2];
                }
                imagenFinal.getPixeles()[j][i] = med;
            }
        }
    }
    
    // Encontrar el valor máximo de intensidad
    int max_pixel = -1;
    for(int i = 0; i < imagenFinal.getAlto(); i++){
        for(int j = 0; j < imagenFinal.getAncho(); j++){
            if(imagenFinal.getPixeles()[i][j] > max_pixel){
                max_pixel = imagenFinal.getPixeles()[i][j];
            }
        }
    }
    
    max_pixel = max(1, max_pixel);
    imagenFinal.setIntensidadMaxima(max_pixel);
    
    // Verificar que la imagen sea válida antes de guardar
    if(!imagenFinal.esValida()) {
        cout << RED << "Error: La imagen no es válida. Alto=" << imagenFinal.getAlto() 
             << ", Ancho=" << imagenFinal.getAncho() 
             << ", IntensidadMax=" << imagenFinal.getIntensidadMaxima() 
             << ", Nombre=" << imagenFinal.getNombre() 
             << ", Pixeles vacíos=" << imagenFinal.getPixeles().empty() << RESET << endl;
        return false;
    }
    
    if(imagenFinal.guardarEnArchivo(nombreArchivo)){
        return true;
    } else {
        cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
        return false;
    }
}

bool Sistema::proyeccion2D_x(string criterio, string nombreArchivo){
    if(serieImagenes.getImagenes().empty()){
        cout << RED << "Error: Volumen no cargado, use el comando para cargar uno antes de ejecutar este" << RESET << endl;
        return false; 
    }
    
    // Inicializar la imagen final
    imagenFinal = Imagen();
    imagenFinal.setNombre(nombreArchivo);
    imagenFinal.setAlto(serieImagenes.getNumImagenes());
    imagenFinal.setAncho(serieImagenes.getAncho());
    
    // Inicializar la matriz de píxeles con el tamaño correcto
    imagenFinal.getPixeles().resize(imagenFinal.getAlto());
    for(int i = 0; i < imagenFinal.getAlto(); i++){
        imagenFinal.getPixeles()[i].resize(imagenFinal.getAncho());
    }
    
    imagenFinal.setIntensidadMaxima(1);
    
    if(criterio == "minimo"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int j = 0; j < serieImagenes.getImagenes()[i].getAncho(); j++){
                int min = 256;
                for(int k = 0; k < serieImagenes.getImagenes()[i].getAlto(); k++){
                    if(serieImagenes.getImagenes()[i].getPixeles()[k][j] < min){
                        min = serieImagenes.getImagenes()[i].getPixeles()[k][j];
                    }
                }
                imagenFinal.getPixeles()[i][j] = min;
            }
        }
    }
    else if(criterio == "maximo"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int j = 0; j < serieImagenes.getImagenes()[i].getAncho(); j++){
                int max = -1;
                for(int k = 0; k < serieImagenes.getImagenes()[i].getAlto(); k++){
                    if (serieImagenes.getImagenes()[i].getPixeles()[k][j] > max){
                        max = serieImagenes.getImagenes()[i].getPixeles()[k][j];
                    }
                }
                imagenFinal.getPixeles()[i][j] = max;
            }
        }
    }
    else if(criterio == "promedio"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int j = 0; j < serieImagenes.getImagenes()[i].getAncho(); j++){
                int prom = 0, cont = 0;
                for(int k = 0; k < serieImagenes.getImagenes()[i].getAlto(); k++){
                    prom += serieImagenes.getImagenes()[i].getPixeles()[k][j];
                    cont++;
                }
                prom /= cont;
                imagenFinal.getPixeles()[i][j] = prom;
            }
        }
    }
    else if(criterio == "mediana"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int j = 0; j < serieImagenes.getImagenes()[i].getAncho(); j++){
                vector<int> orden;
                for(int k = 0; k < serieImagenes.getImagenes()[i].getAlto(); k++){
                    orden.push_back(serieImagenes.getImagenes()[i].getPixeles()[k][j]);
                }

                sort(orden.begin(), orden.end());

                int med;
                if(orden.size() % 2 == 0){
                    med = (orden[orden.size()/2] + orden[(orden.size()/2) - 1]) / 2;
                }
                else{
                    med = orden[orden.size()/2];
                }
                imagenFinal.getPixeles()[i][j] = med;
            }
        }
    }
    
    // Encontrar el valor máximo de intensidad
    int max_pixel = -1;
    for(int i = 0; i < imagenFinal.getAlto(); i++){
        for(int j = 0; j < imagenFinal.getAncho(); j++){
            if(imagenFinal.getPixeles()[i][j] > max_pixel){
                max_pixel = imagenFinal.getPixeles()[i][j];
            }
        }
    }
    
    max_pixel = max(1, max_pixel);
    imagenFinal.setIntensidadMaxima(max_pixel);
    
    // Verificar que la imagen sea válida antes de guardar
    if(!imagenFinal.esValida()) {
        cout << RED << "Error: La imagen no es válida. Alto=" << imagenFinal.getAlto() 
             << ", Ancho=" << imagenFinal.getAncho() 
             << ", IntensidadMax=" << imagenFinal.getIntensidadMaxima() 
             << ", Nombre=" << imagenFinal.getNombre() 
             << ", Pixeles vacíos=" << imagenFinal.getPixeles().empty() << RESET << endl;
        return false;
    }
    
    if(imagenFinal.guardarEnArchivo(nombreArchivo)){
        return true;
    } else {
        cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
        return false;
    }
}

bool Sistema::proyeccion2D_z(string criterio, string nombreArchivo){
    if(serieImagenes.getImagenes().empty()){
        cout << RED << "Error: Volumen no cargado, use el comando para cargar uno antes de ejecutar este" << RESET << endl;
        return false; 
    }
    
    // Inicializar la imagen final
    imagenFinal = Imagen();
    imagenFinal.setNombre(nombreArchivo);
    imagenFinal.setAncho(serieImagenes.getAncho());
    imagenFinal.setAlto(serieImagenes.getAlto());
    
    // Inicializar la matriz de píxeles con el tamaño correcto
    imagenFinal.getPixeles().resize(imagenFinal.getAlto());
    for(int i = 0; i < imagenFinal.getAlto(); i++){
        imagenFinal.getPixeles()[i].resize(imagenFinal.getAncho());
    }
    
    imagenFinal.setIntensidadMaxima(1);
    
    if(criterio == "minimo"){
        // Inicializar con el valor máximo posible
        for(int i = 0; i < imagenFinal.getAlto(); i++){
            for(int j = 0; j < imagenFinal.getAncho(); j++){
                imagenFinal.getPixeles()[i][j] = 256;
            }
        }
        
        // Buscar el mínimo
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int y = 0; y < serieImagenes.getAlto(); y++){
                for(int x = 0; x < serieImagenes.getAncho(); x++){
                    if(serieImagenes.getImagenes()[i].getPixeles()[y][x] < imagenFinal.getPixeles()[y][x]){
                        imagenFinal.getPixeles()[y][x] = serieImagenes.getImagenes()[i].getPixeles()[y][x];
                    }
                }
            }
        }
    }
    else if(criterio == "maximo"){
        // Inicializar con el valor mínimo posible
        for(int i = 0; i < imagenFinal.getAlto(); i++){
            for(int j = 0; j < imagenFinal.getAncho(); j++){
                imagenFinal.getPixeles()[i][j] = -1;
            }
        }
        
        // Buscar el máximo
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){
            for(int y = 0; y < serieImagenes.getAlto(); y++){
                for(int x = 0; x < serieImagenes.getAncho(); x++){
                    if(serieImagenes.getImagenes()[i].getPixeles()[y][x] > imagenFinal.getPixeles()[y][x]){
                        imagenFinal.getPixeles()[y][x] = serieImagenes.getImagenes()[i].getPixeles()[y][x];
                    }
                }
            }
        }
    }
    else if(criterio == "promedio"){
        // Matrices para sumas y contadores
        vector<vector<int>> sumas(imagenFinal.getAlto(), vector<int>(imagenFinal.getAncho(), 0));
        vector<vector<int>> contadores(imagenFinal.getAlto(), vector<int>(imagenFinal.getAncho(), 0));
        
        // Inicializar los pixeles de la imagen final con ceros
        for(int i = 0; i < imagenFinal.getAlto(); i++){
            for(int j = 0; j < imagenFinal.getAncho(); j++){
                imagenFinal.getPixeles()[i][j] = 0;
            }
        }
        
        // Sumar valores y contar ocurrencias
        for(int k = 0; k < serieImagenes.getNumImagenes(); k++){
            for(int i = 0; i < serieImagenes.getAlto(); i++){
                for(int j = 0; j < serieImagenes.getAncho(); j++){
                    sumas[i][j] += serieImagenes.getImagenes()[k].getPixeles()[i][j];
                    contadores[i][j]++;
                }
            }
        }
        
        // Calcular promedios
        for(int i = 0; i < imagenFinal.getAlto(); i++){
            for(int j = 0; j < imagenFinal.getAncho(); j++){
                if(contadores[i][j] > 0){
                    imagenFinal.getPixeles()[i][j] = sumas[i][j] / contadores[i][j];
                }
            }
        }
    }
    else if(criterio == "mediana"){
        // Inicializar los pixeles de la imagen final con ceros
        for(int i = 0; i < imagenFinal.getAlto(); i++){
            for(int j = 0; j < imagenFinal.getAncho(); j++){
                imagenFinal.getPixeles()[i][j] = 0;
            }
        }
        
        // Para cada posición (x, y), recopilar los valores de intensidad en la dirección Z
        for(int y = 0; y < imagenFinal.getAlto(); y++){
            for(int x = 0; x < imagenFinal.getAncho(); x++){
                vector<int> mediana;
                
                // Recopilar valores de todas las imágenes
                for(int z = 0; z < serieImagenes.getNumImagenes(); z++){
                    mediana.push_back(serieImagenes.getImagenes()[z].getPixeles()[y][x]);
                }
                
                sort(mediana.begin(), mediana.end());
                
                if(mediana.size() % 2 == 0){
                    imagenFinal.getPixeles()[y][x] = (mediana[mediana.size()/2] + mediana[(mediana.size()/2)-1]) / 2;
                } else {
                    imagenFinal.getPixeles()[y][x] = mediana[mediana.size()/2];
                }
            }
        }
    }
    
    // Encontrar el valor máximo de intensidad
    int max_pixel = -1;
    for(int i = 0; i < imagenFinal.getAlto(); i++){
        for(int j = 0; j < imagenFinal.getAncho(); j++){
            if(imagenFinal.getPixeles()[i][j] > max_pixel){
                max_pixel = imagenFinal.getPixeles()[i][j];
            }
        }
    }
    
    max_pixel = max(1, max_pixel);
    imagenFinal.setIntensidadMaxima(max_pixel);
    
    // Verificar que la imagen sea válida antes de guardar
    if(!imagenFinal.esValida()) {
        cout << RED << "Error: La imagen no es válida. Alto=" << imagenFinal.getAlto() 
             << ", Ancho=" << imagenFinal.getAncho() 
             << ", IntensidadMax=" << imagenFinal.getIntensidadMaxima() 
             << ", Nombre=" << imagenFinal.getNombre() 
             << ", Pixeles vacíos=" << imagenFinal.getPixeles().empty() << RESET << endl;
        return false;
    }
    
    if(imagenFinal.guardarEnArchivo(nombreArchivo)){
        return true;
    } else {
        cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
        return false;
    }
}

bool Sistema::segmentarImagen(const Imagen& imagen, const vector<Semilla>& semillas, const string& nombreArchivoSalida) {
    if (!imagen.esValida()) {
        cout << RED << "No hay una imagen cargada en memoria." << RESET << endl;
        return false;
    }
    
    return segmentador.segmentar(imagen, semillas, nombreArchivoSalida);
}