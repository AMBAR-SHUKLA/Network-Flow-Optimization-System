#include "graph.hpp"
#include <queue>
#include <algorithm>
#include <omp.h>
using namespace std;

long long pushRelabelMaxFlow(Graph &g, int s, int t) {
    int n = g.N;
    vector<long long> excess(n,0);
    vector<int> height(n,0), seen(n,0);

    height[s] = n;
    for(int i : g.adj[s]) {
        g.edges[i].flow = g.edges[i].capacity;
        g.edges[i^1].flow = -g.edges[i].flow;
        excess[g.edges[i].to] += g.edges[i].flow;
    }

    auto push = [&](int u, Edge &e) {
        long long amt = min(excess[u], e.capacity - e.flow);
        if(height[u] == height[e.to]+1 && amt>0) {
            e.flow += amt;
            g.edges[&e - &g.edges[0]^1].flow -= amt;
            excess[u] -= amt;
            excess[e.to] += amt;
            return true;
        }
        return false;
    };

    auto relabel = [&](int u) {
        int minH = 2*n;
        for(int idx : g.adj[u]) {
            Edge &e = g.edges[idx];
            if(e.capacity - e.flow > 0)
                minH = min(minH, height[e.to]);
        }
        if(minH < 2*n)
            height[u] = minH +1;
    };

    queue<int> q;
    for(int i=0;i<n;i++) if(i!=s && i!=t && excess[i]>0) q.push(i);

    while(!q.empty()) {
        int u = q.front(); q.pop();
        bool pushed = false;

        // Parallel push for all edges
        #pragma omp parallel for
        for(size_t idx = 0; idx < g.adj[u].size(); idx++) {
            Edge &e = g.edges[g.adj[u][idx]];
            if(push(u,e)) {
                pushed = true;
            }
        }

        if(!pushed) {
            relabel(u);
            q.push(u);
        }
    }

    long long maxFlow = 0;
    for(int idx : g.adj[s]) maxFlow += g.edges[idx].flow;
    return maxFlow;
}
