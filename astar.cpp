#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> state;
    int g, h;
    Node* parent;

    Node(vector<int> s, int g, int h, Node* p = nullptr) : state(s), g(g), h(h), parent(p) {}

    int f() const { return g + h; }

    // For priority_queue (min-heap)
    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

void Print(const vector<int>& puzzle) {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) cout << "\n";
        if (puzzle[i] == -1) cout << "_ ";
        else cout << puzzle[i] << " ";
    }
    cout << "\n";
}

int manhattan(const vector<int>& a, const vector<int>& goal) {
    int dist = 0;
    for (int i = 0; i < 9; i++) {
        if (a[i] == -1) continue;
        for (int j = 0; j < 9; j++) {
            if (a[i] == goal[j]) {
                dist += abs(i / 3 - j / 3) + abs(i % 3 - j % 3);
                break;
            }
        }
    }
    return dist;
}

bool solvable(const vector<int>& puzzle) {
    int inv = 0;
    for (int i = 0; i < 9; i++) {
        if (puzzle[i] == -1) continue;
        for (int j = i + 1; j < 9; j++) {
            if (puzzle[j] == -1) continue;
            if (puzzle[i] > puzzle[j]) inv++;
        }
    }
    return inv % 2 == 0;
}

vector<vector<int>> getNeighbors(const vector<int>& state) {
    vector<vector<int>> neighbors;
    int pos = find(state.begin(), state.end(), -1) - state.begin();
    int row = pos / 3, col = pos % 3;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // up, down, left, right

    for (size_t i = 0; i < directions.size(); ++i) {
        int dr = directions[i].first;
        int dc = directions[i].second;
        int newRow = row + dr, newCol = col + dc;
        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            int newPos = newRow * 3 + newCol;
            vector<int> newState = state;
            swap(newState[pos], newState[newPos]);
            neighbors.push_back(newState);
        }
    }
    return neighbors;
}

void printPath(Node* node) {
    vector<vector<int>> path;
    while (node) {
        path.push_back(node->state);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); ++i) {
        Print(path[i]);
        cout << "-------\n";
    }
    cout << "Solved in " << path.size() - 1 << " moves.\n";
}

void solvePuzzle(const vector<int>& start, const vector<int>& goal) {
    priority_queue<Node, vector<Node>, greater<Node>> open;
    set<vector<int>> visited;

    open.emplace(start, 0, manhattan(start, goal));

    while (!open.empty()) {
        Node current = open.top();
        open.pop();

        if (visited.count(current.state)) continue;
        visited.insert(current.state);

        if (current.state == goal) {
            printPath(new Node(current));
            return;
        }

        vector<vector<int>> neighbors = getNeighbors(current.state);
        for (size_t i = 0; i < neighbors.size(); ++i) {
            if (!visited.count(neighbors[i])) {
                open.emplace(neighbors[i], current.g + 1, manhattan(neighbors[i], goal), new Node(current));
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<int> start(9), goal(9);
    cout << "Enter start state (use -1 for empty tile): ";
    for (int i = 0; i < 9; i++) cin >> start[i];
    cout << "Enter goal state (use -1 for empty tile): ";
    for (int i = 0; i < 9; i++) cin >> goal[i];

    if (!solvable(start)) {
        cout << "\nThis puzzle is not solvable.\n";
        return 0;
    }

    solvePuzzle(start, goal);

    return 0;
}
