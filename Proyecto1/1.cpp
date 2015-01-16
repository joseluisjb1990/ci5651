#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <math.h>

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

/* Funcion que lee la entrada y almacena la informacion del caso */
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

/* Funcion que obtiene y almacena los puntos de stdin */
vector< pair<int,int> > obPuntos(int n)
{
  string scasos, temp;
  vector< pair<int,int> > vp;
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
// Vector de la forma < d(1,2),..,d(1,n),d(2,3),..,d(2,n),...d(n-1,n) >

vector<float> obtenerDist(vector< pair<int,int> > vp, int n)
{
    // Vector que almacena las distancias
    vector<float> vd;

    // Cálculo y almacenamiento de distancias, costo amortizado.
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            vd.push_back(sqrt(pow(vp[i].first-vp[j].first,2) + pow(vp[i].second-vp[j].second,2)));
        }
       
    }

    return vd;

}

int main()
{
  string scasos;
  int cantCasos;
  RegValores v;
  // Vector que almacena los puntos
  vector< pair<int,int> > vp;
  // Vector que almacena las distancias entre los puntos.
  vector< float > vd;

  getline(cin, scasos); stringstream(scasos) >> cantCasos;
  cout << cantCasos << '\n';

  for(int i = 0; i < cantCasos; i++)
  {
    v = getValores();
    cout << v.n << " " << v.m << " " << v.r << " " << v.u << " " << v.v << endl;
    vp = obPuntos(v.n);
    vd = obtenerDist(vp,v.n);
    for( vector<float>::const_iterator i = vd.begin(); i != vd.end(); ++i)
        cout << *i << ' ';
    cout << '\n';
  }
}
