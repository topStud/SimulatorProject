//
// Created by topaz on 19/12/2019.
//

#include "Client.h"
#include "UpdateSimulator.h"
#include "SymbolTable.h"
/*
 * creates socket and returns file descriptor
 */
int Client::create_socket(){
  int my_socket = socket(AF_INET, SOCK_STREAM,0);
  if (my_socket == -1) {
    // error
    throw "Could not create a socket";
  }
  return my_socket;
}

/*
 * receives as an input a file object
 * creates sockaddr object
 * requests a connection with the server on local host with port 5402
 */
void Client::connect_com(const std::string& ip, int port) const {
  // create sockaddr obj
  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ip.c_str());
  address.sin_port = htons(port);

  // connect command
  int is_connect = connect(client_socket, (struct sockaddr*) &address, sizeof(address));
  if (is_connect == -1) {
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

void Client::close_socket() const{
  close(client_socket);
}

Client::Client(const std::string& ip, int port) {
  flag_stop_communication_client = false;
  client_socket = create_socket();
  connect_com(ip, port);
}

void start_sock(const Client& c) {
  std::string key{}, message{};
  double value;

  while (true) {
    // check if the communication continues
    if (flag_stop_communication_client) {
      c.close_socket();
      break;
    }

    if (UpdateSimulator::get_instance()->updates_available()) {
      key = UpdateSimulator::get_instance()->pop_update();
      if (SymbolTable::get_instance()->is_key_exists_in_main_map(key)) {
        value = SymbolTable::get_instance()->get_value_from_main_map(key)->get_value();
        message = "set " + SymbolTable::get_instance()->get_value_from_main_map(key)->get_sim() + " " + std::to_string(value) + "\r\n";
        c.send_message_to_server(message);
      } else {
        std::cout << "an error from the client, the key was not recognized in the map";
      }
    }
  }
}