/*
    Problema: ACMAKER
    Autores: Arturo Voltattorni, Jose Jimenez
    Fecha: 13/05/2015.
*/

#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

vector<string>* words;
vector<string>* ignWords; 
string abbr;

//Funcion para buscar todas las formas en que un acronimo puede ser usado en una palabra
int abbrWordAux(string word, int posWord, int posAbbrI, int posAbbrF)
{
  int r = 0;

  //Comenzar a revisar desde la posicion posWord de la palabra
  for(int i = posWord; i < word.size(); i++)
  {
    //Si la letra que estamos revisando en la palabra es la misma que la letra en el acronimo
    if(word[i] == abbr[posAbbrI])
    {
      //Si estamos revisando la ultima letra del rango en el alcronimo, entonces solo sumamos
      // uno por cada letra que consigamos
      if(posAbbrI == posAbbrF)
      {
        r++;

      //Si no estamos revisando la ultima letra, entonces debemos revisar el resto de las letras del acronimo
      // con el resto de la palabra, y eso lo sumamos al total
      } else
      {
        r += abbrWordAux(word, i+1, posAbbrI+1, posAbbrF);
      }
    }
  }

  return r;
}

//Funcion auxiliar para comenzar a revisar los acronimos.
int abbrWord(int posWords, int posAbbrI, int posAbbrF)
{
  string word  = words->at(posWords);
  return abbrWordAux(word, 0, posAbbrI, posAbbrF);
}

//Funcion que se encarga del aplicar el algoritmo principal
int dp()
{
  int nWords  = words->size();
  int nAbbr   = abbr.size();

  //Arreglo de memoizacion. La posicion i, j representa el numero de formas que puede usarse el acronimo desde
  //la posicion 0 hasta la i del acronimo, usando j palabras.
  int memoMatrix[nAbbr][nWords];

  //Inicializamos el arreglo para el caso en que se mas palabras que letras en el acronimo.
  for(int i = 0; i < nWords; i++)
    memoMatrix[0][i] = 0;

  //Inicializamos el arreglo para el caso en que solo se usa la primera palabra para todos los acronimos.
  for(int i = 0; i < nAbbr; i++)
    memoMatrix[i][0] = abbrWord(0, 0, i);

  //Ciclo para llenar la matriz, haciendo el recorrido por columna
  for(int i = 1; i < nWords; i++)
  {
    for(int j = 1; j < nAbbr; j++)
    {
      memoMatrix[j][i] = 0;

      //Para cada casilla i, j del arreglo, buscamos en las soluciones anteriores en la misma columna. Es decir,
      //comenzamos a revisar las posiciones anteriores en la columna y por cada una multiplicamos por la cantidad
      //de formas que se puede combinar el acronimo desde las posicion i, hasta la posicion k.
      for(int k = j; k >= i; k--)
      {
        memoMatrix[j][i] += memoMatrix[k-1][i-1] * abbrWord(i, k, j);
      }
    }
  }
  return memoMatrix[nAbbr-1][nWords-1];


}

int main()
{
  string in;
  string buf;
  int n;

  cin >> n;

  while(n != 0)
  {
    ignWords = new vector<string>();

    for(int i = 0; i < n; i++)
    {
      cin >> in;
      ignWords->push_back(in);
    }

    //Consumimos una linea vacia
    getline(cin, in);
    
    getline(cin, in);

    while(in.compare("LAST CASE") != 0)
    {
      words = new vector<string>();
      stringstream ss(in);
      ss >> abbr;
      for(int i = 0; i < abbr.size(); i++) abbr[i] = tolower(abbr[i]);
      while(ss >> buf)
        if(find(ignWords->begin(), ignWords->end(), buf) == ignWords->end())
          words->push_back(buf);

      //Aplicamos la funcion de programacion dinamica
      int r = dp();

      for(int i = 0; i < abbr.size(); i++) abbr[i] = toupper(abbr[i]);

      //Mostramos la posicion
      if(r==0) cout << abbr << " is not a valid abbreviation" << endl;
      else     cout << abbr << " can be formed in " << r << " ways" << endl;

      getline(cin, in);
    }

    cin >> n;
  }
  return 0;
}