#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nrJetoane 26
#define nrJucatori 2

//parte din punctul a
typedef struct
{
	char litera;
	int valoare;
} JETON;

//parte din punctul b
typedef struct
{
	int multiplicareLitera;
	int multiplicareCuvant;
	int ocupat;
	char litera;
	char valoare;
} PATRAT;


//parte din punctul a
int cmpJetoane(const void*a, const void*b)
{
	JETON *pa = (JETON*)a;
	JETON *pb = (JETON*)b;
	return pa->litera - pb->litera;
}

//parte din punctul a
JETON* incarcaJetoane(char* numeFisier)
{
	JETON *v = (JETON *) malloc(nrJetoane * sizeof(JETON));
	FILE *f = fopen(numeFisier,"r");
	int i;
	for (i=0;i<nrJetoane;i++)
	{
		fscanf(f,"%c %d\n",&v[i].litera,&v[i].valoare);
	}
	fclose(f);
	qsort(v,nrJetoane,sizeof(JETON),cmpJetoane);
	//afiseaza tabloul 1D sortat
	for(i=0;i<nrJetoane;i++)
		printf("%c %d \n",v[i].litera,v[i].valoare);
	return v;
}

//parte din punctele b si c
void determinaDirectieCuvant(char* pozitieTabla, int* linie, int* coloana, int* directie)
{
	int lungime = strlen(pozitieTabla);
	char c = pozitieTabla[0];
	if (c >='a' && c <= 'z')
		//directie orizontala
		{
			*directie = 1;//directie orizontala
			*linie = c - 'a';
			*coloana = pozitieTabla[1] - '1';
			if (lungime==3)
				*coloana = 10 + pozitieTabla[2]-'1';
		}
	else
		{
		    *directie = 2;//directie verticala
			*linie = pozitieTabla[lungime-1]-'a';
			*coloana = pozitieTabla[0] - '1';
			if (lungime==3)
				*coloana = 10 + pozitieTabla[1]-'1';

		}
}

//parte din punctul c
PATRAT** incarcaConfiguratieTabla(char* numeFisier, int *nrPatrate)
{
	int n,i,j;
	FILE *f = fopen(numeFisier,"r");
	//citesc linia 1
	fscanf(f,"%d",&n);
	*nrPatrate = n;
	PATRAT** tablaJoc = (PATRAT**) malloc(sizeof(PATRAT*) *n);

	printf("Dimensiune tabla este n=%d \n",n);
	for(i=0;i<n;i++)
	{
		tablaJoc[i] = (PATRAT*) malloc(sizeof(PATRAT) * n);
		for(j=0;j<n;j++)
		{   //initializare tabla de joc
			tablaJoc[i][j].multiplicareLitera = 1;
			tablaJoc[i][j].multiplicareCuvant = 1;
			tablaJoc[i][j].ocupat = 0;;
			tablaJoc[i][j].litera = ' ';
			tablaJoc[i][j].valoare = 0;
		}
	}
	char pozitieTabla[4],multiplicare[10];
	int linie, coloana, directie;
	//citesc pozitiile patratelor din fisier cu proprietati speciale
	//while(1)
	//{
		//citesc stringurile de pe linie
		while(fscanf(f, "%s %s\n",multiplicare,pozitieTabla) !=EOF){
		determinaDirectieCuvant(pozitieTabla, &linie, &coloana, &directie);
		//printf("Am citit optiunea de multiplicare %s pe pozitia %s \n",multiplicare,pozitieTabla);
		if(!strcmp(multiplicare,"bleu"))
			tablaJoc[linie][coloana].multiplicareLitera = 2;
		if(!strcmp(multiplicare,"albastru"))
			tablaJoc[linie][coloana].multiplicareLitera = 3;
		if(!strcmp(multiplicare,"roz"))
			tablaJoc[linie][coloana].multiplicareCuvant = 2;
		if(!strcmp(multiplicare,"rosu"))
			tablaJoc[linie][coloana].multiplicareCuvant = 3;
		if(feof(f))
			break;
	}
	fclose(f);

	//afiseaza multiplicareLitera
	for(i=0;i<n;i++)
		{
		for(j=0;j<n;j++)
			printf("%d ",tablaJoc[i][j].multiplicareLitera);
		printf("\n");

		}
	printf("\n");

	//afiseaza multiplicareCuvant
	for(i=0;i<n;i++)
		{
		for(j=0;j<n;j++)
			printf("%d ",tablaJoc[i][j].multiplicareCuvant);
		printf("\n");

		}

	return tablaJoc;
}

void afiseazaTablaJoc(PATRAT** tablaJoc, int dim)
{
 int i,j;
 printf("**************************");
 for (i=0;i<dim;i++)
	{
		for(j=0;j<dim;j++)
			printf("%c ",tablaJoc[i][j].litera);
		printf("\n");
	}
  printf("**************************\n");
}




void completeazaTablaJoc(PATRAT** tablaJoc, char* cuvant, int linie, int coloana, int directie)
{
	int i;
	if(directie == 1) //directia orizontala
	{
		for(i=coloana;i<=coloana+strlen(cuvant)-1;i++)
			tablaJoc[linie][i].litera = cuvant[i-coloana];
	}
	if(directie == 2) //directia verticala
	{
		for(i=linie;i<=linie+strlen(cuvant)-1;i++)
			tablaJoc[i][coloana].litera = cuvant[i-linie];
	}
}

int calculeazaScorCuvantOrizontala(PATRAT** tablaJoc, int inceputColoana ,int sfarsitColoana, int linie, JETON* tablouJetoane)
{

	int scor = 0,k;
	int multiplicareCuvant = 1;
	int nrLitereFolosite = 0;
	for (k=inceputColoana;k<=sfarsitColoana;k++)
	{
		int valoareLitera = 0;
		//determina valoarea literei
		if((tablaJoc[linie][k].litera <'A') || (tablaJoc[linie][k].litera > 'Z'))
			valoareLitera = 0;//joker
		else
		{
			char litera = tablaJoc[linie][k].litera;
			valoareLitera = tablouJetoane[litera - 'A'].valoare;
		}
		int multiplicareLitera=1;
		if(tablaJoc[linie][k].ocupat==0)
		{
			multiplicareLitera = tablaJoc[linie][k].multiplicareLitera;
			nrLitereFolosite++;
			multiplicareCuvant *= tablaJoc[linie][k].multiplicareCuvant;
		}
		scor += valoareLitera * multiplicareLitera;
	}
	printf("Scorul cuvantului se multiplica de %d ori \n", multiplicareCuvant);
	scor = scor * multiplicareCuvant;

	if(nrLitereFolosite==7)
	{
		printf("BONUS \n");
		scor = scor + 50;
	}
	printf("Scorul final al cuvantului este %d\n", scor);
	return scor;
}


int calculeazaScorCuvantVerticala(PATRAT** tablaJoc, int inceputLinie ,int sfarsitLinie, int coloana,JETON* tablouJetoane)
{

	int scor = 0,k;
	int multiplicareCuvant = 1;
	int nrLitereFolosite = 0;
	for (k=inceputLinie;k<=sfarsitLinie;k++)
	{
		int valoareLitera = 0;
		//determina valoarea literei
		if((tablaJoc[k][coloana].litera <'A') || (tablaJoc[k][coloana].litera > 'Z'))
			valoareLitera = 0;//joker
		else
		{
			char litera = tablaJoc[k][coloana].litera;
			printf("Am litera %c \n", litera);
			valoareLitera = tablouJetoane[litera - 'A'].valoare;
		}

		int multiplicareLitera=1;
		if(tablaJoc[k][coloana].ocupat==0)
		{
			multiplicareLitera = tablaJoc[k][coloana].multiplicareLitera;
			nrLitereFolosite++;
			multiplicareCuvant *= tablaJoc[k][coloana].multiplicareCuvant;
		}
		scor += valoareLitera * multiplicareLitera;
	}
	printf("Scorul cuvantului se multiplica de %d ori \n", multiplicareCuvant);
	scor = scor * multiplicareCuvant;

	if(nrLitereFolosite==7)
	{
		printf("BONUS \n");
		scor = scor + 50;
	}
	printf("Scorul final al cuvantului este %d\n", scor);
	return scor;
}



int determinaScorDepunere(PATRAT** tablaJoc,char* cuvant,int linie, int coloana, int directie, int dim,JETON* tablouJetoane)
{
	int scor = 0;
	if (directie==1)//cuvant pe orizontala
	{
		int inceputColoana = coloana;
		int sfarsitColoana = coloana + strlen(cuvant)-1;
		scor = calculeazaScorCuvantOrizontala(tablaJoc, inceputColoana,sfarsitColoana , linie, tablouJetoane);
	}

	if (directie == 2)//cuvant pe verticala
	{
		int inceputLinie = linie;
		int sfarsitLinie = linie+strlen(cuvant)-1;
		scor = calculeazaScorCuvantVerticala(tablaJoc,inceputLinie,sfarsitLinie, coloana, tablouJetoane);
	}
	return scor;
}


void updateazaTabla(PATRAT** tablaJoc, char* cuvant, int linie, int coloana, int directie)
{
	int i;
	if (directie==1)//cuvant orizontal
		{
			for(i=coloana;i<=coloana + strlen(cuvant)-1;i++)
				tablaJoc[linie][i].ocupat = 1;
		}
	if (directie==2)//cuvant vertical
		{
			for(i=linie;i<=linie + strlen(cuvant)-1;i++)
				tablaJoc[i][coloana].ocupat = 1;
		}
}


void realizeazaDepuneri(char* numeFisierCuvinte, PATRAT** tablaJoc, int dim, int* scorJucatori, JETON* tablouJetoane)
{
	char pozitieTabla[4];
	char cuvant[30];
	int numarJucator;

	FILE *f = fopen(numeFisierCuvinte,"r");
	int linie, coloana, directie;
	while(1)
	{
		fscanf(f,"%d %s %s",&numarJucator, pozitieTabla, cuvant);
		if(feof(f) )
			break;
		printf("Am citit pentru jucatorul %d depunerea de la pozitia %s si cuvantul %s \n",numarJucator, pozitieTabla,cuvant);
		determinaDirectieCuvant(pozitieTabla, &linie, &coloana, &directie);
		completeazaTablaJoc(tablaJoc,cuvant,linie, coloana,directie);
		scorJucatori[numarJucator-1] += determinaScorDepunere(tablaJoc,cuvant,linie,coloana,directie,dim,tablouJetoane);
		printf("scorJucator 1 este %d \n", scorJucatori[0]);
		printf("scorJucator 2 este %d \n", scorJucatori[1]);
		updateazaTabla(tablaJoc,cuvant,linie,coloana,directie);
		afiseazaTablaJoc(tablaJoc,dim);
	}
	fclose(f);

}

int main()
{
	int nrPatrate;
	JETON* tablouJetoane = incarcaJetoane("jetoane.txt");
	PATRAT** tablaJoc = incarcaConfiguratieTabla("tablaJoc.txt", &nrPatrate);
	int scorJucatori[2] = {0};
	realizeazaDepuneri("joc.txt",tablaJoc,nrPatrate,scorJucatori,tablouJetoane);
	afiseazaTablaJoc(tablaJoc,nrPatrate);
	printf("scorJucator 1 este %d \n", scorJucatori[0]);
	printf("scorJucator 2 este %d \n", scorJucatori[1]);
    if(scorJucatori[0] > scorJucatori[1])
            printf("Jucatorul 1 a castigat jocul cu %d puncte \n", scorJucatori[0]);
    if(scorJucatori[1] > scorJucatori[0])
            printf("Jucatorul 2 a castigat jocul cu %d puncte \n", scorJucatori[1]);
    if(scorJucatori[1] == scorJucatori[0])
            printf("EGALITATE \n");

    free(tablouJetoane);
    free(tablaJoc);
	return 0;

}
