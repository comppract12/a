#include <bits/stdc++.h>
using namespace std;

#define V 7 // Number of vertices in the graph

// Function to find the vertex with the minimum key value from the set of vertices
// not yet included in the MST (Minimum Spanning Tree)
int minkey(int *key, bool* mSet)
{
    int min = INT_MAX; // Initialize min value
    int min_index;

    cout << "\nChecking the minimum key from all " << V << " vertices" << endl;
    for(int v = 0; v < V; v++)
    {
        cout <<v<<" Key weight:" << key[v];
        
        // Select the minimum key vertex from the unvisited set
        if(mSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }

        // Print visited/unvisited status
        if(mSet[v] == false)
        {
            cout << " -> unvisited" << endl;
        }
        else
        {
            cout << " -> visited" << endl;
        }
    }

    cout << "Minimum Key:"<<min_index<<" weight: " << key[min_index] <<" Selected"<< endl;
    return min_index;
}

// Function to print the constructed MST stored in the parent[] array
void printMST(int parent[], int graph[V][V])
{
    int sum = 0;
    cout << "\n\nThe Minimum Spanning Tree by Prim's Algorithm is:" << endl;
    cout << "Edge | Weight" << endl;
    for(int i = 1; i < V; i++)
    {
        cout << parent[i] << " <-> " << i << ": " << graph[i][parent[i]] << "\n";
        sum += graph[i][parent[i]]; // Calculate total cost of MST
    }
    cout << "Cost: " << sum;
}

// Function to construct and print the MST using Prim's algorithm
void primMST(int graph[V][V])
{
    int parent[V]; // Array to store constructed MST
    int key[V];    // Key values used to pick minimum weight edge
    bool mstSet[V]; // To represent set of vertices not yet included in MST

    cout << "\nInitializing all key weights to INT_MAX and visited status to false" << endl;
    for(int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    
    // Starting vertex is 0
    cout << "Setting the 0th key as start vertex and its parent to -1" << endl;
    key[0] = 0;
    parent[0] = -1; // First node is the root of MST

    // The MST will have V-1 edges
    for(int count = 0; count < V - 1; count++)
    {
        cout << "\n\n" << (count+1)<< " keys are visited" << endl;
        cout << "Finding the minimum key weight";

        // Pick the minimum key vertex not yet included in MST
        int u = minkey(key, mstSet);
        mstSet[u] = true; // Include u in MST

        cout << "Setting key " << u << " as visited: true" << endl;

        // Update key and parent index of adjacent vertices of the picked vertex
        for(int v = 0; v < V; v++)
        {
            // Update the key only if:
            // graph[u][v] is non-zero (there is an edge)
            // v is not yet included in MST
            // the weight of edge u-v is smaller than current key[v]
            if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
            {
                cout<<"Setting "<<u<<" as parent vertex of "<<v<<endl;
                parent[v] = u;
                cout<<"Setting the cost for vertex "<<v<<" as "<<graph[u][v]<<endl;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph);
}

// Driver code
int main()
{
    // Example graph represented using adjacency matrix
    int graph[V][V] = {
        {0, 9, 0, 0, 0, 1, 0},
        {9, 0, 4, 0, 0, 0, 3},
        {0, 4, 0, 2, 0, 0, 0},
        {0, 0, 2, 0, 6, 0, 5},
        {0, 0, 0, 6, 0, 8, 7},
        {1, 0, 0, 0, 8, 0, 0},
        {0, 3, 0, 5, 7, 0, 0}
    };

    // Run Prim's algorithm on the graph
    primMST(graph);

    return 0;
}
