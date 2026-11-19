#include "Class.hpp"
#include "Graph.hpp"

int main() {
    auto classes = readClasses("Classes.txt");
    Graph G = Graph(classes);
    G.readRestrictions("Restrictions.txt");
    G.recolorGraph();
    G.printGraph();

    return 0;
}