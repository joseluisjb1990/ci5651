#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {

    // Lectura de entrada

    int casos, filas, columnas;

    cin >> casos;


    for (int i=0; i<casos; i++) {

        // Para cada caso, leer y correr algoritmo

        cin >> filas;
        cin >> columnas;

        int matDP[columnas+2];
        for (int init = 0; init < columnas+2; init++) matDP[init] = -3;
        matDP[1] = 0;

        int filaAct, colAct, casilla;
        string linea;

        // Consumir linea        
        getline(cin,linea);

        bool casoBorde = false;
        int maxArbolesParcial = -3;

        // Leer cada fila y columna del caso
        for (filaAct = 0; filaAct < filas; filaAct++) {
    
            /* 
                Ciclo para caso borde en el que no se puede llegar al final
                del tablero, conservar el num max de arboles cortados.                    
            */
            for (int parcial = 1; parcial < columnas+1; parcial++) {
                maxArbolesParcial = max(maxArbolesParcial,matDP[parcial]);
            }  

            getline(cin,linea);

            // Caso borde, no pongo break porque se descuadran los getline
            if ((filaAct == 0) && (linea[0] == '#')) casoBorde = true;

            /*cout << "Fila " << filaAct << " Con string: " << linea << endl;
            for (colAct = 1; colAct < columnas+1; colAct++) {
                cout << "Casilla " << colAct << " = " << matDP[colAct] << endl;
            }*/

            /*
                Los -3 significan que la casilla esta bloqueada, no se puede
                llegar a ella. Se coloca -3 cuando la casilla es un #, o cuando
                sus posibles casillas predecesoras son ambas -3

            */

            if (filaAct % 2 == 0) {

                for (colAct = 0; colAct < columnas; colAct++) {

                    if (linea[colAct] == '#') {
                        matDP[colAct+1] = -3;
                    } else if ((matDP[colAct+1] == -3) && (matDP[colAct] == -3)) {
                        matDP[colAct+1] = -3;
                    } else {
                        casilla = (linea[colAct] == 'T') ? 1 : 0;            
                        matDP[colAct+1] = casilla + max(matDP[colAct+1],matDP[colAct]);
                    }
                }

            } else {

                for (colAct = columnas-1; colAct > -1; colAct--) {

                    if (linea[colAct] == '#') {
                        matDP[colAct+1] = -3;
                    } else if ((matDP[colAct+1] == -3) && (matDP[colAct+2] == -3)) {
                        matDP[colAct+1] = -3;
                    } else {
                        casilla = (linea[colAct] == 'T') ? 1 : 0;                    
                        matDP[colAct+1] = casilla + max(matDP[colAct+1],matDP[colAct+2]);
                    }
                }

            }
    
        }

        if (casoBorde) cout << 0 << endl;
        else {

            int maxCortes = matDP[1];
            for (colAct = 1; colAct < columnas+1; colAct++) {
                maxCortes = max(maxCortes,matDP[colAct]);
            }      

            maxCortes = (maxCortes < 0) ? maxArbolesParcial : maxCortes;
            cout << maxCortes << endl;
        }
        

    }


}
