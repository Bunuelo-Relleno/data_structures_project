#ifndef CODIFICADOR_HUFFMAN_H
#define CODIFICADOR_HUFFMAN_H

#include <vector>
#include <unordered_map>
#include <string>
#include "NodoCodificacion.h"

using namespace std;

template <class T>
unordered_map<T, string> generarCodigos(NodoCodificacion<T>* raiz);

template <class T>
string codificarImagen(const vector<vector<T>>& imagen, const unordered_map<T, string>& codigos);

double guardarArchivoHUF(const string& nombreArchivo, int ancho, int alto, int maxIntensidad, 
                        const vector<unsigned long>& frecuencias, const string& bitsCodificados);

#endif
