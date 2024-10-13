#include "eds.h"

int EDS::getSurtidores() const
{
    return surtidores;
}

void EDS::setSurtidores(int newSurtidores)
{
    surtidores = newSurtidores;
}

EDS::EDS(int codigo, char n, char g, char r, char u, int i, int s, int pN, int pS, int pC)//constructor
{
    int lR = 100; //litros iniciales
    int lP = 150;
    int lE = 200;
    nombre = n;
    codigoES= codigo; //codigos de la estacion
    gerente = g;
    region = r;
    ubicacion = u;

    cantidadI = new int(lR); //cantidades iniciales
    cantidadI = new int(lP);
    cantidadI = new int(lE);

    cantidades = new int(lR); //cantidades actuales
    cantidades = new int(lP);
    cantidades = new int(lE);

    islas = i;
    surtidores = s;

    precios = new int(pN); //damos precios iniciales
    precios = new int(pS);
    precios = new int(pC);

    cantidadV = new int(0);
    cantidadV = new int(0);
    cantidadV = new int(0);
}

char EDS::getNombre() const
{
    return nombre;
}

void EDS::setNombre(char newNombre)
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

char EDS::getGerente() const
{
    return gerente;
}

void EDS::setGerente(char newGerente)
{
    gerente = newGerente;
}

char EDS::getRegion() const
{
    return region;
}

void EDS::setRegion(char newRegion)
{
    region = newRegion;
}

char EDS::getUbicacion() const
{
    return ubicacion;
}

void EDS::setUbicacion(char newUbicacion)
{
    ubicacion = newUbicacion;
}

int *EDS::getCantidades() const
{
    return cantidades;
}

void EDS::setCantidades(int *newCantidades)
{
    cantidades = newCantidades;
}

int *EDS::getCantidadI() const
{
    return cantidadI;
}

void EDS::setCantidadI(int *newCantidadI)
{
    cantidadI = newCantidadI;
}

int EDS::getIslas() const
{
    return islas;
}

void EDS::setIslas(int newIslas)
{
    islas = newIslas;
}







int *EDS::getPrecios() const
{
    return precios;
}

void EDS::setPrecios(int *newPrecios)
{
    precios = newPrecios;
}

int *EDS::getCantidadV() const
{
    return cantidadV;
}

void EDS::setCantidadV(int *newCantidadV)
{
    cantidadV = newCantidadV;
}

void EDS::registroC(int *cantidadV, int pN, int pS, int pC)
{

}

void EDS::registroV(int *cantidadV, int lR, int lP, int lE)
{

}

void EDS::actualizarC(int *cantidades, int lR, int lP, int lE)
{

}

void EDS::fuga(int *cantidadI, int *cantidadV, int *cantidades)
{

}
