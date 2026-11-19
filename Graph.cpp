#include "Graph.hpp"
#include "Class.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Graph::Graph(const std::vector<Class>& classes)
    : vertices(classes.size()),
      adjacencyList(classes.size()),
      classes(classes.size())
{
    this->classes = classes;

    for(int i = 0; i < classes.size(); i++) {
        vertices[i].color.startBlock = 0;
        vertices[i].color.pattern = getPossiblePatterns(classes[i].frequency)[0];
    }
}

void Graph::printGraph() {
    for (int i = 0; i < getVertexCount(); i++) {
        std::cout << classes[i].CRN
                  << " (" << classes[i].courseCode << ") -> ";

        for (int neighbor : getNeighbors(i)) {
            std::cout << classes[neighbor].CRN << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl << "TIMESHEETS" << std::endl;

    for (int i = 0; i < getVertexCount(); i++) {
        int time = DAY_START + vertices[i].color.startBlock * BLOCK_SIZE;

        std::cout << classes[i].CRN
                  << " (" << classes[i].courseCode << "):  "
                  << vertices[i].color.pattern << ", " << time / 60 << ":" << time % 60;

        std::cout << std::endl;
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
        if(classes[i].CRN == CRN) return i;
    }

    return -1;
}

Color Graph::findMinColor(int vertexIdx, const std::vector<int>& neighbors) {
    struct Color currChoice = vertices[vertexIdx].color;
    for(MeetingPattern p : getPossiblePatterns(this->classes[vertexIdx].frequency)) {
        currChoice.pattern = p;

        bool keepColoring = false;
        bool foundColor = true;
        do {
            keepColoring = false;
            if(DAY_START + currChoice.startBlock * BLOCK_SIZE + classes[vertexIdx].length > DAY_END) { //If the class would finish after the last class has to end
                currChoice = vertices[vertexIdx].color;
                foundColor = false;
                break; // Go to next meeting pattern
            }

            for(int neighborIdx : neighbors) {
                //Pattern with this neighbor does not overlap. Don't check!
                if(!(p & vertices[neighborIdx].color.pattern)) continue;

                //If a ends after b starts or viceversa, then the colors are clashing. Recolor!
                //BTW, just in case we use >= so that we give at least 1 time period of difference between classes. May change later!
                if(currChoice.startBlock * BLOCK_SIZE <= vertices[neighborIdx].color.startBlock * BLOCK_SIZE + classes[neighborIdx].length && vertices[neighborIdx].color.startBlock * BLOCK_SIZE <= currChoice.startBlock * BLOCK_SIZE + classes[vertexIdx].length) {
                    currChoice.startBlock =  vertices[neighborIdx].color.startBlock + classes[neighborIdx].length / BLOCK_SIZE + (classes[neighborIdx].length % BLOCK_SIZE ? 1 : 0) + 1; //Add one just in case...?
                    keepColoring = true;
                    break;
                }
            }
        } while(keepColoring);

        if(foundColor) break;
    }

    return currChoice;
}

//Greedy Coloring inspired by https://arxiv.org/pdf/1505.05825
void Graph::recolorGraph() {
    for(int i = 0; i < getVertexCount(); i++) {
        auto neighbors = getNeighbors(i);
        this->vertices[i].color = findMinColor(i, neighbors);
    }
}