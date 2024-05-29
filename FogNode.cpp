#include "FogNode.h"
static map<int, vector<string>> security;      // defines if a security protocol is active in the node
static map<string, vector<string>> vulnerabilites;// defines if an attack is executable on a node

/**
 * Constructor for the Nodes objects contained with the network strucutre
 * a security feature in a node is defined as the {name, intrusion it mitigates, cost, benefit}
 * while a vulenrability feature in a node is defined as the {protection is active against it, cost}
 *
 * @param type defines what type of node is being constructed for the network
 * @param infected determines if the node is the inital infected node of the network
 * @param admin determines if the node possess admin privliges
 */

FogNode::FogNode(int type){

switch(type){
case 0:
    server();// two servers
    break;
case 1:
    router();// one router
    break;
}
}// Constructor

/**
 * This method defines the security and vulnerability 
 * features associated with the server node in the network
 * 
*/

void FogNode::server(){
}//server

void FogNode::router(){

}//router