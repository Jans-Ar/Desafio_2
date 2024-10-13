#ifndef TERMEX_H
#define TERMEX_H

#include <iostream>
using namespace std;

class Termex
{
private:
    int *codigosES; //codigos de todas las estaciones
    char *regiones;
    int *precios;
    int nES; //numero de estaciones
public:
    Termex(); //constructor donde se inicializan la variables
    ~Termex(); //destructor

    int *getCodigosES() const;
    void setCodigosES(int *newCodigosES);
    char *getRegiones() const;
    void setRegiones(char *newRegiones);
    int *getPrecios() const;
    void setPrecios(int *newPrecios);
    int getNES() const;
    void setNES(int newNES);

    void crearEstacion();
    void eliminarEstacion(int codigoES);
    float montoEstaciones(int *codigosES);
    void modificarPrecios(int pN, int pS, int pC);

};

#endif // TERMEX_H
