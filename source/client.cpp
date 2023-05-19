// Copyright (C) Alin Ichim 2023
#include <iostream>
#include <string>
#include <vector>

#include <sys/socket.h>
#include <poll.h>

#include "logger.h"
#include "config.h"
#include "client-funcs.hpp"
#include "helpers.h"

int main(void) {
  LOG_INIT(LOGFILE);

  std::string command;
  std::string jwt_token = "";
  std::vector<std::string> cookies;
  while (true) {
    // Receive command from STDIN.
    std::cout << "> ";
    std::cin >> command;
    LOG_INFO("Received command: " + command);

    // Process command.
    process_code code = process_get_code(command);
    switch(code) {
      case REGISTER: {
        process_register();
        break;
      }
      case LOGIN: {
        // TODO
        process_login(cookies);
        break;
      }
      case LOGOUT: {
        // TODO
        // * process_logout()
        break;
      }
      case ENTER_LIBRARY: {
        // TODO
        // * process_enter_library()
        break;
      }
      case GET_BOOKS_LIST: {
        // TODO
        // * process_get_books_list()
        break;
      }
      case GET_BOOK: {
        // TODO
        // * process_get_book()
        break;
      }
      case ADD_BOOK: {
        // TODO
        // * process_add_book()
        break;
      }
      case DELETE_BOOK: {
        // TODO
        // * process_delete_book()
        break;
      }
      case EXIT: {
        // * Exit command.
        break;
      }
      default: {
        // ! Invalid command
        LOG_ERROR("Invalid command!");
        break;
      }
    }

    if (command == "exit") break;
  }

  return 0;
}