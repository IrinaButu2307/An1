#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <ctype.h>
#include<string.h>
#include <fstream>

using namespace std;

struct functie
{
    char nodinitial;
    char nodfinal;
    char muchie;
} v[30];

int main()
{
    int n, m, i, j, dim, tip, numar, k=0;//TAB!!!
    char st;
    char l, s[100];
    char x;

    ifstream fin("afd.txt");

//cout<<" nr de elem in multimea de stari"<<endl;
    fin>>n;
//cout<<"dati elem din multimea de stari"<<endl;
    for(i=0; i<n; i++)
        fin>>st;
//cout<<"dati nr de stari finale ";
//cout<<endl;
    fin>>m;
    char f[20];
    for (i=0; i<m; i++)
        f[i]='0';
    for(i=0; i<m; i++)
{
    //cout<<" o stare finala"<<endl;
        fin>>x;
        f[i]=x;
}

//cout<<"dati cardinalul functiei de tranzitie"<<endl;
    fin>>n;


    for(i=0; i<n; i++)
{
        fin >> v[i].nodinitial >> v[i].nodfinal >> v[i].muchie;
        if(v[i].nodinitial >= 'a' && v[i].nodinitial <= 'z')
            tip = 1;
    else
        tip = 0 ;
}

    int ok;
    int nr;
    char c;

    if(tip == 0)//nodurile sunt cifre
    {
        cout << "dati un nr care sa repr starea initiala q0"<<endl;
        cin >> nr;
    }
    else
    {
        cout << "dati o litera care sa repr starea initiala q0"<<endl;
        cin >> c;
    }

    cout << "dati cuvantul de verificat"<<endl;
    cin >> s;
    for(i=0; i < strlen(s); i++)
{

    ok = 0;
    l = s[i];
    if(l=='*')
    {
        cout << "cuvantul vid nu este acceptat";
        return 0;
    }

    for(j=0; j< n; j++)//verific toate "perechile" din functie
       if(tip == 0)//nodurile sunt cifre
          {
            if(v[j].nodinitial-'0' == nr && v[j].muchie == l)
           {
               nr = v[j].nodfinal-'0';//actualizez punctul de inceput al urmatorului pas
               j = n;
               ok = 1;
           }
          }
          else //nodurile sunt litere
                if(v[j].nodinitial == c && v[j].muchie == l)
          {
              c = v[j].nodfinal;
              j = n;
              ok = 1;
          }

    if(ok == 0 )
    {
        cout << "cuvant neacceptat, din cauza unei litere care nu se verifica";
        return 0;
    }

}

    for(i = 0; i < m; i++)
        if(tip == 0)
            if(nr == f[i]-'0')
              {
                  cout << "cuvant acceptat";
                  return 0;
              }
                    else
            if(c == f[i])
            {
                cout << "cuvant acceptat";
                return 0;
            }
    cout <<  "cuvant neacceptat, nu exista starea finala dorita";
    fin.close();
    return 0;
}
