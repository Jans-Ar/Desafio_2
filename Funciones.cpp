#include "Funciones.h"
void copiar(int *origen, int *destino, int nDatos){
    for (int i = 0; i < nDatos; ++i) {
        *(destino+i) = *(origen+i);
    }
}

void eliminar(int *origen, int *destino, int nDatos, int codigoES){ //codigoES:codigo a eliminar
    for (int i = 0; i < nDatos; ++i) {
        if((*(origen+i))!=codigoES){
            *(destino+i) = *(origen+i);
        }
    }
}


bool validarCodigo(int *origen, int nDatos, int codigo){
    bool find=false;
    for (int i = 0; i < nDatos; ++i) {
        if((*(origen+i))==codigo){
            find=true;
        }
    }
    return find;
}

void imprimirEstaciones(EDS **estacion, int nES){
    for(int i=0 ; i<nES ; i++){
        separador();
        cout << "Codigo: " << estacion[i]->getCodigoES() << ", Nombre: " << estacion[i]->getNombre()
             << ", Gerente: " << estacion[i]->getGerente() << ", Region: " << estacion[i]->getRegion()
             << ", Ubicacion: " << estacion[i]->getUbicacion() << ", Tanque-Tarifa(R,P,E): " << *(estacion[i]->getCantidades()+0)
             << "L-$" << *(estacion[i]->getPrecios()+0) << ", " << *(estacion[i]->getCantidades()+1) << "L-$"
             << *(estacion[i]->getPrecios()+1) << ", " << *(estacion[i]->getCantidades()+2) << "L-$"
             << *(estacion[i]->getPrecios()+2) << ", Islas: " << estacion[i]->getIslas() << ", Surtidores: "
             << estacion[i]->getSurtidores() << ", litros vendidos(R,P,E): " << *(estacion[i]->getCantidadV()+0) << "L, "
             << *(estacion[i]->getCantidadV()+1) << "L, " << *(estacion[i]->getCantidadV()+2) << "L" << endl;

    }
    separador();
}

void separador(){
    for (int i=0 ; i<237 ; i++){
        cout << '-';
    }
    cout << endl;
}

void espacios(){
    for (int i=0 ; i<25 ; i++){
        cout << endl;
    }
}

void eliminarEstacion(EDS **estaciones, int nES, int codigoES)
{
    EDS **aux=nullptr; //puntero auxiliar
    aux= new EDS*[nES-2]; //le asigno un espacio de memoria menos 1
    int esc = 0;
    for (int i = 0 ; i < (nES-1) ; i++) {
            if((estaciones[i]->getCodigoES())!=codigoES){
                aux[esc] = new EDS(*estaciones[esc]);
                aux[esc]->setCodigoES(esc+1);
                esc++;
            }
    }
    //imprimirEstaciones(aux, nES-2);
    borrarPtr(estaciones, nES-1);
    estaciones = new EDS*[nES-1];
    estaciones[nES-2]=nullptr;
    for (int i = 0 ; i < (nES-2) ; i++) {
        estaciones[i] = new EDS(*aux[i]);
        //aux[i]->setCodigoES(i+1);
    }

    borrarPtr(aux,nES-2);
    aux=nullptr;
}

void borrarPtr(EDS **ptr, int n){
    for (int i = 0; i < n; i++) {
        delete ptr[i];  // Elimina cada objeto EDS
    }
    delete[] ptr;  // Elimina el arreglo de punteros
}

void copiarEstacion(EDS **origen, EDS **destino, int nES){
    for (int i = 0 ; i < nES ; i++) {
        destino[i] = new EDS(*origen[i]);
    }
}



void menu(){
    char fechaHora[20];
    obtenerFechaHora(fechaHora);

    cout << "Bienvenido a TerMax EDS! " << "Fecha y hora: " << fechaHora << endl;
    cout << "1. Crear EDS" << endl;
    cout << "2. Ver EDS" << endl;
    cout << "3. Elminar EDS" << endl;
    cout << "4. Calcular montos EDS" << endl;
    cout << "5. Modificar precios por region" << endl;
    cout << "6. salir" << endl;
    cout << "Ingrese una opcion: ";
}

void obtenerFechaHora(char* buffer) {
    using namespace std::chrono;
    const size_t bufferSize = 20;
    // Obtener la hora actual
    auto ahora = system_clock::now();
    std::time_t tiempoActual = system_clock::to_time_t(ahora);

    // Convertir a formato legible
    std::tm* tm = std::localtime(&tiempoActual);

    // Formatear y guardar en el buffer
    std::strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", tm);
}


