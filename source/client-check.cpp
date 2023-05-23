// Copyright (C) Alin Ichim 2023
#include "client-check.hpp"

#include <string>
#include <iostream>

bool client_check_book_id(std::string input) {

  if (input == "") return false;
  int n;
  try {
    n = std::stoi(input, nullptr, 10);
  } catch (std::invalid_argument &e) {
    return false;
  }

  return n >= 0;
}

bool client_check_book_attr(std::string input) {
  return input != "";
}

bool client_check_credential(std::string input) {

  return (input != "") && (input.find_first_of(" ") == std::string::npos);
}

bool client_check_command(std::string input) {

  return (input != "") && (input.find_first_of(" ") == std::string::npos);
}

bool client_check_book_page_count(std::string input) {
  return client_check_book_id(input);
}
