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
    struct Color color;
};

class Graph {
private:
    std::vector<Class> classes;
    std::vector<Vertex> vertices;
    std::vector<std::vector<int>> adjacencyList;

public:
    Graph(const std::vector<Class>& classes);
    void printGraph();
    void readRestrictions(std::string filename);

    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool hasEdge(int u, int v) const;
    int getVertexCount() const;
    std::vector<int> getNeighbors(int vertex) const;
    int getDegree(int vertex) const;
    int findVertexByCRN(int CRN) const;

    bool colorConflict(int a, int b);
    Color findMinColor(int vertexIdx, const std::vector<int>& neighbors);
    void recolorGraph();
};

#endif