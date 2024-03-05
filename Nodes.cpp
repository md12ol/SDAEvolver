#include "Nodes.h"
bool admin = false;
map<int, vector<string>> security;      // defines if a security protocol is active in the node
map<string, vector<string>> vulnerabilites;// defines if an attack is executable on a node

/**
 * Constructor for the Nodes objects contained with the network strucutre
 * a security feature in a node is defined as the {name, intrusion it mitigates, cost, benefit}
 * while a vulenrability feature in a node is defined as the {protection is active against it, cost}
 *
 * @param type defines what type of node is being constructed for the network
 * @param infected determines if the node is the inital infected node of the network
 * @param admin determines if the node possess admin privliges
 */

Nodes::Nodes(int type, bool admin){

if(admin) admin = true;

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


/**
 * This method defines the security and vulenrabilities
 * associated with a desktop node in the network
*/

void Nodes::desktop(){

//Security features (can associate a cost value with implemeting each type of securtiy measure)
security = {
{0,{"set+ohistory","UnsecuredCredentials:BashHistory","false"}},
{1,{"TrojanAntivirus","TrojanHorse","false"}},
{2,{"RansomWareAntivirus","Ransomware","false"}},
{3,{"MultiFactorAuthentication","Spyware","false"}},
{4,{"RestrictWebAccess","Spyware","false"}},
{5,{"RestrictEmail","Spyware","false"}}};

//Vulnerabilities (can associate a cost to each type of vulnerabilite)
vulnerabilites = {
{"UnsecuredCredentials:BashHistory",{"true"}},
{"SearchHistory",{"true"}},
{"TrojanHorse",{"true"}},
{"Spyware",{"true"}},
{"Ransomware",{"true"}}};

} // desktop

/**
 * This method defines the security and vulnerability 
 * features associated with the server node in the network
 * 
*/

void Nodes::server(){
        
//Security features (can associate a cost value with implemeting each type of securtiy measure)
security = {
{0,{"Uptodatesoftware","Outdatedsoftware","false"}},
{1,{"TrojanAntivirus","TrojanHorse","false"}},
{2,{"RansomWareAntivirus","Ransomware","false"}},
{3,{"MultiFactorAuthentication","Bruteforce","false"}},
{4,{"InputValidation&Sanitization","SQLInjection","false"}},
{5,{"Scalablecloud","DOS","false"}},//costly
{6,{"IPRestriction","DOS","false"}},//will restrict some valid users(unless it is a worker specefic site)
{7,{"RateLimiting","DOS","false"}}};

//Vulnerabilities (can associate a cost to each type of vulnerabilite)
vulnerabilites = {
{"Bruteforce",{"true"}},
{"DOS",{"true"}},
{"TrojanHorse",{"true"}},
{"SQLInjection",{"true"}},
{"Ransomware",{"true"}},
{"Outdatedsoftware",{"true"}}};
}//server

void Nodes::router(){

}//router

void Nodes::printer(){

}//printer

void Nodes::website(){

}//website