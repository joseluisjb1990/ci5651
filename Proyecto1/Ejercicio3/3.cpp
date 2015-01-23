#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct tarea
{
  int   ti; // Tiempo de inicio
  int   tf; // Tiempo de fin
};

vector<tarea> getTareas(int cantTareas)
{
  string aux, temp;
  vector<tarea> vc;
  tarea c;
  int posF;

  for(int i = 0; i < cantTareas; i++)
  {
    getline(cin, aux);
    posF  = aux.find(" ");  
    temp  = aux.substr(0, posF);
    aux   = aux.substr(posF + 1);
    stringstream(temp)  >> c.ti;
    stringstream(aux)   >> c.tf;
    vc.push_back(c);
  }
  return vc;
}

//Funcion que compara nodos para hacer el ordenamiento
bool compararTiempoFinal(const tarea &n1, const tarea &n2)
{
  return n1.tf < n2.tf;
}

// Funcion que compara solapamiento entre dos tareas
bool verificarSolapamiento(tarea t1, tarea t2)
{
  return (t1.tf > t2.ti);

}

// Funcion que cuenta la cantidad maxima de tareas que puede hacer el empleado
int cantMaxTareas(vector<tarea> vt)
{
  tarea temp;
  temp.ti = 0;
  temp.tf = 0;
  int res = 0;

  for(vector<tarea>::iterator it = vt.begin(); it != vt.end(); ++it)
  {
    if (!verificarSolapamiento(temp,*it)) {
      temp = *it;
      res++;
    }
  }

  return res;
}

int main()
{
  string scasos;
  int cantEmpleados;
  int cantTareas;
  int cantQueries;

  getline(cin, scasos); stringstream(scasos) >> cantEmpleados; //Obtenemos la cantidad total de empleados
  
  for(int h = 0; h < cantEmpleados; h++)
  {
    getline(cin, scasos); stringstream(scasos) >> cantTareas; //Obtenemos la cantidad total de tareas

    vector<tarea> vt = getTareas(cantTareas);  

    sort(vt.begin(), vt.end(), compararTiempoFinal);

    int res = cantMaxTareas(vt);

    cout << endl << res;
  }
}
