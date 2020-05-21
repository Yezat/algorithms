#include <vector>
#include <iostream>
#include <stack>

using namespace std;

vector<vector<int> > AdjazenzenListe;
vector<bool> seen;
stack<int> s;

bool DFS(int ziel)
{
	if(!s.empty())
	{
		int v = s.top();
		if(v != ziel)
		{
			s.pop();
			for (int i = 0; i < AdjazenzenListe[v].size(); i++)
			{
				int element = AdjazenzenListe[v][i];
				if(element == ziel)
					return true;
				if(!seen[element])
				{
					seen[element] = true;
					s.push(element);
				}
			}
			return DFS(ziel);
		}
		else
		{
			return true;
		}
	}else
		return false;
}

int main()
{
	int V,E;
	cin >> V >> E;
	AdjazenzenListe.resize(V);
	for (int i = 0; i < E; i++)
	{
		int startKnoten, endKnoten;
		cin >> startKnoten >> endKnoten;
		AdjazenzenListe[startKnoten].push_back(endKnoten);
		AdjazenzenListe[endKnoten].push_back(startKnoten);
	}
	
	seen.resize(V);



	//ist Knoten n von S aus erreichbar?
	int n,st;
	cin >> n >> st;

	s.push(st);
	seen[st] = true;

	cout << DFS(n) << endl;

}