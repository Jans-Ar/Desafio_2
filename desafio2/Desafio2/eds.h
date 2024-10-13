#ifndef EDS_H
#define EDS_H

class EDS
{
private:
    char nombre;
    int codigoES; //codigos de todas las estaciones
    char gerente;
    char region;
    char ubicacion;
    int *cantidades; //cantidad de combustible actual
    int *cantidadI; //cantidad de combustible inicial
    int islas;
    int surtidores;
    int *precios;
    int *cantidadV; //cantidades vendidas
public:
    EDS(int codigo, char n, char g, char r, char u, int i, int s, int pN, int pS, int pC);
    char getNombre() const;
    void setNombre(char newNombre);
    int getCodigoES() const;
    void setCodigoES(int newCodigoES);
    char getGerente() const;
    void setGerente(char newGerente);
    char getRegion() const;
    void setRegion(char newRegion);
    char getUbicacion() const;
    void setUbicacion(char newUbicacion);
    int *getCantidades() const;
    void setCantidades(int *newCantidades);
    int *getCantidadI() const;
    void setCantidadI(int *newCantidadI);
    int getIslas() const;
    void setIslas(int newIslas);
    int *getPrecios() const;
    void setPrecios(int *newPrecios);
    int *getCantidadV() const;
    void setCantidadV(int *newCantidadV);
    int getSurtidores() const;
    void setSurtidores(int newSurtidores);

    void registroC(int *cantidadV, int pN , int pS, int pC);
    void registroV(int *cantidadV, int lR , int lP, int lE); //resgistro por litro
    void actualizarC(int *cantidades, int lR , int lP, int lE);
    void fuga(int *cantidadI, int *cantidadV, int *cantidades);

};

#endif // EDS_H
