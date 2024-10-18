#include "TerMax.h"

// Constructor de TerMax
TerMax::TerMax() : numEstaciones(0), capacidadMaxima(3) {
    estaciones = new estacionServ*[capacidadMaxima];

    // Se inicializan los precios para las 3 regiones
    preciosNorte[0] = 15030;
    preciosNorte[1] = 25000;
    preciosNorte[2] = 20000;

    preciosSur[0] = 13000;
    preciosSur[1] = 22000;
    preciosSur[2] = 18000;

    preciosCentro[0] = 10000;
    preciosCentro[1] = 20000;
    preciosCentro[2] = 15000;

    agregarEstacion(new estacionServ("Estacion 1", "E001", "Gerente 1", "Norte"));
    agregarEstacion(new estacionServ("Estacion 2", "E002", "Gerente 2", "Sur"));
    agregarEstacion(new estacionServ("Estacion 3", "E003", "Gerente 3", "Centro"));
}

// Destructor de TerMax
TerMax::~TerMax() {
    for (int i = 0; i < numEstaciones; i++) {
        delete estaciones[i];
    }
    delete[] estaciones;
}

// Redimensiona el arreglo de estaciones cuando se excede la capacidad
void TerMax::redimensionarEstaciones() {
    unsigned short int nuevaCapacidad = capacidadMaxima * 2;
    estacionServ** nuevoArreglo = new estacionServ*[nuevaCapacidad];

    for (int i = 0; i < numEstaciones; i++) {
        nuevoArreglo[i] = estaciones[i];
    }

    delete[] estaciones;
    estaciones = nuevoArreglo;
    capacidadMaxima = nuevaCapacidad;
}

int TerMax::getNumEstaciones() const {
    return numEstaciones;
}

float* TerMax::getPreciosNorte() {
    return preciosNorte;
}

float* TerMax::getPreciosSur() {
    return preciosSur;
}

float* TerMax::getPreciosCentro() {
    return preciosCentro;
}

// Retorna una estación específica por su índice
estacionServ* TerMax::getEstacion(int index) const {
    if (index >= 0 && index < numEstaciones) {
        return estaciones[index];
    }
    return nullptr;  // Retorna nullptr si el índice es inválido
}

// Agrega una nueva estación, redimensiona si es necesario
void TerMax::agregarEstacion(estacionServ* nuevaEstacion) {
    if (numEstaciones == capacidadMaxima) {
        redimensionarEstaciones();
    }
    estaciones[numEstaciones++] = nuevaEstacion;
    cout << "Estacion agregada: " << nuevaEstacion->getNombre() << "\n" << endl;
}

// Elimina una estación por su ID, si no tiene surtidores activos
void TerMax::eliminarEstacion(string id) {
    for (int i = 0; i < numEstaciones; i++) {
        if (estaciones[i]->getIdentificador() == id) {
            if (estaciones[i]->surtidorestaActivo()) {
                cout << "La estacion no puede ser eliminada porque tiene surtidores activos.\n";
                return;
            } else {
                delete estaciones[i];
                for (int j = i; j < numEstaciones - 1; j++) {
                    estaciones[j] = estaciones[j + 1];
                }
                numEstaciones--;
                cout << "Estacion con ID " << id << " eliminada.\n";
                return;
            }
        }
    }
    cout << "La estacion no fue encontrada.\n";
}

void TerMax::establecerPrecioRegion(string region, int tipoCombustible, float precio) {
    if (region == "Norte") {
        preciosNorte[tipoCombustible] = precio;
        cout << "Precio de " << obtenerNombreCombustible(tipoCombustible) << " en la region Norte establecido en: " << precio << endl;
    } else if (region == "Sur") {
        preciosSur[tipoCombustible] = precio;
        cout << "Precio de " << obtenerNombreCombustible(tipoCombustible) << " en la region Sur establecido en: " << precio << endl;
    } else if (region == "Centro") {
        preciosCentro[tipoCombustible] = precio;
        cout << "Precio de " << obtenerNombreCombustible(tipoCombustible) << " en la region Centro establecido en: " << precio << endl;
    } else {
        cout << "Region no valida." << endl;
    }
}

// Muestra los precios de combustible para una región específica
void TerMax::mostrarPreciosRegion(string region) {
    if (region == "Norte") {
        cout << "Precios en la region Norte:\n";
        for (int i = 0; i < 3; i++) {
            cout << obtenerNombreCombustible(i) << ": " << preciosNorte[i] << " por litro\n";
        }
    } else if (region == "Sur") {
        cout << "Precios en la region Sur:\n";
        for (int i = 0; i < 3; i++) {
            cout << obtenerNombreCombustible(i) << ": " << preciosSur[i] << " por litro\n";
        }
    } else if (region == "Centro") {
        cout << "Precios en la region Centro:\n";
        for (int i = 0; i < 3; i++) {
            cout << obtenerNombreCombustible(i) << ": " << preciosCentro[i] << " por litro\n";
        }
    } else {
        cout << "Region no valida." << endl;
    }
}

// Devuelve el nombre del tipo de combustible
string TerMax::obtenerNombreCombustible(int tipo) {
    switch (tipo) {
    case 0: return "Regular";
    case 1: return "Premium";
    case 2: return "EcoExtra";
    default: return "Desconocido";
    }
}

// Muestra todas las estaciones de la red
void TerMax::mostrarEstaciones() const {
    cout << "Estaciones en la red TerMax:\n";
    for (int i = 0; i < numEstaciones; i++) {
        cout << "Nombre: " << estaciones[i]->getNombre() << endl;
        cout << "ID: " << estaciones[i]->getIdentificador() << endl;
        cout << "Gerente: " << estaciones[i]->getGerente() << endl;
        cout << "Region: " << estaciones[i]->getRegion() << endl;
        cout << "Coordenadas: " << estaciones[i]->getCoordenadas() << endl;
        cout << "---------------------\n";
    }
}

// Activa un surtidor en una estación
void TerMax::activarSurtidor(string idEstacion, string codigoSurtidor) {
    for (int i = 0; i < numEstaciones; i++) {
        if (estaciones[i]->getIdentificador() == idEstacion) {
            estaciones[i]->activarSurtidor(codigoSurtidor, true);
            return;
        }
    }
    cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
}

void TerMax::desactivarSurtidor(string idEstacion, string codigoSurtidor) {
    for (int i = 0; i < numEstaciones; i++) {
        if (estaciones[i]->getIdentificador() == idEstacion) {
            estaciones[i]->activarSurtidor(codigoSurtidor, false);
            return;
        }
    }
    cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
}

void TerMax::agregarSurtidor(string idEstacion, string codigoSurtidor) {
    for (int i = 0; i < numEstaciones; i++) {
        if (estaciones[i]->getIdentificador() == idEstacion) {
            estaciones[i]->agregarSurtidor(codigoSurtidor);
            return;
        }
    }
    cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
}

void TerMax::eliminarSurtidor(string idEstacion, string codigoSurtidor) {
    for (int i = 0; i < numEstaciones; i++) {
        if (estaciones[i]->getIdentificador() == idEstacion) {
            estaciones[i]->eliminarSurtidor(codigoSurtidor);
            return;
        }
    }
    cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
}

// Muestra los litros restantes en cada estación
void TerMax::mostrarLitrosRestantes() {
    for (int i = 0; i < numEstaciones; i++) {
        cout << "Estacion: " << estaciones[i]->getNombre() << endl;
        estaciones[i]->mostrarLitrosRestantes();
    }
}

// Verifica si un surtidor existe en una estación
bool TerMax::surtidorExiste(string idEstacion, string codigoSurtidor) {
    for (int i = 0; i < numEstaciones; i++) {
        if (estaciones[i]->getIdentificador() == idEstacion) {
            if (estaciones[i]->surtidorExiste(codigoSurtidor)) {
                return true;
            }
        }
    }
    return false;
}

// Verifica si hay fugas en las estaciones
void TerMax::verificarFugas() {
    for (int i = 0; i < numEstaciones; i++) {
        unsigned short int litrosE = estaciones[i]->getLitrosE();
        unsigned short int litrosR = estaciones[i]->getLitrosR();
        unsigned short int litrosP = estaciones[i]->getLitrosP();
        unsigned short int litrosVendidosE = estaciones[i]->getLitrosVendidosE();
        unsigned short int litrosVendidosR = estaciones[i]->getLitrosVendidosR();
        unsigned short int litrosVendidosP = estaciones[i]->getLitrosVendidosP();
        unsigned short int litrosInicialE = estaciones[i]->getLitrosInicialE();
        unsigned short int litrosInicialR = estaciones[i]->getLitrosInicialR();
        unsigned short int litrosInicialP = estaciones[i]->getLitrosInicialP();

        float totalRegular = litrosR + litrosVendidosR;
        float totalPremium = litrosP + litrosVendidosP;
        float totalEcoExtra = litrosE + litrosVendidosE;

        bool fugaRegular = totalRegular < 0.95 * litrosInicialR;
        bool fugaPremium = totalPremium < 0.95 * litrosInicialP;
        bool fugaEcoExtra = totalEcoExtra < 0.95 * litrosInicialE;

        cout << "Verificacion de fugas para estacion: " << estaciones[i]->getNombre() << ".\n";
        cout << "Regular: " << (fugaRegular ? "FUGA DETECTADA" : "SIN FUGA.") << endl;
        cout << "Premium: " << (fugaPremium ? "FUGA DETECTADA" : "SIN FUGA.") << endl;
        cout << "EcoExtra: " << (fugaEcoExtra ? "FUGA DETECTADA" : "SIN FUGA.\n") << endl;
    }
}