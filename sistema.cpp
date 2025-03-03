#include <iostream>
#include "sistema.h"

using namespace std;

// Definición de colores para las lineas de comando
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

bool Sistema::guardar_imagen(string nombreArchivo){
    archivo.open(nombreArchivo); // Se abre el archivo en modo escritura

    // Se comprueba que el archivo se haya podido abrir.
    if (!archivo.is_open()) {
        cout << RED << "Error: No se pudo abrir el archivo para escritura." << RESET << endl;
        return false;
    }

    // Escribir el formato (PGM)
    archivo << "P2" << endl;

    // Escribir ancho y alto
    archivo << imagenFinal.ancho << " " << imagenFinal.alto << endl;

    // Escribir la intensidad máxima
    archivo << imagenFinal.intensidad_Maxima << endl;

    // Escribir los píxeles
    int s = 0;
    for (int k = 0; k < imagenFinal.___________; k++) {  //--> Recorre todos los pixeles de la imagen
        archivo << imagenFinal.___________<< " ";   //--> Cada que se escriba un pixel se deja un espacio en blanco
        s++;
        if (s == 26){   //--> Para mayor rendimiento a la hora de escribir en el archivo cada 26 pixeles se hace un salto de linea (no afecta a la imagen aunque el ancho sea otro).
            archivo << endl;
            s = 0;
        }
    }
    archivo.close();
    return true;
}

bool Sistema::proyeccion2D_x(string criterio, string nombreArchivo){
    if(criterio == "minimo"){
        for(int i = 0; i < serieImagenes.____; i++){        //--> Este recorrería todas las imagenes
            for(int j = 0; j < serieImagenes._____; j++){   //--> Este recorrería de una imagen, su altura (eje y). 
                int min = 256;  //--> Variable que almacena el valor minimo de los pixeles.
                for(int k = 0; k < serieImagenes._____; k++){ //--> Este recorrería de una imagen, y un punto Y, su anchura (eje x).
                    if(serieImagenes._____ == j){   //--> Se comprueba que todos los puntos X, compartan el mismo punto Y, para hacer el colapso.
                        if(serieImagenes._____ < min){ //-->Se guarda del conjunto anterior, el menor punto X.
                            min = serieImagenes._____;
                        }
                    }
                }
                /*
                _____ = min; //--> Se guarda el pixel minimo en una variable con sus coordenadas.
                
                ...

                imagenFinal._______.push_back(____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }

        //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
        int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
        for(int i = 0; i < imagenFinal.______; i++){
            if(imagenFinal._______ > max_pixel){
                max_pixel = imagenFinal.________;
            }
        }
        //Guardar el alto y ancho de la imagen.
        imagenFinal.alto = serieImagenes.______; 
        imagenFinal.ancho = serieImagenes.________;
        imagenFinal.intensidad_Maxima = max_pixel;

        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
    else if(criterio == "maximo"){
        for(int i = 0; i < serieImagenes.____; i++){    //--> Este recorrería todas las imagenes.
                for(int j = 0; j < serieImagenes._____; j++){   //--> Este recorrería de una imagen, su altura (eje Y).
                    int max = 0;    //-> Variable que almacena el valor maximo de los pixeles.
                    for(int k = 0; k < serieImagenes._____; k++){  //--> Este recorrería de una imagen, y un punto Y, su anchura (eje x).
                        if(serieImagenes.______ == j){  //--> Se comprueba que todos los puntos X, comparten el mismo punto Y, para hacer el colapso.
                            if (serieImmagenes._______ > max){  //--> Se guarda del conjunto anterior el mayor punto X
                                max = serieImagenes.______;
                            }
                        }
                    }

                    /*
                    _______ = max; //--> Se guarda el pixel maximo en una variable con sus coordenadas.
                
                    ...

                    imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
                }
            }

            //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
            int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
            for(int i = 0; i < imagenFinal.______; i++){
                if(imagenFinal._______ > max_pixel){
                    max_pixel = imagenFinal.________;
                }
            }
            //Guardar el alto y ancho de la imagen.
            imagenFinal.alto = serieImagenes.______; 
            imagenFinal.ancho = serieImagenes.________;
            imagenFinal.intensidad_Maxima = max_pixel;

            if(guardar_imagen(nombreArchivo)){
                return true;
            }
            else{
                cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
                return false;
            }
        }
    else if(criterio == "promedio"){
        for(int i = 0; i < serieImagenes.______; i++){ //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes.______; j++){  //--> Este recorrería de una imagen, su altura (eje Y).
                int prom = 0, cont = 0; //Variable que guarda el promedio y un contador para dividir.
                for(int k = 0; k < serieImagenes._______; k++){ //--> Este recorrería de una imagen, y un punto Y, su anchuera (eje x).
                    if(serieImagenes._______ == j)  //Se comprueba que todos los puntos X, comparten el mismo punto Y, para hacer el colapso.
                        prom += serieImagenes._______;
                        cont++;
                    }
                }
                prom /= cont;

                /*
                _______ = prom; //--> Se guarda el promedio de los pixeles en una variable con sus coordenadas.
                
                ...

                imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }

        //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
        int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
        for(int i = 0; i < imagenFinal.______; i++){
            if(imagenFinal._______ > max_pixel){
                max_pixel = imagenFinal.________;
            }
        }
        //Guardar el alto y ancho de la imagen.
        imagenFinal.alto = serieImagenes.______; 
        imagenFinal.ancho = serieImagenes.________;
        imagenFinal.intensidad_Maxima = max_pixel;

        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
    else if(criterio == "mediana"){
        for(int i = 0; i < serieImagenes._____; i++){ //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes._____; j++){ //--> Este recorrería de una imagen, su altura (eje Y).
                vector<int> orden;  //--> Vector para almacenar todos los pixeles de la linea.
                for(int k = 0; k < serieImagenes._____; k++){   //--> Este recorrería de una imagen, y un punto Y, su anchura (eje x).
                    if(serieImagenes.______ == j){
                        orden.push_back(serieImagenes._______);
                    }
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
                /*
                _______ = med; //--> Se guarda la mediana de los pixeles en una variable con sus coordenadas.
                
                ...

                imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }

        //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
        int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
        for(int i = 0; i < imagenFinal.______; i++){
            if(imagenFinal._______ > max_pixel){
                max_pixel = imagenFinal.________;
            }
        }
        //Guardar el alto y ancho de la imagen.
        imagenFinal.alto = serieImagenes.______; 
        imagenFinal.ancho = serieImagenes.________;
        imagenFinal.intensidad_Maxima = max_pixel;

        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
}

bool Sistema::proyeccion2D_y(string criterio, string nombreArchivo){
    if(criterio == "minimo"){
        for(int i = 0; i < serieImagenes.____; i++){        //--> Este recorrería todas las imagenes
            for(int j = 0; j < serieImagenes._____; j++){   //--> Este recorrería de una imagen, su anchura (eje x). 
                int min = 256;  //--> Variable que almacena el valor minimo de los pixeles.
                for(int k = 0; k < serieImagenes._____; k++){ //--> Este recorrería de una imagen, y un punto X, su altura (eje y).
                    if(serieImagenes._____ == j){   //--> Se comprueba que todos los puntos Y, compartan el mismo punto X, para hacer el colapso.
                        if(serieImagenes._____ < min){ //-->Se guarda del conjunto anterior, el menor punto Y.
                            min = serieImagenes._____;
                        }
                    }
                }
                /*
                _____ = min; //--> Se guarda el pixel minimo en una variable con sus coordenadas.
                
                ...

                imagenFinal._______.push_back(____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }

        //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
        int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
        for(int i = 0; i < imagenFinal.______; i++){
            if(imagenFinal._______ > max_pixel){
                max_pixel = imagenFinal.________;
            }
        }
        //Guardar el alto y ancho de la imagen.
        imagenFinal.alto = serieImagenes.______; 
        imagenFinal.ancho = serieImagenes.________;
        imagenFinal.intensidad_Maxima = max_pixel;

        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
    else if(criterio == "maximo"){
        for(int i = 0; i < serieImagenes.____; i++){    //--> Este recorrería todas las imagenes.
                for(int j = 0; j < serieImagenes._____; j++){   //--> Este recorrería de una imagen, su anchura (eje X).
                    int max = 0;    //-> Variable que almacena el valor maximo de los pixeles.
                    for(int k = 0; k < serieImagenes._____; k++){  //--> Este recorrería de una imagen, y un punto X, su altura (eje Y).
                        if(serieImagenes.______ == j){  //--> Se comprueba que todos los puntos Y, comparten el mismo punto X, para hacer el colapso.
                            if (serieImmagenes._______ > max){  //--> Se guarda del conjunto anterior el mayor punto Y.
                                max = serieImagenes.______;
                            }
                        }
                    }

                    /*
                    _______ = max; //--> Se guarda el pixel maximo en una variable con sus coordenadas.
                
                    ...

                    imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
                }
            }

            //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
            int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
            for(int i = 0; i < imagenFinal.______; i++){
                if(imagenFinal._______ > max_pixel){
                    max_pixel = imagenFinal.________;
                }
            }
            //Guardar el alto y ancho de la imagen.
            imagenFinal.alto = serieImagenes.______; 
            imagenFinal.ancho = serieImagenes.________;
            imagenFinal.intensidad_Maxima = max_pixel;

            if(guardar_imagen(nombreArchivo)){
                return true;
            }
            else{
                cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
                return false;
            }
        }
    else if(criterio == "promedio"){
        for(int i = 0; i < serieImagenes.______; i++){ //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes.______; j++){  //--> Este recorrería de una imagen, su anchura (eje X).
                int prom = 0, cont = 0; //Variable que guarda el promedio y un contador para dividir.
                for(int k = 0; k < serieImagenes._______; k++){ //--> Este recorrería de una imagen, y un punto X, su altura (eje y).
                    if(serieImagenes._______ == j)  //Se comprueba que todos los puntos Y, comparten el mismo punto X, para hacer el colapso.
                        prom += serieImagenes._______;
                        cont++;
                    }
                }
                prom /= cont;

                /*
                _______ = prom; //--> Se guarda el promedio de los pixeles en una variable con sus coordenadas.
                
                ...

                imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }

        //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
        int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
        for(int i = 0; i < imagenFinal.______; i++){
            if(imagenFinal._______ > max_pixel){
                max_pixel = imagenFinal.________;
            }
        }
        //Guardar el alto y ancho de la imagen.
        imagenFinal.alto = serieImagenes.______; 
        imagenFinal.ancho = serieImagenes.________;
        imagenFinal.intensidad_Maxima = max_pixel;

        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
    else if(criterio == "mediana"){
        for(int i = 0; i < serieImagenes._____; i++){ //--> Este recorrería todas las imagenes.
            for(int j = 0; j < serieImagenes._____; j++){ //--> Este recorrería de una imagen, su anchura (eje X).
                vector<int> orden;  //--> Vector para almacenar todos los pixeles de la linea.
                for(int k = 0; k < serieImagenes._____; k++){   //--> Este recorrería de una imagen, y un punto X, su altura (eje Y).
                    if(serieImagenes.______ == j){  //Se comprueba que todos los puntos Y, comparten el mismo punto X, para hacer el colapso.
                        orden.push_back(serieImagenes._______);
                    }
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
                /*
                _______ = med; //--> Se guarda la mediana de los pixeles en una variable con sus coordenadas.

                ...

                imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }

        //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
        int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
        for(int i = 0; i < imagenFinal.______; i++){
            if(imagenFinal._______ > max_pixel){
                max_pixel = imagenFinal.________;
            }
        }
        //Guardar el alto y ancho de la imagen.
        imagenFinal.alto = serieImagenes.______; 
        imagenFinal.ancho = serieImagenes.________;
        imagenFinal.intensidad_Maxima = max_pixel;

        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
}
bool Sistema::proyeccion2D_z(string criterio, string nombreArchivo){
    if(criterio == "minimo"){
        // Lo primero es copiar las dimensiones de la imagen de salida, puesto que sera de igual tamaño que cualquier imagen de la secuencia.
        imagenFinal.ancho = secuenciaImagenes.________;
        imagenFinal.alto = secuenciaImagenes.________;
        
        // Se rellenan todos los pixeles de la imagen final con un numero maximo de intensidad.
        for(int i = 0; i < imagenFinal.ancho; i++){
            for(int j = 0; j < imagenFinal.alto; j++){
                /*
                _______ = 256; //--> Se guarda en todos los pixeles una intensidad enorme.

                ...

                imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
        
        // Ahora se busca el pixel de menor intensidad en cada imagen
        for(int i = 0; i < serieImagenes.______; i++){  //-->   Este recorrería todas las imagenes.
            for(int x = 0; x < serieImagenes._____; x++)    //-->  Este recorrería todas las posiciones del eje X, que el numero es igual para toda la serie.
                for(int y = 0; y < serieImagenes._____; y++)    //--> Este recorrería todas las posiciones del eje Y, que el numero es igual para toda la serie.

                if(serieImagenes.____ < imagenFinal.______){   //--> Aqui se compararía que el pixel de las mismas coordenadas sea menor.
                    imagenFinal.______ = serieImagenes.______   //--> Se reemplaza por el minimo.
                }
            }
        }
        
        //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
        int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
        for(int i = 0; i < imagenFinal.______; i++){
            if(imagenFinal._______ > max_pixel){
                max_pixel = imagenFinal.________;
            }
        }
        imagenFinal.intensidad_Maxima = max_pixel;

        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
    else if(criterio == "maximo"){
        // Lo primero es copiar las dimensiones de la imagen de salida, puesto que sera de igual tamaño que cualquier imagen de la secuencia.
        imagenFinal.ancho = secuenciaImagenes.________;
        imagenFinal.alto = secuenciaImagenes.________;
        
        // Se rellenan todos los pixeles de la imagen final con un numero minimo de intensidad.
        for(int i = 0; i < imagenFinal.ancho; i++){
            for(int j = 0; j < imagenFinal.alto; j++){
                /*
                _______ = 0; //--> Se guarda en todos los pixeles una intensidad pequeña.

                ...

                imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
        
        // Ahora se busca el pixel de mayor intensidad en cada imagen
        for(int i = 0; i < serieImagenes.______; i++){  //-->   Este recorrería todas las imagenes.
            for(int x = 0; x < serieImagenes._____; x++)    //-->  Este recorrería todas las posiciones del eje X, que el numero es igual para toda la serie.
                for(int y = 0; y < serieImagenes._____; y++)    //--> Este recorrería todas las posiciones del eje Y, que el numero es igual para toda la serie.

                if(serieImagenes.____ > imagenFinal.______){   //--> Aqui se compararía que el pixel de las mismas coordenadas sea mayor.
                    imagenFinal.______ = serieImagenes.______   //--> Se reemplaza por el mayor.
                }
            }
        }
        
        //Lo siguiente es una lógica para crear el archivo pgm y guardarlo.
        int max_pixel = 0;  //Lógica para sacar el pixel de mayor intensidad de la imagen.
        for(int i = 0; i < imagenFinal.______; i++){
            if(imagenFinal._______ > max_pixel){
                max_pixel = imagenFinal.________;
            }
        }
        imagenFinal.intensidad_Maxima = max_pixel;

        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
    else if(criterio == "promedio"){
        // Lo primero es copiar las dimensiones de la imagen de salida, puesto que sera de igual tamaño que cualquier imagen de la secuencia.
        imagenFinal.ancho = secuenciaImagenes.________;
        imagenFinal.alto = secuenciaImagenes.________;
        
        // Matrices para sumas y contadores
        int sumas[imagenFinal.ancho][imagenFinal.alto];
        int contadores[imagenFinal.ancho][imagenFinal.alto];
        
        // Inicializar las matrices de sumas y contadores con ceros.
        for(int i = 0; i < imagenFinal.ancho; i++){
            for(int j = 0; j < imagenFinal.alto; j++){
                sumas[i][j] = 0;
                contadores[i][j] = 0;
            }
        }
        
        // Sumar valores y contar ocurrencias
        for(int k = 0; k < secuenciaImagenes.________; k++){ //--> Recorre todas las imagenes
            for(int i = 0; i < secuenciaImagenes._______; i++){ //--> Recorre posiciones X de una imagen (ancho).
                for(int j = 0; j < secuenciaImagenes.________; j++){     //--> Recorre posiciones Y de una imagen (alto).
                    sumas[i][j] += secuenciaImagenes._______;
                    contadores[i][j]++;
                }
            }
        }
        
        // Calcular promedios y encontrar el valor máximo
        int max_pixel = 0;
        for(int i = 0; i < imagenFinal.ancho; i++){
            for(int j = 0; j < imagenFinal.alto; j++){
                if(contadores[i][j] > 0){
                    imagenFinal.______ = sumas[i][j] / contadores[i][j];
                    
                    // Actualizar el valor máximo
                    if(imagenFinal________ > max_pixel){
                        max_pixel = imagenFinal._______;
                    }
                }
            }
        }
        
        imagenFinal.intensidad_Maxima = max_pixel;
        if(guardar_imagen(nombreArchivo)){
            return true;
        }
        else{
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
    else if(criterio == "mediana"){
        // Lo primero es copiar las dimensiones de la imagen de salida, puesto que sera de igual tamaño que cualquier imagen de la secuencia.
        imagenFinal.ancho = secuenciaImagenes.ancho;
        imagenFinal.alto = secuenciaImagenes.alto;
    
        // Se rellenan todos los pixeles de la imagen final con un numero de intensidad 0.
        for(int i = 0; i < imagenFinal.ancho; i++){
            for(int j = 0; j < imagenFinal.alto; j++){
                /*
                _______ = 0; //--> Se guarda en todos los pixeles una intensidad pequeña.

                ...

                imagenFinal._______.push_back(_____)*/ //--> Se agrega el pixel a la secuencia de pixeles de la imagenFinal.
            }
        }
    
        // Para cada posición (x, y), recopilar los valores de intensidad en la dirección Z
        for(int x = 0; x < imagenFinal.ancho; x++){ //--> Recorre todo el eje X de una imagen.
            for(int y = 0; y < imagenFinal.alto; y++){  //--> Recorre todo el eje Y de una imagen.
                vector<int> mediana;    //--> Almacena todas las intensidades de pixeles para una posicion (x, y) especifica en todas las imagenes.
    
                // Recorrer todas las imágenes en la secuencia
                for(int z = 0; z < secuenciaImagenes.______; z++){
                    mediana.push_back(secuenciaImagenes.__________________________) //--> Se guardan las intensidades que compartan misma coordenada en todas las imagenes.
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
                imagenFinal.__________ = mediana;
            }
        }
    
        // Encontrar el valor máximo de intensidad en la imagen final
        int max_pixel = 0;
        for(int x = 0; x < imagenFinal.ancho; x++){
            for(int y = 0; y < imagenFinal.alto; y++){
                if(imagenFinal._________ > max_pixel){
                    max_pixel = imagenFinal._________;
                }
            }
        }
        imagenFinal.intensidad_Maxima = max_pixel;
    
        // Guardar la imagen final
        if(guardar_imagen(nombreArchivo)){
            return true;
        } else {
            cout << RED << "Error: La imagen no pudo ser guardada en el archivo" << RESET << endl;
            return false;
        }
    }
}