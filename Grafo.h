#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <vector>

template <class T, class U>
class Grafo {
private:
    std::vector<T> vertices;
    U** aristas;
public:
    Grafo();
    void setVertices(std::vector<T> v);
    void setAristas(U** a);
    std::vector<T> getVertices();
    U** getAristas();
    int cantVertices();
    int cantAristas();
    int buscarVertice(T vert);
    bool insertarVertice(T vert);
    bool insertarArista(T ori, T des, U cos);
    U buscarArista(T ori, T des);
    bool eliminarArista(T ori, T des);
    std::vector<T> tspVecinoMasCercano(const T& origen);
};

#include "Grafo.hxx"

#endif //_GRAFO_H_