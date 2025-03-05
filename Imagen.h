#ifndef IMAGEN_H
#define IMAGEN_H

#include <string>
#include <vector>

class Imagen {
public:
    // Constructor
    Imagen();

    // Atributos públicos
    std::string nombre;
    int ancho;
    int alto;
    int intensidadMaxima;
    std::vector<std::vector<int>> pixeles; // Matriz de píxeles en escala de grises

    // Métodos funcionales
    bool cargarDesdeArchivo(const std::string& nombreArchivo);
    bool guardarEnArchivo(const std::string& nombreArchivo) const;
    
    // Información de la imagen
    void infoImagen() const;

    // Validación de imagen cargada
    bool esValida() const;
};

#endif // IMAGEN_H