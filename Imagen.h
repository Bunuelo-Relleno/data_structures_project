#ifndef IMAGEN_H
#define IMAGEN_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>

/*
 * Clase que representa una imagen en escala de grises en formato PGM.
 * Permite cargar, manipular y guardar imágenes en formato PGM (Portable Gray Map).
 * Implementa validaciones para asegurar la integridad de los datos de la imagen.
 */
class Imagen {
private:
    std::string nombre;              // Nombre del archivo de la imagen
    int ancho;                       // Ancho de la imagen en píxeles
    int alto;                        // Alto de la imagen en píxeles
    int intensidadMaxima;            // Valor máximo de intensidad (típicamente 255)
    std::vector<std::vector<int>> pixeles; // Matriz de píxeles en escala de grises

    /*
     * Valida que una intensidad esté dentro del rango permitido.
     * ENTRADA: intensidad - valor a validar
     * LANZA: std::runtime_error si la intensidad está fuera de rango
     */
    void validarIntensidad(int intensidad) const;

    /*
     * Valida que las dimensiones de la imagen sean coherentes.
     * LANZA: std::runtime_error si las dimensiones son inválidas
     */
    void validarDimensiones() const;

public:
    /*
     * Constructor de la clase Imagen.
     * Inicializa una imagen vacía con dimensiones y valores por defecto.
     */
    Imagen();

    // Getters y Setters con validaciones
    std::string getNombre() const;
    void setNombre(const std::string& nuevoNombre);

    int getAncho() const;
    void setAncho(int nuevoAncho);

    int getAlto() const;
    void setAlto(int nuevoAlto);

    int getIntensidadMaxima() const;
    void setIntensidadMaxima(int nuevaIntensidadMaxima);

    std::vector<std::vector<int>>& getPixeles();
    const std::vector<std::vector<int>>& getPixeles() const;
    void setPixeles(const std::vector<std::vector<int>>& nuevaMatriz);

    /*
     * Carga una imagen desde un archivo PGM.
     * ENTRADA: nombreArchivo - ruta del archivo a cargar
     * RETORNO: true si la carga fue exitosa, false en caso contrario
     * LANZA: std::runtime_error si hay errores de formato o acceso al archivo
     */
    bool cargarDesdeArchivo(const std::string& nombreArchivo);

    /*
     * Guarda la imagen en un archivo PGM.
     * ENTRADA: nombreArchivo - ruta donde guardar la imagen
     * RETORNO: true si el guardado fue exitoso, false en caso contrario
     * LANZA: std::runtime_error si hay errores de acceso al archivo
     */
    bool guardarEnArchivo(const std::string& nombreArchivo) const;

    /*
     * Muestra información básica de la imagen.
     * Incluye dimensiones, intensidad máxima y nombre del archivo.
     */
    void infoImagen() const;

    /*
     * Verifica si la imagen es válida.
     * Comprueba dimensiones, rango de intensidades y coherencia de datos.
     * RETORNO: true si la imagen es válida, false en caso contrario
     */
    bool esValida() const;

    /*
     * Calcula las frecuencias de cada intensidad en la imagen.
     * SALIDA: Mapa que asocia cada intensidad con su frecuencia
     * PRECONDICIÓN: La imagen debe ser válida
     */
    std::map<int, unsigned long> calcular_frecuencias();
};

#endif // IMAGEN_H