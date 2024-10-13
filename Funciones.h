#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "eds.h"

#include <chrono>
#include <thread>
#include <iomanip>
#include <iostream>
using namespace std;

void copiar(int *origen, int *destino, int nDatos);
void eliminar(int *origen, int *destino, int nDatos, int codigoES);
void imprimirEstaciones(EDS **estacion, int nES);
void eliminarEstacion(EDS **estaciones, int nES, int codigoES);
void copiarEstacion(EDS **origen, EDS **destino, int nES);
void borrarPtr(EDS **misES, int nES);
void separador();
void espacios();
void menu();
void obtenerFechaHora(char* buffer);
#endif // FUNCIONES_H
