#ifndef ESTACIONSERV_H
#define ESTACIONSERV_H

#include <iostream>
#include <string>
#include "Surtidor.h"

using namespace std;

class estacionServ {
private:
    string nombre;
    string identificador;
    string gerente;
    string region;

    static const short int MaxSurtidores = 12;
    Surtidor surtidores[MaxSurtidores];
    unsigned short int cantidadSurtidores;
    unsigned short int litrosVendidosR = 0;
    unsigned short int litrosVendidosP = 0;
    unsigned short int litrosVendidosE = 0;

    int litrosR, litrosP, litrosE, litrosInicialR, litrosInicialP, litrosInicialE;
    float preciosRegion[3];  // [0] Norte, [1] Sur, [2] Centro
    float ventasR, ventasP, ventasE;
    string coordenadas;

public:
    estacionServ(string nom, string ide, string ger, string reg);
    ~estacionServ(); // Destructor

    string generarCoordenadas();
    void LitrosTanqueCentral();
    string getNombre() const;
    string getGerente() const;
    string getRegion() const;
    string getCoordenadas() const;
    string getIdentificador() const;
    int getLitrosVendidosR() const;
    int getLitrosVendidosP() const;
    int getLitrosVendidosE() const;
    int getLitrosR() const;
    int getLitrosP() const;
    int getLitrosE() const;
    int getCantidadSurtidores() const;
    int getLitrosInicialR() const;
    int getLitrosInicialP() const;
    int getLitrosInicialE() const;
    bool surtidorExiste(string codigo);
    bool surtidorestaActivo();
    void agregarSurtidor(string codigo);
    void eliminarSurtidor(string codigo);
    void activarSurtidor(string codigo, bool activar);
    void simularVenta(float* PreciosR);
    void mostrarLitrosRestantes() const;
    void mostrarVentas() const;

};


#endif // ESTACIONSERV_H
