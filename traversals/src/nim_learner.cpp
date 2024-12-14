/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */
#include <string>
#include "nim_learner.h"
#include <ctime>

map<Vertex, int> Dijkstra::shortestPath(const Graph& graph, Vertex source) {
    // Priority queue: {distance, vertex}
    priority_queue<pair<int, Vertex>, vector<pair<int, Vertex>>, greater<pair<int, Vertex>>> pq;
    map<Vertex, int> distances; // Stores shortest distance to each vertex

    // Initialize distances
    for (Vertex v : graph.getVertices()) {
        distances[v] = INT_MAX;
    }
    distances[source] = 0;
    pq.push({0, source});

    for (int i = graph.getEdges().size() - 1; i > 0; i--){
        Vertex u = pq.top().second;
        pq.pop();

        // Explore neighbors
        for (Vertex neighbor : graph.getAdjacent(u)) {
            int weight = graph.getEdgeWeight(u, neighbor);
            if (weight == Graph::InvalidWeight) continue;

            int newDistance = distances[u] + weight;
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                pq.push({newDistance, neighbor});
            }
        }
    }

    return distances;
}
