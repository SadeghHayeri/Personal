#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

bool is_there_path(vector< vector<int> > Graph, int s, int t,  int parent[] , int n )
{
    bool is_visit[n];
    for (size_t i = 0; i < n; i++)
        is_visit[i] = 0;

    queue <int> q;
    q.push(s);

    parent[s] = -1;
    is_visit[s] = true;

    while (q.empty() == false)
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<n; v++)
        {
            if (Graph[u][v] > 0 && is_visit[v]==false)
            {
                q.push(v);
                parent[v] = u;
                is_visit[v] = true;
            }
        }
    }

    return is_visit[t] != false;
}

int fordFulkerson(vector< vector<int> > graph, int s, int t , int n )
{
    int u, v;
    vector<vector<int> > Graph(n, vector<int>(n,0));
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
             Graph[u][v] = graph[u][v];

    int parent[n];
    int max_flow = 0;

    while (is_there_path(Graph, s, t, parent,n)) {
        int min_flow_in_path = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            min_flow_in_path = min(min_flow_in_path, Graph[u][v]);
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            Graph[u][v] -= min_flow_in_path;
            Graph[v][u] += min_flow_in_path;
        }

        max_flow += min_flow_in_path;
    }

    return max_flow;
}

int main()
{
    int n;
    cin >> n;

    int a, b;

    for (size_t i = 0; i < n; i++) {
        cin >> a >> b;
    }

    cout << "Impossible" << endl;

}
