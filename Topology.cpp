#include "Topology.h"

/**
 * Constructor for the topology object that will represent the network layour the SDA program will
 * be attempting to construct an optimal configuration for.
*/

Topology::Topology(int x, int y, int starts, int ends, int numNodes){

    network.reserve(y);
    for (vector<bool> v: network) {
        v.reserve(x);
        v = {false};
    }

    cout << "Works" << endl;

    PrintLayout();

    cout << "Works1" << endl;

    ChooseStart(y, starts);

    cout << "Works2" << endl;

    ChooseEnd(y, ends);

    cout << "Works3" << endl;

    ChooseNodeLocations(x, y, numNodes);

    cout << "Works4" << endl;
}

void Topology::PrintLayout(){
    for (int y = 0; y < network.size(); y++){
        for (int x = 0; x < network[0].size(); x++){
            cout << network[y][x] << '\t';
        }
        cout << '\n';
    }
}

/**
 * This will randomly select the start location(s) the information is originating from in the network
 * from the first row in the 2-d array representing the topology
 * 
 * @param y
 * @param numStarts
*/

int Topology::ChooseStart(int y, int numStarts){
    for (int x = 0; x < numStarts; x++){
        int start;
        do{
            start = (int)lrand48() % y; // randomly choose the data starting position in the network
        } while (network[0][start] == true);
        network[0][start] = true;
    }
    return 0;
}

/**
 * This will randomly select the end lolcations the data in our network is attempting to reach
 * these will be located in the row furthest from the row the start locations are positioned
 * 
 * @param y
 * @param numEnds
*/

int Topology::ChooseEnd(int y, int numEnds){
    for (int x = 0; x < numEnds; x++){
        int end;
        do{
            end = (int)lrand48() % y; // randomly choose the data starting position in the network
        } while (network[y][end] == true); // if position was already choosen choose another
        network[y][end] = true;
    }
    return 0;
}

/**
 * 
*/

void Topology::ChooseNodeLocations(int x, int y, int numNodes){
    for (int x = 0; x < numNodes; x++){
        int row;
        int column;
        do{
            row = (int)lrand48() % y; // randomly choose row to insert node
            column = (int)lrand48() % x;// randmoly choose column to insert node
        } while (network[row][column] == true); // if position is already choosen choose another
        network[row][column] = true;
    }
}

/**
 * 
*/

int Topology::ShortestPath(int position, vector<double> &sPath, vector<vector<bool>> connections){// initialize distance from start node to all others at max value){

    for (int x = 0; x < connections[position].size(); x++){ // go through the row recording the connections for the current position
        if (connections[position][x] == true){ // if there is a connection to explore
            int x1, x2, y1, y2;
            findNode(x1, y1, position + 1);// find x and y co-ordinate of node we are at
            findNode(x2, y2, x + 1);// find x and y co-ordinate of node we wish to calculate distance to

            int dist = sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));//caluclate euclidean distance
            if(dist + sPath[position] < sPath[x]){// compare distance
                sPath[x] = dist + sPath[position];// if shorter path update distance in shorter path vector
                ShortestPath(x, sPath, connections);// recalculate distance to all other nodes from that node to find shorter paths
            } 
        }
    }
    return 0;
}

/**
 * 
*/

void Topology::findNode(int &x, int &y, int node){
    int count = 0;// keep track of what node we have found in the network
    for (y = 0; y < network.size(); y++){// select row we will look through
        for (int x = 0; x < network[0].size() ; x++){// select column
            if(network[y][x] == true) count++;// if there is a node at position increment count
            if(count == node)return;// if found the node return to call
        }
    }
}