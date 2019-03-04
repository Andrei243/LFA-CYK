#include <bits/stdc++.h>

using namespace std;

void hashing(char x,vector<pair<char,int > >&vec )
{
    static int poz=-1;
    poz++;
    vec.push_back(make_pair(x,poz));
}

int pozitie(char x,vector<pair<char,int > >&vec)
{
    for(vector<pair<char,int> >::iterator it=vec.begin(); it!=vec.end(); it++)if((*it).first==x)return (*it).second;
    return -1;
}

char literapoz(int x,vector<pair<char,int > >&vec)
{
    return vec[x].first;
}

bool seaflainvector(char x,vector<char > y)
{
    vector<char>::iterator it=y.begin();
    for(; it!=y.end(); it++)if(*it==x)return true;
    return false;
}

void citire_neterminal_initial(vector<char> &vec,vector<pair<char,int > > &tabel)
{
    char t;
    do
    {
        cin>>t;
        if(!isupper(t)||seaflainvector(t,vec))cout<<"Ai citit gresit neterminalul\n";

    }
    while(!isupper(t)||seaflainvector(t,vec));
    vec.push_back(t);
    hashing(t,tabel);
}

char citire_neterminal_prod(vector<char> &vec)
{
    char t;
    do
    {
        cin>>t;
        if(!isupper(t)||!seaflainvector(t,vec))cout<<"Ai citit gresit neterminalul\n";

    }
    while(!isupper(t)||!seaflainvector(t,vec));
    return t;
}

string citire_dreapta(vector<char>&neterminale)
{
    string x;
    bool ok=false;
    do
    {
        ok=false;
        cin>>x;
        if(x.length()==1&&islower(x[0]))ok=true;
        else if(x.length()==2&&seaflainvector(x[0],neterminale)&&seaflainvector(x[1],neterminale))ok=true;
        else cout<<"Ai introdus gresit partea dreapta\n";
    }
    while(!ok);
    return x;
}

void citire_productie(vector<char>&neterminale,vector<vector<string > >&productii,vector<pair<char,int > >&hashare)
{
    char x=citire_neterminal_prod(neterminale);
    int t=pozitie(x,hashare);
    string prod=citire_dreapta(neterminale);
    productii[t].push_back(prod);
}

void eliminare_duplicate(vector<char>& vec)
{
    sort(vec.begin(),vec.end());
    for(unsigned int i=0; i<vec.size(); i++)
    {
        while(i!=vec.size()&&vec[i]==vec[i+1])vec.erase(vec.begin()+i+1);
    }
}

void afisare_productii(vector<vector<string> >&productii,vector<char> &neterminale)
{
    for(unsigned int i=0; i<productii.size(); i++)
    {
        cout<<neterminale[i]<<" -> ";
        for(unsigned int j=0; j<productii[i].size(); j++)cout<<productii[i][j]<<" ";
        cout<<'\n';
    }
}

vector<char> ret_pos(char a,char b,vector<vector<string> >&productii,vector<pair<char,int> >&hashare)
{
    vector<char> litere;
    for(unsigned int i=0; i<productii.size(); i++)
    {
        for(unsigned int j=0; j<productii[i].size(); j++)if(productii[i][j][0]==a&&productii[i][j][1]==b)litere.push_back(literapoz(i,hashare));
    }
    return litere;
}

vector<char> ret_pos(char a,vector<vector<string> >&productii,vector<pair<char,int> >&hashare)
{
    vector<char> litere;

    for(unsigned int i=0; i<productii.size(); i++)
    {
        for(unsigned int j=0; j<productii[i].size(); j++)if(productii[i][j][0]==a)litere.push_back(literapoz(i,hashare));
    }
    return litere;
}

void atasare(vector<char>&vec1,vector<char> vec2)
{
    for(unsigned int i=0; i<vec2.size(); i++)vec1.push_back(vec2[i]);
}

int main()
{
    vector<vector<string> >productii;
    vector<char> neterminale;
    vector<pair<char,int > >numerotare_neterminale;
    int nr_neterminale;
    cout<<"Introdu numarul de neterminale: ";
    cin>>nr_neterminale;
    for(int i=0; i<nr_neterminale; i++)
    {
        citire_neterminal_initial(neterminale,numerotare_neterminale);
    }
    productii=vector<vector<string> >(neterminale.size(),vector<string>(0));
    cout<<"Introdu numarul de productii: ";
    int nr_productii;
    cin>>nr_productii;
    for(int i=0; i<nr_productii; i++)citire_productie(neterminale,productii,numerotare_neterminale);

    string cuvant_citit;
    cout<<"Introdu cuvantul pe care vrei sa il verifici: ";
    cin>>cuvant_citit;
    vector<vector<vector<char> > > cyk(cuvant_citit.length(),vector<vector<char> >(cuvant_citit.length(),vector<char>(0)));
    for(unsigned int i=0; i<cuvant_citit.length(); i++)
    {
        cyk[0][i]=ret_pos(cuvant_citit[i],productii,numerotare_neterminale);
       // eliminare_duplicate(cyk[0][1]);
    }

    for(unsigned int i=1; i<cuvant_citit.length(); i++)
    {
        for(unsigned int j=0; j<cuvant_citit.length()-i; j++)
        {
            unsigned int pozx,pozy;
            pozx=i-1;
            pozy=j+1;
            for(unsigned int k=0; k<i; k++)
            {
                for(unsigned int l=0; l<cyk[k][j].size(); l++)
                {
                    for(unsigned int m=0; m<cyk[pozx][pozy].size(); m++)
                    {
                        atasare(cyk[i][j],ret_pos(cyk[k][j][l],cyk[pozx][pozy][m],productii,numerotare_neterminale));
                    }
                }
                pozx--;
                pozy++;
            }
           // eliminare_duplicate(cyk[i][j]);
        }
    }
    for(unsigned int i=0; i<cuvant_citit.length(); i++)
    {
        for(unsigned int j=0; j<cuvant_citit.length()-i; j++)
        {
            cout<<"CYC["<<i<<"]["<<j<<"] contine: ";
            for(unsigned int k=0; k<cyk[i][j].size(); k++)cout<<cyk[i][j][k];
            cout<<'\n';
        }
    }

    if(seaflainvector(neterminale[0],cyk[cuvant_citit.length()-1][0]))cout<<"Poate sa fie generat\n";
    else cout<<"Nu poate sa fie generat\n";
    afisare_productii(productii,neterminale);

    return 0;
}
