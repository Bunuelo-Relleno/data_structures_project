#ifndef IMAGEN_H
#define IMAGEN_H

#include <string>
#include <vector>

class Imagen {
private:
    std::string nombre;
    int ancho;
    int alto;
    int intensidadMaxima;
    std::vector<std::vector<int>> pixeles; // Matriz de píxeles en escala de grises

public:
    // Constructor
    Imagen();

    // Getters y Setters
    std::string nombre() const;
    void nombre(const std::string& nuevoNombre);

    int ancho() const;
    void ancho(int nuevoAncho);

    int alto() const;
    void alto(int nuevoAlto);

    int intensidadMaxima() const;
    void intensidadMaxima(int nuevaIntensidadMaxima);

    std::vector<std::vector<int>> pixeles() const;
    void pixeles(const std::vector<std::vector<int>>& nuevaMatriz);

    // Métodos funcionales
    bool cargarDesdeArchivo(const std::string& nombreArchivo);
    bool guardarEnArchivo(const std::string& nombreArchivo) const;
    
    // Información de la imagen
    void infoImagen() const;

    // Validación de imagen cargada
    bool esValida() const;
};

#endif // IMAGEN_H