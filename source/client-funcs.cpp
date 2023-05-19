// Copyright (C) Alin Ichim 2023
#include "client-funcs.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include <sys/socket.h>
#include <poll.h>

#include "config.h"
#include "logger.h"
#include "requests.h"
#include "helpers.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define REGISTER_URL "/api/v1/tema/auth/register"
#define LOGIN_URL "/api/v1/tema/auth/login"
#define ACCESS_URL "/api/v1/tema/library/access"
#define BOOKS_URL "/api/v1/tema/library/books"
#define LOGOUT_URL "/api/v1/tema/auth/logout"
#define CONTENT_TYPE "application/json"

process_code process_get_code(std::string command) {
  if (command == "register") return REGISTER;
  if (command == "login") return LOGIN;
  if (command == "logout") return LOGOUT;
  if (command == "enter_library") return ENTER_LIBRARY;
  if (command == "get_books") return GET_BOOKS_LIST;
  if (command == "get_book") return GET_BOOK;
  if (command == "add_book") return ADD_BOOK;
  if (command == "delete_book") return DELETE_BOOK;
  if (command == "exit") return EXIT;
  return INVALID;
}

void process_register() {
  // Get username and password.
  std::string username, password;
  std::cout << "username=";
  std::cin >> username;
  std::cout << "password=";
  std::cin >> password;

  // Compute JSON data.
  json data;
  data["username"] = username;
  data["password"] = password;
  LOG_INFO("Computed data to send to server:\n" + data.dump());

  // Compute POST message.
  char *message = compute_post_request(HOST, REGISTER_URL, CONTENT_TYPE, data.dump().data(), NULL, 0);

  // Open connection to server.
  int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

  // Send message.
  send_to_server(sockfd, message);
  LOG_INFO("Message sent:\n" + (std::string)message);
  free(message);

  // Await server response.
  char *response = receive_from_server(sockfd);

  // Process server response.
  LOG_INFO("Server response:\n" + (std::string)response);
  if ((std::string)response == "") {
    std::cout << " -- New user registered!" << std::endl;
  } else {
    std::string json_str = basic_extract_json_response(response);

    // Extract response code.
    std::string code = strtok(response, "\n");
    code.erase(code.end() - 1);  // Carriage return.
    std::cout << code << " -- ";

    json response_data = json::parse(json_str);
    std::cout << response_data["error"] << std::endl;
  }

  free(response);
  close_connection(sockfd);
}