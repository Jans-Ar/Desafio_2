#include <iostream>
#include <string>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <limits>
using namespace std;

//Se incluyen las clases
#include <surtidor.h>
#include <estacionserv.h>
#include <termax.h>

void mostrarMenu() {
    cout << "----- Menu TerMax -----\n";
    cout << "1. Mostrar estaciones\n";
    cout << "2. Agregar estacion\n";
    cout << "3. Eliminar estacion\n";
    cout << "4. Establecer precios\n";
    cout << "5. Simular venta\n";
    cout << "6. Mostrar litros vendidos por estacion\n";
    cout << "7. Activar surtidor\n";
    cout << "8. Desactivar surtidor\n";
    cout << "9. Agregar surtidor\n";
    cout << "10. Eliminar surtidor\n";
    cout << "11. Mostrar precios de una region\n";
    cout << "12. Verificar Fugas\n";
    cout << "13. Mostrar los litros restantes\n";
    cout << "14. Monto total de las ventas en una estacion de servicio\n";
    cout << "15. Salir\n";
    cout << "Ingrese una opcion: ";
}

int main() {
    srand(time(0));
    TerMax TerMax1;
    int opcion;

    do {
        mostrarMenu();
        // Validación de entrada
        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Por favor, ingrese un numero entero.\n";
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada incorrecta
            cout << "\n";
            continue; // Volver a mostrar el menú
        }
        cout << "\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer de entrada

        switch (opcion) {

        case 1:
            TerMax1.mostrarEstaciones();
            break;
        case 2: {
            string nombre, id, gerente, region;
            cout << "Ingrese el nombre de la nueva estacion: ";
            getline(cin, nombre);
            cout << "Ingrese el ID de la nueva estacion: ";
            getline(cin, id);
            bool idExiste = false;
            for (int i = 0; i < TerMax1.getNumEstaciones(); i++) {
                if (TerMax1.getEstacion(i)->getIdentificador() == id) {
                    idExiste = true;
                    cout << "La estacion con el codigo " << TerMax1.getEstacion(i)->getIdentificador() << " no se puede agregar de nuevo.\n";
                    break;
                }
            }

            if (idExiste) {
                break;
            }

            cout << "Ingrese el nombre del gerente: ";
            getline(cin, gerente);
            cout << "Ingrese la region (Norte/Sur/Centro): ";
            getline(cin, region);
            cout << "\n";
            TerMax1.agregarEstacion(new estacionServ(nombre, id, gerente, region));
            break;
        }

        case 3: {
            string id, codigoSurtidor;
            cout << "Ingrese el ID de la estacion a eliminar: ";
            getline(cin, id);
            cout << "\n";
            TerMax1.eliminarEstacion(id);
            break;
        }


        case 4: {

            string region;
            int tipoCombustible;
            float precio;
            cout << "Ingrese la region (Norte, Sur, Centro): ";
            getline(cin, region);
            cout << "Seleccione el tipo de combustible (0 para Regular, 1 para Premium, 2 para EcoExtra): ";
            cin >> tipoCombustible;
            cout << "Ingrese el nuevo precio: ";
            cin >> precio;
            cout << "\n";
            TerMax1.establecerPrecioRegion(region, tipoCombustible, precio);

            break;
        }

        case 5: {
            string idEstacion;
            cout << "Ingrese el ID de la estacion donde desea simular la venta: ";
            getline(cin, idEstacion);
            cout << "\n"      ;

            bool estacionEncontrada = false;
            for (int i = 0; i < TerMax1.getNumEstaciones(); i++) {
                if (TerMax1.getEstacion(i)->getIdentificador() == idEstacion) {
                    estacionEncontrada = true;
                    cout << "Simulando venta en la estacion: " << TerMax1.getEstacion(i)->getNombre() << endl;
                    if (TerMax1.getEstacion(i)->getRegion() == "Norte") {
                        TerMax1.getEstacion(i)->simularVenta(TerMax1.getPreciosNorte());
                    } else if (TerMax1.getEstacion(i)->getRegion() == "Sur") {
                        TerMax1.getEstacion(i)->simularVenta(TerMax1.getPreciosSur());
                    } else if (TerMax1.getEstacion(i)->getRegion() == "Centro") {
                        TerMax1.getEstacion(i)->simularVenta(TerMax1.getPreciosCentro());
                    }
                    break;
                }
            }

            if (!estacionEncontrada) {
                cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
            }
            break;
        }
        case 6: {
            string idEstacion;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);

            bool estacionEncontrada = false;
            for (int i = 0; i < TerMax1.getNumEstaciones(); i++) {
                if (TerMax1.getEstacion(i)->getIdentificador() == idEstacion) {
                    estacionEncontrada = true;
                    cout << "Litros vendidos en la estacion " << TerMax1.getEstacion(i)->getNombre() << ":\n";
                    cout << "Regular: " << TerMax1.getEstacion(i)->getLitrosVendidosR() << " litros\n";
                    cout << "Premium: " << TerMax1.getEstacion(i)->getLitrosVendidosP() << " litros\n";
                    cout << "EcoExtra: " << TerMax1.getEstacion(i)->getLitrosVendidosE() << " litros\n";
                    break;
                }
            }
            if (!estacionEncontrada) {
                cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
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
            TerMax1.activarSurtidor(idEstacion, codigoSurtidor);
            break;
        }

        case 8: {
            string idEstacion, codigoSurtidor;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);
            cout << "Ingrese el codigo del surtidor a desactivar: ";
            getline(cin, codigoSurtidor);
            cout << "\n";
            TerMax1.desactivarSurtidor(idEstacion, codigoSurtidor);
            break;
        }

        case 9: {
            string idEstacion, codigoSurtidor;
            bool Existe;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);
            cout << "Ingrese el codigo del surtidor a agregar: ";
            getline(cin, codigoSurtidor);
            Existe = TerMax1.surtidorExiste(idEstacion, codigoSurtidor);
            if(Existe){
                cout << "El codigo del surtidor ya existe.\n";
                break;
            }
            else{
                cout << "\n";
                TerMax1.agregarSurtidor(idEstacion, codigoSurtidor);
                break;
            }
        }

        case 10: {
            string idEstacion, codigoSurtidor;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);
            cout << "Ingrese el codigo del surtidor a eliminar: ";
            getline(cin, codigoSurtidor);
            cout << "\n";
            TerMax1.eliminarSurtidor(idEstacion, codigoSurtidor);
            break;
        }

        case 11:{
            string Region;
            cout << "Ingrese la region (Norte, Centro, Sur):";
            getline(cin, Region);
            TerMax1.mostrarPreciosRegion(Region);
            break;
        }
        case 12:
            TerMax1.verificarFugas();
            break;
        case 13:
            TerMax1.mostrarLitrosRestantes();
            break;
        case 14:{
            string idEstacion;
            cout << "Ingrese el ID de la estacion: ";
            getline(cin, idEstacion);
            cout << "\n";
            bool estacionEncontrada = false;
            for (int i = 0; i < TerMax1.getNumEstaciones(); i++) {
                if (TerMax1.getEstacion(i)->getIdentificador() == idEstacion) {
                    estacionEncontrada = true;
                    TerMax1.getEstacion(i)->mostrarVentas();
                }
            }
            if (!estacionEncontrada) {
                cout << "Estacion con ID " << idEstacion << " no encontrada.\n";
            }
        }
        break;
        case 15:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
        }
        cout << endl;
    } while (opcion != 15);

    return 0;
}
