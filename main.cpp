#include <iostream>
#include <string>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <limits>
using namespace std;

class Surtidor {
private:
    string codigoSurtidor;
    bool activo;

public:
    Surtidor() : codigoSurtidor(""), activo(false) {}

    Surtidor(string C) : codigoSurtidor(C), activo(true) {}

    string getCodigo() {
        return codigoSurtidor;
    }

    bool estaActivo() {
        return activo;
    }

    void activar() {
        activo = true;
        cout << "Surtidor " << codigoSurtidor << " activado." << endl;
    }

    void desactivar() {
        activo = false;
        cout << "Surtidor " << codigoSurtidor << " desactivado." << endl;
    }

    // Venta de combustible actualiza los litros en el tanque de la estacion
    void venta(int cantidad, char tipoCombustible, int &litrosR, int &litrosP, int &litrosE) {
        if (activo) {
            if (tipoCombustible == 'E') {
                if (litrosE >= cantidad) {
                    litrosE -= cantidad;
                    cout << "Venta realizada de " << cantidad << " litros de EcoExtra." << endl;
                } else {
                    cout << "No hay suficiente combustible tipo EcoExtra." << endl;
                }
            } else if (tipoCombustible == 'P') {
                if (litrosP >= cantidad) {
                    litrosP -= cantidad;
                    cout << "Venta realizada de " << cantidad << " litros de Premium." << endl;
                } else {
                    cout << "No hay suficiente combustible tipo Premium." << endl;
                }
            } else if (tipoCombustible == 'R') {
                if (litrosR >= cantidad) {
                    litrosR -= cantidad;
                    cout << "Venta realizada de " << cantidad << " litros de Regular." << endl;
                } else {
                    cout << "No hay suficiente combustible tipo Regular." << endl;
                }
            } else {
                cout << "Tipo de combustible no valido." << endl;
            }
        } else {
            cout << "El surtidor esta desactivado, no se puede hacer la venta." << endl;
        }
    }
};

class estacionServ {
private:
    string nombre;
    string identificador;
    string gerente;
    string region;

    static const short int MaxSurtidores = 12;  // Maximo numero de surtidores
    Surtidor surtidores[MaxSurtidores];
    int cantidadSurtidores;

    int litrosR, litrosP, litrosE;  // Litros del tanque central

public:
    estacionServ(string nom, string ide, string ger, string reg) : nombre(nom), identificador(ide), gerente(ger), region(reg), cantidadSurtidores(0) {
        srand(time(0));  // Inicializar semilla para numeros aleatorios
        LitrosTanqueCentral();  // Inicializar tanque
        agregarSurtidor("S1");  // Agregar surtidor S1
        agregarSurtidor("S2");  // Agregar surtidor S2
    }

    // Asignar valores aleatorios entre 100 y 200 litros a cada tipo de combustible
    void LitrosTanqueCentral() {
        litrosR = 100 + rand() % 101;
        litrosP = 100 + rand() % 101;
        litrosE = 100 + rand() % 101;

        cout << "Litros asignados de forma aleatoria:\n";
        cout << "Regular: " << litrosR << " litros\n";
        cout << "Premium: " << litrosP << " litros\n";
        cout << "EcoExtra: " << litrosE << " litros\n";
    }

    void agregarSurtidor(string codigo) {
        if (cantidadSurtidores < MaxSurtidores) {
            surtidores[cantidadSurtidores] = Surtidor(codigo);
            cantidadSurtidores++;
            cout << "Surtidor " << codigo << " agregado.\n";
        } else {
            cout << "No se puede agregar mas surtidores. Capacidad maxima alcanzada.\n";
        }
    }

    void eliminarSurtidor(string codigo) {
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

    void activarSurtidor(string codigo, bool activar) {
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

    void simularVenta() {
        if (cantidadSurtidores == 0) {
            cout << "No hay surtidores disponibles para la venta.\n";
            return;
        }
        // Seleccionar aleatoriamente un surtidor activo
        int surtidorElegido;
        do {
            surtidorElegido = rand() % cantidadSurtidores;
        } while (!surtidores[surtidorElegido].estaActivo());
        unsigned short int cantidad;
        cantidad = 3 + rand() % 18;
        char tipoCombustible;
        cout << "Simulando venta en surtidor " << surtidores[surtidorElegido].getCodigo() << endl;
        cout << "Ingrese el tipo de combustible (R para Regular, P para Premium, E para EcoExtra): ";
        cin >> tipoCombustible;
        surtidores[surtidorElegido].venta(cantidad, tipoCombustible, litrosR, litrosP, litrosE);
    }

    void mostrarLitrosRestantes() {
        cout << "Litros restantes en el tanque central:\n";
        cout << "Regular: " << litrosR << " litros\n";
        cout << "Premium: " << litrosP << " litros\n";
        cout << "EcoExtra: " << litrosE << " litros\n";
    }
};

int main() {
    estacionServ estacion("Estacion 1", "E001", "Juan Perez", "Centro");

    int opcion;
    string codigoSurtidor;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Activar surtidor\n";
        cout << "2. Desactivar surtidor\n";
        cout << "3. Agregar surtidor\n";
        cout << "4. Eliminar surtidor\n";
        cout << "5. Simular venta\n";
        cout << "6. Mostrar litros restantes\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        // Verificar si la opcion es valida
        if (opcion < 1 || opcion > 7){
            cout << "Opcion no valida. Por favor, ingrese un numero entre 1 y 7.\n";
            cin.clear();  // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada no válida
            continue;  // Volver a pedir la opcion
        }

        switch (opcion) {
        case 1:
            cout << "Ingrese el codigo del surtidor a activar: ";
            cin >> codigoSurtidor;
            estacion.activarSurtidor(codigoSurtidor, true);
            break;
        case 2:
            cout << "Ingrese el codigo del surtidor a desactivar: ";
            cin >> codigoSurtidor;
            estacion.activarSurtidor(codigoSurtidor, false);
            break;
        case 3:
            cout << "Ingrese el codigo del surtidor a agregar: ";
            cin >> codigoSurtidor;
            estacion.agregarSurtidor(codigoSurtidor);
            break;
        case 4:
            cout << "Ingrese el codigo del surtidor a eliminar: ";
            cin >> codigoSurtidor;
            estacion.eliminarSurtidor(codigoSurtidor);
            break;
        case 5:
            estacion.simularVenta();
            break;
        case 6:
            estacion.mostrarLitrosRestantes();
            break;
        case 7:
            cout << "Saliendo del programa...\n";
            return 0;
        }
    }

    return 0;
}