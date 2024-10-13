#include <iostream>
#include "termex.h"
#include "eds.h"
#include "Funciones.h"
using namespace std;

int main()
{
    Termex emp;
    emp.crearEstacion();
    EDS **misES = nullptr;
    misES = new EDS*[2];
    int opc=0;
    while(opc!=3){
        cout << "Bienvenido a TerMax EDS!" << endl;
        cout << "1. Crear EDS" << endl;
        cout << "2. Ver EDS" << endl;
        cout << "3. salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opc;
        if (opc==1){
            *(misES+0) = new EDS(1, 'M', 'M', 'S', 'M', 2, 4, 12000, 13000 , 17000);
            *(misES+1) = new EDS(2, 'T', 'M', 'N', 'C', 2, 4, 12000, 13000 , 17000);

        }else if(opc==2){
            imprimirEstaciones(misES);
        }
    }

    return 0;
}
