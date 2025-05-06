#include <bits/stdc++.h>
using namespace std;

#define V 7

int minkey(int *key,bool* mSet)
{
    int min=INT_MAX;
    int min_index;
    for(int v=0;v<V;v++)
    {
        if(mSet[v]==false && key[v]<min)
        {
            min=key[v];
            min_index=v;
        }
    }
    return min_index;
}
void printMST(int parent[],int graph[V][V])
{
    int sum=0;
    cout<<"The Minimum Spanning Tree by Prim's Algorithm is"<<endl;
    cout<<"Edge | Weight"<<endl;
    for(int i=1;i<V;i++)
    {
        cout<<parent[i]<<"<->"<<i<<": "<<graph[i][parent[i]]<<" \n";
        sum+=graph[i][parent[i]];
    }
    cout<<"Cost:"<<sum;
}
void primMST(int graph[V][V])
{
    int parent[V];
    int key[V];
    bool mstSet[V];
    for(int i=0;i<V;i++)
    {
        key[i]=INT_MAX;
        mstSet[i]=false;
    }
    key[0]=0;
    parent[0]=-1;
    for(int count=0;count<V-1;count++)
    {
        int u=minkey(key,mstSet);
        mstSet[u]=true;
        for(int v=0;v<V;v++)
        {
            if(graph[u][v] && mstSet[v]==false && graph[u][v]<key[v])
            {
                parent[v]=u;
                key[v]=graph[u][v];
            }
        }
    }
    printMST(parent,graph);
}
int main()
{
    int graph[V][V]={
        {0,9,0,0,0,1,0},
        {9,0,4,0,0,0,3},
        {0,4,0,2,0,0,0},
        {0,0,2,0,6,0,5},
        {0,0,0,6,0,8,7},
        {1,0,0,0,8,0,0},
        {0,3,0,5,7,0,0}
    };
    primMST(graph);
    return 0;
}
