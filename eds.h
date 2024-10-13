#ifndef EDS_H
#define EDS_H

#include "islas.h"
class EDS
{
private:
    char *nombre;
    int codigoES; //codigos de todas las estaciones
    char *gerente;
    char *region;
    char *ubicacion;
    float *cantidades; //cantidad de combustible actual
    float *cantidadI; //cantidad de combustible inicial
    Islas **misIslas;
    int islas;
    int surtidores;
    float *precios;
    float *cantidadV; //cantidades vendidas
public:
    EDS(int codigo);

    char *getNombre() const;
    void setNombre(char *newNombre);
    int getCodigoES() const;
    void setCodigoES(int newCodigoES);
    float *getCantidades() const;
    void setCantidades(float *newCantidades);
    float *getCantidadI() const;
    void setCantidadI(float *newCantidadI);
    float *getPrecios() const;
    void setPrecios(float *newPrecios);
    float *getCantidadV() const;
    void setCantidadV(float *newCantidadV);
    char *getRegion() const;
    void setRegion(char *newRegion);
    char *getGerente() const;
    void setGerente(char *newGerente);
    char *getUbicacion() const;
    void setUbicacion(char *newUbicacion);
    int getIslas() const;
    void setIslas(int newIslas);
    int getSurtidores() const;
    void setSurtidores(int newSurtidores);

    void registroC(float *cantidadV, float pN , float pS, float pC);
    void registroV(float *cantidadV, float lR , float lP, float lE); //resgistro por litro
    void actualizarC(float *cantidades, float lR , float lP, float lE);
    void fuga(float *cantidadI, float *cantidadV, float *cantidades);

};

#endif // EDS_H
