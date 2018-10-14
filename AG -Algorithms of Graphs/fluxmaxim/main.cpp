#include <iostream>
#include <queue>
#include<fstream>
#include <vector>

#define NMX 10002
using namespace std;


int tata[NMX],n,m,viz[NMX], viz2[NMX];
vector<int> l[NMX];
vector<int> lin[NMX];
int f[NMX][NMX],cost[NMX][NMX];

int bf(int s, int t){
    int i,x;
    for(i=0; i<=NMX; i++)
        tata[i]=viz[i]=0;

    queue<int> c;

    c.push(s);
    viz[s]=1;
    while(c.size()>0){
        x=c.front();
        c.pop();
        for(i=0;i<l[x].size();i++) ///arc direct
        {
            int y=l[x][i];
            if(viz[y]==0 && f[x][y]<cost[x][y])///FLUX NU FULL
                {
                tata[y]=x;
                c.push(y);
                viz[y]=1;

                if(y==t)
                    return 1;
                }
        }
        for(i=0;i<lin[x].size();i++) ///arc invers
        {
            int y=lin[x][i];
            if(viz[y]==0 && f[y][x]>0){  ///FLUX NENUL
                tata[y]=-x; ///!!!!!!!!!!!!!
                c.push(y);
                viz[y]=1;

                if(y==t)
                    return 1;
            }
        }
    }
    return 0;
}

int main(){
    ifstream fin("retea.in");
    ofstream fout("retea.out");

    int i,x,y,j, start, term, t;
    int c, flux, cop;

    fin>>n; cop=n;
    int valfluxpoz[100]={0}, valfluxneg[100]={0};
    fin>>start>>term;
    fin>>m;

    for(i=1;i<=m;i++){
        fin>>x>>y>>c>>flux;
        if(0<= flux && flux<=c) ///COND 1-
        {
        l[x].push_back(y);
        lin[y].push_back(x); ///liste adiacenta intrare --pt directie arc!

        cost[x][y]=c; ///tin cont de directia arcului
        f[x][y]=flux;

        valfluxpoz[x]+=flux;
        valfluxneg[y]+=flux;
        }
        else {cout<<"NU"<<endl;
        break;
        return 0;}
    }

    /// ATENTIE LA VF DE START SI LA CEL DE FINAL !!!
    ///LOR TRB SA LE ADAUG EU VALORILE PT FLUX NEG SAU POZ...
    ///PT CA DIN ELE NU INTRA/ IESE NIMIC si trebuie pt a funtiona alg

    valfluxneg[start]=valfluxpoz[start];
    valfluxpoz[term]=valfluxneg[term];
   ///
   ///

    for(i=1; i<=n; i++)
        if(valfluxneg[i]!=valfluxpoz[i])  ///COND 2 -
    {
        cout<<"NU val flux";
        break;
        return 0;
    }

    fin.close();
   /// int fmax=0; /// ar fi fost 0 pt standard
   int fmax=valfluxpoz[start]; ///ASA !!!!!!!!!!

    cout<<"inainte de bf"<<endl;
    while(bf(start, term))
        {
		//calculam i(P) = capacitatea reziduala minima pe un arc de pe drumul de la s la t determinat cu bf
        int iP=1100; //i(P)
        t=term;
        fout<<"lantul (afisat invers -tema de modificat): ";
        cout<<"lantul (afisat invers -tema de modificat): ";

        while(t!=start)  { ///ACTUALIZARE IP
        	fout<<t<<" ";
        	cout<<t<<" ";
            if(tata[t]>=0){ ///arc direct - capacitate c(e)-f(e)
                if(cost[tata[t]][t]-f[tata[t]][t] < iP)
                    iP= cost[tata[t]][t]-f[tata[t]][t];
                t=tata[t];
            }
           else{ ///arc invers - capacitate f(e)
                if( f[t][-tata[t]] < iP)
                   iP= f[t][-tata[t]];
                t=-tata[t]; ///!!!!!!!!!!!!!!
               }
        }
        fout<<start<<" ";
        cout<<start<<" ";
        cout<<"capacitate "<<iP<<endl;
        fout<<" capacitate "<<iP<<endl;


          ///REVIZUIM FLUXUL  de-a lungul lantului determinat
        t=term;
        while(t!=start)  {
            if(tata[t]>=0 ){ ///arc direct - creste fluxul cu iP
                f[tata[t]][t]+=iP;
                t=tata[t];
            }
            else{///arc invers - scade fluxul cu iP
                f[t][-tata[t]]-=iP;
                t=-tata[t];
            }
        }
        fmax+=iP; ///creste valoarea fluxului cu iP
        t=term;
    }

    fout<<"-----------------------------------------"<<endl;
    fout<<"valoarea fluxului maxim = "<<fmax<<endl;
    cout<<"valoarea fluxului maxim = "<<fmax<<endl;


    fout<<"un flux maxim: "<<endl;
    cout<<fmax<<endl;

    for(i=1;i<=n;i++)
    	for(j=0;j<l[i].size();j++){ ///fiecare vecin
    		int v=l[i][j];
    		//fout<<"arcul "<<u<<" "<<v<<" flux "<<f[u][v]<<endl;
    		cout<<"arcul "<<i<<" "<<v<<" flux "<<f[i][v]<<endl;
		}
    fout<<"taietura minima"<<endl;
    cout<<"taietura minima"<<endl;


    int fluxtaietura=0;
    for(i=1; i<=cop; i++)
    {
    if (viz[i]==1)
    for(auto j:l[i])
    {
        if(viz[j]==0)   ///are o extremitate vizitata si cealalta nevizitata indreptata spre destinatie
            {cout<<"taietura "<<i<<" , "<<j<<endl;
            fluxtaietura+=f[i][j];}
    }

    }


    fout.close();



    return 0;
}
