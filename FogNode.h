#ifndef FogNode_H
#define FogNode_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class FogNode {
public:
    FogNode();

    explicit FogNode(int type);

private:
    void server();// two servers
    void router();// one router
};

#endif // FogNode_H