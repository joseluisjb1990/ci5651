#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct nodo 
{
  int cantNodos;
  nodo* padre;
  vector<int> hijos;
};

struct conexion
{
  int   prim;
  int   sec;
};

int dfs(vector<nodo> &vn, nodo &n, nodo &pad)
{

  n.padre = &pad;

  for(vector<int>::iterator t = n.hijos.begin(); t != n.hijos.end(); t++)
  {
    if (&vn[(*t)]!=&pad) {
      n.cantNodos += dfs(vn,vn[(*t)],n);
    }
  }

  return n.cantNodos;

}

int desconectar(vector<nodo> &vn, conexion c)
{
  if(&vn[c.prim - 1] == vn[c.sec - 1].padre)
  {
    vn[c.prim - 1].cantNodos -= vn[c.sec - 1].cantNodos;
    vn[c.sec - 1].padre = &vn[c.sec - 1];
    return vn[c.prim - 1].cantNodos * vn[c.sec - 1].cantNodos;
  }
  else
  {
    vn[c.sec - 1].cantNodos -= vn[c.prim - 1].cantNodos;
    vn[c.prim - 1].padre = &vn[c.prim - 1];
    return vn[c.sec - 1].cantNodos * vn[c.prim - 1].cantNodos;
  }
}

// Funcion que inicializa el grafo
vector<nodo> initGrafo(vector<conexion> vc, int cantNodos)
{
  vector<nodo> vn = *(new vector<nodo>());

  for(int i = 0; i< cantNodos; i++) {
    nodo n;
    n.cantNodos = 1;
    n.hijos = *(new vector<int>());
    vn.push_back(n);
  }

  for(vector<conexion>::iterator it = vc.begin(); it != vc.end(); it++)
  {
    vn.at((*it).prim - 1).hijos.push_back((*it).sec - 1);
    vn.at((*it).sec - 1).hijos.push_back((*it).prim - 1);
  }

  vn.at(0).padre = &vn.at(0);
  dfs(vn,vn.at(0),vn.at(0));

  return vn;
}



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

    vector<nodo> vn = initGrafo(vc,cantNodos);
    for(vector<nodo>::iterator it = vn.begin(); it != vn.end(); it++)
    {
      for(vector<int>::iterator t = (*it).hijos.begin(); t != (*it).hijos.end(); t++)
      {
        cout << (*t)+1 << " ";
      }

      cout << "CN " << (*it).cantNodos << endl;
    }

    getline(cin, scasos); stringstream(scasos) >> cantQueries; //Obtenemos la cantidad total de queries
    cout << "La cantidad de queries es " << cantQueries << endl;
    int desc = 0;
    for(int i = 0; i < cantQueries; i++)
    {
      getline(cin, scasos);
      switch (scasos[0])
      {
        case 'Q' : cout << desc << endl; break;
        case 'R' :
          int pos;
          pos = scasos.find(" ");
          stringstream(scasos.substr(pos + 1)) >> pos;
          cout << "----------------------------- " << pos << endl;
          desc += desconectar(vn, vc[pos - 1]);
          break;
      }
    }
  }
}