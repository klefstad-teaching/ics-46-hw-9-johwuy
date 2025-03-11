#include "dijkstras.h"
#include <algorithm>
#include <climits>
#include <vector>

std::vector<int> dijkstra_shortest_path(const Graph &G, int source,
                                        vector<int> &previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);

    vector<bool> visited(n, false);
    previous.resize(n, -1);  // To be safe.
    using pII = pair<int, int>;
    priority_queue<pII, vector<pII>, greater<pII>> pq;

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [dist_u, u] = pq.top();
        pq.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int w = e.weight;

            if (!visited[v] && dist_u + w < distance[v]) {
                distance[v] = dist_u + w;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}
std::vector<int> extract_shortest_path(const std::vector<int> & /*distances*/,
                                       const std::vector<int> &previous,
                                       int destination) {
    std::vector<int> path;
    for (int iter = destination; iter != -1; iter = previous[iter]) {
        path.push_back(iter);
    }

    std::reverse(path.begin(), path.end());

    return path;
}
void print_path(const vector<int> &v, int total) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout  << '\n' << "Total cost is " << total << '\n';
}
