#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct conexion
{
  int   prim;
  int   sec;
};

vector<conexion> getConexiones(int cantConexiones)
{
  string aux, temp;
  vector<conexion> vc;
  conexion c;
  int posF;

  for(int i = 0; i < cantConexiones; i++)
  {
    getline(cin, aux);
    posF  = aux.find(" ");  
    temp  = aux.substr(0, posF);
    aux   = aux.substr(posF + 1);
    stringstream(temp)  >> c.prim;
    stringstream(aux)   >> c.sec;
    vc.push_back(c);
  }
  return vc;
}

int main()
{
  string scasos;
  int cantCasos;
  int cantNodos;
  int cantQueries;

  getline(cin, scasos); stringstream(scasos) >> cantCasos; //Obtenemos la cantidad total de casos
  cout << "La cantidad de casos es " << cantCasos << endl;
  
  for(int h = 0; h < cantCasos; h++)
  {
    getline(cin, scasos); // Leemos la linea vacia
    getline(cin, scasos); stringstream(scasos) >> cantNodos; //Obtenemos la cantidad total de nodos
    cout << "La cantidad de nodos es " << cantNodos << endl;

    vector<conexion> vc = getConexiones(cantNodos - 1);  
    for(int i = 0; i < cantNodos - 1; i++)
    {
      cout << vc.at(i).prim << " " << vc.at(i).sec << endl;
    }
    getline(cin, scasos); stringstream(scasos) >> cantQueries; //Obtenemos la cantidad total de nodos
    cout << "La cantidad de queries es " << cantQueries << endl;
    for(int i = 0; i < cantQueries; i++)
    {
      getline(cin, scasos);
      switch (scasos[0])
      {
        case 'Q' : cout << "Tengo que hacer un query" << endl; break;
        case 'R' :
          int pos;
          pos = scasos.find(" ");
          cout << "Tengo que romper la conexion" << scasos.substr(pos + 1) << endl;
          break;
      }
    }
  }
}
