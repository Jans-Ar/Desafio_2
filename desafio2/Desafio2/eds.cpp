#include "eds.h"
#include <iostream>
using namespace std;

int EDS::getSurtidores() const
{
    return surtidores;
}

void EDS::setSurtidores(int newSurtidores)
{
    surtidores = newSurtidores;
}

char *EDS::getGerente() const
{
    return gerente;
}

void EDS::setGerente(char *newGerente)
{
    gerente = newGerente;
}



char *EDS::getUbicacion() const
{
    return ubicacion;
}

void EDS::setUbicacion(char *newUbicacion)
{
    ubicacion = newUbicacion;
}


char *EDS::getRegion() const
{
    return region;
}

void EDS::setRegion(char *newRegion)
{
    region = newRegion;
}

char *EDS::getNombre() const
{
    return nombre;
}

void EDS::setNombre(char *newNombre)
{
    nombre = newNombre;
}

int EDS::getCodigoES() const
{
    return codigoES;
}

void EDS::setCodigoES(int newCodigoES)
{
    codigoES = newCodigoES;
}

float *EDS::getCantidades() const
{
    return cantidades;
}

void EDS::setCantidades(float *newCantidades)
{
    cantidades = newCantidades;
}

float *EDS::getCantidadI() const
{
    return cantidadI;
}

void EDS::setCantidadI(float *newCantidadI)
{
    cantidadI = newCantidadI;
}

float *EDS::getPrecios() const
{
    return precios;
}

void EDS::setPrecios(float *newPrecios)
{
    precios = newPrecios;
}

float *EDS::getCantidadV() const
{
    return cantidadV;
}

void EDS::setCantidadV(float *newCantidadV)
{
    cantidadV = newCantidadV;
}

EDS::EDS(int codigo)//constructor
{
    int lR = 100; //litros iniciales
    int lP = 150;
    int lE = 200;

    codigoES= codigo; //codigos de la estacion

    nombre = "terpel";
    gerente = "mateo";
    region = "norte";
    ubicacion = "copa";
    islas = 2;
    surtidores = 8;
    /*cout << "Ingrese nombre de la estacion: ";
    nombre = new char[20];
    cin >> nombre;
    cout << endl;

    cout << "Ingrese nombre del gerente: ";
    gerente = new char[20];
    cin >> gerente;
    cout << endl;

    cout << "Ingrese region de la estacion (N,S,C): ";
    region = new char[20];
    cin >> region;
    cout << endl;

    cout << "Ingrese ubicacion de la estacion: ";
    ubicacion = new char[20];
    cin >> ubicacion;
    cout << endl;

    cout << "Ingrese numero de islas para la estacion: ";
    cin >> islas;
    cout << endl;

    cout << "Ingrese numero de surtidores para la estacion: ";
    cin >> surtidores;
    cout << endl;*/

    cantidadI = new float[3]; //cantidades actuales
    *(cantidadI+0)=lR;
    *(cantidadI+1)=lP;
    *(cantidadI+2)=lE;

    cantidades = new float[3]; //cantidades actuales
    *(cantidades+0)=lR;
    *(cantidades+1)=lP;
    *(cantidades+2)=lE;

    precios = new float[3]; //precios actuales
    *(precios+0)=10000;
    *(precios+1)=12000;
    *(precios+2)=14000;

    cantidadV = new float[3]; //cantidades vendidas
    *(cantidadV+0)=0;
    *(cantidadV+1)=0;
    *(cantidadV+2)=0;

}

int EDS::getIslas() const
{
    return islas;
}

void EDS::setIslas(int newIslas)
{
    islas = newIslas;
}

void EDS::registroC(float *cantidadV, float pN, float pS, float pC)
{

}

void EDS::registroV(float *cantidadV, float lR, float lP, float lE)
{

}

void EDS::actualizarC(float *cantidades, float lR, float lP, float lE)
{

}

void EDS::fuga(float *cantidadI, float *cantidadV, float *cantidades)
{

}
