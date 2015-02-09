#include<vector>
#include<map>
#include<algorithm>
#include<utility>
#include<iostream>

using namespace std;

bool compVector(pair<int, int >v1, pair< int, int >v2)
{
  return v1.second > v2.second;
}

class Grafo
{
  private:
    map< int,vector<int> > listAdy;
  
  public:
    void agregarLado (int partida, int destino)
    {
      listAdy[partida].push_back(destino);
      listAdy[destino].push_back(partida);
    }
    
    void print()
    {
      cout << endl;
      for(map< int,vector<int> >::iterator it = listAdy.begin(); it != listAdy.end(); it++)
      {
        cout << it->first << ": ";
        for(vector<int>::iterator itv = (it->second).begin(); itv != (it->second).end(); itv++)
          cout << *itv << " ";
        cout << endl;
      }
    }

    vector< pair<int, int> >* sortByDegree()
    {
      vector< pair<int, int> >* vm = new vector< pair<int, int> >();

      for(map< int,vector<int> >::iterator it = listAdy.begin(); it != listAdy.end(); it++)
        vm->push_back(make_pair((*it).first, (*it).second.size()));

      sort(vm->begin(), vm->end(), compVector);

      return vm;
    }

    vector<int>* maximalClique()
    {
      vector< pair<int, int> >* vm = sortByDegree();

      vector<int>* mc = new vector<int>();

      for(vector< pair< int,int > >::iterator it = vm->begin(); it != vm->end(); it++)
      {
        bool esta = true; 
        for(vector<int>::iterator itmc = mc->begin(); itmc != mc->end(); itmc++)
        {
          if(find(listAdy[*itmc].begin(), listAdy[*itmc].end(), it->first) == listAdy[*itmc].end())
          {
            esta = false;
            break;
          }
        }
        if(esta) mc->push_back(it->first);
      }
    
      return mc;
    }

    int Dsatur()
    {
      int color = 1;

      vector< pair<int, int> >* vm = sortByDegree();
      
      map<int, int> nodoColor;

      for(vector< pair< int,int > >::iterator it = vm->begin(); it != vm->end(); it++)
        nodoColor[it->first] = 0;
      
      map<int, vector<int> > colorAdy;

      nodoColor[vm->at(0).first] = color;

      for(vector<int>::iterator it = listAdy[vm->at(0).first].begin(); it != listAdy[vm->at(0).first].end(); it++)
        colorAdy[*it].push_back(color);
    
      while(true)
      {
        int maxSat    = 0;
        int nodMaxSat = 0;
        bool todosColor = true;
        for(vector< pair< int,int > >::iterator it = vm->begin(); it != vm->end(); it++)
        {
          if(nodoColor[(*it).first] == 0)
          {
            todosColor = false;
            if(colorAdy[(*it).first].size() > maxSat)
            {
              maxSat = colorAdy[(*it).first].size();
              nodMaxSat = (*it).first;
            }
          }
        }

        if(todosColor) break;

        int colorAct = 0;
        for(int i = 1; i <= color; i++)
        {
          if(find(colorAdy[nodMaxSat].begin(), colorAdy[nodMaxSat].end(), i) == colorAdy[nodMaxSat].end())
          {
            colorAct = i;
            break;
          }
        }
        
        if (colorAct == 0) colorAct = ++color;
   
        nodoColor[nodMaxSat] = colorAct;
          
        for(vector<int>::iterator it = listAdy[nodMaxSat].begin(); it != listAdy[nodMaxSat].end(); it++)
          if (find(colorAdy[*it].begin(), colorAdy[*it].end(), colorAct) == colorAdy[*it].end())
            colorAdy[*it].push_back(colorAct);

      }

      cout << endl;
      for(map<int, vector<int> >::iterator it = colorAdy.begin(); it != colorAdy.end(); it++)
      {
        cout << (*it).first << ": ";
        for(vector<int>::iterator itv = (*it).second.begin(); itv != (*it).second.end(); itv++)
        {
          cout << *itv << " ";
        }
        cout << endl;
      }
      
      for(map<int, int >::iterator it = nodoColor.begin(); it != nodoColor.end(); it++)
      {
        cout << (*it).first << ": " << (*it).second << endl;
      }
      
      for(vector< pair< int,int > >::iterator it = vm->begin(); it != vm->end(); it++)
      {
        cout << (*it).first << " " << (*it).second << endl;
      }
    
      return color;
    }

    int argoritmo()
    {
      vector<int>* maxClique = maximalClique();
      vector< pair<int, int> >* vm = sortByDegree();
                
      int   arrK[vm->size() + 1]; //Arreglo de nodos ordenados por k
      int   solsParcial[vm->size() + 1]; //Cantidad de colores en la solucion parcial k-1
      bool  labeled[vm->size() + 1];
      int w = maxClique->size();
      int q = Dsatur();
      vector<int>* Uk[vm->size() + 1];
      int colores[vm->size() + 1][q];
      int[vm->size() + 1] nodoColor;
      
      for(int i = 1; i <= vm->size(); i++)
      {
        for(int j = 1; j <= q; j++)
          colores[i][j] = 1;

        nodoColor[i] = 0;
      }

      for(int i = 1; i <= maxClique->size(); i++)
      {
        arrK[i] = maxClique->at(i-1);
        labeled[i] = true;
        Uk[i] = new vector<int>();
        solsParcial[i] = w;
        nodoColor[i] = i;
      }

      int i = maxClique->size() + 1;
      for(vector< pair<int, int> >::iterator it = vm->begin(); it != vm->end(); it++)
      {
        if(find(maxClique->begin(), maxClique->end(), it->first) == maxClique->end())
        {
          arrK[i]     = it->first;
          labeled[i]  = false;
          Uk[i++] = new vector<int>();
        }
      }



      int color = 1;      
      int rank[vm->size()];     // Diccionario de nodo a rango

      int n = vm->size();
      int s;
      bool back = false;
      int k = w + 1;
       for()
      
      while(false)
      {
        if(!back)
        {
          int uk = solsParcial[k-1];
          int min;
          if(uk + 1 < q - 1) min = uk + 1;
          else              min = q - 1;

          listAdy[arrK[k]]

        } else
        {

        }
        // si no back uk es el numero de colores en la solucion parcial 
      }
    }
};  