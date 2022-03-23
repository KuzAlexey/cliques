#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>

using namespace std;

int M[878][878] = {0};

vector<int> graphColoring(vector<int> graph[], int V)
{
    vector<int> color(V, -1);
    color[0]  = 1;

    // colors already assigned to neighbors
    vector<bool> alreadyAssigned(V);

    for (int u = 1; u < V; u++)
    {
        fill(alreadyAssigned.begin(), alreadyAssigned.end(), false);
        
        for (auto av : graph[u])
            if (color[av] != -1)
                alreadyAssigned[color[av]] = true;

            // Find the first available color
            int c;
            for (c = 1; c <= V; c++)
                if (alreadyAssigned[c] == false)
                    break;

                color[u] = c; // Assign the found color
    }

    return color;
}

void addEdge(vector<int> graph[],
             int u, int v)
             {
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
             }

int main()
{
    int V = 878;
    //freopen("/Users/kuzalexey/cmc/G.txt", "r", stdin);
    ifstream in("/Users/kuzalexey/cmc/G.txt");
    int x = 0, y = 0, w = 0;
    int S = 0;
    while (in >> x >> y >> w) {
        x--;y--;
        M[x][y] = w;
        M[y][x] = w;
        S += w;
    }
    int ANS = 0;
    for (int iter = 0; ;++iter) {
        vector<int> graph[V];
        int cnt = 0;
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                if (M[i][j] == 0) {
                    addEdge(graph, i, j);
                } else {
                    cnt++;
                }
            }
        }
        cout << "CNT " << cnt << '\n';
        vector<int> res = graphColoring(graph, V);
        int C = *max_element(res.begin(), res.end());
        for (int i = 1; i <= C; ++i) {
            if (count(res.begin(), res.end(), i) > 1) {
                ANS++;
            }
        }
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                if (res[i] == res[j]) {
                    M[i][j]--;
                    M[j][i]--;
                    if (M[i][j] < 0) {
                        return 0;
                    }
                    S--;
                }
            }
        }
        cout << "ANS = " << ANS << ' ' << "SUM = " << S << endl;
        if (S == 0) {
            break;
        }
    }
    return 0;
}

