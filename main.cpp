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

    void activar() {
        activo = true;
        cout << "Surtidor " << codigoSurtidor << " activado." << endl;
    }

    void desactivar() {
        activo = false;
        cout << "Surtidor " << codigoSurtidor << " desactivado." << endl;
    }

    void venta(int cantidad, char tipoCombustible, int &litrosR, int &litrosP, int &litrosE,
               short unsigned int &vendidosR, short unsigned int &vendidosP, short unsigned int &vendidosE, float &costo,
               const float preciosR[3]) {

        int tipoCombustibleI;
        if (tipoCombustible == 'R') tipoCombustibleI = 0;
        else if (tipoCombustible == 'P') tipoCombustibleI = 1;
        else if (tipoCombustible == 'E') tipoCombustibleI= 2;
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
        } else if (tipoCombustible == 'P') {
            vendidosP += litrosAUsar;
        } else if (tipoCombustible == 'E') {
            vendidosE += litrosAUsar;
        }

        // Actualizar litros restantes
        litrosDisponibles -= litrosAUsar; // Actualiza litros restantes

        cout << "Venta realizada de " << litrosAUsar << " litros de " << tipoCombustible << "." << endl;
        cout << "Costo total de la venta: " << costo << endl;
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
    unsigned short int cantidadSurtidores;
    unsigned short int litrosVendidosR = 0;
    unsigned short int litrosVendidosP = 0;
    unsigned short int litrosVendidosE = 0;

    int litrosR, litrosP, litrosE, litrosInicialR, litrosInicialP, litrosInicialE;


    float preciosRegion[3];  // [0] Norte, [1] Sur, [2] Centro

public:
    estacionServ(string nom, string ide, string ger, string reg) : nombre(nom), identificador(ide), gerente(ger), region(reg), cantidadSurtidores(0) {
        srand(time(0));
        LitrosTanqueCentral();
        agregarSurtidor("S1");
        agregarSurtidor("S2");
    }

    void LitrosTanqueCentral() {
        litrosInicialR = litrosR = 100 + rand() % 101;
        litrosInicialP = litrosP = 100 + rand() % 101;
        litrosInicialE = litrosE = 100 + rand() % 101;

        cout << "Litros asignados de forma aleatoria:\n";
        cout << "Regular: " << litrosR << " litros\n";
        cout << "Premium: " << litrosP << " litros\n";
        cout << "EcoExtra: " << litrosE << " litros\n";
    }

    string getNombre() const {
        return nombre;
    }
    string getGerente() const {
        return gerente;
    }

    string getRegion() const {
        return region;
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
    int getLitrosR() const {
        return litrosR;
    }

    int getLitrosP() const {
        return litrosP;
    }

    int getLitrosE() const {
        return litrosE;
    }
    int getCantidadSurtidores() const {
        return cantidadSurtidores;
    }
    int getLitrosInicialR() const {
        return litrosInicialR;
    }

    int getLitrosInicialP() const {
        return litrosInicialP;
    }

    int getLitrosInicialE() const {
        return litrosInicialE;
    }
    bool surtidorExiste(string codigo) {
        for (int i = 0; i < MaxSurtidores; i++) {
            if (surtidores[i].getCodigo() == codigo) {
                return true;
            }
        }
        return false;
    }

    bool surtidorestaActivo() {
        for (int i = 0; i < MaxSurtidores; i++) {
            if (surtidores[i].estaActivo()) {
                return true;
            }
        }
        return false;
    }

    void agregarSurtidor(string codigo) {
        if (cantidadSurtidores < MaxSurtidores) {
            surtidores[cantidadSurtidores] = Surtidor(codigo, region);
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

    void simularVenta(float* PreciosR) {
        if (cantidadSurtidores == 0) {
            cout << "No hay surtidores disponibles para la venta.\n";
            return;
        }
        if(surtidorestaActivo() == false){
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
        surtidores[surtidorElegido].venta(cantidad, tipoCombustible, litrosR, litrosP, litrosE,  litrosVendidosR, litrosVendidosP, litrosVendidosE, costo, PreciosR);
    }

    void mostrarLitrosRestantes() const {
        cout << "Litros restantes en el tanque central:\n";
        cout << "Regular: " << litrosR << " litros\n";
        cout << "Premium: " << litrosP << " litros\n";
        cout << "EcoExtra: " << litrosE << " litros\n";
        cout << "\n" ;
    }

};

// Clase TerMax
class TerMax {
private:
    estacionServ** estaciones;
    unsigned short int numEstaciones;
    unsigned short int capacidadMaxima;

    float preciosNorte[3];  // Precios para Regular, Premium y EcoExtra en Norte
    float preciosSur[3];    // Precios para Regular, Premium y EcoExtra en Sur
    float preciosCentro[3]; // Precios para Regular, Premium y EcoExtra en Centro

    void redimensionarEstaciones() {
        unsigned short int nuevaCapacidad = capacidadMaxima * 2;
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

    float* getPreciosNorte() {
        return preciosNorte; // Devuelve un puntero al primer elemento
    }
    float* getPreciosSur() {
        return preciosSur;
    }
    float* getPreciosCentro() {
        return preciosCentro;
    }


    estacionServ* getEstacion(int index) const {
        if (index >= 0 && index < numEstaciones) {
            return estaciones[index];
        }
        return nullptr;  // Retorna nullptr si el índice es invalido
    }
    TerMax() : numEstaciones(0), capacidadMaxima(3) {
        estaciones = new estacionServ*[capacidadMaxima];

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
                if (estaciones[i]->surtidorestaActivo()){
                    cout << "La estacion no puede ser eliminada porque tiene surtidores activos. \n";
                    return;
                }
                else {
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

    void establecerPrecioRegion(string region, int tipoCombustible, float precio) {
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

    void mostrarPreciosRegion(string region) {
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
            cout << "Nombre: " << estaciones[i]->getNombre() << endl;
            cout << "ID: " << estaciones[i]->getIdentificador() << endl;
            cout << "Gerente: " << estaciones[i]->getGerente() << endl;
            cout << "Region: " << estaciones[i]->getRegion() << endl;
            cout << "---------------------\n";
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
            cout << "Estacion: " << estaciones[i]->getNombre() << endl;
            estaciones[i]->mostrarLitrosRestantes();  // Llamada al método de estacionServ
        }
    }

    bool surtidorExiste(string idEstacion, string codigoSurtidor) {
        for (int i = 0; i < numEstaciones; i++) {
            if (estaciones[i]->getIdentificador() == idEstacion) {
                if(estaciones[i]->surtidorExiste(codigoSurtidor) == true){
                    return true;
                }
            }
        }
        return false;
    }
    void verificarFugas() {
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

            // Calculamos el total restante más el vendido para cada tipo de combustible
            float totalRegular = litrosR + litrosVendidosR;
            float totalPremium = litrosP + litrosVendidosP;
            float totalEcoExtra = litrosE + litrosVendidosE;

            // Comprobamos si es al menos el 95% de los litros iniciales
            bool fugaRegular = totalRegular < 0.95 * litrosInicialR;
            bool fugaPremium = totalPremium < 0.95 * litrosInicialP;
            bool fugaEcoExtra = totalEcoExtra < 0.95 * litrosInicialE;


            // Imprimimos resultados
            cout << "Verificacion de fugas para estacion:"<< estaciones[i]->getNombre() << ".\n";
            ;
            cout << "Regular: " << (fugaRegular ? "FUGA DETECTADA" : "SIN FUGA.") << endl;
            cout << "Premium: " << (fugaPremium ? "FUGA DETECTADA" : "SIN FUGA.") << endl;
            cout << "EcoExtra: " << (fugaEcoExtra ? "FUGA DETECTADA" : "SIN FUGA.\n") << endl;
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
    cout << "6. Mostrar litros vendidos por estacion\n";
    cout << "7. Activar surtidor\n";
    cout << "8. Desactivar surtidor\n";
    cout << "9. Agregar surtidor\n";
    cout << "10. Eliminar surtidor\n";
    cout << "11. Mostrar precios de una region\n";
    cout << "12. Verificar Fugas\n";
    cout << "13. Mostrar los litros restantes\n";
    cout << "14. Salir\n";
    cout << "Ingrese una opcion: ";
}


int main() {
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
        case 14:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
        }
        cout << endl;
    } while (opcion != 14);

    return 0;
}