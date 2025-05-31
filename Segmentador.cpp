#include "Segmentador.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>

// Definición de colores para las lineas de comando
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

Segmentador::Segmentador() {}

bool Segmentador::segmentar(const Imagen& imagen, const std::vector<Semilla>& semillas, const std::string& nombreArchivoSalida) {
    // Validar la imagen
    if (!imagen.esValida()) {
        std::cerr << RED << "Error: No hay una imagen válida para segmentar" << RESET << std::endl;
        return false;
    }
    
    // Guardar la imagen original y las semillas
    this->imagenOriginal = imagen;
    this->semillas = semillas;
    
    // Validar las semillas
    if (!validarSemillas()) {
        std::cerr << RED << "Error: Las semillas no son válidas" << RESET << std::endl;
        return false;
    }
    
    // Construir el grafo
    construirGrafo();
    
    // Inicializar la imagen segmentada
    imagenSegmentada = imagen;
    imagenSegmentada.setNombre(nombreArchivoSalida);
    
    // Matriz para almacenar las distancias mínimas de cada semilla
    std::vector<std::vector<int>> distanciasMinimas(imagen.getAlto(), std::vector<int>(imagen.getAncho(), std::numeric_limits<int>::max()));
    
    // Matriz para almacenar las etiquetas asignadas
    std::vector<std::vector<int>> etiquetas(imagen.getAlto(), std::vector<int>(imagen.getAncho(), 0));
    
    // Ejecutar Dijkstra desde cada semilla
    for (const auto& semilla : semillas) {
        Pixel pixelSemilla(semilla.x, semilla.y, imagen.getPixeles()[semilla.y][semilla.x]);
        std::vector<int> distancias = dijkstra(pixelSemilla);
        
        // Actualizar distancias mínimas y etiquetas
        for (int y = 0; y < imagen.getAlto(); ++y) {
            for (int x = 0; x < imagen.getAncho(); ++x) {
                int idx = y * imagen.getAncho() + x;
                if (distancias[idx] < distanciasMinimas[y][x]) {
                    distanciasMinimas[y][x] = distancias[idx];
                    etiquetas[y][x] = semilla.etiqueta;
                }
            }
        }
    }
    
    // Asignar las etiquetas a la imagen segmentada
    for (int y = 0; y < imagen.getAlto(); ++y) {
        for (int x = 0; x < imagen.getAncho(); ++x) {
            imagenSegmentada.getPixeles()[y][x] = etiquetas[y][x];
        }
    }
    
    // Guardar la imagen segmentada
    if (!imagenSegmentada.guardarEnArchivo(nombreArchivoSalida)) {
        std::cerr << RED << "Error: No se pudo guardar la imagen segmentada" << RESET << std::endl;
        return false;
    }
    
    return true;
}

void Segmentador::construirGrafo() {
    // Crear vector de vértices (píxeles)
    std::vector<Pixel> vertices;
    for (int y = 0; y < imagenOriginal.getAlto(); ++y) {
        for (int x = 0; x < imagenOriginal.getAncho(); ++x) {
            vertices.push_back(Pixel(x, y, imagenOriginal.getPixeles()[y][x]));
        }
    }
    
    // Inicializar el grafo con los vértices
    grafo.setVertices(vertices);
    
    // Crear matriz de adyacencia
    int n = vertices.size();
    int** matrizAristas = new int*[n];
    for (int i = 0; i < n; i++) {
        matrizAristas[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrizAristas[i][j] = -1;  // "no hay adyacencia aún"
        }
    }
    
    // Conectar píxeles vecinos
    for (int y = 0; y < imagenOriginal.getAlto(); ++y) {
        for (int x = 0; x < imagenOriginal.getAncho(); ++x) {
            Pixel actual(x, y, imagenOriginal.getPixeles()[y][x]);
            std::vector<Pixel> vecinos = obtenerVecinos(actual);
            
            for (const auto& vecino : vecinos) {
                int costo = calcularCostoArista(actual, vecino);
                int idxActual = y * imagenOriginal.getAncho() + x;
                int idxVecino = vecino.y * imagenOriginal.getAncho() + vecino.x;
                matrizAristas[idxActual][idxVecino] = costo;
            }
        }
    }
    
    grafo.setAristas(matrizAristas);
}

std::vector<int> Segmentador::dijkstra(const Pixel& origen) {
    int n = imagenOriginal.getAlto() * imagenOriginal.getAncho();
    std::vector<int> distancias(n, std::numeric_limits<int>::max());
    std::vector<bool> visitado(n, false);
    
    // Cola de prioridad para Dijkstra
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    
    // Inicializar con el origen
    int idxOrigen = origen.y * imagenOriginal.getAncho() + origen.x;
    distancias[idxOrigen] = 0;
    pq.push({0, idxOrigen});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (visitado[u]) continue;
        visitado[u] = true;
        
        // Explorar vecinos
        for (int v = 0; v < n; v++) {
            int peso = grafo.getAristas()[u][v];
            if (peso != -1) {  // Si hay arista
                if (distancias[u] != std::numeric_limits<int>::max() && 
                    distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    pq.push({distancias[v], v});
                }
            }
        }
    }
    
    return distancias;
}

bool Segmentador::validarSemillas() const {
    if (semillas.empty() || semillas.size() > 5) {
        std::cerr << RED << "Error: Debe proporcionar entre 1 y 5 semillas" << RESET << std::endl;
        return false;
    }
    
    for (const auto& semilla : semillas) {
        // Validar coordenadas
        if (!esCoordenadaValida(semilla.x, semilla.y)) {
            std::cerr << RED << "Error: Semilla fuera de los límites de la imagen" << RESET << std::endl;
            return false;
        }
        
        // Validar etiqueta
        if (semilla.etiqueta < 1 || semilla.etiqueta > 255) {
            std::cerr << RED << "Error: Etiqueta fuera de rango (debe estar entre 1 y 255)" << RESET << std::endl;
            return false;
        }
    }
    
    return true;
}

bool Segmentador::esCoordenadaValida(int x, int y) const {
    return x >= 0 && x < imagenOriginal.getAncho() && 
           y >= 0 && y < imagenOriginal.getAlto();
}

std::vector<Pixel> Segmentador::obtenerVecinos(const Pixel& p) const {
    std::vector<Pixel> vecinos;
    int dx[] = {-1, 0, 1, 0};  // Movimientos: izquierda, arriba, derecha, abajo
    int dy[] = {0, -1, 0, 1};
    
    for (int i = 0; i < 4; ++i) {
        int nx = p.x + dx[i];
        int ny = p.y + dy[i];
        
        if (esCoordenadaValida(nx, ny)) {
            vecinos.push_back(Pixel(nx, ny, imagenOriginal.getPixeles()[ny][nx]));
        }
    }
    
    return vecinos;
}

int Segmentador::calcularCostoArista(const Pixel& p1, const Pixel& p2) const {
    return std::abs(p1.valor - p2.valor);
} 