#include "surtidor.h"
#include <iostream>
#include <algorithm> // Para min()

using namespace std;

// Constructor por defecto
Surtidor::Surtidor() : codigoSurtidor(""), activo(false), region("") {}

// Constructor con parámetros
Surtidor::Surtidor(string C, string reg) : codigoSurtidor(C), activo(true), region(reg) {}

string Surtidor::getCodigo() {
    return codigoSurtidor;
}

bool Surtidor::estaActivo() {
    return activo;
}

void Surtidor::activar() {
    activo = true;
    cout << "Surtidor " << codigoSurtidor << " activado." << endl;
}

void Surtidor::desactivar() {
    activo = false;
    cout << "Surtidor " << codigoSurtidor << " desactivado." << endl;
}

void Surtidor::venta(int cantidad, char tipoCombustible, int &litrosR, int &litrosP, int &litrosE,
                     short unsigned int &vendidosR, short unsigned int &vendidosP, short unsigned int &vendidosE, float &costo,
                     const float preciosR[3], float &ventasR, float &ventasP, float &ventasE) {

    int tipoCombustibleI;
    if (tipoCombustible == 'R') tipoCombustibleI = 0;
    else if (tipoCombustible == 'P') tipoCombustibleI = 1;
    else if (tipoCombustible == 'E') tipoCombustibleI = 2;
    else {
        cout << "Tipo de combustible no valido." << endl;
        return;
    }
    // Calcular litros disponibles
    int &litrosDisponibles = (tipoCombustible == 'R') ? litrosR : (tipoCombustible == 'P') ? litrosP : litrosE;
    int litrosAUsar = min(litrosDisponibles, cantidad); // Usar lo que haya disponible

    if (litrosAUsar < cantidad) {
        cout << "No hay suficientes litros. Se venderan solo " << litrosAUsar << " litros.\n";
    }

    // Calcular costo
    costo += litrosAUsar * preciosR[tipoCombustibleI];

    // Actualizar litros vendidos
    if (tipoCombustible == 'R') {
        vendidosR += litrosAUsar;
        ventasR += costo;
    } else if (tipoCombustible == 'P') {
        vendidosP += litrosAUsar;
        ventasP += costo;
    } else if (tipoCombustible == 'E') {
        vendidosE += litrosAUsar;
        ventasE += costo;
    }

    // Actualizar litros restantes
    litrosDisponibles -= litrosAUsar; // Actualiza litros restantes

    cout << "Venta realizada de " << litrosAUsar << " litros de " << tipoCombustible << "." << endl;
    cout << "Costo total de la venta: " << costo << endl;
}

// Destructor
Surtidor::~Surtidor() {
    // Destructor vacío (puedes agregar lógica aquí si es necesario)
}

