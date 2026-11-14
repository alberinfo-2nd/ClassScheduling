#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "Class.hpp"

//Color is a composite of what days and what time a class meets 
struct Color {
    MeetingPattern pattern;
    int startBlock;
};

struct Vertex {
    int id;
    struct Color color;
};

class Graph {
private:
    std::vector<Vertex> vertices;
    std::vector<std::vector<int>> adjacencyList;

public:
    Graph(const std::vector<Class>& classes);

    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool hasEdge(int u, int v) const;
    int getVertexCount() const;
    std::vector<int> getNeighbors(int vertex) const;
    int getDegree(int vertex) const;
};

#endif