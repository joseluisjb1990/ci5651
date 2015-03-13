#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void dp(vector<int>* numeros)
{
		for(vector<int>::iterator it = numeros->begin(); it != numeros->end(); it++)
		{
			cout << *it << endl;
		}
}
int main()
{
	vector<int>* numeros;
	int n;
	int buff;
	string entrada;
	cin >> n;

	while(n != -1)
	{
		getline(cin, entrada);
		stringstream ss(entrada);
		numeros = new vector<int>();

		while(ss >> buff)
			numeros->push_back(buff);

		dp(numeros);
		
		cin >> n;
	}
}