#include <bits/stdc++.h>
using namespace std;

#define edge pair<int,int>

class Graph
{
    private:
    vector<pair<int,edge>> G;
    vector<pair<int,edge>> T;
    int *parent;
    int v;

    public:
    Graph(int v);
    void newWeightedEdge(int u,int v,int w);
    int find_set(int i);
    void union_set(int u,int v);
    void kruskal();
    void print();
};
Graph::Graph(int v)
{
    parent =new int[v];
    for(int i=0;i<v;i++)
    {
        parent[i]=i;
    }
    G.clear();
    T.clear();
}

void Graph::newWeightedEdge(int u,int v,int w)
{
    G.push_back(make_pair(w,edge(u,v)));
}

int Graph::find_set(int i)
{
    if(i==parent[i])
    {
        return i;
    }
    else
    {
        return find_set(parent[i]);
    }
}

void Graph::union_set(int u,int v)
{
    parent[u]=parent[v];
}

void Graph::kruskal()
{
    int i,uRep,vRep;
    sort(G.begin(),G.end());
    for(int i=0;i<G.size();i++)
    {
        uRep=find_set(G[i].second.first);
        vRep=find_set(G[i].second.second);

        if(uRep!=vRep)
        {
            T.push_back(G[i]);
            union_set(uRep,vRep);
        }
    }

}

void Graph::print()
{
    cout<<"The minimum spanning tree by Kruskal is"<<endl;
    cout<<"Edge  | Weight"<<endl;
    int sum=0;
    for(int i=0;i<T.size();i++)
    {
        cout<<T[i].second.first<<"<->"<<T[i].second.second<<" : "<<T[i].first<<endl;
        sum+=T[i].first;
    }
    cout<<"Cost:"<<sum;
}

int main()
{
    Graph g(6);
    g.newWeightedEdge(0,2,3);
    g.newWeightedEdge(0,1,1);
    g.newWeightedEdge(1,2,4);
    g.newWeightedEdge(1,3,11);
    g.newWeightedEdge(1,5,10);
    g.newWeightedEdge(2,4,12);
    g.newWeightedEdge(2,5,5);
    g.newWeightedEdge(4,5,2);
    g.newWeightedEdge(3,5,6);

    g.kruskal();
    g.print();
}