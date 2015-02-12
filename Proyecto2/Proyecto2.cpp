#include <fstream>
#include <string>
#include "grafo.cpp"

Grafo* leerArchivo(string nombreArch)
{
  string linea;
  ifstream archivo;
  archivo.open(nombreArch);

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

int main (int argc, char* argv[])
{
  Grafo* g = leerArchivo(argv[1]);
  cout << g->Dsatur() << " " << g->brelazModificado() << endl; 
}
