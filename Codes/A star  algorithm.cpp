#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    double f, g, h;
    Node* parent;
    Node(int x, int y, double g, double h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

class AStar {
public:
    AStar(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal)
        : grid(grid), start(start), goal(goal) {}

    vector<pair<int, int>> run() {
        priority_queue<Node, vector<Node>, greater<Node>> open_set;
        unordered_map<int, unordered_map<int, Node*>> all_nodes;

        Node* start_node = new Node(start.first, start.second, 0, heuristic(start.first, start.second));
        open_set.push(*start_node);
        all_nodes[start.first][start.second] = start_node;

        while (!open_set.empty()) {
            Node current = open_set.top();
            open_set.pop();

            if (current.x == goal.first && current.y == goal.second) {
                return reconstruct_path(&current);
            }

            for (auto& dir : directions) {
                int nx = current.x + dir.first;
                int ny = current.y + dir.second;

                if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size() || grid[nx][ny] == 1)
                    continue;

                double tentative_g = current.g + 1;
                Node* neighbor = all_nodes[nx][ny];

                if (!neighbor) {
                    double h = heuristic(nx, ny);
                    neighbor = new Node(nx, ny, tentative_g, h, all_nodes[current.x][current.y]);
                    open_set.push(*neighbor);
                    all_nodes[nx][ny] = neighbor;
                } else if (tentative_g < neighbor->g) {
                    neighbor->g = tentative_g;
                    neighbor->f = tentative_g + neighbor->h;
                    neighbor->parent = all_nodes[current.x][current.y];
                    open_set.push(*neighbor);
                }
            }
        }

        return {}; // No path found
    }

private:
    vector<vector<int>>& grid;
    pair<int, int> start, goal;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    double heuristic(int x, int y) {
        return sqrt(pow(x - goal.first, 2) + pow(y - goal.second, 2));
    }

    vector<pair<int, int>> reconstruct_path(Node* node) {
        vector<pair<int, int>> path;
        while (node) {
            path.emplace_back(node->x, node->y);
            node = node->parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

vector<vector<int>> create_grid(int rows, int cols, double block_probability) {
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    srand(time(0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (static_cast<double>(rand()) / RAND_MAX < block_probability) {
                grid[i][j] = 1;
            }
        }
    }
    return grid;
}

int main() {
    int rows = 10, cols = 10;
    double block_probability = 0.1;
    pair<int, int> start = {0, 0};
    pair<int, int> goal = {1, 1};

    vector<vector<int>> grid = create_grid(rows, cols, block_probability);

    // Ensure start and goal are not blocked
    grid[start.first][start.second] = 0;
    grid[goal.first][goal.second] = 0;

    AStar astar(grid, start, goal);
    vector<pair<int, int>> path = astar.run();

    cout << "Grid:" << endl;
    for (const auto& row : grid) {
        for (int cell : row) {
            cout << (cell == 1 ? "#" : ".") << " ";
        }
        cout << endl;
    }

    cout << "Path:" << endl;
    for (const auto& p : path) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl;

    return 0;
}
