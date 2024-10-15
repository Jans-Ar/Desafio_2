#include <iostream>
#include <string>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <limits>
using namespace std;

// Clase Surtidor
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

// Clase estacionServ
class estacionServ {
private:
    string nombre;
    string identificador;
    string gerente;
    string region;

    static const short int MaxSurtidores = 12;
    Surtidor surtidores[MaxSurtidores];
    int cantidadSurtidores;

    int litrosR, litrosP, litrosE;

public:
    estacionServ(string nom, string ide, string ger, string reg) : nombre(nom), identificador(ide), gerente(ger), region(reg), cantidadSurtidores(0) {
        srand(time(0));
        LitrosTanqueCentral();
        agregarSurtidor("S1");
        agregarSurtidor("S2");
    }


    void LitrosTanqueCentral() {
        litrosR = 100 + rand() % 101;
        litrosP = 100 + rand() % 101;
        litrosE = 100 + rand() % 101;

        cout << "Litros asignados de forma aleatoria:\n";
        cout << "Regular: " << litrosR << " litros\n";
        cout << "Premium: " << litrosP << " litros\n";
        cout << "EcoExtra: " << litrosE << " litros\n";
    }

    string getNombre() const {
        return nombre;
    }

    string getIdentificador() const {
        return identificador;
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

        int surtidorElegido;
        do {
            surtidorElegido = rand() % cantidadSurtidores;
        } while (!surtidores[surtidorElegido].estaActivo());
        unsigned short int cantidad = 3 + rand() % 18;
        char tipoCombustible;
        cout << "Simulando venta en surtidor " << surtidores[surtidorElegido].getCodigo() << endl;
        cout << "Ingrese el tipo de combustible (R para Regular, P para Premium, E para EcoExtra): ";
        cin >> tipoCombustible;
        surtidores[surtidorElegido].venta(cantidad, tipoCombustible, litrosR, litrosP, litrosE);
    }

    void mostrarLitrosRestantes() const {
        cout << "Litros restantes en el tanque central:\n";
        cout << "Regular: " << litrosR << " litros\n";
        cout << "Premium: " << litrosP << " litros\n";
        cout << "EcoExtra: " << litrosE << " litros\n";
    }
};

// Clase TerMax
class TerMax {
private:
    estacionServ** estaciones;
    int numEstaciones;
    int capacidadMaxima;
    float precioNorte, precioSur, precioCentro;

    void redimensionarEstaciones() {
        int nuevaCapacidad = capacidadMaxima * 2;
        estacionServ** nuevoArreglo = new estacionServ*[nuevaCapacidad];

        for (int i = 0; i < numEstaciones; i++) {
            nuevoArreglo[i] = estaciones[i];
        }

        delete[] estaciones;
        estaciones = nuevoArreglo;
        capacidadMaxima = nuevaCapacidad;
    }

public:
    TerMax() : numEstaciones(0), capacidadMaxima(3), precioNorte(0.0), precioSur(0.0), precioCentro(0.0) {
        estaciones = new estacionServ*[capacidadMaxima];
        agregarEstacion(new estacionServ("Estacion 1", "E001", "Gerente 1", "Norte"));
        agregarEstacion(new estacionServ("Estacion 2", "E002", "Gerente 2", "Sur"));
        agregarEstacion(new estacionServ("Estacion 3", "E003", "Gerente 3", "Centro"));
    }

    friend class EstacionServ;
    friend class Surtidor;

    ~TerMax() {
        for (int i = 0; i < numEstaciones; i++) {
            delete estaciones[i];
        }
        delete[] estaciones;
    }

    void agregarEstacion(estacionServ* nuevaEstacion) {
        if (numEstaciones == capacidadMaxima) {
            redimensionarEstaciones();
        }
        estaciones[numEstaciones++] = nuevaEstacion;
        cout << "Estacion agregada: " << nuevaEstacion->getNombre() << "\n"<< endl;
    }

    void eliminarEstacion(string id) {
        for (int i = 0; i < numEstaciones; i++) {
            if (estaciones[i]->getIdentificador() == id) {
                delete estaciones[i];
                for (int j = i; j < numEstaciones - 1; j++) {
                    estaciones[j] = estaciones[j + 1];
                }
                numEstaciones--;
                cout << "Estacion con ID " << id << " eliminada.\n";
                return;
            }
        }
        cout << "Estacion con ID " << id << " no encontrada.\n";
    }

    void establecerPrecioNorte(float precio) {
        precioNorte = precio;
        cout << "Precio para la region Norte establecido en: " << precio << endl;
    }

    void establecerPrecioSur(float precio) {
        precioSur = precio;
        cout << "Precio para la region Sur establecido en: " << precio << endl;
    }

    void establecerPrecioCentro(float precio) {
        precioCentro = precio;
        cout << "Precio para la region Centro establecido en: " << precio << endl;
    }

    void mostrarEstaciones() const {
        cout << "Estaciones en la red TerMax:\n";
        for (int i = 0; i < numEstaciones; i++) {
            cout << estaciones[i]->getNombre() << " (ID: " << estaciones[i]->getIdentificador() << ")\n";
        }
    }

    void activarSurtidor(string idEstacion, string codigoSurtidor) {
        for (int i = 0; i < numEstaciones; i++) {
            if (estaciones[i]->getIdentificador() == idEstacion) {
                estaciones[i]->activarSurtidor(codigoSurtidor, true);
                return;
            }
        }
        cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
    }

    void desactivarSurtidor(string idEstacion, string codigoSurtidor) {
        for (int i = 0; i < numEstaciones; i++) {
            if (estaciones[i]->getIdentificador() == idEstacion) {
                estaciones[i]->activarSurtidor(codigoSurtidor, false);
                return;
            }
        }
        cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
    }

    void agregarSurtidor(string idEstacion, string codigoSurtidor) {
        for (int i = 0; i < numEstaciones; i++) {
            if (estaciones[i]->getIdentificador() == idEstacion) {
                estaciones[i]->agregarSurtidor(codigoSurtidor);
                return;
            }
        }
        cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
    }

    void eliminarSurtidor(string idEstacion, string codigoSurtidor) {
        for (int i = 0; i < numEstaciones; i++) {
            if (estaciones[i]->getIdentificador() == idEstacion) {
                estaciones[i]->eliminarSurtidor(codigoSurtidor);
                return;
            }
        }
        cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
    }

    void mostrarLitrosRestantes() {
        for (int i = 0; i < numEstaciones; i++) {
            cout << "Estación: " << estaciones[i]->getNombre() << endl;
            estaciones[i]->mostrarLitrosRestantes();  // Llamada al método de estacionServ
        }
    }

    void simularVenta() {
        for (int i = 0; i < numEstaciones; i++) {
            cout << "Simulando venta en la estación: " << estaciones[i]->getNombre() << endl;
            estaciones[i]->simularVenta();  // Llamada al método de estacionServ
        }
    }
};

// Menu principal
void mostrarMenu() {
    cout << "----- Menu TerMax -----\n";
    cout << "1. Mostrar estaciones\n";
    cout << "2. Agregar estacion\n";
    cout << "3. Eliminar estacion\n";
    cout << "4. Establecer precio Norte\n";
    cout << "5. Establecer precio Sur\n";
    cout << "6. Establecer precio Centro\n";
    cout << "7. Simular venta\n";
    cout << "8. Mostrar litros restantes\n";
    cout << "9. Activar surtidor\n";
    cout << "10. Desactivar surtidor\n";
    cout << "11. Agregar surtidor\n";
    cout << "12. Eliminar surtidor\n";
    cout << "13. Salir\n";
    cout << "Ingrese una opcion: ";
}

int main() {
    TerMax redNacional;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cout << "\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer de entrada

        switch (opcion) {
        case 1:
            redNacional.mostrarEstaciones();
            break;

        case 2: {
            string nombre, id, gerente, region;
            cout << "Ingrese el nombre de la nueva estacion: ";
            getline(cin, nombre);
            cout << "Ingrese el ID de la nueva estacion: ";
            getline(cin, id);
            cout << "Ingrese el nombre del gerente: ";
            getline(cin, gerente);
            cout << "Ingrese la region (Norte/Sur/Centro): ";
            getline(cin, region);
            cout << "\n";
            redNacional.agregarEstacion(new estacionServ(nombre, id, gerente, region));
            break;
        }

        case 3: {
            string id;
            cout << "Ingrese el ID de la estacion a eliminar: ";
            getline(cin, id);
            cout << "\n";
            redNacional.eliminarEstacion(id);
            break;
        }

        case 4: {
            float precio;
            cout << "Ingrese el nuevo precio para la region Norte: ";
            cin >> precio;
            cout << "\n";
            redNacional.establecerPrecioNorte(precio);
            break;
        }

        case 5: {
            float precio;
            cout << "Ingrese el nuevo precio para la region Sur: ";
            cin >> precio;
            cout << "\n";
            redNacional.establecerPrecioSur(precio);
            break;
        }

        case 6: {
            float precio;
            cout << "Ingrese el nuevo precio para la region Centro: ";
            cin >> precio;
            cout << "\n";
            redNacional.establecerPrecioCentro(precio);
            break;
        }

        case 7:
            redNacional.simularVenta();
            break;

        case 8:
            redNacional.mostrarLitrosRestantes();
            break;

        case 9: {
            string idEstacion, codigoSurtidor;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);
            cout << "Ingrese el codigo del surtidor a activar: ";
            getline(cin, codigoSurtidor);
            cout << "\n";
            redNacional.activarSurtidor(idEstacion, codigoSurtidor);
            break;
        }

        case 10: {
            string idEstacion, codigoSurtidor;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);
            cout << "Ingrese el codigo del surtidor a desactivar: ";
            getline(cin, codigoSurtidor);
            cout << "\n";
            redNacional.desactivarSurtidor(idEstacion, codigoSurtidor);
            break;
        }

        case 11: {
            string idEstacion, codigoSurtidor;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);
            cout << "Ingrese el codigo del surtidor a agregar: ";
            getline(cin, codigoSurtidor);
            cout << "\n";
            redNacional.agregarSurtidor(idEstacion, codigoSurtidor);
            break;
        }

        case 12: {
            string idEstacion, codigoSurtidor;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);
            cout << "Ingrese el codigo del surtidor a eliminar: ";
            getline(cin, codigoSurtidor);
            cout << "\n";
            redNacional.eliminarSurtidor(idEstacion, codigoSurtidor);
            break;
        }

        case 13:
            cout << "Saliendo del programa...\n";
            break;

        default:
            cout << "Opcion no valida.\n";
            break;
        }

        cout << endl;
    } while (opcion != 13);

    return 0;
}
