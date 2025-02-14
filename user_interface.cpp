#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Definición de colores
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// Función para separar la entrada en tokens
vector<string> splitString(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Muestra la ayuda específica de cada comando
void showCommandHelp(const string& command) {
    if (command == "cargar_imagen") {
        cout << "Para usar el comando escribir: cargar_imagen nombre_imagen.pgm, siendo nombre_imagen_pgm el nombre del archivo de la imagen que desea cargar. Se encarga de cargar una imagen." << endl;
    }
    else if (command == "cargar_volumen") {
        cout << "Para usar comando escribir cargar_volumen nombre_base n_im, siendo nombre_base la serie ordenada de imágenes y n_im el tamaño de esta. Se encarga de cargar el volumen de una serie de imágenes." << endl;
    }
    else if (command == "info_imagen") {
        cout << "Para usar comando escribir: info_imagen, mostrara la información de la imagen cargada actualmente." << endl;
    }
    else if (command == "info_volumen") {
        cout << "Para usar el comando escribir: info_volumen, mostrara la información de la serie de imágenes actual." << endl;
    }
    else if (command == "proyeccion2D") {
        cout << "Para usar el comando escribir: proyeccion2D direccion criterio nombre_archivo.pgm, siendo direccion x, y o z; según se requiera, criterio mínimo, máximo, promedio o mediana; según se requiera y nombre_archivo.pgm, el nombre del archivo donde se guardará la imagen generada." << endl;
    }
    else if (command == "codificar_imagen") {
        cout << "Para usar el comando escribir: codificar_imagen nombre_archivo.huf, siendo nombre_archivo.huf el nombre del archivo donde se guardará la imagen cargada luego de codificarla." << endl;
    }
    else if (command == "decodificar_archivo") {
        cout << "Para usar el comando escribir: decodificar_archivo nombre_archivo.huf nombre_imagen.pgm, siendo nombre_archivo.huf el nombre del archivo donde se encuentra la imagen codificada, y el nombre_imagen.pgm el nombre del archivo donde se guardará la imagen una vez sea decodificada." << endl;
    }
    else if (command == "segmentar") {
        cout << "Para usar el comando escribir segmentar salida_imagen.pgm sx1 sy1 sl1 sx2 syx2 sl2 …, siendo salida_imagen.pgm el nombre del archivo donde se guardará la imagen segmentada, y las diferentes 's', las semillas que representan las segmentaciones." << endl;
    }
    else {
        cout << "Comando no reconocido." << endl;
    }
}

// Muestra todos los comandos disponibles
void showHelp() {
    cout << "Comandos disponibles:" << endl;
    cout << "- ayuda" << endl;
    cout << "- cargar_imagen nombre_imagen.pgm" << endl;
    cout << "- cargar_volumen nombre_base n_im" << endl;
    cout << "- info_imagen" << endl;
    cout << "- info_volumen" << endl;
    cout << "- proyeccion2D direccion criterio nombre_archivo.pgm" << endl;
    cout << "- codificar_imagen nombre_archivo.huf" << endl;
    cout << "- decodificar_archivo nombre_archivo.huf nombre_imagen.pgm" << endl;
    cout << "- segmentar salida_imagen.pgm sx1 sy1 sl1 [sx2 sy2 sl2 ...]" << endl;
    cout << "- quit (para salir)" << endl;
}

// Procesa y valida los comandos
bool processCommand(const vector<string>& tokens) {
    if (tokens.empty()) return true;
    
    const string& command = tokens[0];
    
    if (command == "quit") {
        return false;
    }
    else if (command == "ayuda") {
        if (tokens.size() == 1) {
            showHelp();
        }
        else if (tokens.size() == 2) {
            showCommandHelp(tokens[1]);
        }
        else {
            cout << RED << "Error: Uso correcto: ayuda [comando]" << RESET << endl;
        }
    }
    else if (command == "cargar_imagen") {
        if (tokens.size() != 2) {
            cout << RED << "Error: Uso correcto: cargar_imagen nombre_imagen.pgm" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "La imagen " << tokens[1] << " ha sido cargada." << RESET << endl;
    }
    else if (command == "cargar_volumen") {
        if (tokens.size() != 3) {
            cout << RED << "Error: Uso correcto: cargar_volumen nombre_base n_im" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "El volumen " << tokens[1] << " ha sido cargado." << RESET << endl;
    }
    else if (command == "info_imagen") {
        if (tokens.size() != 1) {
            cout << RED << "Error: Uso correcto: info_imagen" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "Mostrando información de la imagen..." << RESET << endl;
    }
    else if (command == "info_volumen") {
        if (tokens.size() != 1) {
            cout << RED << "Error: Uso correcto: info_volumen" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "Mostrando información del volumen..." << RESET << endl;
    }
    else if (command == "proyeccion2D") {
        if (tokens.size() != 4) {
            cout << RED << "Error: Uso correcto: proyeccion2D direccion criterio nombre_archivo.pgm" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "Generando proyección 2D..." << RESET << endl;
    }
    else if (command == "codificar_imagen") {
        if (tokens.size() != 2) {
            cout << RED << "Error: Uso correcto: codificar_imagen nombre_archivo.huf" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "Codificando imagen en " << tokens[1] << RESET << endl;
    }
    else if (command == "decodificar_archivo") {
        if (tokens.size() != 3) {
            cout << RED << "Error: Uso correcto: decodificar_archivo nombre_archivo.huf nombre_imagen.pgm" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "Decodificando archivo " << tokens[1] << RESET << endl;
    }
    else if (command == "segmentar") {
        if (tokens.size() < 5 || (tokens.size() - 2) % 3 != 0) {
            cout << RED << "Error: Uso correcto: segmentar salida_imagen.pgm sx1 sy1 sl1 [sx2 sy2 sl2 ...]" << RESET << endl;
            return true;
        }
        cout << GREEN << "Comando ejecutado correctamente" << RESET << endl;
        cout << YELLOW << "Segmentando imagen..." << RESET << endl;
    }
    else {
        cout << RED << "Error: Comando no reconocido. Use 'ayuda' para ver la lista de comandos disponibles." << RESET << endl;
    }
    
    return true;
}

// Función principal
int main() {
    string input;
    
    while (true) {
        cout << "$ ";
        getline(cin, input);
        
        vector<string> tokens = splitString(input);
        if (!processCommand(tokens)) {
            break;
        }
    }
    
    return 0;
}
