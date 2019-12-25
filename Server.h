#ifndef EX3_SERVER_H
#define EX3_SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

class Server {

private:
    int m_serverSocket;
    int m_port;
    int m_clientSocket;
    sockaddr_in address;
public:
    Server(int port);
    void createSocket();
    int get_serverSocket();
    void bindSocket();
    void listenAndAccept();
    void readDataFromClient() const;
};

// global
static bool flag_stop_communication_server;
void runServer(Server server);

#endif //EX3_SERVER_H
