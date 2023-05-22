// Copyright (C) Alin Ichim 2023
#include "client-funcs.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>

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

void process_register(bool &authenticated) {

  // Check if the user is already authenticated.
  if (authenticated) {
    std::cout << "[-] User already authenticated! Logout before trying to authenticate again" << std::endl;

    return;
  }

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
  char *message = compute_post_request(HOST, REGISTER_URL, CONTENT_TYPE, data.dump().data(), NULL, 0, NULL, 0);

  // Open connection to server.
  int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

  // Send message.
  send_to_server(sockfd, message);
  LOG_INFO("Message sent");
  free(message);

  // Await server response.
  char *response = receive_from_server(sockfd);

  // Process server response.
  if (response[strlen("HTTP/1.1 ")] == '2') {
    std::cout << "[+] New user registered!" << std::endl;
  } else {
    std::string json_str = basic_extract_json_response(response);
    std::cout << "[-] ";
    json response_data = json::parse(json_str);
    std::cout << response_data["error"] << std::endl;
  }
  free(response);

  // Close connection.
  close_connection(sockfd);
}

void process_login(std::vector<std::string> &cookies, bool &authenticated) {

  // Check if the user is already authenticated.
  if (authenticated) {
    std::cout << "[-] User already authenticated! Logout before trying to authenticate again" << std::endl;

    return;
  }

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
  char *message = compute_post_request(HOST, LOGIN_URL, CONTENT_TYPE, data.dump().data(), NULL, 0, NULL, 0);

  // Open connection to server.
  int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

  // Send message.
  send_to_server(sockfd, message);
  LOG_INFO("Message sent");
  free(message);

  // Await server response.
  char *response = receive_from_server(sockfd);

  // Process server response.
  if (response[strlen("HTTP/1.1 ")] == '2') {
    std::cout << "[+] User authenticated!" << std::endl;

    // Extract cookies.
    std::stringstream ss;
    char *c_start = strstr(response, "Set-Cookie:");
    ss << c_start;
    std::string line;
    getline(ss, line);
    line = line.substr(strlen("Set-Cookie: "), std::string::npos);  // Remove header name.
    line = line.substr(0, line.size() - 1);  // Remove carriage return.

    // Store cookies.
    cookies.push_back(line);

    // Update `authenticated` state.
    authenticated = true;
  } else {
    std::string json_str = basic_extract_json_response(response);
    std::cout << "[-] ";
    json response_data = json::parse(json_str);
    std::cout << response_data["error"] << std::endl;
  }
  free(response);

  // Close connection.
  close_connection(sockfd);
}

void process_logout(std::vector<std::string> &cookies, bool &authenticated) {

  // Check if the user is already authenticated.
  if (!authenticated) {
    std::cout << "[-] User is not authenticated!" << std::endl;

    return;
  }

  // Build `logout` message.
  const char *authorization = cookies[0].data();
  char *message = compute_get_request(HOST, LOGOUT_URL, NULL, (char **)&authorization, 1, NULL, 0);

  // Open connection to server.
  int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

  // Send message to server.
  send_to_server(sockfd, message);
  LOG_INFO("Message sent");
  free(message);

  // Await server response.
  char *response = receive_from_server(sockfd);

  // Process server response.
  if (response[strlen("HTTP/1.1 ")] == '2') {
    std::cout << "[+] User deauthenticated!" << std::endl;
    cookies.clear();
  } else {
    std::string json_str = basic_extract_json_response(response);
    std::cout << "[-] ";
    json response_data = json::parse(json_str);
    std::cout << response_data["error"] << std::endl;
  }
  free(response);

  // Close connection.
  close_connection(sockfd);
}

void process_enter_library(std::vector<std::string> &cookies, bool &authenticated, std::string &jwt_token) {

  // Check if the user is already authenticated.
  if (!authenticated) {
    std::cout << "[-] User is not authenticated!" << std::endl;

    return;
  }

  // Build message.
  const char *authorization = cookies[0].data();
  char *message = compute_get_request(HOST, ACCESS_URL, NULL, (char **)&authorization, 1, NULL, 0); 

  // Open connection to server.
  int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

  // Send message to server.
  send_to_server(sockfd, message);
  LOG_INFO("Message sent");
  free(message);

  // Await server response.
  char *response = receive_from_server(sockfd);

  // Process server response.
  char *payload = basic_extract_json_response(response);
  if (!payload)
    LOG_ERROR("Payload is NULL");
  std::string json_str = payload;
  json response_data = json::parse(json_str);
  if (response[strlen("HTTP/1.1 ")] == '2') {
    // Store JWT token.
    jwt_token = "Bearer " + (std::string)response_data["token"];
    std::cout << "[+] User access granted!" << std::endl;
  } else {
    std::cout << "[-] " << response_data["error"] << std::endl;
  }
  free(response);

  // Close connection.
  close_connection(sockfd);
}

void process_get_books_list(std::vector<std::string> &cookies, bool &authenticated, std::string jwt_token) {
  // Check if the user is already authenticated.
  if (!authenticated) {
    std::cout << "[-] User is not authenticated!" << std::endl;

    return;
  }

  // Build message.
  const char *authorization = cookies[0].data();
  std::string jwt_header = "Authorization: " + jwt_token;
  const char *jwt = jwt_header.data();
  char *message = compute_get_request(HOST, BOOKS_URL, NULL, (char **)&authorization, 1, (char **)&jwt, 1);

  // Open connection to server.
  int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

  // Send message to server.
  send_to_server(sockfd, message);
  LOG_INFO("Message sent");
  free(message);

  // Await server response.
  char *response = receive_from_server(sockfd);

  // Process server response.
  if (response[strlen("HTTP/1.1 ")] == '2') {
    char *payload = strstr(response, "\r\n[") + 2;
    std::cout << "[+] Books accessed!" << std::endl << payload << std::endl;
  } else {
    char *payload = basic_extract_json_response(response);
    std::string json_str = payload;
    json response_data = json::parse(json_str);
    std::cout << "[-] " << response_data["error"] << std::endl;
  }
  free(response);

  // Close connection.
  close_connection(sockfd);
}