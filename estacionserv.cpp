#include "estacionserv.h"

#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <surtidor.h>

using namespace std;

// Constructor
estacionServ::estacionServ(string nom, string ide, string ger, string reg)
    : nombre(nom), identificador(ide), gerente(ger), region(reg), cantidadSurtidores(0) {

    coordenadas = generarCoordenadas();
    LitrosTanqueCentral();
    agregarSurtidor("S1");
    agregarSurtidor("S2");
}

string estacionServ::generarCoordenadas() {
    int latGrados = rand() % 13;  // Latitud entre 0 y 89 grados
    int lonGrados = rand() % 14 + 66; // Longitud entre 0 y 179 grados
    char latDir = 'N'; // Norte o Sur
    char lonDir = 'O'; // Este u Oeste

    return to_string(latGrados) + "G " + to_string(rand() % 60) + "' " + latDir + " y " +
           to_string(lonGrados) + "G " + to_string(rand() % 60) + "' " + lonDir;
}

void estacionServ::LitrosTanqueCentral() {
    litrosInicialR = litrosR = 100 + rand() % 101;
    litrosInicialP = litrosP = 100 + rand() % 101;
    litrosInicialE = litrosE = 100 + rand() % 101;

    cout << "Litros asignados de forma aleatoria:\n";
    cout << "Regular: " << litrosR << " litros\n";
    cout << "Premium: " << litrosP << " litros\n";
    cout << "EcoExtra: " << litrosE << " litros\n";
}

string estacionServ::getNombre() const {
    return nombre;
}

string estacionServ::getGerente() const {
    return gerente;
}

string estacionServ::getRegion() const {
    return region;
}

string estacionServ::getCoordenadas() const {
    return coordenadas;
}

string estacionServ::getIdentificador() const {
    return identificador;
}

int estacionServ::getLitrosVendidosR() const {
    return litrosVendidosR;
}

int estacionServ::getLitrosVendidosP() const {
    return litrosVendidosP;
}

int estacionServ::getLitrosVendidosE() const {
    return litrosVendidosE;
}

int estacionServ::getLitrosR() const {
    return litrosR;
}

int estacionServ::getLitrosP() const {
    return litrosP;
}

int estacionServ::getLitrosE() const {
    return litrosE;
}

int estacionServ::getCantidadSurtidores() const {
    return cantidadSurtidores;
}

int estacionServ::getLitrosInicialR() const {
    return litrosInicialR;
}

int estacionServ::getLitrosInicialP() const {
    return litrosInicialP;
}

int estacionServ::getLitrosInicialE() const {
    return litrosInicialE;
}

bool estacionServ::surtidorExiste(string codigo) {
    for (int i = 0; i < MaxSurtidores; i++) {
        if (surtidores[i].getCodigo() == codigo) {
            return true;
        }
    }
    return false;
}

bool estacionServ::surtidorestaActivo() {
    for (int i = 0; i < MaxSurtidores; i++) {
        if (surtidores[i].estaActivo()) {
            return true;
        }
    }
    return false;
}

void estacionServ::agregarSurtidor(string codigo) {
    if (cantidadSurtidores < MaxSurtidores) {
        surtidores[cantidadSurtidores] = Surtidor(codigo, region);
        cantidadSurtidores++;
        cout << "Surtidor " << codigo << " agregado.\n";
    } else {
        cout << "No se puede agregar mas surtidores. Capacidad maxima alcanzada.\n";
    }
}

void estacionServ::eliminarSurtidor(string codigo) {
    for (int i = 0; i < cantidadSurtidores; ++i) {
        if (surtidores[i].getCodigo() == codigo) {
            for (int j = i; j < cantidadSurtidores - 1; ++j) {
                surtidores[j] = surtidores[j + 1];
            }
            cantidadSurtidores--;
            cout << "Surtidor " << codigo << " eliminado.\n";
            return;
        }
    }
    cout << "Surtidor con codigo " << codigo << " no encontrado.\n";
}

void estacionServ::activarSurtidor(string codigo, bool activar) {
    for (int i = 0; i < cantidadSurtidores; ++i) {
        if (surtidores[i].getCodigo() == codigo) {
            if (activar) {
                surtidores[i].activar();
            } else {
                surtidores[i].desactivar();
            }
            return;
        }
    }
    cout << "Surtidor con codigo " << codigo << " no encontrado.\n";
}

void estacionServ::simularVenta(float* PreciosR) {
    if (cantidadSurtidores == 0) {
        cout << "No hay surtidores disponibles para la venta.\n";
        return;
    }
    if (surtidorestaActivo() == false) {
        cout << "No tiene surtidores activos para la venta.\n";
        return;
    }
    for (int i = 0; i < 3; i++) {
        preciosRegion[i] = PreciosR[i]; // Copia los precios
    }

    int surtidorElegido;
    do {
        surtidorElegido = rand() % cantidadSurtidores;
    } while (!surtidores[surtidorElegido].estaActivo());

    unsigned short int cantidad = 3 + rand() % 18; // Genera una cantidad aleatoria
    char tipoCombustible;
    cout << "Simulando venta en surtidor " << surtidores[surtidorElegido].getCodigo() << endl;
    cout << "Ingrese el tipo de combustible (R para Regular, P para Premium, E para EcoExtra): ";
    cin >> tipoCombustible;

    float costo = 0.0;  // Inicializa costo

    // Llama a la funcion de venta litrosVendidosR;
    surtidores[surtidorElegido].venta(cantidad, tipoCombustible, litrosR, litrosP, litrosE,  litrosVendidosR,
                                      litrosVendidosP, litrosVendidosE, costo, PreciosR, ventasR, ventasP, ventasE);
}

void estacionServ::mostrarLitrosRestantes() const {
    cout << "Litros restantes en el tanque central:\n";
    cout << "Regular: " << litrosR << " litros\n";
    cout << "Premium: " << litrosP << " litros\n";
    cout << "EcoExtra: " << litrosE << " litros\n";
    cout << "\n";
}

void estacionServ::mostrarVentas() const {
    cout << "Ventas generadas en la estacion:\n";
    cout << "Regular: $" << ventasR << "\n";
    cout << "Premium: $" << ventasP << "\n";
    cout << "EcoExtra: $" << ventasE << "\n";
    cout << "\n";
}

// Destructor
estacionServ::~estacionServ() {
    // Destructor vacío (puedes agregar lógica aquí si es necesario)
}
