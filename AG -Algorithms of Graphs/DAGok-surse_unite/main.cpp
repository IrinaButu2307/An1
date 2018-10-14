#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int mat [100][100]; ///unde retin duratele

void sortareTopologica(queue<int> &q,int *din,int n,int mat[100][100],int *cost){
    int viz[100]={0},nod;

    queue<int> myqueue;
    myqueue.push(n+1);

    int *d;
    d=new int[n+3];
    for(int i=0;i<=n+2;i++)
        d[i]=0;

    while(!myqueue.empty()){
        nod=myqueue.front();
        myqueue.pop();
        cout<<nod<<" ";
        q.push(nod);
        viz[nod]=1;
        for(int j=1;j<=n+1;j++)
            if(mat[nod][j]!=-10000&&viz[j]==0){
                din[j]--;
                if(din[j]==0)///daca nu mai intra nimic in nod
                myqueue.push(j);
                d[j]=d[nod]+1; ///cresc distanta fata de start pt a sti cine intra in term
            }
        }
    int maxim=0;
    for(int i=1;i<=n;i++)
        if(d[i]>maxim)
            maxim=d[i]; ///cele mai departate noduri de sursa sunt cele care vor intra in destinatie
    for(int i=1;i<=n;i++)
        if(d[i]==maxim){
        mat[i][n+2]=cost[i-1]; ///destinatia (i, t) arc!
        }
    q.push(n+2); ///si el adaugat
    cout<<n+2;

}

void DAGs(int n,queue<int> myqueue,int *d,int *tata){
    int nod;
    d[myqueue.front()]=0;
    while(!myqueue.empty()){
        nod=myqueue.front();
        myqueue.pop();
        for(int j=1;j<=n+2;j++)
            if(mat[nod][j]!=-10000) ///daca exista aceasta activitate
                if(d[j]<mat[nod][j]+d[nod]){
                    d[j]=mat[nod][j]+d[nod];
                    tata[j]=nod;
                }
    }
}

int main()
{
    ifstream fin("grafpond.in");
    int n,x,y,m;
    fin>>n;///n activitati
    int *cost,*din;
    cost=new int[n+3];
    din=new int [n+3];

    for(int i=0;i<=n+3;i++)
        for(int j=0;j<=n+3;j++)
            mat[i][j]=-10000;

    for(int i=0;i<=n;i++)
        din[i]=0;

    for(int i=0;i<n;i++)
        fin>>cost[i];
    fin>>m; ///m perechi

    for(int i=0;i<m;i++){
        fin>>x>>y;
        din[y]++;
        mat[x][y]=cost[x-1];
    }

    for(int i=1;i<=n;i++)
        if(din[i]==0){ ///daca din[i]==0 atunci trb unit la o sursa
            mat[n+1][i]=0; /// (s, i) arc
            din[i]++; ///le cresc din pt ca le leg de sursa
            din[n+1]=0;
        }
    queue<int> myqueue;
    sortareTopologica(myqueue,din,n,mat,cost);
    int *d,*tata;
    d=new int[n+3];
    tata=new int [n+3];
    for(int i=0;i<=n+2;i++){
        d[i]=-10000;
        tata[i]=0;
    }
    DAGs(n,myqueue,d,tata);
    cout<<endl<<"Durata minima "<<d[n+2]<<endl;
    cout<<"Activitati critice :";
    int i=n+2;
    i=tata[i];
    while(tata[i]){
        cout<<i<<" ";
        i=tata[i];
    }

    cout<<endl<<"Intervale de desfasurare :"<<endl;
    for(int i=1;i<=n;i++){
        cout<<"Activitatea "<<i<<": "<<d[i]<<" "<<d[i]+cost[i-1]<<endl; ///durata activitatilor este de cand incepe plus cat dureaza
    }

    return 0;
}
