#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

#define CANT_VALORES 5

struct RegValores
{
  int n;
  int m;
  int r;
  int u;
  int v;
};

RegValores getValores()
{
  string entrada, temp;
  int posI = 0;
  int posF;
  RegValores r;
  vector<string> valores;

  getline(cin, entrada);
  
  for(int i = 0; i < CANT_VALORES - 1; i++)
  {
    posF    = entrada.find(" ");  
    temp    = entrada.substr(posI, posF);
    entrada = entrada.substr(posF + 1);
    valores.push_back(temp);
    posI = posF + 1;
  }
  
  stringstream(valores.at(0)) >> r.n;
  stringstream(valores.at(1)) >> r.m;
  stringstream(valores.at(2)) >> r.r;
  stringstream(valores.at(3)) >> r.u;
  stringstream(entrada) >> r.v;

  return r;
}

vector<pair<int,int>> obPuntos(int n)
{
  string scasos, temp;
  vector<pair<int,int>> vp;
  int posF;
  pair<int,int> p;

  for(int i = 0; i < n; i++)
  { 
    getline(cin, scasos); 
    posF   = scasos.find(" ");  
    temp   = scasos.substr(0, posF);
    scasos = scasos.substr(posF + 1);
    stringstream(temp)   >> p.first;
    stringstream(scasos) >> p.second;
    vp.push_back(p);
  }

  return vp;
}

// Obtener el vector de las distancias.

// vector<int> obtenerDist(vector<pair<int,int>>)
// {
//     for (int i = 0; i < 
// 
// }


int main()
{
  string scasos;
  int cantCasos;
  RegValores v;
  vector<pair<int,int>> vp;

  getline(cin, scasos); stringstream(scasos) >> cantCasos;
  cout << cantCasos << '\n';
0
  for(int i = 0; i < cantCasos; i++)
  {
    v = getValores();
    cout << v.n << " " << v.m << " " << v.r << " " << v.u << " " << v.v << endl;
    vp = obPuntos(v.n);
  }
}
