#ifndef EX3_SERVER_H
#define EX3_SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
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
    std::vector<std::string> m_commandsVec= {"airspeed-indicator_indicated-speed-kt", "time_warp, switches_magnetos",
     "heading-indicator_offset-deg", "altimeter_indicated-altitude-ft", "altimeter_pressure-alt-ft", "attitude-indicator_indicated-pitch-deg",
      "attitude-indicator_indicated-roll-deg", "attitude-indicator_internal-pitch-deg", "attitude-indicator_internal-roll-deg",
      "encoder_indicated-altitude-ft", "encoder_pressure-alt-ft", "gps_indicated-altitude-ft", "gps_indicated-ground-speed-kt",
      "gps_indicated-vertical-speed", "indicated-heading-deg", "magnetic-compass_indicated-heading-deg",
      "slip-skid-ball_indicated-slip-skid", "turn-indicator_indicated-turn-rate", "vertical-speed-indicator_indicated-speed-fpm",
      "flight_aileron", "flight_elevator", "flight_rudder", "flight_flaps", "engine_throttle", "current-engine_throttle",
      "switches_master-avionics", "switches_starter", "active-engine_auto-start", "flight_speedbrake", "c172p_brake-parking",
      "engine_primer", "current-engine_mixture", "switches_master-bat", "switches_master-alt", "engine_rpm"};
public:
    Server(int port);
    void createSocket();
    void bindSocket();
    void listenAndAccept();
    void readDataFromClient() const;
    std::vector<double> splitString(std::string str) const;



};

// global
void runServer(const Server &server);

#endif //EX3_SERVER_H
