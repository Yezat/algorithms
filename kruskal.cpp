#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int llint;

struct Kante
{
    llint Kosten;
    int Start,Ende;
    bool operator<(const Kante& kante)const
    {
        return Kosten< kante.Kosten;
    }
};

vector<Kante> Kanten;
vector<int> Eltern;
llint Total;

int find(int x)
{
    if(Eltern[x] == x) return x;
    else
    {
        return Eltern[x] = find(Eltern[x]);
    }
}

void KruskalUnion(int x, int y)
{
    int px = find(x);
    int py = find(y);
    Eltern[px] = py;
}

void Kruskal()
{
    sort(Kanten.begin(),Kanten.end());
    for(int i=0;i<Kanten.size();i++)
    {
        int a= Kanten[i].Start;
        int b = Kanten[i].Ende;
        if(find(a)!=find(b))
        {
            Total += Kanten[i].Kosten;
            KruskalUnion(a,b);
        }
    }
}

int main()
{
    Total = 0;
    llint gesamtsumme = 0;
    int N,M;
    cin >> N >> M;
    for(int i=0;i<N;i++)
    {
        Eltern.push_back(i);
    }
    for(int i=0;i<M;i++)
    {
        int a,b,p;
        cin >> a >> b >> p;

        gesamtsumme += p;

        Kante kante;
        kante.Kosten = p; kante.Ende = b; kante.Start = a;
        Kanten.push_back(kante);
    }
    Kruskal();
    cout << gesamtsumme -Total<< endl;

}
