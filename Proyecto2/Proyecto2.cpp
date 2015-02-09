#include <fstream>
#include <string>
#include "grafo.cpp"

Grafo* leerArchivo()
{
  string linea;
  ifstream archivo;
  archivo.open("DSJC125.1.col");

  Grafo* g = new Grafo();

  if(archivo.is_open())
  {
    while(getline(archivo, linea))
    {
      if(linea[0] == 'e')
      {
        size_t pos     = linea.find(" ");
        size_t posSep  = linea.substr(pos + 1).find(" ");
        
        int partida = stoi(linea.substr(pos+1, posSep));
        int llegada = stoi(linea.substr(pos + 1).substr(posSep+1));

        g->agregarLado(partida, llegada);
      }
    }
    archivo.close();
  }

  return g;
}

int main ()
{
  cout<< "HOLAAAAAAAAAAAAAA" << endl;

  //Grafo* g = leerArchivo();

  Grafo* g = new Grafo();

  g->agregarLado(1,2);
  g->agregarLado(1,3);
  g->agregarLado(2,4);
  g->agregarLado(2,3);
  g->agregarLado(3,4);
  g->agregarLado(2,8);
  g->agregarLado(8,6);
  g->agregarLado(4,8);
  g->agregarLado(4,6);
  g->agregarLado(6,7);
  g->agregarLado(7,9);
  g->agregarLado(4,9);
  g->agregarLado(2,9);
  g->agregarLado(7,5);
  g->print();
  g->maximalClique();
  g->Dsatur();
  g->argoritmo();
}
