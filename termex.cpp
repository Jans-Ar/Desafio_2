#include "termex.h"
#include "Funciones.h"

int *Termex::getCodigosES() const
{
    return codigosES;
}

void Termex::setCodigosES(int *newCodigosES)
{
    codigosES = newCodigosES;
}

char *Termex::getRegiones() const
{
    return regiones;
}

int *Termex::getPrecios() const
{
    return precios;
}

void Termex::setPrecios(int *newPrecios)
{
    precios = newPrecios;
}

void Termex::eliminarEstacion(int codigoES)
{
    int *aux=nullptr; //puntero auxiliar
    aux= new int[nES-1]; //le asigno un espacio de memoria menos 1
    eliminar(codigosES, aux, nES, codigoES);
    delete[] codigosES;
    codigosES = new int[nES-1];
    copiar(aux, codigosES, nES-1);
    nES-=1;
    delete []aux;
}

float Termex::montoEstaciones(int *codigosES)
{

}

void Termex::modificarPrecios(int pN, int pS, int pC)
{
    *(precios+0)=pN;
    *(precios+1)=pS;
    *(precios+2)=pC;
}

int Termex::getNES() const
{
    return nES;
}

void Termex::setNES(int newNES)
{
    nES = newNES;
}

void Termex::crearEstacion()
{
    codigosES = new int(nES+1);
    nES+=1;
}

Termex::Termex(){//constructor
    nES = 0;
    regiones = nullptr;
    precios = nullptr;
    regiones= new char('N'); //creamos regiones
    regiones= new char('S');
    regiones= new char('C');

    precios = new int(15000); //damos precios iniciales
    precios = new int(16000);
    precios = new int(17000);

}
Termex::~Termex() {
    cout<< "destructor";
    delete[] precios;
    delete[] regiones;
}
