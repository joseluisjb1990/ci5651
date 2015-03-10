#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

vector<string>* words;
vector<string>* ignWords; 
string abbr;

int abbrWordAux(string word, int posWord, int posAbbrI, int posAbbrF)
{
  int r = 0;

  for(int i = posWord; i < word.size(); i++)
  {
    if(word[i] == abbr[posAbbrI])
    {
      if(posAbbrI == posAbbrF)
      {
        r++;
      } else
      {
        r += abbrWordAux(word, i+1, posAbbrI+1, posAbbrF);
      }
    }
  }
  return r;
}

int abbrWord(int posWords, int posAbbrI, int posAbbrF)
{
  string word  = words->at(posWords);
  return abbrWordAux(word, 0, posAbbrI, posAbbrF);
}

int dp()
{
  int nWords  = words->size();
  int nAbbr   = abbr.size();
  int memoMatrix[nAbbr][nWords];

  for(int i = 0; i < nWords; i++)
    memoMatrix[0][i] = 0;

  for(int i = 0; i < nAbbr; i++)
    memoMatrix[i][0] = abbrWord(0, 0, i);

  for(int i = 1; i < nWords; i++)
  {
    for(int j = 1; j < nAbbr; j++)
    {
      memoMatrix[j][i] = 0;
      for(int k = j; k >= i; k--)
      {
        memoMatrix[j][i] += memoMatrix[k-1][i-1] * abbrWord(i, k, j);
      }
    }
  }
  return memoMatrix[nAbbr-1][nWords-1]; 
//      cout << endl;
//      for(int j = 0; j < abbr.size(); j++)
//      {
//        for(int k = 0; k < words->size(); k++)
//          cout << memoMatrix[j][k];
//        cout << endl;
//      } 

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

    getline(cin, in); //Consumimos una linea vacia
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

      int r = dp();

      for(int i = 0; i < abbr.size(); i++) abbr[i] = toupper(abbr[i]);

      if(r==0) cout << abbr << " is not a valid abbreviation" << endl;
      else     cout << abbr << " can be formed in " << r << " ways" << endl;

      getline(cin, in);
    }

    cin >> n;
  }
  return 0;
}

