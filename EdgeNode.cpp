#include "EdgeNode.h"
static map<int, vector<string>> security;      // defines if a security protocol is active in the node
static map<string, vector<string>> vulnerabilites;// defines if an attack is executable on a node

/**
 * Constructor for the Nodes objects contained with the network strucutre
 * a security feature in a node is defined as the {name, intrusion it mitigates, cost, benefit}
 * while a vulenrability feature in a node is defined as the {protection is active against it, cost}
 *
 * @param type defines what type of node is being constructed for the network
 */

EdgeNode::EdgeNode(int type){

switch(type){
case 0:
    desktop();
    break;
case 1:
    server();// two servers
    break;
case 2:
    router();// one router
    break;
case 3:
    printer();// two printers
    break;
case 4:
    website();
    break;
}
}// Constructor

void EdgeNode::desktop(){

} // desktop

void EdgeNode::server(){
}//server

void EdgeNode::router(){

}//router

void EdgeNode::printer(){

}//printer

void EdgeNode::website(){

}//website