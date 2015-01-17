/* 
 * Solucion al problema de repartir M modens en una red de N oficinas
 * Autores: Arturo Voltattorni y Jose Luis Jimenez
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define CANT_VALORES 5

class UnionFind 
{
  private:
    vector<int> arrPadres;

  public:
    UnionFind(int cantNodos)
    { 
      arrPadres = *(new vector<int>(cantNodos));
      for (int i = 0; i < cantNodos; i++) arrPadres[i] = i; 
    }
    
    int find(int nodo) 
    { 
      int padre = arrPadres[nodo];
      if(padre == nodo) return padre;
      else return find(padre);
    }

    int join(int izq, int der)
    {
      int liderIzq = find(izq);
      int liderDer = find(der);
      arrPadres[liderDer] = liderIzq;
    }

    void print()
    {
      cout << endl;
      for(vector<int>::iterator it = arrPadres.begin(); it != arrPadres.end(); it++) cout << *it << " ";
      cout << endl;
    }
};

struct RegValores
{
  int n;
  int m;
  int r;
  float u;
  float v;
};

struct NodoDist 
{
  int   izq;  //Nodo de partida del vertice
  int   der;  //Nodo de llegada del vertice
  float dist; //Distancia entre ambos nodos
};

//Funcion que compara nodos para hacer el ordenamiento
bool compararNodos(const NodoDist &n1, const NodoDist &n2)
{
  return n1.dist < n2.dist;
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
vector<NodoDist> obtenerDist(vector< pair<int,int> > vp, int n)
{
                         
    vector<NodoDist> vd; // Vector que almacena las distancias
    NodoDist nd;

    // Cálculo y almacenamiento de distancias, costo amortizado.
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            nd.izq = i;
            nd.der = j;
            nd.dist = sqrt(pow(vp[i].first-vp[j].first,2) + pow(vp[i].second-vp[j].second,2));
            vd.push_back(nd);
        }
    }
    return vd;
}

int main()
{
  string scasos;
  int cantCasos;
  RegValores v;
                      
  vector< pair<int,int> > vp;   // Vector que almacena los puntos
  vector< NodoDist > vd;        // Vector que almacena las distancias entre los puntos.


  getline(cin, scasos); stringstream(scasos) >> cantCasos; //Obtenemos la cantidad total de casos

  for(int h = 0; h < cantCasos; h++)
  {
    v = getValores();     //Obtenemos las cantidades n, m, r, u, v
    vp = obPuntos(v.n);   //Leemos la lista de pares de puntos
    UnionFind uf(v.n);    //Creamos una estructura union-find para llevar registro de las componentes conexas

    vd = obtenerDist(vp,v.n); //Calculamos todas las distancias
    
    sort(vd.begin(), vd.end(), compararNodos); //Ordenamos los nodos de menor a mayor con respecto a las distancias.

    // Aplcamos el algoritmos de Kruskal para buscar el arbol minimo cobertor, guardamos las distancias de los 
    // vertices seleccionados en el arreglo vecDist
    float vecDist[v.n - 1];
    int k = 0;
    for(vector<NodoDist>::const_iterator itd = vd.begin(); itd != vd.end(); itd++)
    {
      NodoDist temp = *itd;
      if(uf.find(temp.izq) != uf.find(temp.der)) 
      { 
        uf.join(temp.izq, temp.der);
        vecDist[k++] = temp.dist;
        if(k == v.n - 1) break; 
      }
    }

    //Calculamos el costo por metro de usar los cables.
    float precioU = 0.0;
    float precioV = 0.0;

    for(int i = 0; i < v.n - v.m; i++)
    {
      if(vecDist[i] <= v.r) precioU += vecDist[i] * v.u;
      else precioV += vecDist[i] * v.v;
    }

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(3);
    cout << "Caso #" << h << ": " << precioU << " " << precioV << endl; 
  }
}
