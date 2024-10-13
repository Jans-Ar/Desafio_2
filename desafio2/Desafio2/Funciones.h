#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "eds.h"

#include <iostream>
using namespace std;

void copiar(int *origen, int *destino, int nDatos);
void eliminar(int *origen, int *destino, int nDatos, int codigoES);
void imprimirEstaciones(EDS **estacion);
#endif // FUNCIONES_H
