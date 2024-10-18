#ifndef TERMAX_H
#define TERMAX_H

#include <iostream>
#include "estacionServ.h"

using namespace std;

class TerMax {
private:
    estacionServ** estaciones;
    unsigned short int numEstaciones;
    unsigned short int capacidadMaxima;

    float preciosNorte[3];  // Precios para Regular, Premium y EcoExtra en Norte
    float preciosSur[3];    // Precios para Regular, Premium y EcoExtra en Sur
    float preciosCentro[3]; // Precios para Regular, Premium y EcoExtra en Centro

    void redimensionarEstaciones(); // Redimensiona el arreglo dinámico de estaciones

public:
    TerMax();   // Constructor
    ~TerMax();  // Destructor

    // Getters
    int getNumEstaciones() const;
    estacionServ* getEstacion(int index) const;
    float* getPreciosNorte();
    float* getPreciosSur();
    float* getPreciosCentro();

    // Operaciones con estaciones
    void agregarEstacion(estacionServ* nuevaEstacion);
    void eliminarEstacion(string id);
    void mostrarEstaciones() const;

    // Precios por región
    void establecerPrecioRegion(string region, int tipoCombustible, float precio);
    void mostrarPreciosRegion(string region);
    string obtenerNombreCombustible(int tipo);

    // Operaciones con surtidores
    void activarSurtidor(string idEstacion, string codigoSurtidor);
    void desactivarSurtidor(string idEstacion, string codigoSurtidor);
    void agregarSurtidor(string idEstacion, string codigoSurtidor);
    void eliminarSurtidor(string idEstacion, string codigoSurtidor);
    bool surtidorExiste(string idEstacion, string codigoSurtidor);

    // Verificación de fugas
    void mostrarLitrosRestantes();
    void verificarFugas();
};

#endif // TERMAX_H