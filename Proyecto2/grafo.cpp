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
    
      return color;
    }

    int brelazModificado()
    {
      vector<int>* maxClique = maximalClique();
      vector< pair<int, int> >* vm = sortByDegree();
                
      int   arrK[vm->size() + 1];        // Arreglo de indice k y entrada etiqueta de nodo
      int   rank[vm->size() + 1];        // Arreglo de indice etiqueta de nodo y entrada k
      int   solsParcial[vm->size() + 1]; // Cantidad de colores en la solucion parcial k-1
      bool  labeled[vm->size() + 1];
      int w = maxClique->size();
      int q = Dsatur();
      vector<int>* Uk[vm->size() + 1];
      int colores[vm->size() + 1][q];
      int nodoColor[vm->size() + 1] ;     // Arreglo que tiene para cada nodo (k-indx) su color
      
      // Matriz de colores, las filas son nodos y las columnas colores disponibles
      // para ese nodo. el nodoColor representa el color de ese nodo.
      // Tanto esta matriz, como el nodoColor es k-indexado.
      for(int i = 1; i <= vm->size(); i++)
      {
      	colores[i][0] = 0;
        for(int j = 1; j < q; j++)
          colores[i][j] = 1;

        nodoColor[i] = 0;
      }

      for(int i = 1; i <= maxClique->size(); i++)
      {
        arrK[i] = maxClique->at(i-1);
        rank[maxClique->at(i-1)] = i;
        labeled[i] = true;
        solsParcial[i] = w;
        nodoColor[i] = i;
      }

      int i = maxClique->size() + 1;
      for(vector< pair<int, int> >::iterator it = vm->begin(); it != vm->end(); it++)
      {
        if(find(maxClique->begin(), maxClique->end(), it->first) == maxClique->end())
        {
          arrK[i]     = it->first;
          rank[it->first] = i;
          labeled[i]  = false;
          Uk[i++] = new vector<int>();
        }
      }



      int color = 1;      


      int n = vm->size();
      bool back = false;
      int k = w + 1;
      
      while(true)
      {
        if(!back)
        {
          int min = 0;    
          int uk = solsParcial[k-1];
          if(uk + 1 < q - 1) min = uk + 1;
          else               min = q - 1;

          // Recorro el vector de nodos adyacentes, y busco el color de cada uno
          // para eliminarlo de la matriz de colores del nodo de rango k.
          vector<int> ady = listAdy[arrK[k]];

          // Devuelvo la fila correspondiente al nodo k a 1, para determinar
          // el conjunto de colores disponibles.
          for ( int p = 1; p <= min; p++)
	      	colores[k][p] = 1;

          // Para cada nodo adyacente, eliminar su color del conjunto de colores
          // disponibles para el nodo de rango k.
          for( vector<int>::iterator it = ady.begin(); it != ady.end(); it++)
          {
          //  	if (rank[(*it)] < k) colores[k][nodoColor[rank[(*it)]]] = 0; Ciclo infinito con esta linea sin comentario
                colores[k][nodoColor[rank[(*it)]]] = 0;
          }

          for ( int e = min+1; e < q; e++)
	      	colores[k][e] = 0;

	      nodoColor[k] = 0;

        } else
        {
          // PENDIENTE ACA QUE NO SE "DESPINTA", NO ESTOY ASIGNANDO A NODOCOLOR 0.
          colores[k][nodoColor[k]] = 0;
          labeled[k] = false;
        }

        // Segundo condicional, verificar si hay colores disponibles
        bool hayColor = false;
        int colorSeleccionado = 0;
        for (int i = 1; i < q; i++)
        {
            if (colores[k][i] != 0)
            {
            	hayColor = true;
                colorSeleccionado = i;
                break;
            }
        }

        if (hayColor)
        {
            nodoColor[k] = colorSeleccionado;

            // Si colorSeleccionado es mayor, quiere decir que use un nuevo
            // color, y aumenta la cantidad de colores usados.

          	if (colorSeleccionado > solsParcial[k-1]) 
          		solsParcial[k] = solsParcial[k-1]+1;
          	else solsParcial[k] = solsParcial[k-1];

            k++;

            if (k>n) {
              q = solsParcial[k];
              // Retornar q si se llega a la menor solucion posible.
              if (q == w)
                return q;

              // Recorrer el arreglo de colores hasta encontrar el primer
              // nodo con el color q.
              int minK_colorQ = 0;
              for (int i = 1; i < vm->size() + 1; i++)
              {
                if (nodoColor[i] == q)
                {
                  minK_colorQ = i;
                  break;
                }
              }

              for (int i = minK_colorQ; i < vm->size() + 1; i++) {
                labeled[i] = false;
              }

              k = minK_colorQ;
              back = true;
            } else
            {
              back = false;
            }

        } else
        {
          back = true;
        }

	    if(back)
	    {
	      vector<int> ady = listAdy[arrK[k]];
	      bool candidato;
	      for(vector<int>::iterator it = ady.begin(); it != ady.end(); it++)
	      {
	      	candidato = true;
	      	int adyActual = *it;
	      	int rankAdy = rank[adyActual];
	      	if(rankAdy < k)
	      	{
	      		int colAdy = nodoColor[rankAdy];
	      		
	      		for(int i = 1; i < rankAdy; i++)
	      		{
	      			if(find(ady.begin(), ady.end(), arrK[i]) != ady.end())
	      				if(nodoColor[i] == colAdy) { candidato = false; break; }
	      		}
	      	} else
	      		candidato = false;

	      	if(candidato) labeled[rankAdy] = true;
	      }

	      for(int i = 1; i <= n; i++)
	      	if(labeled[i]) k = i;

	      if(k < w) {  return q; }
        }
      }
    }
}; 
