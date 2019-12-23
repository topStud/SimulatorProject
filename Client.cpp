//
// Created by topaz on 19/12/2019.
//

#include "Client.h"
/*
 * creates socket and returns file descriptor
 */
int Client::create_socket(){
  int client_socket = socket(AF_INET, SOCK_STREAM,0);
  if (client_socket == -1) {
    // error
    throw "Could not create a socket";
  }
  return client_socket;
}

/*
 * receives as an input a file object
 * creates sockaddr object
 * requests a connection with the server on local host with port 5402
 */
void Client::connect_com(const std::string& ip, int port) const{
  // create sockaddr obj
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ip.c_str());
  address.sin_port = htons(port);

  // connect command
  if (connect(client_socket, (struct sockaddr*) &address, sizeof(address)) == -1) {
    throw "Could not connect to simulator";
  } else {
    std::cout << "Client is now connected to the server" << std::endl;
  }
}

void Client::send_message_to_server(std::string str) const {
  int is_sent = send(client_socket, str.c_str(), str.length(), 0);
  if (is_sent == -1) {
    throw "Error sending message";
  } else {
    std::cout << "message was sent" << std::endl;
  }
}

int Client::get_client_sock() const {
  return client_socket;
}

void Client::close_socket() const{
  close(client_socket);
}

Client::Client(const std::string& ip, int port) {
  flag_stop_communication = false;
  client_socket = create_socket();
  connect_com(ip, port);
}

void start_sock(const Client& c) {
  while (true) {

    // check if the communication continues
    if (flag_stop_communication) {
      c.close_socket();
      break;
    }

  }
}