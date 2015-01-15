#include <iostream>
#include <string>
#include <sstream>
#include <vector>
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

int main()
{
  string scasos;
  int cantCasos;
  RegValores v;

  getline(cin, scasos); stringstream(scasos) >> cantCasos;
  cout << cantCasos << '\n';

  for(int i = 0; i < cantCasos; i++)
  {
    RegValores v = getValores();
    cout << v.n << " " << v.m << " " << v.r << " " << v.u << " " << v.v << endl;
    for(int i = 0; i < v.n; i++) { getline(cin, scasos); cout << scasos << endl; }
  }
}
