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
    string region;

public:
   Surtidor() : codigoSurtidor(""), activo(false), region("") {}
    Surtidor(string C, string reg) : codigoSurtidor(C), activo(true), region(reg) {}

    string getCodigo() {
        return codigoSurtidor;
    }

    bool estaActivo() {
        return activo;
    }
    
    int getRegionIndex() const {
        if (region == "Norte") return 0;
        else if (region == "Sur") return 1;
        else if (region == "Centro") return 2;
        return -1;  // Región no válida
    }

    void activar() {
        activo = true;
        cout << "Surtidor " << codigoSurtidor << " activado." << endl;
    }

    void desactivar() {
        activo = false;
        cout << "Surtidor " << codigoSurtidor << " desactivado." << endl;
    }

     void venta(int cantidad, char tipoCombustible, int &litrosR, int &litrosP, int &litrosE, int &vendidosR, int &vendidosP, int &vendidosE, float &costo, const float preciosRegiones[3][3]) {
    int tipoCombustibleIndex;
    if (tipoCombustible == 'R') tipoCombustibleIndex = 0;
    else if (tipoCombustible == 'P') tipoCombustibleIndex = 1;
    else if (tipoCombustible == 'E') tipoCombustibleIndex = 2;
    else {
        cout << "Tipo de combustible no valido." << endl;
        return;
    }

    // Calcular litros disponibles
    int &litrosDisponibles = (tipoCombustible == 'R') ? litrosR : (tipoCombustible == 'P') ? litrosP : litrosE;
    int litrosAUsar = min(litrosDisponibles, cantidad); // Usar lo que haya disponible

    // Calcular costo
    costo += litrosAUsar * preciosRegiones[getRegionIndex()][tipoCombustibleIndex];

    // Actualizar litros vendidos
    if (tipoCombustible == 'R') {
        vendidosR += litrosAUsar;
    } else if (tipoCombustible == 'P') {
        vendidosP += litrosAUsar;
    } else if (tipoCombustible == 'E') {
        vendidosE += litrosAUsar;
    }

    // Actualizar litros restantes
    litrosDisponibles -= litrosAUsar; // Actualiza litros restantes

    cout << "Venta realizada de " << litrosAUsar << " litros de " << tipoCombustible << "." << endl;
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
    int litrosVendidosR;
    int litrosVendidosP;
    int litrosVendidosE;

    int litrosR, litrosP, litrosE;

    // Arreglos para precios de combustible por tipo
    float preciosRegiones[3][3];  // [0] Norte, [1] Sur, [2] Centro

public:
    estacionServ(string nom, string ide, string ger, string reg) : nombre(nom), identificador(ide), gerente(ger), region(reg), cantidadSurtidores(0) {
        srand(time(0));
        LitrosTanqueCentral();
        agregarSurtidor("S1");
        agregarSurtidor("S2");
        litrosVendidosR = 0;
        litrosVendidosP = 0;
        litrosVendidosE = 0;

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
    int getLitrosVendidosR() const {
    return litrosVendidosR;
    }

    int getLitrosVendidosP() const {
    return litrosVendidosP;
    }

    int getLitrosVendidosE() const {
    return litrosVendidosE;
    }


    void agregarSurtidor(string codigo) {
    if (cantidadSurtidores < MaxSurtidores) {
        surtidores[cantidadSurtidores] = Surtidor(codigo, region); // Asegúrate de pasar la región
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

    unsigned short int cantidad = 3 + rand() % 18; // Genera una cantidad aleatoria
    char tipoCombustible;
    cout << "Simulando venta en surtidor " << surtidores[surtidorElegido].getCodigo() << endl;
    cout << "Ingrese el tipo de combustible (R para Regular, P para Premium, E para EcoExtra): ";
    cin >> tipoCombustible;

    float costo = 0.0;  // Inicializa costo
    int litrosVendidosR = 0, litrosVendidosP = 0, litrosVendidosE = 0;

    // Llama a la función de venta
    surtidores[surtidorElegido].venta(cantidad, tipoCombustible, litrosR, litrosP, litrosE, litrosVendidosR, litrosVendidosP, litrosVendidosE, costo, preciosRegiones);

    // Imprimir el costo total de la venta
    cout << "Costo total de la venta: " << costo << endl;
}





    void establecerPrecio(float precio, int region, int tipoCombustible) {
        preciosRegiones[region][tipoCombustible] = precio;
    }

    void mostrarPrecios() const {
        const string nombresRegiones[] = {"Norte", "Sur", "Centro"};
        const string tiposCombustible[] = {"Regular", "Premium", "EcoExtra"};
        for (int i = 0; i < 3; i++) {
            cout << "Precios para la region " << nombresRegiones[i] << ":\n";
            for (int j = 0; j < 3; j++) {
                cout << "  " << tiposCombustible[j] << ": " << preciosRegiones[i][j] << endl;
            }
        }
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

    float preciosNorte[3];  // Precios para Regular, Premium y EcoExtra en Norte
    float preciosSur[3];    // Precios para Regular, Premium y EcoExtra en Sur
    float preciosCentro[3]; // Precios para Regular, Premium y EcoExtra en Centro

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
    int getNumEstaciones() const {
        return numEstaciones;
    }

    estacionServ* getEstacion(int index) const {
        if (index >= 0 && index < numEstaciones) {
            return estaciones[index];
        }
        return nullptr;  // Retorna nullptr si el índice es inválido
    }
    TerMax() : numEstaciones(0), capacidadMaxima(3) {
        estaciones = new estacionServ*[capacidadMaxima];


        // Inicializamos los precios de cada tipo de combustible en cada región
        for (int i = 0; i < 3; i++) {
            preciosNorte[i] = 0.0;
            preciosSur[i] = 0.0;
            preciosCentro[i] = 0.0;
        }

        agregarEstacion(new estacionServ("Estacion 1", "E001", "Gerente 1", "Norte"));
        agregarEstacion(new estacionServ("Estacion 2", "E002", "Gerente 2", "Sur"));
        agregarEstacion(new estacionServ("Estacion 3", "E003", "Gerente 3", "Centro"));
    }

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
        cout << "Estacion agregada: " << nuevaEstacion->getNombre() <<"\n"<< endl;
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
    };

    void establecerPrecioRegion(string region, int tipoCombustible, float precio) {
         if (region == "Norte") {
                preciosNorte[tipoCombustible] = precio;
                cout << "Precio de " << obtenerNombreCombustible(tipoCombustible) << " en la región Norte establecido en: " << precio << endl;
            } else if (region == "Sur") {
                preciosSur[tipoCombustible] = precio;
                cout << "Precio de " << obtenerNombreCombustible(tipoCombustible) << " en la región Sur establecido en: " << precio << endl;
            } else if (region == "Centro") {
                preciosCentro[tipoCombustible] = precio;
                cout << "Precio de " << obtenerNombreCombustible(tipoCombustible) << " en la región Centro establecido en: " << precio << endl;
            } else {
                cout << "Región no válida." << endl;
            }
    }

    void mostrarPreciosRegion(string region) {
            if (region == "Norte") {
                cout << "Precios en la región Norte:\n";
                for (int i = 0; i < 3; i++) {
                    cout << obtenerNombreCombustible(i) << ": " << preciosNorte[i] << " por litro\n";
                }
            } else if (region == "Sur") {
                cout << "Precios en la región Sur:\n";
                for (int i = 0; i < 3; i++) {
                    cout << obtenerNombreCombustible(i) << ": " << preciosSur[i] << " por litro\n";
                }
            } else if (region == "Centro") {
                cout << "Precios en la región Centro:\n";
                for (int i = 0; i < 3; i++) {
                    cout << obtenerNombreCombustible(i) << ": " << preciosCentro[i] << " por litro\n";
                }
            } else {
                cout << "Región no válida." << endl;
            }
    }

    string obtenerNombreCombustible(int tipo) {
            switch (tipo) {
            case 0: return "Regular";
            case 1: return "Premium";
            case 2: return "EcoExtra";
            default: return "Desconocido";
            }
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
        cout << "4. Establecer precios\n";
        cout << "5. Simular venta\n";
        cout << "6. Mostrar litros vendidos por estación\n";
        cout << "7. Activar surtidor\n";
        cout << "8. Desactivar surtidor\n";
        cout << "9. Agregar surtidor\n";
        cout << "10. Eliminar surtidor\n";
        cout << "11. Salir\n";
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
                string region;
                int tipoCombustible;
                float precio;
                cout << "Ingrese la región (Norte, Sur, Centro): ";
                getline(cin, region);
                cout << "Seleccione el tipo de combustible (0 para Regular, 1 para Premium, 2 para EcoExtra): ";
                cin >> tipoCombustible;
                cout << "Ingrese el nuevo precio: ";
                cin >> precio;
                cout << "\n";
                redNacional.establecerPrecioRegion(region, tipoCombustible, precio);
                break;
            }
            
            case 5: {
                string idEstacion;
                cout << "Ingrese el ID de la estación donde desea simular la venta: ";
                getline(cin, idEstacion);
                cout << "\n";
                
                bool estacionEncontrada = false;
                for (int i = 0; i < redNacional.getNumEstaciones(); i++) {
                    if (redNacional.getEstacion(i)->getIdentificador() == idEstacion) {
                        estacionEncontrada = true;
                        cout << "Simulando venta en la estación: " << redNacional.getEstacion(i)->getNombre() << endl;
                        redNacional.getEstacion(i)->simularVenta();  // Llamada al método de estacionServ
                        break;
                    }
                }

                if (!estacionEncontrada) {
                    cout << "Estación con ID " << idEstacion << " no encontrada.\n";
                }
                break;
            }
            /*case 6:
                redNacional.mostrarLitrosRestantes();
                break;*/
            case 6: {
              string idEstacion;
              cout << "Ingrese el ID de la estación: ";
              getline(cin, idEstacion);

              bool estacionEncontrada = false;
              for (int i = 0; i < redNacional.getNumEstaciones(); i++) {
                  if (redNacional.getEstacion(i)->getIdentificador() == idEstacion) {
                   estacionEncontrada = true;
                  // Aquí deberías tener métodos para obtener los litros vendidos
                  // Suponiendo que tienes variables litrosVendidosR, litrosVendidosP, litrosVendidosE en estacionServ
                  cout << "Litros vendidos en la estación " << redNacional.getEstacion(i)->getNombre() << ":\n";
                 cout << "Regular: " << redNacional.getEstacion(i)->getLitrosVendidosR() << " litros\n";
                 cout << "Premium: " << redNacional.getEstacion(i)->getLitrosVendidosP() << " litros\n";
                 cout << "EcoExtra: " << redNacional.getEstacion(i)->getLitrosVendidosE() << " litros\n";
                  break;
                 }
    }
            

             if (!estacionEncontrada) {
              cout << "Estación con ID " << idEstacion << " no encontrada.\n";
        }
    break;
    }


            case 7: {
                string idEstacion, codigoSurtidor;
                cout << "Ingrese el ID de la estacion: ";
                getline(cin, idEstacion);
                cout << "Ingrese el codigo del surtidor a activar: ";
                getline(cin, codigoSurtidor);
                cout << "\n";
                redNacional.activarSurtidor(idEstacion, codigoSurtidor);
                break;
            }

            case 8: {
                string idEstacion, codigoSurtidor;
                cout << "Ingrese el ID de la estacion: ";
                getline(cin, idEstacion);
                cout << "Ingrese el codigo del surtidor a desactivar: ";
                getline(cin, codigoSurtidor);
                cout << "\n";
                redNacional.desactivarSurtidor(idEstacion, codigoSurtidor);
                break;
            }

            case 9: {
                string idEstacion, codigoSurtidor;
                cout << "Ingrese el ID de la estacion: ";
                getline(cin, idEstacion);
                cout << "Ingrese el codigo del surtidor a agregar: ";
                getline(cin, codigoSurtidor);
                cout << "\n";
                redNacional.agregarSurtidor(idEstacion, codigoSurtidor);
                break;
            }

            case 10: {
                string idEstacion, codigoSurtidor;
                cout << "Ingrese el ID de la estacion: ";
                getline(cin, idEstacion);
                cout << "Ingrese el codigo del surtidor a eliminar: ";
                getline(cin, codigoSurtidor);
                cout << "\n";
                redNacional.eliminarSurtidor(idEstacion, codigoSurtidor);
                break;
            }

            case 11:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida.\n";
                break;
            }

            cout << endl;
        } while (opcion != 11);

        return 0;
    }
