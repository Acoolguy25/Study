/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#pragma once

using namespace std;

#include <vector>
#include <map>
#include <queue>
#include <algorithm>

#include "nim_graph/graph.h"
#include "nim_graph/edge.h"

class Dijkstra{
    public:
        static map<Vertex, int> shortestPath(const Graph& graph, Vertex source);
};
