#ifndef Nodes_H
#define Nodes_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Nodes {
public:
    Nodes();

    explicit Nodes(int type, bool admin);

private:
    void desktop();// four computers
    void server();// two servers
    void router();// one router
    void printer();// two printers
    void website();// one website
};

#endif // Nodes_H
