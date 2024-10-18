#ifndef SURTIDOR_H
#define SURTIDOR_H

#include <iostream>
#include <string>

using namespace std;
class Surtidor {
private:
    string codigoSurtidor;
    bool activo;
    string region;
    string modelo;

public:
    Surtidor();
    Surtidor(string C, string reg);
    ~Surtidor(); // Destructor

    string getCodigo();
    bool estaActivo();
    void activar();
    void desactivar();
    void venta(int cantidad, char tipoCombustible, int &litrosR, int &litrosP, int &litrosE,
               short unsigned int &vendidosR, short unsigned int &vendidosP, short unsigned int &vendidosE, float &costo,
               const float preciosR[3], float &ventasR, float &ventasP, float &ventasE);

};

#endif // SURTIDOR_H
