#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <map>
#include <queue>

using namespace std;

#include "nim_graph/graph.h"
#include "nim_graph/edge.h"
#include "nim_learner.h"

TEST_CASE("Dijkstras", "[weight=1][part=1]") {
    Graph graph(true, true); // Weighted and directed graph

    // Add vertices
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertVertex("E");

    // Add edges with weights
    graph.insertEdge("A", "B");
    graph.setEdgeWeight("A", "B", 1);
    graph.insertEdge("A", "C");
    graph.setEdgeWeight("A", "C", 4);
    graph.insertEdge("B", "C");
    graph.setEdgeWeight("B", "C", 2);
    graph.insertEdge("B", "D");
    graph.setEdgeWeight("B", "D", 6);
    graph.insertEdge("C", "D");
    graph.setEdgeWeight("C", "D", 3);
    graph.insertEdge("D", "E");
    graph.setEdgeWeight("D", "E", 2);

    // Run Dijkstra's algorithm
    Vertex source = "A";
    map<Vertex, int> distances = Dijkstra::shortestPath(graph, source);

    // Print shortest paths
    std::vector<std::pair<string, int>> your_code;
    for (const auto& pair : distances) {
        your_code.push_back(pair);
    }
    std::vector<std::pair<string, int>> solution({{"A", 0},{"B", 1},{"C", 3},{"D", 6},{"E", 8}});
    REQUIRE(solution == your_code);
}