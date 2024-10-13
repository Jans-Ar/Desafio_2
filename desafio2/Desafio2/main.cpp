#include <iostream>
#include "termex.h"
#include "eds.h"
#include "Funciones.h"
using namespace std;

int main()
{
    espacios();
    char regiones[3]={'N', 'S', 'C'};
    float precios[3]={10000, 12000, 160000};
    int nES = 1;
    EDS **misES = nullptr;
    misES = new EDS*[nES];
    EDS **aux = nullptr;
    aux = new EDS*[nES];
    int codigoES = 0;

    int opc=0;

    while(opc!=6){
        menu();
        cin >> opc;
        switch (opc) {
        case 1:
            *(misES+(nES-1)) = new EDS(nES);
            //cout << misES[nES-1]->getCodigoES() << endl;
            copiarEstacion(misES,aux, nES);
            borrarPtr(misES, nES);
            nES+=1;
            misES = new EDS*[nES];
            copiarEstacion(aux, misES, nES-1);
            borrarPtr(aux, nES-1);
            aux = new EDS*[nES];
            break;
        case 2:
            imprimirEstaciones(misES, nES-1);
            cout << "Elija una estacion por codigo:";
            //cin >> opc;
            break;
        case 3:
            cout << "Ingrese codigo de estacion a eliminar: ";
            cin >> codigoES;
            eliminarEstacion(misES, nES, codigoES);
            nES-=1;
            break;
        default:
            cout << "Elija una opcion correcta: " << endl;
            break;
        }

        espacios();
    }
    return 0;
}
