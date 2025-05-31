#ifndef SEGMENTADOR_H
#define SEGMENTADOR_H

#include <vector>
#include <queue>
#include <limits>
#include "Imagen.h"
#include "Grafo.h"

// Estructura para representar un píxel como nodo del grafo
struct Pixel {
    int x, y;  // Coordenadas del píxel
    int valor; // Valor de intensidad del píxel
    
    Pixel(int _x = 0, int _y = 0, int _valor = 0) : x(_x), y(_y), valor(_valor) {}
    
    // Operador de igualdad para comparar píxeles
    bool operator==(const Pixel& otro) const {
        return x == otro.x && y == otro.y;
    }
};

// Estructura para representar una semilla
struct Semilla {
    int x, y;     // Coordenadas de la semilla
    int etiqueta; // Etiqueta asignada (1-255)
    
    Semilla(int _x = 0, int _y = 0, int _etiqueta = 0) : x(_x), y(_y), etiqueta(_etiqueta) {}
};

class Segmentador {
private:
    Imagen imagenOriginal;
    Imagen imagenSegmentada;
    std::vector<Semilla> semillas;
    Grafo<Pixel, int> grafo;
    
    // Métodos auxiliares
    void construirGrafo();
    std::vector<int> dijkstra(const Pixel& origen);
    bool validarSemillas() const;
    bool esCoordenadaValida(int x, int y) const;
    std::vector<Pixel> obtenerVecinos(const Pixel& p) const;
    int calcularCostoArista(const Pixel& p1, const Pixel& p2) const;
    
public:
    Segmentador();
    
    // Método principal para segmentar la imagen
    bool segmentar(const Imagen& imagen, const std::vector<Semilla>& semillas, const std::string& nombreArchivoSalida);
    
    // Getters
    const Imagen& getImagenSegmentada() const { return imagenSegmentada; }
};

#endif // SEGMENTADOR_H 