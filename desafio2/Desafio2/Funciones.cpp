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

void imprimirEstaciones(EDS **estacion){
    cout << "Nombre: " << estacion[0]->getNombre()<<endl;
    cout << "Codigo: " << estacion[0]->getCodigoES()<<endl;
    cout << "Gerente: " << estacion[0]->getGerente()<<endl;
    cout << "Nombre: " << estacion[1]->getNombre()<<endl;
    cout << "Codigo: " << estacion[1]->getCodigoES()<<endl;
    cout << "Gerente: " << estacion[1]->getGerente()<<endl;
}
