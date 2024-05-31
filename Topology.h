#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Topology {
    public:
        explicit Topology(int x = 10, int y = 10, int starts = 1, int ends = 1, int numNodes = 30);
        int ShortestPath(int position, vector<double> &sPath);
        void setConnections(vector<int> c);

    private:
        void PrintLayout();
        int ChooseStart(int x, int numStarts);
        int ChooseEnd(int y, int x, int numEnds);
        void ChooseNodeLocations(int x, int y, int numNodes);
        void findNode(int &x, int &y, int node);
        
        static int numNodes;// variable representing number of fog layer nodes present in the network

        /**
         * The layout of the network that the program will attempt to find the optimal configuration for
         */
        vector<vector<bool>> network;
        vector<vector<int>> connections;
};