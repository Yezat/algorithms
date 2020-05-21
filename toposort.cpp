#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

struct Knoten
{
	int Vorgaenger;

	int V;

	vector<int> Nachfolger;

};

map<int,Knoten> graph;
vector<int> result;



bool toposort()
{
	//Vorgänger ermitteln
	for (int i = 0; i < graph.size(); i++)
	{
		auto find = graph.find(i+1);
		for (int j = 0; j < find->second.Nachfolger.size(); j++)
		{
			auto res = graph.find(find->second.Nachfolger[j]);
			res->second.Vorgaenger += 1;
		}
	}
	//Toposort
	//graphsize as a control variable to not get in an endless circle caused of an eulercirle
	int graphSize = 0;
	int graphMaxSize = 1;

	vector<int> toDelete;

	while(!graph.empty())
	{
		if(graphSize == graphMaxSize)
			return false;
		graphSize = 0;
		graphMaxSize = graph.size();
		for(map<int,Knoten>::iterator i = graph.begin();i!=graph.end();i++)
		{
			auto search = graph.find(i->first);
			if(search->second.Vorgaenger == 0)
			{
				result.push_back(search->second.V);

				for (int i = 0; i < search->second.Nachfolger.size(); i++)
				{
					auto found = graph.find(search->second.Nachfolger[i]);
					found->second.Vorgaenger-=1;
				}

				toDelete.push_back(search->first);
			}else
			{
				graphSize += 1;
			}
		}
		if(!toDelete.empty())
		{
			for (int i = 0; i < toDelete.size(); i++)
			{
				auto found = graph.find(toDelete[i]);
				graph.erase(found);
			}
			toDelete.clear();
		}
	}
	return true;
}

int main()
{
	int V,E;
	cin >> V >> E;

	for (int i = 0; i < V; i++)
	{
		Knoten neu;
		neu.V = i+1;
		neu.Vorgaenger = 0;
		graph.insert(pair<int,Knoten>(i+1,neu));
	}

	//Initialize the graph
	for (int i = 0; i < E; i++)
	{
		int a, b;
		cin >> a >> b;

		auto searched = graph.find(a);
		searched->second.Nachfolger.push_back(b);

	}

	bool test = toposort();
	for(auto i : result)
	{
		cout << i << " " ;
	}
	cout << endl;

}