#ifndef EX3_SERVER_H
#define EX3_SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include "SymbolTable.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sstream>

class Server {

private:
    int m_serverSocket;
    int m_port;
    int m_clientSocket;
    sockaddr_in address;
    std::string m_tempString;
    std::vector<std::string> m_commandsVec= {"/instrumentation/airspeed-indicator/indicated-speed-kt", "/sim/time/warp", "/controls/switches/magnetos",
     "/instrumentation/heading-indicator/offset-deg", "/instrumentation/altimeter/indicated-altitude-ft", "/instrumentation/altimeter/pressure-alt-ft", "/instrumentation/attitude-indicator/indicated-pitch-deg",
      "/instrumentation/attitude-indicator/indicated-roll-deg", "/instrumentation/attitude-indicator/internal-pitch-deg", "/instrumentation/attitude-indicator/internal-roll-deg",
      "/instrumentation/encoder/indicated-altitude-ft", "/instrumentation/encoder/pressure-alt-ft", "/instrumentation/gps/indicated-altitude-ft", "/instrumentation/gps/indicated-ground-speed-kt",
      "/instrumentation/gps/indicated-vertical-speed", "/instrumentation/heading-indicator/indicated-heading-deg", "/instrumentation/magnetic-compass/indicated-heading-deg",
      "/instrumentation/slip-skid-ball/indicated-slip-skid", "/instrumentation/turn-indicator/indicated-turn-rate", "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
      "/controls/flight/aileron", "/controls/flight/elevator", "/controls/flight/rudder", "/controls/flight/flaps", "/controls/engines/engine/throttle", "/controls/engines/current-engine/throttle",
      "/controls/switches/master-avionics", "/controls/switches/starter", "/engines/active-engine/auto-start", "/controls/flight/speedbrake", "/sim/model/c172p/brake-parking",
      "/controls/engines/engine/primer", "/controls/engines/current-engine/mixture", "/controls/switches/master-bat", "/controls/switches/master-alt", "/engines/engine/rpm"};
public:
    Server(int port);
    void createSocket();
    int get_clientSocket();
    void bindSocket();
    void listenAndAccept();
    void readDataFromClient();
    std::vector<double> splitString() const;



};

// global
static bool flag_stop_communication_server;
void runServer(Server server);

#endif //EX3_SERVER_H
