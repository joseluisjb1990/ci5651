#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>

using namespace std;

#define CANT_VALORES 5

struct RegValores
{
  int n;
  int m;
  int r;
  float u;
  float v;
};

struct nodo 
{
  // Cantidad de nodos que estan a distancia con costo U
  int cu;
  // Nodo actual
  int nod;
  vector<nodo>* ady;

};

//Funcion que compara nodos para hacer el ordenamiento
bool compararNodos(const nodo &n1, const nodo &n2)
{
  return n1.cu > n2.cu;
}

// Funcion que crea e inicializa una estructura para cada punto.
vector<nodo> initNodos(int cantN)
{
  vector<nodo> vn;
  nodo n;
  for (int i = 0; i < cantN; i++)
  { 
    n.cu = 0;
    n.nod = i;
    n.ady = new vector<nodo>();
    vn.push_back(n);
  }

  return vn;
}

/* 
   Funcion que toma el vector de nodos, y para cada nodo guarda la cantidad
   de nodos cuya distancia tiene costo U y cuales son. 
*/

void contarDistancias(vector<nodo> &vn, vector<float> vp, int n, int u)
{
  int acc = 0;
  int  in = 0;
  for(int i = 1; i < n; i++)
  {
    int k = i;
    while (in <= i * n - i - acc - 1)
    {
      if(vp[in] <= u) { vn[i-1].cu++; vn[i-1].ady->push_back(vn[k]); vn[k].cu++; vn[k].ady->push_back(vn[i-1]);} 
      in++;
      k++;
    }
    acc = acc + i;
  }
}


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
    temp    = entrada.substr(0, posF);
    entrada = entrada.substr(posF + 1);
    valores.push_back(temp);
  }
  
  stringstream(valores.at(0)) >> r.n;
  stringstream(valores.at(1)) >> r.r;
  stringstream(valores.at(2)) >> r.m;
  stringstream(valores.at(3)) >> r.u;
  stringstream(entrada) >> r.v;

  cout << "ALALA " << r.n << valores.at(1) << r.m << r.u << r.v << endl;

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

// Funcion que selecciona el nodo a asignar modem y conectar.
pair<nodo,bool> seleccionarCandidato(vector< nodo > vn, vector<bool> conectados)
{
  pair<nodo,bool> res;
  for( vector< nodo >::const_iterator i = vn.begin(); i != vn.end(); ++i)
  {
    if (!conectados[(*i).nod]) { res.first=*i; res.second=true; return res;  }
  }

  res.second = false;

  return res;

}

// Funcion que conecta recursivamente.
int conectarNodos(nodo n, vector<bool> &conectados)
{
  conectados[n.nod] = true;
  int c = 1;

  for (vector< nodo >::const_iterator i = n.ady->begin(); i != n.ady->end(); ++i)
  {
    if (!conectados[(*i).nod]) { c += conectarNodos(*i,conectados); }
  }

  return c;

}

int main()
{
  string scasos;
  int cantCasos;
  RegValores v;
  // Lista de nodos
  vector< nodo > vn;
  // Vector que almacena los puntos
  vector< pair<int,int> > vp;
  // Vector que almacena las distancias entre los puntos.
  vector< float > vd;


  getline(cin, scasos); stringstream(scasos) >> cantCasos;

  for(int h = 0; h < cantCasos; h++)
  {
    v = getValores();
    vp = obPuntos(v.n);
    vd = obtenerDist(vp,v.n);

    vn = initNodos(v.n);
    
    for( vector<float>::const_iterator i = vd.begin(); i != vd.end(); ++i)
        cout << *i << ' ';
    cout << endl;

    // Se cuentan las distancias entre puntos y se genera el vector
    // con la informacion de cada nodo.
    contarDistancias(vn, vd, v.n, v.r);  
    for(int i = 0; i < v.n; i++) { cout << vn[i].nod << " " << vn[i].cu << " | "; 
				   for(vector<nodo>::iterator it = vn[i].ady->begin(); it != vn[i].ady->end(); it++) cout << (*it).nod << " ";
			           cout << endl;
				 }

    // Se ordena el vector de nodos de acuerdo a la cantidad de nodos adyacentes
    // con costo U

    cout << "Antes/Despues del sort" << endl;

    sort(vn.begin(), vn.end(), compararNodos);

    for(int i = 0; i < v.n; i++) { cout << vn[i].nod << " " << vn[i].cu << " | "; 
				   for(vector<nodo>::iterator it = vn[i].ady->begin(); it != vn[i].ady->end(); it++) cout << (*it).nod << " ";
			           cout << endl;
				 }

    cout << "-----------------------------------------" << endl;

    // Arreglo que contiene el estado de conexion de los nodos
    vector< bool > conectados(v.n,false);
    pair< nodo, bool > tnb;
    int cantU = 0;
    float precioU = 0.0, precioV = 0.0;
    int cm;
    // Asignar modem y conectar recursivamente.
    for(cm = 0; cm < v.m; cm++)
    {
      tnb = seleccionarCandidato(vn,conectados);

      if (tnb.second) cantU += conectarNodos(tnb.first,conectados);
      else break; 
    }
    cout << "CU " << v.n << v.r << v.m << v.u << v.v << endl; 
    if (cantU!=v.n) {
        precioV = (v.n-cantU)*(v.v);
    }
    
    // Se restan las oficinas que tienen modem
    precioU = (cantU-v.m)*v.u;

    cout << "Caso #" << h << ": "<< precioU << " " << precioV << endl;
  }
}
