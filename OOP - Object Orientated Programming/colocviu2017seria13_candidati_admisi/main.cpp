#include <iostream>
#include <vector>
#include <string>
#include <typeindex>
#include <algorithm>

using namespace std;

template < typename T>
class triplet
{
    T zi , luna, an;

public:
    triplet <T>(){}
    triplet<T>(T a, T b, T c): zi(a), luna(b), an(c){}
    T get_zi() const{return zi;}
    T get_luna() const{return luna;}
    T get_an() const{return an;}
friend istream& operator >>(istream &i, triplet &t)
    {
        cout<<"dati zi luna an"<<endl;
        i>>t.zi>>t.luna>>t.an;
        return i;
    }
    friend ostream& operator <<(ostream &o,const triplet &t)
    {
        cout<<"am citit data: zi luna an"<<endl;
        o<<t.zi<<" , "<<t.luna<<" , "<<t.an;
        return o;
    }
};
typedef triplet<int> data;




class Candidat
{

protected:
    ///fct virtuala pt LEGITIMATIE???
    static int nrcandidati;
    string nume;
    string serieci;
    int numarci;
    float mediebac;
    float nota;

     ///  mai am de ad ceva la ce se incadreaza?? ----fct/tip de data?
public:
    Candidat(){}
    virtual~Candidat(){}

    virtual float calcul_medie()=0;

    virtual void citire ()
    {
        cout<<"dati nume, serieci, numarci, mediebac si nota"<<endl;
        cin>>nume>>serieci>>numarci>>mediebac>>nota;
        Candidat::nrcandidati++;
    }

     virtual void afisare ()
        const
    {
        cout<<"am afisat CANDIDAT :nume, serieci, numarci, mediebac, nota"<<endl;
        cout<<nume<<", "<<serieci<<" , "<<numarci<<" , "<<mediebac<<" ,"<<nota<<endl;
    }

    friend istream & operator>>(istream &i, Candidat &c){c.citire(); return i;}
    friend ostream & operator<<(ostream &o, const Candidat &c){c.afisare(); return o;}


};

int Candidat::nrcandidati=0;

class Candidat_ID: virtual public Candidat
{
protected:

    float notamate;
     float medieadm;
public:
    Candidat_ID(){}
    float calcul_medie(){return 0.6*nota + 0.4*mediebac;}
    void citire(){Candidat::citire();cout<<"dati notamate"<<endl; cin>>notamate;}
    void afisare()const{Candidat::afisare();cout<<"nota la mate "<<notamate<<endl;}
    friend istream&  operator>>(istream& i, Candidat_ID&c){c.citire(); return i;}
    friend ostream & operator<<(ostream &o, const Candidat_ID &c){c.afisare(); return o;}

};

class Candidat_IF: virtual public Candidat
{
    protected:
     float medieadm;

public:
    Candidat_IF(){}

    float calcul_medie(){return 0.8*nota + 0.2*mediebac;}
    void citire(){Candidat::citire();}
    void afisare()const {Candidat::afisare();}
    friend istream&  operator>>(istream& i, Candidat_IF&c){c.citire(); return i;}
    friend ostream & operator<<(ostream &o, const Candidat_IF &c){c.afisare(); return o;}

};

class Candidat_fac_2:virtual public Candidat
{
protected:

    float medieabs;
     float medieadm;
public:

    Candidat_fac_2(){}
    virtual void citire(){Candidat::citire();cout<<"dati medie absolv"<<endl; cin>>medieabs;}
    virtual void afisare()const{Candidat::afisare();cout<<"medie abs "<<medieabs<<endl;}
    friend istream&  operator>>(istream& i, Candidat_fac_2&c){c.citire(); return i;}
    friend ostream & operator<<(ostream &o, const Candidat_fac_2 &c){c.afisare(); return o;}


};

class Candidat_IF_fac_2: public Candidat_IF, public Candidat_fac_2
{
protected:
 float medieadm;
public:
    Candidat_IF_fac_2(){}
    float calcul_medie(){return 0.6*nota + 0.4*medieabs;}
    void citire(){Candidat_fac_2::citire();}
    void afisare()const{Candidat_fac_2::afisare();}
    friend istream&  operator>>(istream& i, Candidat_IF_fac_2&c){c.citire(); return i;}
    friend ostream & operator<<(ostream &o, const Candidat_IF_fac_2 &c){c.afisare(); return o;}

};

class Candidat_ID_fac_2: public Candidat_ID, public Candidat_fac_2
{
    protected:
         float medieadm;
public:
    Candidat_ID_fac_2(){}
    float calcul_medie(){return 0.6*nota + 0.4*medieabs;}
    void citire(){Candidat_fac_2::citire();cout<<"dati nota mate"<<endl; cin>>notamate;}
    void afisare()const{Candidat_fac_2::afisare();cout<<" nota mate "<<notamate<<endl;}
    friend istream&  operator>>(istream& i, Candidat_ID_fac_2&c){c.citire(); return i;}
    friend ostream & operator<<(ostream &o, const Candidat_ID_fac_2 &c){c.afisare(); return o;}

};

int cmp (Candidat_IF *a, Candidat_IF *b )
{
    return a->calcul_medie()>b->calcul_medie();
}



class Manager
{
private :
   // static Manager *instance;
    vector <Candidat *> v;
    vector<Candidat_IF *>f;
     vector<Candidat_ID *>d;
      vector<Candidat_IF_fac_2 *>f2;
       vector<Candidat_ID_fac_2 *>d2;

public:
    Manager(){}
    void citire(){
        cout<<"dati nr de candidati"<<endl;
        int n; cin >>n;
        int op;
        cout<<"meniu"<<endl;
        for(int i=0; i<n; i++)
    { cout<<"1-if.... 2- id... 3-fac2-if... 4-fac2id "<<endl;
    cin>>op;
    switch(op)
        {
            case 1:{
            v.push_back(new Candidat_IF());
             break;
            }
             case 2:{v.push_back(new Candidat_ID());
                 break;
            }
             case 3:{v.push_back(new Candidat_IF_fac_2());// Candidat_IF *cand= new Candidat_IF();
            break; //v.push_back(cand);
            }
             case 4:{v.push_back(new Candidat_ID_fac_2());
             // Candidat_IF *cand= new Candidat_IF();
                    //cin>>*cand;
           break; //v.push_back(cand);
            }
                }
        v[i]->citire();
    }

    for(int i=0; i<n; i++)
    {
    if(Candidat_IF *c= dynamic_cast <Candidat_IF*> (v[i]))
                f.push_back(c);
    if(Candidat_ID *c= dynamic_cast <Candidat_ID*> (v[i]))
                d.push_back(c);
    if(Candidat_IF_fac_2 *c= dynamic_cast <Candidat_IF_fac_2*> (v[i]))
                f2.push_back(c);
    if(Candidat_ID_fac_2 *c= dynamic_cast <Candidat_ID_fac_2*> (v[i]))
                d2.push_back(c);
    }
    }

    void afiseaza ()
    {
      for (int i=0; i<v.size(); i++)
          {
            if(Candidat_IF *c= dynamic_cast<Candidat_IF *>(v[i]))
                cout<<"IF"<<endl;
            else
                if(Candidat_ID*c= dynamic_cast<Candidat_ID *>(v[i]))
                cout<<"Id"<<endl;
            else if(Candidat_IF_fac_2 *c= dynamic_cast<Candidat_IF_fac_2 *>(v[i]))
                cout<<"IF fac 2"<<endl;
                else if(Candidat_ID_fac_2 *c= dynamic_cast<Candidat_ID_fac_2 *>(v[i]))
                cout<<"ID face 2"<<endl;

              v[v.size()-1]->afisare();
              }

    }

    void admisi()
    {
        sort(f.begin(), f.end(), cmp);
        for( int i=0; i<f.size(); i++)
            f[i]->afisare();
        for( int i=0; i<d.size(); i++)
            d[i]->afisare();
        for( int i=0; i<f2.size(); i++)
            f2[i]->afisare();
        for( int i=0; i<d2.size(); i++)
            d2[i]->afisare();
    }

    /*
    static Manager* get_instance ()
    {
        if (instance ==NULL)
    instance=new Manager();
    return instance;
    }
    void afisare(){
    for(int i=0; i<=n; i++}
        */

};
int main()
{
    try{
    int n,  i ,j;
    Manager m;

    m.citire();
    //m.afiseaza();
    m.admisi();
    }
    catch(...)
    {
        cout<<"AMPRINS O EROARE "<<endl;
    }

    return 0;
}
