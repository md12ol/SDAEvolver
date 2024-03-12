#ifndef EdgeNode_H
#define EdgeNode_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class EdgeNode {
public:
    EdgeNode();

    explicit EdgeNode(int type);

private:
    void desktop();// four computers
    void server();// two servers
    void router();// one router
    void printer();// two printers
    void website();// one website
};

#endif // EdgeNodes_H
