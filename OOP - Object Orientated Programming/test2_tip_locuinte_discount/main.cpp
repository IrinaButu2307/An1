#include <iostream>
#include <string>
#include <fstream>

using namespace std;


class Locuinta
{
protected:


    string numeClient; ///sir/ null
    int suprafataUtila;
    float discount;
public: static int val_standard_chirie;
    Locuinta(){}
    Locuinta (string, int , float);
    Locuinta (const Locuinta &);
    Locuinta& operator = (const Locuinta&);
    ~Locuinta (){cout<<"destructor locuinta"<<endl;}

          friend ifstream & operator >>(ifstream &, Locuinta &);

      friend istream & operator >>(istream &, Locuinta &);
      friend ostream& operator<<(ostream &, const Locuinta&);
    virtual void Afisare()
    {
        cout<<"scriu locuinta nume client suprafata utila si discount"<<endl;

    cout<<numeClient<<" , "<<suprafataUtila<<" ,"<<discount<<endl;
    };
    virtual double CalculChirie(int,bool )=0;

};

int Locuinta ::val_standard_chirie=500;

   Locuinta :: Locuinta (const Locuinta &l)
   {
       numeClient=l.numeClient;
       suprafataUtila=l.suprafataUtila;
       discount=l.discount;
   }

   Locuinta:: Locuinta (string s, int a,  float g)
   {
       this->numeClient=s;
       this->suprafataUtila=a;
       this->discount=g;
   }
    Locuinta& Locuinta::operator = (const Locuinta&l)
    {
        if (this!= &l)
        {
            this->numeClient=l.numeClient;
            this->discount=l.discount;
            this->suprafataUtila=l.suprafataUtila;
        }
        return *this;
    }

istream & operator >>(istream& i, Locuinta &l)
{
    cout<<"dati nume client, suprafata utila si discount"<<endl;
    i>>l.numeClient>>l.suprafataUtila>>l.discount;
    return i;
}

ifstream & operator >>(ifstream& i, Locuinta &l)
{
    i>>l.numeClient>>l.suprafataUtila>>l.discount;
    return i;
}


class Apartament : public Locuinta
{
    int etaj;
public :
    Apartament(){}
    ~Apartament(){cout<<"destructor apartament"<<endl;}
    Apartament (int, string, int, float);
    Apartament (const Apartament &);
    Apartament& operator= (const Apartament &);

        friend ifstream& operator>>(ifstream &, Apartament&);

    friend istream& operator>>(istream &, Apartament&);
    double CalculChirie(int x , bool y){
        double suma=0;
        if (y==1)
        suma=x* suprafataUtila* (1-y *discount/100.0);
        else
            suma=x*suprafataUtila;
        return suma;
    }

    void Afisare()
    {
        Locuinta::Afisare();
        cout<<"elemente din clasa apartament; etaj"<<endl;
        cout<<etaj;
    }

};

Apartament :: Apartament (int a, string b, int c, float d): Locuinta(b, c,d)
{
    etaj=a;
}

Apartament ::Apartament(const Apartament &a):Locuinta(a)
{
    etaj=a.etaj;
}
Apartament & Apartament:: operator =(const Apartament&a)
{
    if(this != &a)
    {
        this->Locuinta::operator=(a);
        this->etaj=a.etaj;
    }
    return *this;
}

istream& operator>>(istream &i, Apartament&a){
    i>>(Locuinta&)a;
    cout<<"dati etaj"<<endl;
    i>>a.etaj;
    return i;
}

ifstream& operator>>(ifstream &i, Apartament&a){
    i>>(Locuinta&)a;
    i>>a.etaj;
    return i;
}

class Casa: public Locuinta
{
    int suprafataCurte;
    int nrEtaje;
    float *suprafataEtaje;

public:
    Casa(){}
    ~Casa(){cout<<"destructor casa"<<endl;}
    Casa (int, int, float*, string, int , float);
    Casa (const Casa&);
    Casa& operator =(const Casa&);

    friend istream& operator>>(istream &, Casa&);
     friend ifstream& operator>>(ifstream &, Casa&);

    void Afisare()
    {
        Locuinta ::Afisare();
        cout<<"elementele din clasa casa suprafata curte, nr etaje, si supr pt fiecare etaj"<<endl;
        cout<<suprafataCurte<<" , "<<nrEtaje<<endl;
        for(int i=0; i<nrEtaje; i++)
            cout<<suprafataEtaje[i]<<endl;
    }

    double CalculChirie(int x , bool y){
        double suma=0;
        if (y==1)
        suma=x* (suprafataUtila+ 0.2* suprafataCurte)* (1-y *discount/100.0);
        else
            suma=x*(suprafataUtila+ 0.2*suprafataCurte);
        return suma;
    }

};

istream& operator>>(istream &i, Casa&c)
{
  i>>(Locuinta &)c;
  cout<<"dati suprafata curte si nr etaje"<<endl;
  i>>c.suprafataCurte>>c.nrEtaje;
  c.suprafataEtaje= new float [c.nrEtaje+1];

  for(int i=0; i<c.nrEtaje; i++)
  {
     cout<<"dati suprafata etaj"<<endl;
    cin>>c.suprafataEtaje[i];
  }
  return i;
  }
  /*
ifstream& operator>>(ifstream &i, Casa&c)
{
  i>>(Locuinta &)c;
  i>>c.suprafataCurte>>c.nrEtaje;
  c.suprafataEtaje= new float [c.nrEtaje+1];
  for(int i=0; i<c.nrEtaje; i++)
    i>>c.suprafataEtaje[i];
  return i;
  }
*/
Casa::Casa (int a, int b, float*sir, string s, int c, float d):Locuinta(s, c, d)
{
    suprafataCurte=a;
    nrEtaje=b;
    suprafataEtaje=new float [nrEtaje+1];
    for(int i=0; i<nrEtaje; i++)
        suprafataEtaje[i]=sir[i];
}

Casa & Casa :: operator =(const Casa &c)
{
    if(this !=&c)
   {
    this->Locuinta::operator=(c);
    suprafataCurte=c.suprafataCurte;
    nrEtaje=c.nrEtaje;
    suprafataEtaje=new float [nrEtaje+1];
    for (int i=0; i<nrEtaje; i++)
        suprafataEtaje[i]=c.suprafataEtaje[i];
    }
        return *this;

}
int main()
{
   // Apartament a1(1,"Stoica", 100, 10), a2(a1), a3;
   // a3=a2;

    //float sir[2]={10, 10};
  //Casa c1(100, 2, sir, "marin", 100, 20);


    ifstream f("test.in");
    Locuinta **l;

    int i, n, op;

  //  cout<<"dati nr de locuinte pe care vreti sa le cititi di fisier"<<endl;
    cin>>n;

    l= new Locuinta *[n];

    for(int i=0; i<n; i++)
    {
        cout<<"Meniu"<<endl;
        cout<<"tasta 1- citire apartament"<<endl;
        cout<<"tasta 2- citire casa"<<endl;
        cin>>op;
        if(op==1)
        {
            l[i]=new Apartament();
            cin>>*(Apartament *)l[i];//f>>*(Apartament *)l[i];
        }
        else
        if(op==2)
        {
            l[i]=new Casa();
            cin>>*(Casa *)l[i];//f>>*(Casa*)l[i];
        }
    cout<<"ciclu in for"<<endl;
    }

    for (int i =0 ; i< n; i++)
        if(Apartament *a=dynamic_cast<Apartament *>(l[i]))
        {
        cout<<"am citit un APARTAMENT"<<endl;
        l[i]->Afisare();
        cout<<"cu chiria cu discuount "<<endl;
        cout<<l[i]->CalculChirie(Locuinta::val_standard_chirie, 1);
        cout<<"cu chiria fara discuount "<<endl;
        cout<<l[i]->CalculChirie(Locuinta::val_standard_chirie, 0);

        }
        else
        if(Casa*c=dynamic_cast<Casa *>(l[i]))
        {
        cout<<"am citit o CASA"<<endl;
        l[i]->Afisare();
        cout<<"cu chiria cu discount"<<endl;
        cout<<l[i]->CalculChirie(Locuinta::val_standard_chirie, 1);
        cout<<"cu chiria fara discuount "<<endl;
        cout<<l[i]->CalculChirie(Locuinta::val_standard_chirie, 0);
        }


    delete[]l;
    return 0;
}
