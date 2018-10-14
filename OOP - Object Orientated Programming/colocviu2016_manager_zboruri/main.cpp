#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class Triplet
{
    T zi, luna, an;
public:
    T get_zi(){return zi;}
    T get_luna(){return luna;}
    T get_an(){return an;}
    void citire(){cout<<"dati zi luna an"<<endl;
    cin>>zi>>luna>>an;}
    void afisare(){cout<<"am citit clasa DATA"<<endl;
    cout<<zi<<" "<<luna<<" "<<an<<endl;}
    friend istream & operator>>(istream &in, Triplet <T> &t)
    {t.citire();return in;}
    friend ostream & operator<<(ostream &out, Triplet<T> &t)
    {t.afisare();return out;}

};
typedef Triplet <int> Data;

class Zbor
{
    protected:
    string id;
    int ora;
    Data data_plecarii;
    string ruta;
    int durata;

public:
    Zbor(){}
    int get_an(){data_plecarii.get_an();}
    int get_zi(){data_plecarii.get_an();}
    int get_luna(){data_plecarii.get_luna();}
    virtual ~Zbor(){}
    virtual void citire() {cout<<" id ora data plecarii ruta durata"<<endl;
    cin>>id>>ora>>data_plecarii>>ruta;
        try{cin>>durata;
        if(cin.fail())
            throw 0;
        }
        catch(bool e)
        {
            cout<<"nu ati citit durata cum trebuie"<<endl;
        }
    }
    virtual void afisare() {cout<<"ZBOR; id ora data plecariisi ruta durata"<<endl;
    cout<<id<<" "<<ora<<" "<<data_plecarii<<" "<<ruta<<" "<<durata<<endl;
    }
    friend istream& operator>>(istream & in, Zbor &z){z.citire(); return in;}
    friend ostream& operator<<(ostream & out, Zbor &z){z.afisare(); return out;}

};

class Zbor_temporar: virtual public Zbor
{
protected:

    int perioada;

public:
    Zbor_temporar(){}
    void citire(){cout<<"Zbor tempo"<<endl;Zbor::citire();cout<<"dati valabilitate"<<endl; cin>>perioada;}
    void afisare(){cout<<"ZBOR TEMP"<<endl;Zbor::afisare(); cout<<"perioada valab "<<perioada<<endl;}
    friend istream& operator>>(istream & in, Zbor_temporar &z){z.citire(); return in;}
    friend ostream& operator<<(ostream & out, Zbor_temporar &z){z.afisare(); return out;}
};

class Zbor_promo: virtual public Zbor
{
    protected:
    int discount;
    public:
    Zbor_promo(){}
    void citire(){cout<<"Zbor promo"<<endl;Zbor::citire();cout<<"dati discount"<<endl; cin>>discount;}
    void afisare(){cout<<"ZBOR promo"<<endl;Zbor::afisare(); cout<<"discount "<<discount<<endl;}
    friend istream& operator>>(istream & in, Zbor_promo &z){z.citire(); return in;}
    friend ostream& operator<<(ostream & out, Zbor_promo &z){z.afisare(); return out;}

};
class Zbor_temporar_promo: public Zbor_temporar, public Zbor_promo
{
public:

    void citire(){cout<<"Zbor tempo promo"<<endl;Zbor_temporar::citire();cout<<"dati discount"<<endl; cin>>discount;}
    void afisare(){cout<<"ZBOR TEMP PROMO"<<endl;Zbor_temporar::afisare(); cout<<"discount "<<discount<<endl;}
    friend istream& operator>>(istream & in, Zbor_temporar_promo &z){z.citire(); return in;}
    friend ostream& operator<<(ostream & out, Zbor_temporar_promo &z){z.afisare(); return out;}

};

class Container{

  static int nrcurse;
protected:
    string ruta;
    int pret_bilet;
    vector<Zbor*>z;

public:
    Container(){}
    bool get_interval(Data &d1, Data &d2)
    { int ok=0;
        for(int i=0; i<z.size(); i++)
            if(z[i]->get_an()>= d1.get_an() && z[i]->get_an()<=d2.get_an())
                if(z[i]->get_luna()>= d1.get_luna() && z[i]->get_luna()<=d2.get_luna())
                 if(z[i]->get_zi()>= d1.get_zi() && z[i]->get_zi()<=d2.get_zi())
                 { ok==1;
                 z[i]->afisare();
                 }


        if(ok==1)   return 1;else
        return 0;
    }
    static int adcurse(){nrcurse++;}
    void citire (){cout<<"dati ruta pret bilet"<<endl;
    cin>>ruta>>pret_bilet;
    cout<<"nr de zboruri cu ruta "<<endl;
    int i, n, op;
    cin>>n;
    nrcurse=n;
    for(i=0; i<n; i++)
    {

        cout<<"1-norma; 2-temp 3- promo 4-temp promo"<<endl;
        cin>>op;
        switch (op)
        {
            case 1:{z.push_back(new Zbor());break;}
            case 2:{z.push_back(new Zbor_temporar());break;}
            case 3:{z.push_back(new Zbor_promo());break;}
            case 4:{z.push_back(new Zbor_temporar_promo());break;}
        }
        z[i]->citire();
    }
    }
     void afisare (){cout<<" ruta pret bilet"<<endl;
    cout<<ruta<<"   "<<pret_bilet<<endl;
    for(int i=0; i<z.size(); i++) //if (Zbor *a= dynamic_cast<Zbor *>(z[i]))
        z[i]->afisare();
    }
    void adauga_cursa(){
        z.push_back(new Zbor());
    z[z.size()-1]->citire();}
    string get_ruta(){return ruta;}
    static int get_nrcurse(){return nrcurse;}

};

int Container::nrcurse;

class Manager
{
    vector<Container*>c;
public:
    Manager(){}
    ~Manager(){}
    void citire(){cout<<"dati nr containere de citit"<<endl;
    int i,n; cin>>n;
    for(i=0; i<n; i++)
       {

        c.push_back(new Container());
        c[i]->citire();
    }}
    void afisare(){ int i;
    for(i=0; i<c.size(); i++)
        c[i]->afisare();
    }
    void adauga_ruta()
    {
        c.push_back(new Container());
        c[c.size()-1]->citire();
    }
    void adauga_cursa_pe_ruta(int i)
    {

           cout<<"ad cursa cu ruta"<<c[i]->get_ruta();
        c[i]->adauga_cursa();
    }
    void verifica_interval(Data &d1, Data &d2)
    {
        for(int i =0; i<c.size(); i++)
        {cout<<"in for"<<endl;
            int x=c[i]->get_interval(d1, d2);
            cout<<"x  "<<x<<endl;
            if(x!=0)
            {
                cout<<"AM GASIT CEVA OK IN RUTA ";
            }
        }
    }
};

int main()
{

    Manager m;
    m.citire();
   m.afisare();
    cout<<"dati 2 date intre care sa se caute cursele"<<endl;
    Data d1, d2;
    d1.citire();
    d2.citire();
    m.verifica_interval(d1, d2);
   // for(int i=0; i<=m.c.size(); i++)

   //m.adauga_ruta();
   //cout<<"da indicele rutei in care vrei sa adaugi curse"<<endl;
   //int i; cin>> i;
   //m.adauga_cursa_pe_ruta(i);
    //m.afisare();


    return 0;
}
