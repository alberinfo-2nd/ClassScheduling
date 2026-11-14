#include <iostream>
#include "Class.hpp"
#include "Graph.hpp"

void printGraph(const Graph& graph, const std::vector<Class>& classes) {
    for (int i = 0; i < graph.getVertexCount(); i++) {
        std::cout << classes[i].CRN
                  << " (" << classes[i].courseCode << ") -> ";

        for (int neighbor : graph.getNeighbors(i)) {
            std::cout << classes[neighbor].CRN << " ";
        }

        std::cout << std::endl;
    }
}

int main() {
    auto classes = readClasses("Classes.txt");
    Graph G = Graph(classes);

    return 0;
}