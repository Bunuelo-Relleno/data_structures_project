#include <iostream>
#include <algorithm>
#include "sistema.h"

using namespace std;

// Definición de colores para las lineas de comando
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

bool Sistema::proyeccion2D_x(string criterio, string nombreArchivo){
    if(serieImagenes.getImagenes().empty()){
        cout << RED << "Error: Volumen no cargado, use el comando para cargar uno antes de ejecutar este" << RESET << endl;
        return false; 
    }
    if(criterio == "minimo"){
        for(int i = 0; i < serieImagenes.____; i++){        //--> Este recorrería todas las imagenes
            for(int j = 0; j < serieImagenes._____; j++){   //--> Este recorrería de una imagen, su altura(eje Y). 
                int min = 256;  //--> Variable que almacena el valor minimo de los pixeles.
                for(int k = 0; k < serieImagenes._____; k++){ //--> Este recorrería de una imagen, y un punto Y, su anchura (eje X).
                    if(serieImagenes.getImagenes()[i].pixeles[j][k] < min){ //-->Se guarda del conjunto anterior, el menor punto X.
                        min = serieImagenes.getImagenes()[i].pixeles[j][k];
                    }
                }
                imagenFinal.pixeles[j].push_back(min); //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    }
    else if(criterio == "maximo"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){    //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes.getImagenes()[i].alto; j++){   //--> Este recorrería de una imagen, su altura (eje Y).
                int max = -1;    //-> Variable que almacena el valor maximo de los pixeles.
                for(int k = 0; k < serieImagenes.getImagenes()[i].ancho; k++){  //--> Este recorrería de una imagen, y un punto Y, su anchura (eje x).
                    if (serieImagenes.getImagenes()[i].pixeles[j][k] > max){  //--> Se guarda del conjunto anterior el mayor punto X
                        max = serieImagenes.getImagenes()[i].pixeles[j][k];
                    }
                }
                imagenFinal.pixeles[j].push_back(max); //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    }
    else if(criterio == "promedio"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){ //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes.getImagenes()[i].alto; j++){  //--> Este recorrería de una imagen, su altura (eje Y).
                int prom = 0, cont = 0; //Variable que guarda el promedio y un contador para dividir.
                for(int k = 0; k < serieImagenes.getImagenes()[i].ancho; k++){ //--> Este recorrería de una imagen, y un punto Y, su anchuera (eje x).
                    prom += serieImagenes.getImagenes()[i].pixeles[j][k];
                    cont++;
                }
                prom /= cont;
                imagenFinal.pixeles[j].push_back(prom); //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    }
    else if(criterio == "mediana"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){ //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes.getImagenes()[i].alto; j++){ //--> Este recorrería de una imagen, su altura (eje Y).
                vector<int> orden;  //--> Vector para almacenar todos los pixeles de la linea.
                for(int k = 0; k < serieImagenes.getImagenes()[i].ancho; k++){   //--> Este recorrería de una imagen, y un punto Y, su anchura (eje x).
                    orden.push_back(serieImagenes.getImagenes()[i].pixeles[j][k]);
                }

                sort(orden.begin(), orden.end());   //Se ordenan los pixeles

                //Lógica para calcular la mediana, en caso de que la secuencia sea par o impar.
                int med = 0;
                if(orden.size() % 2 == 0){
                    med = orden[orden.size()/2] + orden[(orden.size()/2) - 1];
                    med /= 2;
                }
                else{
                    med = orden[orden.size()/2];
                }
                imagenFinal.pixeles[j].push_back(med); //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    }
    int max_pixel = -1;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
    for(int i = 0; i < imagenFinal.pixeles.size(); i++){
        for(int j = 0; j < imagenFinal.pixeles[i].size(); j++){
            if(imagenFinal.pixeles[i][j] > max_pixel){
                max_pixel = imagenFinal.pixeles[i][j];
            }
        }
    }
    //Guardar el alto y ancho de la imagen.
    imagenFinal.alto = serieImagenes.alto;
    imagenFinal.ancho = serieImagenes.getNumeroImagenes();
    imagenFinal.intensidadMaxima = max_pixel;

    if(imagenFinal.guardarEnArchivo(nombreArchivo)){
        return true;
    }
    else{
        cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
        return false;
    }
}

bool Sistema::proyeccion2D_y(string criterio, string nombreArchivo){
    if(serieImagenes.getImagenes().empty()){
        cout << RED << "Error: Volumen no cargado, use el comando para cargar uno antes de ejecutar este" << RESET << endl;
        return false; 
    }
    if(criterio == "minimo"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){        //--> Este recorrería todas las imagenes
            for(int j = 0; j < serieImagenes.getImagenes()[i].ancho; j++){   //--> Este recorrería de una imagen, su anchura (eje x). 
                int min = 256;  //--> Variable que almacena el valor minimo de los pixeles.
                for(int k = 0; k < serieImagenes.getImagenes()[i].alto; k++){ //--> Este recorrería de una imagen, y un punto X, su altura (eje y).
                    if(serieImagenes.getImagenes()[i].pixeles[k][j] < min){ //-->Se guarda del conjunto anterior, el menor punto Y.
                        min = serieImagenes.getImagenes()[i].pixeles[k][j];
                    }
                }
                imagenFinal.pixeles[i].push_back(min); //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    }
    else if(criterio == "maximo"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){    //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes.getImagenes()[i].ancho; j++){   //--> Este recorrería de una imagen, su anchura (eje X).
                int max = -1;    //-> Variable que almacena el valor maximo de los pixeles.
                for(int k = 0; k < serieImagenes.getImagenes()[i].alto; k++){  //--> Este recorrería de una imagen, y un punto X, su altura (eje Y).
                    if (serieImagenes.getImagenes()[i].pixeles[k][j] > max){  //--> Se guarda del conjunto anterior el mayor punto Y.
                        max = serieImagenes.getImagenes()[i].pixeles[k][j];
                    }
                }
                imagenFinal.pixeles[i].push_back(max); //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    }
    else if(criterio == "promedio"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){ //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes.getImagenes()[i].ancho; j++){  //--> Este recorrería de una imagen, su anchura (eje X).
                int prom = 0, cont = 0; //Variable que guarda el promedio y un contador para dividir.
                for(int k = 0; k < serieImagenes.getImagenes()[i].alto; k++){ //--> Este recorrería de una imagen, y un punto X, su altura (eje y).
                    prom += serieImagenes.getImagenes()[i].pixeles[k][j];
                    cont++;
                }
                prom /= cont;
                imagenFinal.pixeles[i].push_back(prom); //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    }
    else if(criterio == "mediana"){
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){ //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes.getImagenes()[i].ancho; j++){ //--> Este recorrería de una imagen, su anchura (eje X).
                vector<int> orden;  //--> Vector para almacenar todos los pixeles de la linea.
                for(int k = 0; k < serieImagenes.getImagenes()[i].alto; k++){   //--> Este recorrería de una imagen, y un punto X, su altura (eje Y).
                    orden.push_back(serieImagenes.getImagenes()[i].pixeles[k][j]);
                }

                sort(orden.begin(), orden.end());   //Se ordenan los pixeles

                //Lógica para calcular la mediana, en caso de que la secuencia sea par o impar.
                int med = 0;
                if(orden.size() % 2 == 0){
                    med = orden[orden.size()/2] + orden[(orden.size()/2) - 1];
                    med /= 2;
                }
                else{
                    med = orden[orden.size()/2];
                }
                imagenFinal.pixeles[i].push_back(med); //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    }
    int max_pixel = -1;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
    for(int i = 0; i < imagenFinal.pixeles.size(); i++){
        for(int j = 0; j < imagenFinal.pixeles[i].size(); j++){
            if(imagenFinal.pixeles[i][j] > max_pixel){
                max_pixel = imagenFinal.pixeles[i][j];
            }
        }
    }
    //Guardar el alto y ancho de la imagen.
    imagenFinal.alto = serieImagenes.getNumImagenes();
    imagenFinal.ancho = serieImagenes.getAncho();
    imagenFinal.intensidadMaxima = max_pixel;

    if(imagenFinal.guardarEnArchivo(nombreArchivo)){
        return true;
    }
    else{
        cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
        return false;
    }
}
bool Sistema::proyeccion2D_z(string criterio, string nombreArchivo){
    if(serieImagenes.getImagenes().empty()){
        cout << RED << "Error: Volumen no cargado, use el comando para cargar uno antes de ejecutar este" << RESET << endl;
        return false; 
    }
    if(criterio == "minimo"){
        // Lo primero es copiar las dimensiones de la imagen de salida, puesto que sera de igual tamaño que cualquier imagen de la secuencia.
        imagenFinal.ancho = serieImagenes.getAncho();
        imagenFinal.alto = serieImagenes.getAlto();
        
        // Se rellenan todos los pixeles de la imagen final con un numero maximo de intensidad.
        for(int i = 0; i < imagenFinal.alto; i++){
            for(int j = 0; j < imagenFinal.ancho; j++){
                imagenFinal.pixeles[i].push_back(256);
            }
        }
        
        // Ahora se busca el pixel de menor intensidad en cada imagen
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){  //-->   Este recorrería todas las imagenes.
            for(int y = 0; y < serieImagenes.getAlto(); y++){    //-->  Este recorrería todas las posiciones del eje Y, que el numero es igual para toda la serie.
                for(int x = 0; x < serieImagenes.getAncho(); x++){    //--> Este recorrería todas las posiciones del eje X, que el numero es igual para toda la serie.
                    if(serieImagenes.getImagenes()[i].pixeles[y][x] < imagenFinal.pixeles[y][x]){   //--> Aqui se compararía que el pixel de las mismas coordenadas sea menor.
                        imagenFinal.pixeles[y][x] = serieImagenes.getImagenes()[i].pixeles[y][x];  //--> Se reemplaza por el minimo.
                    }
                }
            }
        }
    }
    else if(criterio == "maximo"){
        // Lo primero es copiar las dimensiones de la imagen de salida, puesto que sera de igual tamaño que cualquier imagen de la secuencia.
        imagenFinal.ancho = serieImagenes.getAncho();
        imagenFinal.alto = serieImagenes.getAlto();
        
         // Se rellenan todos los pixeles de la imagen final con un numero mínimo de intensidad.
         for(int i = 0; i < imagenFinal.alto; i++){
            for(int j = 0; j < imagenFinal.ancho; j++){
                imagenFinal.pixeles[i].push_back(-1);
            }
        }
        // Ahora se busca el pixel de menor intensidad en cada imagen
        for(int i = 0; i < serieImagenes.getNumImagenes(); i++){  //-->   Este recorrería todas las imagenes.
            for(int y = 0; y < serieImagenes.getAlto(); y++){    //-->  Este recorrería todas las posiciones del eje Y, que el numero es igual para toda la serie.
                for(int x = 0; x < serieImagenes.getAncho(); x++){    //--> Este recorrería todas las posiciones del eje X, que el numero es igual para toda la serie.
                    if(serieImagenes.getImagenes()[i].pixeles[y][x] > imagenFinal.pixeles[y][x]){   //--> Aqui se compararía que el pixel de las mismas coordenadas sea menor.
                        imagenFinal.pixeles[y][x] = serieImagenes.getImagenes()[i].pixeles[y][x];  //--> Se reemplaza por el máximo.
                    }
                }
            }
        }
    }
    else if(criterio == "promedio"){
        // Lo primero es copiar las dimensiones de la imagen de salida, puesto que sera de igual tamaño que cualquier imagen de la secuencia.
        imagenFinal.ancho = serieImagenes.getAncho();
        imagenFinal.alto = serieImagenes.getAlto();
        
        // Matrices para sumas y contadores
        vector<vector<int>> sumas;
        vector<vector<int>> contadores;
        
        // Inicializar las matrices de sumas y contadores con ceros.
        for(int i = 0; i < imagenFinal.alto; i++){
            for(int j = 0; j < imagenFinal.ancho; j++){
                sumas[i][j] = 0;
                contadores[i][j] = 0;
            }
        }
        // Sumar valores y contar ocurrencias
        for(int k = 0; k < serieImagenes.getNumImagenes(); k++){ //--> Recorre todas las imagenes
            for(int i = 0; i < serieImagenes.getAlto(); i++){ //--> Recorre posiciones Y de una imagen (altp).
                for(int j = 0; j < serieImagenes.getAncho(); j++){     //--> Recorre posiciones X de una imagen (ancho).
                    sumas[i][j] += serieImagenes.getImagenes()[k].pixeles[i][j];
                    contadores[i][j]++;
                }
            }
        }
        // Calcular promedios y encontrar el valor máximo
        for(int i = 0; i < imagenFinal.alto; i++){
            for(int j = 0; j < imagenFinal.ancho; j++){
                if(contadores[i][j] > 0){
                    imagenFinal.pixeles[i].push_back(sumas[i][j] / contadores[i][j]);
                }
            }
        }
    }
    else if(criterio == "mediana"){
        // Lo primero es copiar las dimensiones de la imagen de salida, puesto que sera de igual tamaño que cualquier imagen de la secuencia.
        imagenFinal.ancho = serieImagenes.getAncho();
        imagenFinal.alto = serieImagenes.getAlto();
    
         // Se rellenan todos los pixeles de la imagen final con un numero mínimo de intensidad.
         for(int i = 0; i < imagenFinal.alto; i++){
            for(int j = 0; j < imagenFinal.ancho; j++){
                imagenFinal.pixeles[i].push_back(0);
            }
        }
    
        // Para cada posición (x, y), recopilar los valores de intensidad en la dirección Z
        for(int y = 0; y < imagenFinal.alto; y++){ //--> Recorre todo el eje Y de una imagen.
            for(int x = 0; x < imagenFinal.ancho; x++){  //--> Recorre todo el eje X de una imagen.
                vector<int> mediana;    //--> Almacena todas las intensidades de pixeles para una posicion (x, y) especifica en todas las imagenes.
    
                // Recorrer todas las imágenes en la secuencia
                for(int z = 0; z < serieImagenes.getNumImagenes(); z++){
                    mediana.push_back(serieImagenes.getImagenes()[z].pixeles[y][x]); //--> Se guardan las intensidades que compartan misma coordenada en todas las imagenes.
                }
    
                // Ordenar los valores de intensidad
                sort(mediana.begin(), mediana.end());
    
                // Logica de calcular la mediana
                int medianaFinal;
                if(mediana.size() % 2 == 0){
                    medianaFinal = mediana[mediana.size() / 2] + mediana[(mediana.size() / 2) - 1]; 
                    medianaFinal /= 2;
                } else {
                    medianaFinal = mediana[mediana.size() / 2];
                }

                // Asignar la mediana a la imagen final
                imagenFinal.pixeles[y][x] = medianaFinal;
            }
        }
    }
    int max_pixel = -1;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
    for(int i = 0; i < imagenFinal.pixeles.size(); i++){
        for(int j = 0; j < imagenFinal.pixeles[i].size(); j++){
            if(imagenFinal.pixeles[i][j] > max_pixel){
                max_pixel = imagenFinal.pixeles[i][j];
            }
        }
    }

    imagenFinal.intensidadMaxima = max_pixel;

    if(imagenFinal.guardarEnArchivo(nombreArchivo)){
        return true;
    }
    else{
        cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
        return false;
    }
}