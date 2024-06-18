#ifndef Topology_H
#define Topology_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Topology {
public:
    explicit Topology(int x = 10, int y = 10, int starts = 1, int ends = 1, int numNodes = 30);
    int ShortestPath(int position, vector<double> &sPath);
    void setConnections(vector<int> c, bool verbose = false);

    /**
     * The layout of the network that the program will attempt to find the optimal configuration for
     */

    vector<vector<bool>> network;
    vector<vector<int>> connections;
    int numNodes;// variable representing number of fog layer nodes present in the network
    int numCNodes;// varialbe representing total number of cloud nodes in the topology
    int numENodes;
    int tNumNodes; // variable representing total number of nodes in the network

private:
    void PrintLayout();
    void printConnections();
    int ChooseStart(int x, int numStarts);
    int ChooseEnd(int y, int x, int numEnds);
    void ChooseNodeLocations(int x, int y, int numNodes);
    void findNode(int &x, int &y, int node);
};

#endif // Topology_H