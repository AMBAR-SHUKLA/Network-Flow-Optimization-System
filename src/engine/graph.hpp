#pragma once
#include <vector>
#include <iostream>
using namespace std;

struct Edge {
    int from, to;
    long long capacity, flow;
};

class Graph {
public:
    int N;
    vector<Edge> edges;
    vector<vector<int>> adj;

    Graph(int n) : N(n) {
        adj.resize(N);
    }

    void addEdge(int u, int v, long long cap) {
        Edge a{u, v, cap, 0};
        Edge b{v, u, 0, 0}; 
        adj[u].push_back(edges.size());
        edges.push_back(a);
        adj[v].push_back(edges.size());
        edges.push_back(b);
    }
};
