#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;


void afiseaza(int n, int *r, ofstream &g){
	int k;
     for(k=1;k<=n;k++)
		g<<r[k]<<" ";
	g<<endl;
}

struct muchie{
    int vi,vf;
    double cost;

};

void afis(muchie m, ofstream &g){
    g<<"("<<m.vi<<", "<<m.vf<<") cost "<<m.cost<<endl;
}

//--------KRUSKAL

void Initial(int u, int *tata, int *h)
{
        tata[u]=h[u]=0;
}


/*fara compresie de cale
int Reprez(int u)
{
    while(tata[u]!=0)
       u=tata[u];
    return u;
}*/

//cu compresie de cale
int Reprez(int u, int *tata ){
  if (tata[u]==0)
	return u;
  tata[u]=Reprez(tata[u], tata);
  return tata[u];
}

//reuniune ponderata - dupa inaltimea h
void Reuneste(int u, int v, int *tata, int *h)
{
    int ru,rv;
	ru=Reprez(u,tata);
	rv=Reprez(v,tata);
	if (h[ru]>h[rv])
		tata[rv]=ru;
	else{
		tata[ru]=rv;
		if(h[ru]==h[rv])
			h[rv]=h[rv]+1;

	}

}



int comp(muchie x, muchie y){
	if(x.cost<y.cost)
		return 1;
	return 0;
}

void kruskal(int n, int m, muchie *muchii, vector<muchie> &muchii_apcm, ofstream &g){

    int nrmsel, mc,*tata,*h,u,v,i;

    //structura de date folosita-paduri de multimi disjuncte
    tata=new int[n+1];
    h=new int[n+1];

    //initializarea componenetelor
  	for(v=1;v<=n;v++)
		Initial(v,tata,h);

    nrmsel=0;//numarul de muchii deja selectate;
    mc=0;//indicele muchiei curente

    //initial muchiile se sorteaza crescator dupa cost
    sort(muchii,muchii+m, comp);

    g<<"muchii sortate dupa cost:"<<endl;
    for(i=0;i<m;i++)
		afis(muchii[i],g);

    //while(mc<m && nrmsel<n-1){
	for(mc=0;mc<m;mc++)
	{
		g<<"muchia curenta: ";
		afis(muchii[mc],g);
		u=muchii[mc].vi;
		v=muchii[mc].vf;

		if (Reprez(u,tata)!=Reprez(v, tata)){  //muchia uneste doua componente diferite
	    	nrmsel++;
	    	muchii_apcm.push_back(muchii[mc]);

	        Reuneste(u,v,tata,h);
	        if(nrmsel==n-1)
	            break;
		}
		g<<"tata:" ;
        afiseaza(n,tata,g); //pentru a urmari evolutia padurilor disjuncte
        g<<"h   :" ;
        afiseaza(n,h,g);
    }
    g<<"tata:" ;
    afiseaza(n,tata,g); //pentru a urmari evolutia padurilor disjuncte
    g<<"h   :" ;
    afiseaza(n,h,g);

}

int main(){
	fstream f("kruskal.in",ios::in);
	ofstream g("kruskal_p.out");
	int m,n,mc,i;
	muchie *muchii;

	f>>n;
	f>>m;
	muchii=new muchie[m];//graf- memorat ca lista de muchii
	for(i=0;i<m;i++)
		f>>muchii[i].vi>>muchii[i].vf>>muchii[i].cost;
	f.close();

    vector<muchie> muchii_apcm;
    kruskal(n,m,muchii,muchii_apcm,g);


    if (muchii_apcm.size()<n-1) g<<"graful nu este conex";
    else {
    	double cost=0;
    	g<<endl<<"muchiile arborelui partial optim:"<<endl;
    	for(mc=0;mc<muchii_apcm.size();mc++){
			afis(muchii_apcm[mc],g);
    		cost+=muchii_apcm[mc].cost;
    	}
    	g<<"cost total "<<cost;
	}
    g.close();

	return 0;

}












/*
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

int n, m;
int lm[100][3], tata[20], h[10], cost;

void initializare (int u)
{
    tata[u] = h[u] = 0;
}
/*
int reprez(int u)  ///pt varianta cu culori
{
    while (tata[u] != 0)
        u=tata[u];
    return u;
}


int reprez(int u) ///compresie de cale
{
    if (tata[u]==0)
        return u;
    tata[u]=reprez(tata[u]);  ///tatal "suprem" vfurilor de pe lant se seteaza ca radacina
    return tata[u]; ///faciliteaza cautarile ulterioare
}

///desi arb se modifica, h[rad] ramane cea initiala

void reuneste(int u, int v) //rad unui arb devine fiu al rad celuilalt
{   ///reprez(u)==reprez(v) nu e tratat
    int ru, rv;
    ru = reprez(u);
    rv = reprez(v);
    if(h[ru] > h[rv])
        tata[rv]=ru; /// rad cu rang mic va indica catre rad cu rang mare
        ///arbore ponderat
    else
    {
        tata[ru] = rv;  ///arbore ponderat
        if (h[ru] == h[rv])
            h[rv] ++; ///cazul 1 aici merge
            ///h[ ] - inalt din nodul din arb nou format
    }
}

void kruskal( )
{
    int i, j, k, c, aux, nrmsel;
    ///ordonare crescatoare in functie de cost
    for(i=1; i <= m-1; i ++)
     for(j=i+1; j<= m; j++ )
        if(lm[i][2] > lm[j][2])
    {///incomplet
        /*
        aux = lm[i][2];
        lm[i][2] = lm[j][2];
        lm[j][2] = aux;

        swap(lm[i][0],lm[j][0]);
        swap(lm[i][1],lm[j][1]);
        swap(lm[i][2],lm[j][2]);
    }

    ///initializare
    for (i = 1; i <=n; i ++)
        initializare(i);

    nrmsel=0;

    ///actualizare
    for(k = 1; k <= m; k ++)
    {
        i = lm[k][0]; //vf1;
        j = lm[k][1]; // vf2;
        c = lm[k][2]; //cost
        if(reprez(i) != reprez (j))
        {
            reuneste(i, j);
            nrmsel++;
            if(nrmsel==n-1)
                break;
        }

    }

}



int main()
{
    int i, j, x, y, z;
    ifstream f("kruskal.txt");
    f>>n>>m;
    for(i = 1; i <=m ; i ++)
    {
        f>>x>>y>>z;
        lm[i][0] = x;
        lm[i][1] = y;
        lm[i][2] = z;
    }

    kruskal( );
    for(i=1; i<=m; i++)
        cout<<lm[i][2]<<" ";

    for(i=1; i<=n; i++)
        cout<<"nodul "<< i<<"are tata "<< tata[i]<<" si h "<<h[i]<<endl;


    return 0;
}
*/
