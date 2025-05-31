#ifndef _GRAFO_HXX_
#define _GRAFO_HXX_

#include "Grafo.h"
#include <vector>
#include <limits>


template <class T, class U>
Grafo<T, U>::Grafo() {
    aristas = nullptr;
}

template <class T, class U>
void Grafo<T, U>::setVertices(std::vector<T> v) {
    vertices = v;
}

template <class T, class U>
void Grafo<T, U>::setAristas(U** a) {
    aristas = a;
}

template <class T, class U>
std::vector<T> Grafo<T, U>::getVertices() {
    return vertices;
}

template <class T, class U>
U** Grafo<T, U>::getAristas() {
    return aristas;
}

template <class T, class U>
int Grafo<T, U>::cantVertices() {
    return vertices.size();
}

template <class T, class U>
int Grafo<T, U>::cantAristas() {
    int suma = 0;
    for (int i = 0; i < cantVertices(); i++) {
        for (int j = 0; j < cantVertices(); j++) {
            if (*(*(aristas+i)+j) != 0)  suma++;
        }
    }
    return suma;
}

template <class T, class U>
int Grafo<T, U>::buscarVertice(T vert) {
    int ind = -1;
    for (int i = 0; i < cantVertices(); i++) {
        if (vertices[i] == vert)  ind = i;
    }
    return ind;
}

template <class T, class U>
bool Grafo<T, U>::insertarVertice(T vert) {
    bool res = false;
    if (buscarVertice(vert) == -1) {
        vertices.push_back(vert);
        U** nmatriz = new U*[cantVertices()];
        for (int i = 0; i < cantVertices(); i++) {
            *(nmatriz+i) = new U[cantVertices()];
        }
        for (int i = 0; i < cantVertices()-1; i++) {
            for (int j = 0; j < cantVertices()-1; j++) {
                *(*(nmatriz+i)+j) = *(*(aristas+i)+j);
            }
        }
        for (int i = 0; i < cantVertices(); i++) {
            *(*(nmatriz+i)+(cantVertices()-1)) = 0;
            *(*(nmatriz+(cantVertices()-1))+i) = 0;
        }
        for (int i = 0; i < cantVertices()-1; i++) {
            delete[] *(aristas+i);
        }
        delete[] aristas;
        aristas = nmatriz;
    }
    return res;
}

template <class T, class U>
bool Grafo<T, U>::insertarArista(T ori, T des, U cos) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if ( i_ori != -1 && i_des != -1 ) {
        if (*(*(aristas+i_ori)+i_des) == 0) {
            *(*(aristas+i_ori)+i_des) = cos;
            res = true;
        }
    }
    return res;
}

template <class T, class U>
U Grafo<T, U>::buscarArista(T ori, T des) {
    U res = -1;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if ( i_ori != -1 && i_des != -1 ) {
        res = *(*(aristas+i_ori)+i_des);
    }
    return res;
}

template <class T, class U>
bool Grafo<T, U>::eliminarArista(T ori, T des) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if ( i_ori != -1 && i_des != -1 ) {
        *(*(aristas+i_ori)+i_des) = 0;
        res = true;
    }
    return res;
}

template <class T, class U>
std::vector<T> Grafo<T, U>::tspVecinoMasCercano(const T& origen) {
    std::vector<bool> visitado(vertices.size(), false);
    std::vector<T> orden;
    // Buscar el punto más cercano al origen
    int idx_inicio = 0;
    double min_dist = std::numeric_limits<double>::max();
    for (int i = 0; i < vertices.size(); ++i) {
        double d = T::distancia(origen, vertices[i]);
        if (d < min_dist) {
            min_dist = d;
            idx_inicio = i;
        }
    }
    int actual = idx_inicio;
    orden.push_back(vertices[actual]);
    visitado[actual] = true;

    for (int paso = 1; paso < vertices.size(); ++paso) {
        int siguiente = -1;
        double mejor = std::numeric_limits<double>::max();
        for (int i = 0; i < vertices.size(); ++i) {
            if (!visitado[i]) {
                double d = T::distancia(vertices[actual], vertices[i]);
                if (d < mejor) {
                    mejor = d;
                    siguiente = i;
                }
            }
        }
        actual = siguiente;
        orden.push_back(vertices[actual]);
        visitado[actual] = true;
    }
    return orden;
}

#endif //_GRAFO_HXX