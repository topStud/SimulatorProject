#include "Server.h"


Server::Server(int port)
{
    this->m_port= port;
}

void Server::createSocket()
{
   m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket == -1) {
        //error
        throw "Could not create a socket";
    }
}

void Server::bindSocket()
{
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    //sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(m_port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(m_serverSocket, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw "Could not bind the socket to an IP";
    }
}

void Server::listenAndAccept()
{
    //making socket listen to the port
    if (listen(m_serverSocket, 1) == -1) { //can also set to SOMAXCON (max connections)
        throw "Error during listening command";
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    m_clientSocket = accept(m_serverSocket, (struct sockaddr *)&address,
                               (socklen_t*)&address);

    if (m_serverSocket == -1) {
        throw "Error accepting client";
    }

    close(m_serverSocket); //closing the listening socket
}

void Server::readDataFromClient() const
{
    char buffer[325] = {0};
    buffer[324] = '\0';
    int val_read = read( m_clientSocket , buffer, 324);
    std::cout<< "Num of Bytes: " << val_read <<", Data: " << buffer<<std::endl;
    std::vector<double> vec = splitString(buffer);
    for (std::size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl;
}

void runServer(const Server &server)
{
    while(true)
    {
        server.readDataFromClient();
    }

}

std::vector<double> Server::splitString(std::string str) const
{
    std::vector<double> vec;

    std::stringstream ss(str);

    for (double i; ss >> i;)
    {
        vec.push_back(i);
        if (ss.peek() == ',')
        {
            ss.ignore();
        }
    }

    for (std::size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl;

    return vec;
}


/* airspeed-indicator_indicated-speed-kt, time_warp, switches_magnetos, heading-indicator_offset-deg,
 * altimeter_indicated-altitude-ft, altimeter_pressure-alt-ft, attitude-indicator_indicated-pitch-deg,
 * attitude-indicator_indicated-roll-deg, attitude-indicator_internal-pitch-deg, attitude-indicator_internal-roll-deg,
 * encoder_indicated-altitude-ft, encoder_pressure-alt-ft, gps_indicated-altitude-ft, gps_indicated-ground-speed-kt,
 * gps_indicated-vertical-speed, indicated-heading-deg, magnetic-compass_indicated-heading-deg,
 * slip-skid-ball_indicated-slip-skid, turn-indicator_indicated-turn-rate, vertical-speed-indicator_indicated-speed-fpm,
 * flight_aileron, flight_elevator, flight_rudder, flight_flaps, engine_throttle, current-engine_throttle,
 * switches_master-avionics, switches_starter, active-engine_auto-start, flight_speedbrake, c172p_brake-parking,
 * engine_primer, current-engine_mixture, switches_master-bat, switches_master-alt, engine_rpm
 * */