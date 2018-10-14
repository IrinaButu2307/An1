#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

///b
typedef struct
{
    int nrversuri;
    char **vers;

}poezie;

typedef struct
{
    char cuv[20];
    int frecv;
}cuvant;

typedef struct
{
    char *rima;
    int min_strofe;
    int max_strofe;
    char **cuvant;


}amprenta_stilistica;


int cmp(const void *a, const void *b)
{
    if(((cuvant *)a)->frecv>((cuvant *)b )->frecv)
        return -1;
    return 1;
}


///a

void versuri_litere(char *numefisier, int *nrvers, int*nrlit)
{
    int vers=0, maxlit=0;
    FILE *f=fopen(numefisier,"r");
    char sir[10000];
    int i;
    while (1)
    {
    fgets(sir, 10000, f);
       int chr=0;
        if(feof(f)) break;
        vers++;
        chr=strlen(sir);
        if(maxlit<chr)
            maxlit=chr;
    }
    *nrvers=vers;
    *nrlit=maxlit;
    fclose(f);
}

void  incarca_poezie(char *numefisier, poezie *p)
{
    int versuri, nrmaxlitere;
    int i;
    versuri_litere(numefisier, &versuri, &nrmaxlitere);
    FILE  *f=fopen(numefisier, "r");
    char s[1000];

    //poezie *p;

    //p->nrversuri=versuri;
    (*p).nrversuri=versuri;
    p->vers=(char **)malloc (versuri* sizeof(char*));
    for(i=0; i<versuri; i++)
    {
        fgets(s, 1000,f );///merge si fara>>
       // if(strcmp(s,"\n")==0)
         //   fgets(s, 1000,f );
        p->vers[i]=(char*)malloc((strlen(s)+1) *sizeof(char));
        strcpy(p->vers[i],s);
      //  fprintf(stdout, "bag %s\n", p->vers[i]);
    }
    fclose(f);

}

char *rima_poezie (poezie p)
{
    if(strcmp(p.vers[0]+strlen(p.vers[0])-3, p.vers[1]+strlen(p.vers[1])-3)==0)
        if(strcmp(p.vers[2]+strlen(p.vers[2])-3, p.vers[3]+strlen(p.vers[3])-3)==0)
            return "imperechiata";
    if(strcmp(p.vers[0]+strlen(p.vers[0])-3, p.vers[3]+strlen(p.vers[3])-3)==0)
        if(strcmp(p.vers[2]+strlen(p.vers[2])-3, p.vers[1]+strlen(p.vers[1])-3)==0)
            return "imbratisata";
    if(strcmp(p.vers[0]+strlen(p.vers[0])-3, p.vers[2]+strlen(p.vers[2])-3)==0)
        if(strcmp(p.vers[1]+strlen(p.vers[1])-3, p.vers[3]+strlen(p.vers[3])-3)==0)
            return "imcrucisata";

}

poezie poezie_creare(char *numefisier)
{
     int versuri, nrmaxlitere;
    int i;
    versuri_litere(numefisier, &versuri, &nrmaxlitere);
    FILE  *f=fopen(numefisier, "r");
    char s[1000];

    poezie p;

    //p->nrversuri=versuri;
    p.nrversuri=versuri;
    p.vers=(char **)malloc (versuri* sizeof(char*));
    for(i=0; i<versuri; i++)
    {
        fgets(s, 1000,f );///merge si fara>>
       // if(strcmp(s,"\n")==0)
         //   fgets(s, 1000,f );
        p.vers[i]=(char*)malloc((strlen(s)+1) *sizeof(char));
        strcpy(p.vers[i],s);
      //  fprintf(stdout, "bag %s\n", p->vers[i]);
    }
    fclose(f);

    return p;
}


char * cuvant_frecvent(poezie p)
{
    int i, k;
    char *point,t[100];

    cuvant *c;

    int contor=0, j=0;
    for(i=0; i<p.nrversuri; i++)
        {
        point=strtok(p.vers[i], "'.','?','!',' ',',', '\n'");
        while (point!=NULL)
        {

            if(strlen(point)>=3)
            {
                if(j==0)
                {
                    c=(cuvant *)malloc(sizeof(cuvant));
                   // c[0].cuv=(char*)malloc(strlen(point) * sizeof(char));
                   strcpy(c[0].cuv, point);
                    c[0].frecv = 1;
                    j++;
                }
                else
                    {
                int flag = 0;
                    for( k = 0; k < j; k++)
                        if(strcmp(c[k].cuv, point) == 0)
                        {
                            c[k].frecv++;
                            flag = 1;
                        }
                    if(!flag)
                    {
                        c = (cuvant*)realloc(c, (j + 1) * sizeof(cuvant));
                        //c[j].cuv = (char*)malloc(strlen(point) * sizeof(char));
                        strcpy(c[j].cuv, point);
                        c[j].frecv = 1;
                        j++;
                    }


                }
            }

             point=strtok(NULL, "'.','?','!',' ',',', '\n'");
        }
    }
    qsort(c,j ,sizeof(cuvant), cmp);

    int gasit=0;
   return c[0].cuv;

}

amprenta_stilistica  amp(int n,...)
{
    va_list lp;
    va_start(lp, n);
    int i;
    char *nume;
    amprenta_stilistica a;
    a.cuvant=(char**)malloc(n*sizeof(char*));
    for(i=0; i<n; i++)
    {
        strcpy(nume, va_arg(lp,char*));
        printf("NUME POEXIE %s\n", nume);
        poezie p;
        incarca_poezie(nume,&p);
       // printf("CUVANT FRECV SDIN POEZIE ==== %s\n", cuvant_frecvent(p));

        //a.cuvant[i]=(char*)malloc((strlen(cuvant_frecvent(p))+1)* sizeof(char));
         a.cuvant[i]=(char*)malloc(200* sizeof(char));
        strcpy(a.cuvant[i], cuvant_frecvent(p));
        printf(" CUV AMPRENTA --------- %s\n ", a.cuvant[i]);

    }
    va_end(lp);
}

int main()
{
   poezie p1;
   p1=poezie_creare("bacovia_1.txt");
  // incarca_poezie("bacovia_1.txt", &p1);
  // char *cuvant=cuvant_frecvent(p1);
   char *rima=rima_poezie(p1);
   printf("rimaaa %s\n", rima);

   //printf("cuvantul e %s\n", cuvant);
   int i, j, n;
    amprenta_stilistica a=amp(5, "bacovia_1.txt","bacovia_2.txt","bacovia_3.txt","bacovia_4.txt","bacovia_5.txt");

    return 0;
}

