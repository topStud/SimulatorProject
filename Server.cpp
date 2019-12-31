#include "Server.h"

/**
 * constructor of class Server.
 * receives as an argument the port number.
 * updates the port number field and the value of the flag;
 */
Server::Server(int port)
{
    flag_stop_communication_server = false;
    this->m_port= port;
}

/**
 * createSocket function of class Server.
 * creates socket. if did not succeed, throws an exception.
 */
void Server::createSocket()
{
   m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket == -1) {
        //error
        throw "Could not create a socket";
    }
}

/**
 * bindSocket function of class Server.
 * creates a new object of type sockaddr_in
 * bind socket to IP address
 */
void Server::bindSocket()
{
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(m_port);

    //the actual bind command
    if (bind(m_serverSocket, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw "Could not bind the socket to an IP";
    }
}

/**
 * listenAndAccept function of class Server.
 * making socket listen to the port and accepts client.
 * if some action did not succeeded an exception will be thrown.
 */
void Server::listenAndAccept()
{
    if (listen(m_serverSocket, 1) == -1) {
        throw "Error during listening command";
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    m_clientSocket = accept(m_serverSocket, (struct sockaddr *)&address,
                               (socklen_t*)&address);

    if (m_serverSocket == -1) {
        throw "Error accepting client";
    } else {
      std::cout << "accepted the client" << std::endl;
    }

    //closing the listening socket
    close(m_serverSocket);
}

/**
 * readDataFromClient function of class Server.
 * the function reads the data from the simulator and
 * updates the relevant variables in the sim_map.
 */
void Server::readDataFromClient()
{
    char buffer[1025] = {0};
    buffer[1024] = '\0';

    int val_read = read( m_clientSocket , buffer, 1024);
    if (val_read == -1) {
      std::cout << "Error reading the data from the simulator" << std::endl;
    }
    std::string str(buffer);
    std::string::size_type pos = 0;
    while ((pos = str.find('\n', 0)) != std::string::npos)
    {
        this->m_tempString.append(str.substr(0, pos));
        std::vector<double> vec = splitString();
        for(int i=0; i< this->m_commandsVec.size(); i++)
        {
            if (SymbolTable::get_instance()->is_key_exists_in_sim_map(this->m_commandsVec[i]))
            {
                SymbolTable::get_instance()->get_value_from_sim_map(this->m_commandsVec[i])->set_value(vec[i]);
            }
        }
        str= str.substr(pos+1);
        this->m_tempString.clear();
    }
    this->m_tempString.append(str);
}

/**
 * get_clientSocket function of class Server.
 * returns the client socket.
 */
int Server::get_clientSocket() {
  return this->m_clientSocket;
}

/**
 * splitString function of class Server.
 * returns a vector with all the values from
 * the server by the correct order.
 */
std::vector<double> Server::splitString() const
{
    std::vector<double> vec;
    std::stringstream ss(this->m_tempString);

    for (double i; ss >> i;)
    {
        vec.push_back(i);
        if (ss.peek() == ',')
        {
            ss.ignore();
        }
    }
    return vec;
}

/**
 * runServer function of class Server.
 * receives a server and runs the loop until the flag says otherwise.
 * the loop reads each time from the simulator.
 */
void runServer(Server server)
{
    while(true)
    {
        if (flag_stop_communication_server) {
            close(server.get_clientSocket());
            break;
        }
        server.readDataFromClient();
    }
}