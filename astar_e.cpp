#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

// Node structure to represent each puzzle state
struct Node
{
    vector<int> state; // Current puzzle configuration
    int g, h;          // g = cost from start, h = estimated cost to goal (heuristic)
    Node *parent;      // Pointer to the parent node for backtracking solution path

    Node(vector<int> s, int g, int h, Node *p = nullptr) : state(s), g(g), h(h), parent(p) {}

    int f() const { return g + h; } // Total estimated cost

    // Comparison for priority queue (min-heap behavior)
    bool operator>(const Node &other) const
    {
        return f() > other.f();
    }
};

// Print the current state of the puzzle
void Print(const vector<int> &puzzle)
{
    for (int i = 0; i < 9; ++i)
    {
        if (i % 3 == 0)
            cout << "\n";
        if (puzzle[i] == -1)
            cout << "_ "; // -1 is the blank tile
        else
            cout << puzzle[i] << " ";
    }
    cout << "\n";
}

// Heuristic: Manhattan distance between each tile and its position in the goal
int manhattan(const vector<int> &a, const vector<int> &goal)
{
    int dist = 0;
    Print(a);
    for (int i = 0; i < 9; i++)
    {

        if (a[i] == -1)
            continue; // skip blank
        for (int j = 0; j < 9; j++)
        {
            if (a[i] == goal[j])
            {
                // current_row=i/3
                // current_col=i%3
                // goal_row=j/3
                // goal_col=j%3
                // Manhattan Distance = |current_row - goal_row| + |current_col - goal_col|
                dist += abs(i / 3 - j / 3) + abs(i % 3 - j % 3); // row diff + col diff
                break;
            }
        }
        cout << "Final Manhattan distance (sum of h of all elements) of current State:" << dist << endl;
    }
    return dist;
}

// Check if a puzzle state is solvable (even number of inversions)
bool solvable(const vector<int> &puzzle)
{
    cout << "Cheking puzzle is solvable or not \nInversions are counted when previous_number is greater than next_number";
    int inv = 0;
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[i] == -1)
            continue;
        for (int j = i + 1; j < 9; j++)
        {
            cout << "\nComparing " << puzzle[i] << " with " << puzzle[j];
            if (puzzle[j] == -1)
                continue;
            if (puzzle[i] > puzzle[j])
            {
                inv++;
                cout << " Inversions:" << inv;
            }
        }
    }
    cout << "\nFinal Inversions:" << inv;
    if (inv % 2 == 0)
    {
        cout << " .Inversions are even number \nso,Puzzle is solvable." << endl;
        return true;
    }
    else
    {
        cout << " .Inversions are odd number" << endl;
        return false;
    }
}

// Generate valid neighbor states by moving the blank tile
vector<vector<int>> getNeighbors(const vector<int> &state)
{
    vector<vector<int>> neighbors;
    // This searches the current puzzle state (a flat 1D vector of size 9).
    // pos is the index (0 to 8) where the blank tile is located
    int pos = find(state.begin(), state.end(), -1) - state.begin(); // find blank tile

    // Puzzle is 3x3.
    // This calculates the row and column of the blank tile in the grid.
    int row = pos / 3, col = pos % 3;

    // Possible move directions: up, down, left, right
    vector<pair<int, int>> directions = {
        {-1, 0}, // up
        {1, 0},  // down
        {0, -1}, // left
        {0, 1}   // right
    };

    // dr = change in row
    // dc = change in column

    //Looping through all directions up,down,left,right
    for (size_t i = 0; i < directions.size(); ++i)
    {
        int dr = directions[i].first;//{int ,int}
        int dc = directions[i].second;
        int newRow = row + dr, newCol = col + dc;

        // Ensure new position is within grid bounds of 3*3 and discard if not 
        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3)
        {
            //Convert newRow and newCol back into 1D index.
            int newPos = newRow * 3 + newCol;

            //Copy the current state to newState
            vector<int> newState = state;

            //Swap the blank tile with the tile at the new position
            swap(newState[pos], newState[newPos]); // swap blank with target tile
            
            //Add the new state to the result
            neighbors.push_back(newState);
        }
    }
    return neighbors;
}

// Print the full path from initial to goal state
void printPath(Node *node)
{
    vector<vector<int>> path;
    while (node)
    {
        path.push_back(node->state);
        node = node->parent;
    }
    reverse(path.begin(), path.end()); // because we tracked from goal to start

    for (size_t i = 0; i < path.size(); ++i)
    {
        Print(path[i]);
        cout << "-------\n";
    }
    cout << "Solved in " << path.size() - 1 << " moves.\n";
}

// Main A* solver
void solvePuzzle(const vector<int> &start, const vector<int> &goal)
{
    // Min-heap priority queue using custom comparator

    // Node: it is datatype of elements to store
    // vector<Node>: it is the datastruture in which elements will be stored
    // greater<Node>: it is comparative function to decide the priority
    priority_queue<Node, vector<Node>, greater<Node>> open;

    set<vector<int>> visited; // stores visited states to avoid loops

    // start: start state of puzzle
    // 0:g
    // manhattan(start, goal):h
    open.emplace(start, 0, manhattan(start, goal)); // add initial state

    while (!open.empty())
    {
        Node current = open.top(); // node with lowest f = g + h
        open.pop();
        cout << "Node with lowest (f=g+h). g:" << current.g << " h:" << current.h << " is Popped Out" << endl;

        if (visited.count(current.state))
            continue; // already seen
        visited.insert(current.state);

        if (current.state == goal)
        {
            cout << "\nCurrent State is Matched with the goal state";
            printPath(new Node(current)); // success
            return;
        }

        // This generates all valid puzzle states by moving the blank tile one step in any valid direction.
        vector<vector<int>> neighbors = getNeighbors(current.state);
        
        // Loop over each neighbor
        for (size_t i = 0; i < neighbors.size(); ++i)
        {
            if (!visited.count(neighbors[i]))
            {
                //Add new neighbor to open list if it's not visited.
                open.emplace(neighbors[i], current.g + 1, manhattan(neighbors[i], goal), new Node(current));
            }
        }
    }

    cout << "No solution found.\n";
}

int main()
{
    // vector<int> start(9), goal(9);
    // cout << "Enter start state (use -1 for empty tile): ";
    // for (int i = 0; i < 9; i++) cin >> start[i];

    // cout << "Enter goal state (use -1 for empty tile): ";
    // for (int i = 0; i < 9; i++) cin >> goal[i];

    vector<int> start = {1, 2, 3, -1, 4, 6, 7, 5, 8};
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, -1};

    if (!solvable(start))
    {
        cout << "\nThis puzzle is not solvable.\n";
        return 0;
    }

    solvePuzzle(start, goal);
    return 0;
}