#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Imagen.h"
#include <fstream>
#include "sistema.h"
#include "ArbolCodificacion.h"
//#include <algorithm>

using namespace std;

// Definición de colores para las lineas de comando
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// Variable global para manejar la imagen actual
Imagen imagenActual;

// Variable global para manejar el sistema
Sistema sistema;

// Variable global para manejar el árbol de Huffman
ArbolCodificacion<int> arbolCodificacion;

// Función para separar la entrada en tokens, de esta forma se sabe que comando es, si sus parametros son correctos, y cual es la informacion que acompaña al comando (archivo, criterio, tamaño, etc)
vector<string> splitString(const string& entrada) {
    vector<string> tokens;
    stringstream ss(entrada);
    string token;
    
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

bool validarExtension(const string& nombre, const string& extension){
    if (nombre.length() < extension.length()) return false;
    if (nombre.substr(nombre.length() - extension.length()) == extension ){
        return true;
    }
    return false;
}

// Muestra la ayuda específica de cada comando
void ayudaComando(const string& comando) {
    if (comando == "cargar_imagen") {
        cout << "Para usar el comando escribir: cargar_imagen (nombre_imagen.pgm), siendo nombre_imagen_pgm el nombre del archivo de la imagen que desea cargar. Se encarga de cargar una imagen." << endl;
    }
    else if (comando == "cargar_volumen") {
        cout << "Para usar el comando escribir: cargar_volumen (nombre_base) (n_im), siendo nombre_base la serie ordenada de imagenes y n_im el tamanio de esta. Se encarga de cargar el volumen de una serie de imagenes." << endl;
    }
    else if (comando == "info_imagen") {
        cout << "Para usar el comando escribir: info_imagen, mostrara la informacion de la imagen cargada actualmente." << endl;
    }
    else if (comando == "info_volumen") {
        cout << "Para usar el comando escribir: info_volumen, mostrara la informacion de la serie de imagenes actual." << endl;
    }
    else if (comando == "proyeccion2D") {
        cout << "Para usar el comando escribir: proyeccion2D (direccion) (criterio) (nombre_archivo.pgm), siendo direccion: x, y o z; segun se requiera, criterio: minimo, maximo, promedio o mediana; segun se requiera y nombre_archivo.pgm, el nombre del archivo donde se guardara la imagen generada." << endl;
    }
    else if (comando == "codificar_imagen") {
        cout << "Para usar el comando escribir: codificar_imagen (nombre_archivo.huf), siendo nombre_archivo.huf el nombre del archivo donde se guardara la imagen cargada luego de codificarla." << endl;
    }
    else if (comando == "decodificar_archivo") {
        cout << "Para usar el comando escribir: decodificar_archivo (nombre_archivo.huf) (nombre_imagen.pgm), siendo nombre_archivo.huf el nombre del archivo donde se encuentra la imagen codificada, y el nombre_imagen.pgm el nombre del archivo donde se guardara la imagen una vez sea decodificada." << endl;
    }
    else if (comando == "segmentar") {
        cout << "Para usar el comando escribir segmentar (salida_imagen.pgm) (sx1) (sy1) (sl1) (sx2) (syx2) (sl2) ..., siendo salida_imagen.pgm el nombre del archivo donde se guardara la imagen segmentada, y las diferentes 's', las semillas que representan las segmentaciones." << endl;
    }
    else {
        cout << "Comando no reconocido." << endl;
    }
}

// Muestra todos los comandos disponibles
void mostrarAyuda() {
    cout << "Comandos disponibles:" << endl;
    cout << "- ayuda" << endl;
    cout << "- cargar_imagen (nombre_imagen.pgm)" << endl;
    cout << "- cargar_volumen (nombre_base) (n_im)" << endl;
    cout << "- info_imagen" << endl;
    cout << "- info_volumen" << endl;
    cout << "- proyeccion2D (direccion) (criterio) (nombre_archivo.pgm)" << endl;
    cout << "- codificar_imagen (nombre_archivo.huf)" << endl;
    cout << "- decodificar_archivo (nombre_archivo.huf) (nombre_imagen.pgm)" << endl;
    cout << "- segmentar (salida_imagen.pgm) (sx1) (sy1) (sl1) [sx2 sy2 sl2 ...]" << endl;
    cout << "- salir (para salir)" << endl;
}

// Procesa y valida los comandos
bool procesarComando(const vector<string>& tokens) {


    if (tokens.empty()) return true;
    
    const string& comando = tokens[0];
    
    if (comando == "salir") {
        return false;
    }

    else if (comando == "ayuda") {
        if (tokens.size() == 1) {
            mostrarAyuda();
        }
        else if (tokens.size() == 2) {
            ayudaComando(tokens[1]);
        }
        else {
            cout << RED << "Error: Uso correcto: ayuda [comando]" << RESET << endl;
        }
    }
    else if (comando == "cargar_imagen") {
        if (tokens.size() != 2) {
            cout << RED << "Error: Uso correcto: cargar_imagen (nombre_imagen.pgm)" << RESET << endl;
            return true;
        }
        else if(!validarExtension(tokens[1], ".pgm")){
            cout << RED << "Error: La extension del archivo es incorrecta" << RESET << endl;
            return true;
        }
        
        if (imagenActual.cargarDesdeArchivo(tokens[1])) {
            cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
            cout << YELLOW << "La imagen " << tokens[1] << " ha sido cargada." << RESET << endl;
        } else {
            cout << RED << "Error: No se pudo cargar la imagen" << RESET << endl;
        }
    }
    else if (comando == "cargar_volumen") {
        if (tokens.size() != 3) {
            cout << RED << "Error: Uso correcto: cargar_volumen (nombre_base) (n_im)" << RESET << endl;
            return true;
        }
        
        string nombreBase = tokens[1];
        int numImagenes;
        
        string numImagenesStr = tokens[2];
        bool esNumero = true;

        // Verificar que todos los caracteres sean dígitos
        for (char c : numImagenesStr) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (!esNumero) {
            cout << RED << "Error: El número de imágenes debe ser un valor entero válido." << RESET << endl;
            return true;
        }

        // Convertir a entero después de validar
        numImagenes = stoi(numImagenesStr);
        
        if (numImagenes <= 0 || numImagenes > 99) {
            cout << RED << "Error: La cantidad de imágenes debe estar en el rango 1-99." << RESET << endl;
        return true;
        }
    
        if (sistema.serieImagenes.cargarVolumen(nombreBase, numImagenes)) {
            cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
            cout << YELLOW << "El volumen " << nombreBase << " ha sido cargado." << RESET << endl;
        } else {
            cout << RED << "Error: El volumen " << nombreBase << " no ha podido ser cargado." << RESET << endl;
        }
    }
    else if (comando == "info_imagen") {
        if (tokens.size() != 1) {
            cout << RED << "Error: Uso correcto: info_imagen" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "Mostrando informacion de la imagen..." << RESET << endl;
        imagenActual.infoImagen();
    }
    else if (comando == "info_volumen") {
        if (tokens.size() != 1) {
            cout << RED << "Error: Uso correcto: info_volumen" << RESET << endl;
            return true;
        }
    
        if (sistema.serieImagenes.getNumImagenes() == 0) {
            cout << RED << "No hay un volumen cargado en memoria." << RESET << endl;
        } else {
            cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
            sistema.serieImagenes.infoVolumen();
        }
    }    
    else if (comando == "proyeccion2D") {
        bool res = false;
        if (tokens.size() != 4) {
            cout << RED << "Error: Uso correcto: proyeccion2D (direccion) (criterio) (nombre_archivo.pgm)" << RESET << endl;
            return true;
        }
        else if(!validarExtension(tokens[3], ".pgm")){
            cout << RED << "Error: La extension del archivo es incorrecta" << RESET << endl;
            return true;
        }
        else if(tokens[1] != "x" && tokens[1] != "y" && tokens[1] != "z"){
            cout << RED << "Error: La direccion no es valida, intente con: x, y o z" << RESET << endl;
            return true;
        }
        else if(tokens[2] != "minimo" && tokens[2] != "maximo" && tokens[2] != "promedio" && tokens[2] != "mediana"){
            cout << RED << "Error: El criterio no es valido, intente con: minimo, maximo, promedio o mediana" << RESET << endl;
            return true;
        }
        else if(tokens[1] == "x"){
            res = sistema.proyeccion2D_x(tokens[2], tokens[3]);
        }
        else if(tokens[1] == "y"){
            res = sistema.proyeccion2D_y(tokens[2], tokens[3]);
        }
        else if(tokens[1] == "z"){
            res = sistema.proyeccion2D_z(tokens[2], tokens[3]);
        }
        if(res){
            cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
            cout << YELLOW << "La proyeccion 2D del volumen en memoria ha sido generada y almacenada en el archivo " << tokens[3] << RESET << endl;   
        }
    }
    else if (comando == "codificar_imagen") {
        if (tokens.size() != 2) {
            cout << RED << "Error: Uso correcto: codificar_imagen (nombre_archivo.huf)" << RESET << endl;
            return true;
        }
        else if(!validarExtension(tokens[1], ".huf")){
            cout << RED << "Error: La extension del archivo es incorrecta" << RESET << endl;
            return true;
        }

        if (imagenActual.esValida()) {
            vector<vector<int>> pixeles = imagenActual.getPixeles();
            int ancho = imagenActual.getAncho();
            int alto = imagenActual.getAlto();
            int maxIntensidad = imagenActual.getIntensidadMaxima();

            // Convierte el vector a mapa para las frecuencias
            map<int, unsigned long> frecuenciasMap = imagenActual.calcular_frecuencias();
            
            ArbolCodificacion<int> arbol;
            arbol.construirArbolCodificacion(frecuenciasMap);
            
            // Codifica la imagen usando el árbol
            string bitsCodificados = arbol.codificarImagen(pixeles);

            // Convierte el mapa de vuelta a vector para guardarlo
            vector<unsigned long> frecuenciasVector(maxIntensidad + 1, 0);
            for (const auto& pair : frecuenciasMap) {
                frecuenciasVector[pair.first] = pair.second;
            }

            double compressionRatio = arbol.guardarArchivoHUF(tokens[1], ancho, alto, maxIntensidad, frecuenciasVector, bitsCodificados);

            cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
            cout << YELLOW << "La imagen en memoria ha sido codificada exitosamente y almacenada en el archivo " << tokens[1] << RESET << endl;
            if (compressionRatio > 0) {
                cout << YELLOW << "Ratio de compresión: " << compressionRatio << ":1" << endl;
                cout << "(Un ratio mayor a 1 significa que el archivo fue comprimido, menor a 1 significa que aumentó de tamaño)" << RESET << endl;
            }
        } else {
            cout << RED << "Error: No hay una imagen válida para codificar" << RESET << endl;
        }
    }
    else if (comando == "decodificar_archivo") {
        if (tokens.size() != 3) {
            cout << RED << "Error: Uso correcto: decodificar_archivo (nombre_archivo.huf) (nombre_imagen.pgm)" << RESET << endl;
            return true;
        }
        else if(!validarExtension(tokens[1], ".huf")){
            cout << RED << "Error: La extensión del primer archivo es incorrecta" << RESET << endl;
            return true;
        }
        else if(!validarExtension(tokens[2], ".pgm")){
            cout << RED << "Error: La extensión del segundo archivo es incorrecta" << RESET << endl;
            return true;
        }
    
        // Intentar decodificar
        try {
            ArbolCodificacion<int> arbol;
            bool exito = arbol.decodificarArchivoHUF(tokens[1], tokens[2]);
            if (exito) {
                cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
                cout << YELLOW << "El archivo " << tokens[1] << " ha sido decodificado exitosamente, y la imagen correspondiente se ha almacenado en el archivo " << tokens[2] << RESET << endl;
            } else {
                cout << RED << "Error: El archivo no pudo ser decodificado correctamente." << RESET << endl;
            }
        } catch (const std::exception& e) {
            cout << RED << "Error durante la decodificación: " << e.what() << RESET << endl;
        }
    }
    
    else if (comando == "segmentar") {
        if (tokens.size() < 5 || (tokens.size() - 2) % 3 != 0) {
            cout << RED << "Error: Uso correcto: segmentar (salida_imagen.pgm) (sx1) (sy1) (sl1) [sx2 sy2 sl2 ...]" << RESET << endl;
            return true;
        }
        else if(!validarExtension(tokens[1], ".pgm")){
            cout << RED << "Error: La extension del archivo es incorrecta" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "La imagen en memoria fue segmentada correctamente y almacenada en el archivo " << tokens[1] << RESET << endl;
    }
    else {
        cout << RED << "Error: Comando no reconocido. Use 'ayuda' para ver la lista de comandos disponibles." << RESET << endl;
    }
    
    return true;
}

int main() {
    string entrada;
    
    while (true) {
        cout << "$ ";
        getline(cin, entrada);
        
        vector<string> tokens = splitString(entrada);
        if (!procesarComando(tokens)) {
            break;
        }
    }
    
    return 0;
}
