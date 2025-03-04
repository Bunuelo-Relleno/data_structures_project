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
    std::string getNombre() const;
    void setNombre(const std::string& nuevoNombre);

    int getAncho() const;
    void setAncho(int nuevoAncho);

    int getAlto() const;
    void setAlto(int nuevoAlto);

    int getIntensidadMaxima() const;
    void setIntensidadMaxima(int nuevaIntensidadMaxima);

    std::vector<std::vector<int>> getPixeles() const;
    void setPixeles(const std::vector<std::vector<int>>& nuevaMatriz);

    // Métodos funcionales
    bool cargarDesdeArchivo(const std::string& nombreArchivo);
    bool guardarEnArchivo(const std::string& nombreArchivo) const;

    // Información de la imagen
    void infoImagen() const;

    // Validación de imagen cargada
    bool esValida() const;
};

#endif // IMAGEN_H