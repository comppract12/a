#include <bits/stdc++.h>
using namespace std;

#define V 9 // Number of vertices in the graph

// Function to find the vertex with the minimum distance value from the set of vertices
// not yet included in the shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    // Iterate over all vertices to find the minimum distance vertex
    cout<<"\n Searching the key with minimum weight"<<endl;
    for (int v = 0; v < V; v++)
    {
        cout<<"Key:"<<v<<" Weight:"<<dist[v];
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
        if(sptSet[v]==false)
        {
            cout<<" unvisted"<<endl;
        }
        else{
            cout<<" visited"<<endl;            
        }
    }
    cout<<"Selected Minimum unvisited Key:"<<min_index<<" Weight:"<<dist[min_index]<<endl;
    return min_index;
}

// Function to print the final shortest distance from the source to each vertex
void printSolution(int dist[])
{
    cout<<"\nDijsktras Single Source Shortest path algorithm";
    cout <<"\nVertex \t Distance from Source \n";
    for (int i = 0; i < V; i++)
    {
        printf("%d      -> %d\n", i, dist[i]);
    }
}

// Function that implements Dijkstra's algorithm
void dijsktras(int graph[V][V], int src)
{
    int dist[V];     // Output array. dist[i] holds the shortest distance from src to i
    bool sptSet[V];  // sptSet[i] is true if vertex i is included in the shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    cout<<"Initializing all the vertex distance to INT_MAX and visted as false"<<endl;
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance from source to itself is always 0
    cout<<"Setting the Source distance as 0";
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the vertex with the minimum distance from the set of vertices
        // not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;
        cout<<"Marked vertex "<<u<<" as visited:true"<<endl;

        // Update distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
        {
            // Update dist[v] only if:
            // - it's not in sptSet
            // - there is an edge from u to v (graph[u][v] != 0)
            // - total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                cout<<"Setting the distance of "<<u<<" as from "<<dist[v]<<" to Minimum distance "<<(dist[u]+graph[u][v])<<endl;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printSolution(dist);
}

int main()
{
    // Representation of the graph using adjacency matrix
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    // Call Dijkstra's algorithm with vertex 0 as the source
    dijsktras(graph, 0);

    return 0;
}
