#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Graph::Graph(const std::vector<Class>& classes)
    : vertices(classes.size()),
      adjacencyList(classes.size())
{
    for(int i = 0; i < classes.size(); i++) {
        vertices[i].CRN = classes[i].CRN;
        vertices[i].color.startBlock = 0;

        switch(classes[i].frequency) {
            case 1:
                vertices[i].color.pattern = M;
                break;
            case 2:
                vertices[i].color.pattern = MW;
                break;
            case 3:
                vertices[i].color.pattern = MWF;
                break;
        }
    }
}

void Graph::readRestrictions(std::string filename) {
    std::ifstream restrictions(filename); //For now assume the filename exists
    std::string line;
    getline(restrictions, line);

    while(getline(restrictions, line)) {
        std::vector<int> CRNList;

        std::stringstream ss(line);
        std::string field = "";
        getline(ss, field, '	'); //Type
        if(field == "Professor" || field == "SharedStudent") {
            while(getline(ss, field, '	')) CRNList.push_back(std::stoi(field));
        }

        for(int i = 0; i < CRNList.size(); i++) {
            for(int j = i + 1; j < CRNList.size(); j++) {
                this->addEdge(findVertexByCRN(CRNList[i]), findVertexByCRN(CRNList[j]));
            }
        }
    }
}

void Graph::addEdge(int u, int v) {
    if (u < 0 || v < 0 ||
        u >= getVertexCount() ||
        v >= getVertexCount()
    ) return;

    //Prevent multigraphs
    if (u == v) return;
    if (hasEdge(u, v)) return;

    adjacencyList[u].push_back(v);
    adjacencyList[v].push_back(u);
}

void Graph::removeEdge(int u, int v) {
    if (!hasEdge(u, v)) return;

    adjacencyList[u].erase(
        std::find(
            adjacencyList[u].begin(),
            adjacencyList[u].end(),
            v
        )
    );

    adjacencyList[v].erase(
        std::find(
            adjacencyList[v].begin(),
            adjacencyList[v].end(),
            u
        )
    );
}

bool Graph::hasEdge(int u, int v) const {
    return std::find(
        adjacencyList[u].begin(),
        adjacencyList[u].end(),
        v
    ) != adjacencyList[u].end();
}

int Graph::getVertexCount() const {
    return adjacencyList.size();
}

std::vector<int> Graph::getNeighbors(int vertex) const {
    if (vertex < 0 || vertex >= getVertexCount())
        return {};

    return adjacencyList[vertex];
}

int Graph::getDegree(int vertex) const {
    //Same as in addEdge, would this happen..?
    // if (vertex < 0 || vertex >= getVertexCount())
    //     return -1;

    return adjacencyList[vertex].size();
}

int Graph::findVertexByCRN(int CRN) const {
    for(int i = 0; i < getVertexCount(); i++) {
        if(vertices[i].CRN == CRN) return i;
    }

    return -1;
}