#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int n;
int *numeros;
int ***memoMatrix;

void initMatrix(int ***memoMatrix)
{
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      for(int k = 0; k < n; k++)
        memoMatrix[i][j][k] = 0;
}

void printMatrix(int ***memoMatrix)
{
  for(int i = 0; i < n; i++){
    cout << "Matriz " << i << endl;
    for(int j = 0; j < n; j++){
      for(int k = 0; k < n; k++){
        cout << memoMatrix[i][j][k] << " ";
      }
      cout << endl;
    }
  }
}

void dp(int asc, int des, int idx)
{
  if(idx < n)
  {
    if(asc == -1)                   dp(idx, des, idx+1);
    else if(numeros[idx] > numeros[asc]) dp(idx, des, idx+1);
    
    if(des == -1) dp(asc, idx, idx+1);
    else if(numeros[idx] < numeros[des]) dp(asc, idx, idx+1);
    
    if(des != -1 && asc != -1) memoMatrix[asc][des][idx] = 1 + memoMatrix[asc][des][idx-1]; dp(asc, des, idx+1);

    //cout << numeros[idx] << " " << numeros[asc] << " " << asc << " " << des << " " << idx << " " << n << endl;  
  }
}

int main()
{
	int buff;
	string entrada;

	cin >> n;

	while(n != -1)
	{
    numeros = new int[n];

		for(int i = 0; i < n; i++)
    {
		  cin >> numeros[i];
    }

    memoMatrix = new int**[n];
    for(int i = 0; i < n; i++)
    {
      memoMatrix[i] = new int*[n];
      for(int j = 0; j < n; j++)
          memoMatrix[i][j] = new int[n];
    }

    initMatrix(memoMatrix);
		dp(-1, -1, 0);
    //printMatrix(memoMatrix);
		
    int min = 0;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(memoMatrix[i][j][n-1] < min)
          min = memoMatrix[i][j][n-1];
    
    cout << min << endl;
		cin >> n;
	}
}
