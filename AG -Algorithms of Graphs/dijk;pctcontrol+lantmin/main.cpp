#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#define infinit 3200

using namespace std;
struct muchie {
       int vi;
       int vf;
       int cost;
};

int  tata[100], viz[100], d[100];

void dijkstra(int s, int n, vector <pair<int,int>> *la, vector<muchie> &adm)
{
    int u, i, j, w, v;

	for (u = 1; u <= n; u++) {
		viz[u] = tata[u] = 0;
		d[u] = infinit;
	}
	d[s] = 0;
    priority_queue<pair <int, int>> Q; //-cost, muhcie
    Q.push({-d[s], s});
    while (!Q.empty())
    {
        u=Q.top().second;
        Q.pop();
        viz[u]++;

        if(viz[u]==1)
        {
            for(j=0; j<la[u].size(); j++)
            {
                v=la[u][j].first;
                w=la[u][j].second;
                if( d[u]+ w < d[v])
                   {
                     d[v]=d[u]+w;
                     tata[v]=u;
                     Q.push({-d[v], v});
                   }

            }
        }
    }

    for(i=1; i<=n; i++) ///
        if (tata[i]!=0)
    adm.push_back({u, tata[u], d[u] });///sau invers?????


}

int main()
{
       muchie* v;
       int n, m,nr, x, y, c, k;
       ifstream fin("grafpond.in");

       fin >> n >> m;
       vector<pair<int, int>> *la;
       la=new vector <pair< int, int>> [n+1];
       //v = new muchie[m + 1];
       for (int i = 1; i <= m; i++) {
           fin>>x>>y>>c;
           la[x].push_back({y, c});
           la[y].push_back({x, c});
       }
       cout<<"dati nr de pct de control";
       cin>>k;
       int *control,s;
       control = new int[k];
       cout<<"dati vectorul de puncte de control"<<endl;
       for (int i = 0; i < k; i++) {
              cin >> control[i];
       }
       cout<<"dati nr de start"<<endl;
       cin>> nr;

       fin.close();

       int  min = 10000,nod, cost=0;
       vector <muchie> adm;
       cout<<"inainte de dijkstra"<<endl;

       dijkstra(nr, n, la, adm);


 ///aici mereu am pb cu fucking arborele :)))

       cout<<endl<<"muchiile arborelui de cost minim:"<<endl;
    	for(int mc=0;mc<adm.size();mc++){
			cout<<adm[mc].vi<<" , "<<adm[mc].vf<<" , " <<adm[mc].cost<<endl;
    		cost+=adm[mc].cost;
    	}
    	cout<<"cost total "<<cost;


       for (int i = 0; i < k; i++)
              if (d[control[i]] < min) {
                    min = d[control[i]];
                    nod = control[i];
              }
       cout <<"Drumul minim este " <<min <<" si duce in "<<nod<< endl;
       cout << "Drumul este:" << endl;
       while (tata[nod]!=0) {
              cout << nod << " ";
              nod = tata[nod];
       }
       cout << nod << endl;


    return 0;
}

/*

void Dijkstra(int s,int m, int n, muchie *v, int *(&d),int *(&tata)) {
       int nod;
       for (int i = 0; i <= n; i++) {
              d[i] = 10000;
              tata[i] = 0;
       }
       d[s] = 0;
       queue<int> myqueue;
       myqueue.push(s);
       while (!myqueue.empty()) {
              nod = myqueue.front();
              myqueue.pop();
              for (int i = 1; i <= m; i++)
                    if (v[i].vf == nod) {///vecin
                           if (d[v[i].vi] > d[v[i].vf] + v[i].cost) {
                                  d[v[i].vi] = d[v[i].vf] + v[i].cost;
                                  tata[v[i].vi] = v[i].vf;
                                  myqueue.push(v[i].vi);
                           }
                    }
                    else
                           if(v[i].vi==nod)
                                  if (d[v[i].vf] > d[v[i].vi] + v[i].cost) {
                                         d[v[i].vf] = d[v[i].vi] + v[i].cost;
                                         tata[v[i].vf] = v[i].vi;
                                         myqueue.push(v[i].vf);
                                  }
       }
}

int main()
{
       muchie* v;
       int n, m,nr;
       ifstream fin("grafpond.in");
       fin >> n >> m;
       v = new muchie[m + 1];
       for (int i = 1; i <= m; i++) {
              fin >> v[i].vi >> v[i].vf >> v[i].cost;
       }
       fin >> nr;
       int *cautate,s;
       cautate = new int[nr];
       for (int i = 0; i < nr; i++) {
              fin >> cautate[i];
       }
       fin >> s;
       fin.close();
       int *d, *tata, min = 10000,nod;
       d = new int[n + 1];
       tata= new int[n + 1];
       Dijkstra(s, m, n, v, d,tata);
       for (int i = 0; i < nr; i++)
              if (d[cautate[i]] < min) {
                    min = d[cautate[i]];
                    nod = cautate[i];
              }
       cout <<"Drumul minim este " <<min <<" si duce in "<<nod<< endl;
       cout << "Drumul este:" << endl;
       while (tata[nod]!=0) {
              cout << nod << " ";
              nod = tata[nod];
       }
       cout << nod << endl;


    return 0;
}*/
