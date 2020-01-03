//
// Created by topaz on 19/12/2019.
//

#ifndef MILESTONE1__CLIENT_H_
#define MILESTONE1__CLIENT_H_

#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client {
  int client_socket;
  int create_socket();
  void connect_com(const std::string& ip, int port) const;
 public:
  Client(const std::string& ip, int port);
  void send_message_to_server(std::string str) const;
  void close_socket() const;
};

// global
void start_sock(const Client& c);

#endif //MILESTONE1__CLIENT_H_
