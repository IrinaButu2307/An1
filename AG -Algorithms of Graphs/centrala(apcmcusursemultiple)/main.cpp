#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <queue>

#define infinit 3029

using namespace std;

pair< double, double > *cladiri;

double cost(int i, int j){

	return sqrt((cladiri[i].first - cladiri[j].first)*
		(cladiri[i].first - cladiri[j].first) +
		(cladiri[i].second - cladiri[j].second)*(cladiri[i].second - cladiri[j].second)); //determinarea costului
}

void afiseaza(int n, int *r){
	int k;
	cout<<" T: ";
    for(k=1;k<=n;k++)
     	cout<<r[k]<<"  ";

	cout<<endl;
}
void afiseazad(int n, double *r){
	int k;
     for(k=1;k<=n;k++)
     	if(r[k]<infinit)
			cout<<r[k]<<"  ";
		else
		    cout<<"inf ";
	cout<<endl;
}

void Prim( int n,int k, vector<pair<int,double>> *la,  vector<pair<pair<int,int>,double>> &muchii_apcm, ofstream &g){
	int u,  *tata, *viz,i,v,j;
	double *d,w_uv;

	//*initializare d,tata,viz
	d=new double[n+1];
	tata=new int[n+1];
	viz=new int[n+1];

	for(u=1;u<=n;u++){
		viz[u]=tata[u]=0;
		d[u]=infinit; ///infinit
	}
	for (i=1; i<=k;i++)
        d[i]=0; ///!!!!!!!!!!!!!!!!!!!!!!! 0 pt noduri de start

	priority_queue <pair<double,int>> Q; //pereche {-d[u],u} - distanta cu -, pentru a se comporta ca min-heap

	for(i=1; i<=k; i++)
	Q.push({-d[i],i}); // varfuri de start

	while (!Q.empty())
    {
		u=Q.top().second;//varful nevizitat cu d minim
	    Q.pop();
		viz[u]++;

		//daca este prima extragere din Q a lui u actualizam etichetele vecinilor nevizitati
		if(viz[u]==1)
            {
		    cout<<"extras "<<u <<endl;
			for(j=0;j<la[u].size();j++)
                {
			    v=la[u][j].first; ///nod
			    w_uv=la[u][j].second; /// cost
				if(viz[v]==0 && d[v]>w_uv)
					{
					    tata[v]=u;
						d[v]=w_uv;
	  				    Q.push(make_pair(-d[v],v)); //adaug noua pereche v,d[v]
	  				}
				}
		    }
			cout<<"d:   ";
			afiseazad(n,d);
			g<<"tata:";
			afiseaza(n,tata);
		}

	for(u=1;u<=n;u++)
		if(tata[u]!=0) //u!=s
        {
            cout<<"BAG "<< u<< ", "<<tata[u]<< "  ,"<<d[u]<<endl;
			muchii_apcm.push_back(make_pair(make_pair(u,tata[u]),d[u]));
        }
}
int main(){
	fstream f("retea.in");
	ofstream g("retea2.out");
	int m,n, i,j,e, s,mc, a, b;
	double x, y;
	vector<pair<int,double>> *la;
	f>>n; //centrale
	f>>m;
	f>>e;

	la=new vector <pair <int,double> >[n+m+ 1];
    cladiri=new pair <double, double> [n+m+1];

    //citim muchiile
	for(i=1;i<=m+n;i++){
		f>>x>>y; ///coord puncte...
		cladiri[i]=make_pair(x,y);
	}

	for(i=1; i<=e; i++)
    {
        f>>a>>b;
        la[a].push_back(make_pair(b,cost(a, b)));
		la[b].push_back(make_pair(a,cost(a, b))); ///cost=dist dintre pct
    }
	f.close();

    vector<pair<pair<int,int>,double>> muchii_apcm;


    Prim(n+m,n,la,muchii_apcm,g);


  double cost=0;
    	cout<<endl<<"muchiile arborelui de cost minim:"<<endl;
    	for(mc=0;mc<muchii_apcm.size();mc++){
			cout<<muchii_apcm[i].first.first<< " , "<<muchii_apcm[i].first.second<<" , "<<muchii_apcm[i].second;
            cost+=muchii_apcm[mc].second;
            cout<<endl;
    	}
    	cout<<"cost total "<<cost;

   // g.close();

	return 0;

}





