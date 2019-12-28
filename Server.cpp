#include "Server.h"



Server::Server(int port)
{
    flag_stop_communication_server = false;
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
    } else {
      std::cout << "accepted the client" << std::endl;
    }
    close(m_serverSocket); //closing the listening socket
}

void Server::readDataFromClient()
{
    char buffer[1025] = {0};
    buffer[1024] = '\0';
    int val_read = read( m_clientSocket , buffer, 1024);
    if(val_read == -1)
    {
        throw "Error while reading from simulator";
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

int Server::get_clientSocket() {
  return this->m_clientSocket;
}

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