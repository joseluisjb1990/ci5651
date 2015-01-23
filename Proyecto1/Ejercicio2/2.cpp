/*
  Fecha: 23/01/2015
  Autores: Arturo Voltattorni & Jose Jimenez
  Programa para calcular la cantidad de oficinas desconectadas 
  a partir de la desconexion de uno o varias.
*/
#include <bits/stdc++.h>

using namespace std;

struct nodo 
{
  int id;
  int cantNodos;
  nodo* padre;
  vector<int> hijos;
};

struct conexion
{
  int   prim;
  int   sec;
};

// Procedimiento usado para inicializar la cantidad de nodos
// por cada componente conexa en el grafo
int dfs(vector<nodo> &vn, nodo &n, nodo &pad)
{
  n.padre = &pad;
  for(vector<int>::iterator t = n.hijos.begin(); t != n.hijos.end(); t++)
    if (&vn[(*t)] != &pad)
      n.cantNodos += dfs(vn,vn[(*t)],n);

  return n.cantNodos;
}

// Procedimiento usado para actualizar la cantidad de nodos en la rama
// perteneciente a la desconexion
int actualizarHijos(vector<nodo> &vn, int x, int n)
{
  vn[x].cantNodos -= n;
  if(vn[x].padre == &vn[x])
    return vn[x].cantNodos;
  else
    return actualizarHijos(vn, vn[x].padre->id - 1,n);
}

// Procedimiento para realizar la desconexion del grafo
int desconectar(vector<nodo> &vn, conexion c)
{
  if(&vn[c.prim - 1] == vn[c.sec - 1].padre)
  {
    int n = actualizarHijos(vn, c.prim -1, vn[c.sec - 1].cantNodos);
    vn[c.sec - 1].padre = &vn[c.sec - 1];
    return n * vn[c.sec - 1].cantNodos;
  }
  else
  {
    int n = actualizarHijos(vn, c.sec - 1, vn[c.prim -1].cantNodos);
    vn[c.prim - 1].padre = &vn[c.prim - 1];
    return n * vn[c.prim - 1].cantNodos;
  }
}

// Funcion que inicializa el grafo
vector<nodo> initGrafo(vector<conexion> vc, int cantNodos)
{
  vector<nodo> vn = *(new vector<nodo>());

  for(int i = 0; i< cantNodos; i++) {
    nodo n;
    n.id = i + 1;
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

// Procedimiento para leer a partir de la entrada estandar
// todas las conexiones que componen el grafo
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

  getline(cin, scasos); stringstream(scasos) >> cantCasos;      // Obtenemos la cantidad total de casos
  
  for(int h = 0; h < cantCasos; h++)
  {
    getline(cin, scasos);                                       // Leemos la linea vacia
    getline(cin, scasos); stringstream(scasos) >> cantNodos;    // Obtenemos la cantidad total de nodos
    vector<conexion> vc = getConexiones(cantNodos - 1);         // Obtenemos todas las conexiones que componen el grafo 
    vector<nodo> vn = initGrafo(vc,cantNodos);                  // Obtenemos el grafo
    getline(cin, scasos); stringstream(scasos) >> cantQueries;  // Obtenemos la cantidad total de queries
    
    int desc = 0;                                               // Variable para llevar la cantidad total de nodos desconectados
    for(int i = 0; i < cantQueries; i++)
    {
      getline(cin, scasos);                                     // Obtenemos el tipo de querie que queremos hacer
      switch (scasos[0])
      {
        case 'Q' : printf("%d\n", desc); break;                 // Escribimos la cantidad de nodos desconectados
        case 'R' :
          int pos;
          pos = scasos.find(" ");
          stringstream(scasos.substr(pos + 1)) >> pos;
          desc += desconectar(vn, vc[pos - 1]);                 // Desconectamos la conexion correspondiente
          break;
      }
    }
    if (h < cantCasos-1)
      printf("%c",'\n');      
  }
}