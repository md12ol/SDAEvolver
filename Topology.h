#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Topology {
    public:
        explicit Topology(int x = 10, int y = 10, int starts = 1, int ends = 1, int numNodes = 30);

    private:
        void PrintLayout();
        int ChooseStart(int y, int numStarts);
        int ChooseEnd(int y, int numEnds);
        void ChooseNodeLocations(int x, int y, int numNodes);
        int ShortestPath(int position, vector<double> &sPath, vector<vector<bool>> connections);
        void findNode(int &x, int &y, int node);

        /**
         * The layout of the network that the program will attempt to find the optimal configuration for
         */
        vector<vector<bool>> network;
};