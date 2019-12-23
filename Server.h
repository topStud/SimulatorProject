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
    void bindSocket();
    void listenAndAccept();
    void readDataFromClient() const;




};

// global
void runServer(const Server &server);

#endif //EX3_SERVER_H
