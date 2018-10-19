// C++ program to find shortest path with exactly k edges
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a <= _b ? _a : _b; })

// Define number of vertices in the graph and inifinite value
#define V 10000 + 10
#define INF 10000000000000

long long DP[V][V];
bool DPV[V][V];

long long ans(vector< vector< pair<long long, long long> > >& graph, long long i, long long v)
{
    if(DPV[i][v] == 0) {
        DP[i][v] = INF;
        for (auto edges : graph[v])
            DP[i][v] = min(DP[i][v], ans(graph, i-1, edges.first) + edges.second);
    }
    DPV[i][v] = 1;
    return DP[i][v];
}

// driver program to test above function
int main()
{
    long long n, m, k;
    cin >> n >> m >> k;
    long long v = n - 1;

    vector< vector< pair<long long, long long> > > graph(n);
    for (size_t i = 0; i < m; i++) {
        long long a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    for (size_t i = 0; i < n; i++) {
        DP[0][i] = INF;
        DPV[0][i] = 1;
    }
    DP[0][0] = 0;

    long long sp = ans(graph, k, v);
    if(sp >= INF)
        cout << "Impossible" << endl;
    else
        cout << sp << endl;
    return 0;
}
