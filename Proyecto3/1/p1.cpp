#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void dp(string abbr, vector<string>* palabras, vector<string>* ign)
{
	int cantLetras 	= palabras->size();
	int cantAbbr 	= abbr.size();

	int Memo[cantAbbr][cantLetras]
}

int main()
{
	int n;

	string abbr;
	string buf;
	string entrada;
	cin >> n;
	vector< string >* frases  = new vector<string>();
	vector< string >* ignorar = new vector<string>();

	while (n != 0)
	{
		ignorar = new vector<string>();
		
		for(int i = 0; i < n; i++)
		{
			string entrada;
			cin >> entrada;
			ignorar->push_back(entrada);
		}

		getline(cin, entrada);

		while(true) 
		{
			string entrada;
			getline(cin, entrada);
			if(entrada.compare(string("LAST CASE")) == 0) break;
			
			frases  = new vector<string>();
			
			stringstream ss(entrada);
			ss >> abbr;
			while(ss >> buf) {
				frases->push_back(buf);
			}

			dp(abbr, frases, ignorar);


		}
		cin >> n;
	}
	return 0;
}