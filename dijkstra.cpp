#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;

struct Nachbar
{
    int KnotenDesNachbarn;
    int Gewicht;
    Nachbar(int k, int g)
    {
        KnotenDesNachbarn = k;
        Gewicht = g;
    }
};

vector<int> Eltern;
vector<int> MinimaleDistanzen;

vector<vector<Nachbar> > AdjList;

const int Unendlich = 4000000;

void Djikstra(int source, int N)
{
    Eltern.resize(N,-1);
    MinimaleDistanzen.resize(N,Unendlich);
    Eltern[source] = 0;
    MinimaleDistanzen[source] = 0;

    set<pair<int,int> > schlange;
    schlange.insert(pair<int,int>(MinimaleDistanzen[source],source));

    while(!schlange.empty())
    {
        int currentVertex = schlange.begin()->second;
        int currentDistance = schlange.begin()->first;
        schlange.erase(schlange.begin());


        vector<Nachbar> Nachbaren = AdjList[currentVertex];

        for(vector<Nachbar>::iterator it = Nachbaren.begin();it != Nachbaren.end();it++)
        {
            int vertex = it->KnotenDesNachbarn;
            int distance = it->Gewicht;

            if(distance + currentDistance < MinimaleDistanzen[vertex])
            {
                schlange.erase(pair<int,int>(MinimaleDistanzen[vertex],vertex));
                MinimaleDistanzen[vertex] = distance + currentDistance;
                Eltern[vertex] = currentVertex;
                schlange.insert(pair<int,int>(MinimaleDistanzen[vertex], vertex));
            }

        }


    }



}


vector<int> GetPath(int source, int ziel)
{
    vector<int> res;

    while(Eltern[ziel] != source)
    {
        res.push_back(ziel);
        ziel = Eltern[ziel];
    }
    res.push_back(ziel);
    res.push_back(source);
    reverse(res.begin(),res.end());
    return res;
}


int main()
{
    int N,M;
    cin >> N >>M;
    AdjList.resize(N);
    for(int i =0;i<M;i++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        Nachbar d = Nachbar(a,c);
        Nachbar e = Nachbar(b,c);
        AdjList[a].push_back(e);
        AdjList[b].push_back(d);
    }
    int start,ziel;
    cin >> start >> ziel;

    Djikstra(start,N);
    vector<int> weg = GetPath(start,ziel);


    cout << "Distances:" << endl;
    for(unsigned int i =0;i<MinimaleDistanzen.size();i++)
    {
        cout << i << ": " << MinimaleDistanzen[i] << endl;
    }

    cout << "Parents: " << endl;
    for(unsigned int i =0;i< Eltern.size();i++)
    {
        cout << i  << ": " << Eltern[i] << endl;
    }


    cout << "Distance: " << MinimaleDistanzen[ziel] << endl;
    for(unsigned int i =0;i<weg.size();i++)
    {
        cout << weg[i] << " ";
    }
    cout << endl;
}
