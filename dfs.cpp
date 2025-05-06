#include<bits/stdc++.h>
using namespace std;
 
class Graph
{
    int **adj,v,e;
    public:
    Graph(int v,int e);
    void newEdge(int start,int e);
    void DFS(int start,bool* visited);
};
 
Graph::Graph(int v,int e)
{
    this->v=v;
    this->e=e;
    adj=new int*[v];
    for(int row=0;row<v;row++)
    {
        adj[row]=new int[v];
        for(int column=0;column<v;column++)
        adj[row][column]=0;
    }
}
 
void Graph::newEdge(int start,int e)
{
    adj[start][e]=1;
    adj[e][start]=1;
}
 
void Graph::DFS(int start,bool* visited)
{
    cout<<start<<" ";
    visited[start]=true;
    for(int i=0;i<v;i++)
    {
        if(adj[start][i]==1 && (!visited[i]))
        DFS(i,visited);
    }
}
 
int main()
{
    int v=8,e=8;
    Graph G(v,e);
    G.newEdge(0,1);
    G.newEdge(0,2);
    G.newEdge(1,3);
    G.newEdge(2,4);
    G.newEdge(2,6);
    G.newEdge(6,7);
    G.newEdge(3,5);
    G.newEdge(5,4);
    bool *visited=new bool[v];
    for(int i=0;i<v;i++)
    visited[i]=false;
    G.DFS(0,visited);
}