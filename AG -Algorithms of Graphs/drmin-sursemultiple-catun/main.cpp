#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#define infinit 23843

using namespace std;

void Dijkstra( int n,int *(&fort), vector<pair<int,int>> *la)
{
	int u,  *tata, *viz,i,v,j;
	int *d,w_uv;

	d=new int[n+1];
	tata=new int[n+1];
	viz=new int[n+1];

	for(u=1;u<=n;u++){
		viz[u]=tata[u]=0;
		d[u]=infinit;
	}
	int ok=0;
	for(i=1; i<= n; i++)
        if(fort[i]!=0)
                d[fort[i]]=0; ///toate distantele din forturi 0


	priority_queue <pair<int,int>> Q; //pereche {-d[u],u} - distanta cu -, pentru a se comporta ca min-heap
	for(i=1; i<= n; i++)
    {
        if(fort[i]!=0)
        Q.push(make_pair(-d[fort[i]],fort[i]));

	}
	while(!Q.empty()){

		u=Q.top().second;//varful nevizitat cu d minim
	    Q.pop();
		viz[u]++;

		//daca este prima extragere din Q a lui u actualizam etichetele vecinilor nevizitati
		if(viz[u]==1){
			for(j=0;j<la[u].size();j++)
                {

			    v=la[u][j].first;
			    w_uv=la[u][j].second;

			//	if(viz[v]==0) {
					if(d[v] > w_uv+ d[u]){
						tata[v]=u;

						fort[v]=fort[u];

						d[v]=w_uv+ d[u];
	  				    Q.push(make_pair(-d[v],v)); //adaug noua pereche v,d[v]
	  				}
	  				else
	  				if (d[v]==w_uv+ d[u] && fort[u]<fort[v])
	  				    fort[v]=fort[u];
				}
		    //}

		}
	}

	cout<<"caunele au tatii   ";
	for(i=1; i<=n; i++)
        cout<<tata[i]<<" ,";

        cout<<endl;

}
int main()
{

    ifstream f("catun.in");
    int n, m, i, k,x ,y, c, a;

    f>>n>>m>>k; ///nr asez, nr drumuri, nr fortarete
    int *asez, *fort;
    asez=new int [n+1];
    fort= new int [n+1]; ///aici retin apartenenta cetatilor

    for(i=1; i<=n; i++)
        fort[i]=0;
    for(i=1; i<=k ; i++)
        {
            f>>a;
            fort[a]=a;  ///initial doar fortaretele sunt nenule
        }

    vector<pair<int,int>> *la;
	la=new vector<pair<int,int>>[n+1];

	for(i=1;i<=m;i++){
		f>>x>>y>>c;
		la[x].push_back(make_pair(y,c));
		la[y].push_back(make_pair(x,c));
	}
	f.close();

	Dijkstra (n, fort, la);

	cout<<"forturi"<<endl;
    for (int i = 1; i <= n; i++)
    if (fort[i] == i)///chiar fortul insusi
      cout << "0 ,";
    else
      cout << fort[i]<<" ,";
///dist ramane nula pt cetatile ce nu pot depinde de fortarete

    return 0;
}
