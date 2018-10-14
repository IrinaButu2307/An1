#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <cstring>
#define NMX 120

using namespace std;
int culoare[100]={0};
int pf, pi;
queue <int> c;
int tata[NMX],n,m,viz[NMX];
vector<int> l[NMX];
vector<int> lin[NMX];
int f[NMX][NMX],cost[NMX][NMX];

///cost [x][y]= 1; (x, y) muchie orientata in graf

int EDK(int s, int t)
{

    int i, j, u, v;
     for(i=0; i<=NMX; i++)
    {
        tata[i]=viz[i]=0;
    }
    queue<int> c;
    c.push(s);
    viz[s]=1;
    while (!c.empty())
    {
        u=c.front();
        cout<<u<<" ";
        c.pop();
        for(auto j: l[u]) ///arc direct
        {
        if(viz[j]==0 && f[u][j]-cost[u][j]<0)
        {
            c.push(j);
            viz[j]=1;
            tata[j]=u;
            if(j==t)
                return 1;
        }
        }
        for(auto j: lin[u]) ///arc invers //arc invers-se ia din lin
        {
            if(viz[j]==0 && f[j][u]>0)
                {
                    c.push(j);
                    viz[j]=1;
                    tata[j]=-u;
                    if(j==t)
                        return 1; ///ating terminalul "ok "
                }
        }
    }
    return 0;
}



int BF(int x, queue<int>c)
{
    int y, pas, i,nod;
    viz[x]=1;
    tata[x]=0;
    c.push(x);
    culoare[x]=1;

    while (!c.empty())
    {
        nod=c.front();
        c.pop();
        for(i=0; i<l[nod].size(); i++)
    {
        int  y=l[nod][i];
        if (viz[y]==0){
            c.push(y);
            tata[y]=nod;
            viz[y]=1;
            culoare[y]= !culoare[nod]; ///culoare opusa
        }
        else
           if(culoare[y]==culoare[nod]) ///intoarcere din ciclu
           {

            ///nivel cu aceeasi paritate
            cout<<"ciclu de lungime impara. GRAFUL NU E BIPARTIT"<<endl;

            while (tata[y]!=0){
                cout<<y<<" , ";
                y=tata[y];
            }
            cout<<y;
            cout<<endl;
            return 0;
            }
    }

    }
return 1;
}

int main()
{
    int i, j,n, m, k, x, y;
    ifstream fin("graf.in");
    fin>>n>>m;
    int fmax=0;

     for(i=0;i<=n+2;i++)
        for(j=0;j<=n+2;j++)
            f[i][j]=cost[i][j]=0;

///graful se citeste ca neorientat
    for(i=0; i<m; i++)
    {
       fin>>x>>y;
       l[x].push_back(y);
       l[y].push_back(x);
       cost[x][y]=cost[y][x]=1;
    }

    cout<<"liste initial"<<endl;
   for(i=1; i<=n; i++)
    {
        cout<<i<<" : ";
         for(auto j: l[i])
            cout<<j <<" ,";
        cout<<endl;
    }

     if(BF(1, c)==1){
         cout<<"graf bipartit"<<endl;
         cout<<"partitia 1"<<endl;
         for(i=1; i<=n; i++)
            if(culoare [i]==1)
            cout<<i<<" , ";
         cout<<endl;

         cout<<"partitia 2"<<endl;
         for(i=1; i<=n; i++)
            if(culoare [i]==0)
            cout<<i<<" , ";
         cout<<endl;
     }


       cout<<"liste dupa orientare"<<endl;
    ///orientam arcele de la culoarea 1 la culoarea 0
    ///l[x] ramane cel din graful initial pentru c in partitia 1
    ///lin se actualizeaza pentru varfurile din partitia 2 (de culoare 0)

    ///actualizare in rap cu nodurile din graf
     for(i=1; i<=n; i++)
     	if(culoare[i]==1)
     		for(auto j: l[i]) //j are sigur culoare 0 pentru ca graful este bipartit, deci arcul este orientat de la i la j
     	  		lin[j].push_back(i); ///i intra in j
     	else
		 	l[i].clear();
		 	///i are cul0, nu iese nimic din el
		 	//stergem lista de adiacenta pe iesire a lui i daca este de culoare 0, deoarece arcele intra in i, nu ies din i
            //din i va iesi doar un arc catre t


int s,t;
s=n+1; t=n+2;

///actualizare in fct de START si TERM
///adaugare start si terminal in fct de culori -> 1 -start  0-terminal
    for(i=1; i<=n; i++)
        if(culoare[i]==1) ///iese din start catre nod
      {
        l[s].push_back(i);
        lin[i].push_back(s);
        cost[s][i]=1;
      }
    else
    {
        l[i].push_back(t);
        lin[t].push_back(i);
        cost[i][t]=1;
    }

    for(i=1; i<=n+2; i++)
    {
        cout<<i<<" : ";
         for(auto j: l[i])
            cout<<j <<" ,";
        cout<<endl;
    }
    for(i=1; i<=n+2; i++)
    {
        cout<<i<<" : ";
         for(auto j: lin[i])
            cout<<j <<" ,";
        cout<<endl;
    }

   cout<<fmax<<endl;

    while (EDK(s, t)) ///actualizez
    {
        int ip= 2; //se initializeaza cu o valoare mare, aici este suficient 2, deoarce ip<=1

        while (t!=s) ///o iau pe lantul tatilor si actualizez
        {
            if (tata[t]>=0 ) ///arc direct
               {
                if(cost[tata[t]][t]-f[tata[t]][t]<ip)
                    ip=cost[tata[t]][t]-f[tata[t]][t];
                t=tata[t];
               }
            else
                if (tata[t]<0 ) ///arc invers
               {

                if(f[t][-tata[t]]<ip)
                    ip=f[t][-tata[t]];
                t=-tata[t];
               }
        }
        cout<<endl<<ip<<endl;
        t=n+2;
        while (t!=s)
            if (tata[t]>=0) ///arc direct
        {
            f[tata[t]][t]+=ip;
            t=tata[t];
        }
        else
            if(tata[t]<0) ///arc invers
        {
            f[t][-tata[t]]-=ip;
            t=-tata[t];
        }

    fmax+=ip;
    t=n+2; ///t trebuie reactualizat, este trimis parametru lui EDK;
    }

    cout<<"fmax "<<fmax<<endl;

    cout<<"un cuplaj: "<<endl;
    for(i=1; i<=n; i++)
    {
        for(auto j: l[i])
            if(f[i][j]!=0 && j!=n+2)
        		cout<<"arc "<<i<<" , "<<j;
        cout<<endl;
    }

    return 0;
}
