// Copyright (C) Alin Ichim 2023
#ifndef CLIENT_FUNCS_H_
#define CLIENT_FUNCS_H_

#include <string>
#include <vector>

enum process_code {
  REGISTER,
  LOGIN,
  LOGOUT,
  ENTER_LIBRARY,
  GET_BOOKS_LIST,
  GET_BOOK,
  ADD_BOOK,
  DELETE_BOOK,
  EXIT,
  INVALID
};

/**
 * @brief Returns the command code from command string.
 * 
 * @param command The command string.
 * @return The command code or INVALID for unknown command.
 */
process_code process_get_code(std::string command);

/**
 * @brief Processes user registration.
 * 
 * @param authenticated Tells if the user is already authenticated.
 */
void process_register(bool &authenticated);

/**
 * @brief Processes user authentication.
 * 
 * @param cookies Stored cookies.
 * @param authenticated Tells if the user is already authenticated.
 */
void process_login(std::vector<std::string> &cookies, bool &authenticated);

/**
 * @brief Processes user deauthentication.
 * 
 * @param cookies Stored cookies.
 * @param authenticated Tells if the user is already authenticated.
 */
void process_logout(std::vector<std::string> &cookies, bool &authenticated);

/**
 * @brief Processes user library access.
 * 
 * @param cookies Stored cookies.
 * @param authenticated Tells if the user is already authenticated.
 */
void process_enter_library(std::vector<std::string> &cookies, bool &authenticated, std::string &jwt_token);

/**
 * @brief Processes library query.
 * 
 * @param cookies Stored cookies.
 * @param authenticated Tells if the user is already authenticated.
 */
void process_get_books_list(std::vector<std::string> &cookies, bool &authenticated);

/**
 * @brief Processes library query on a single book.
 * 
 * @param authenticated Tells if the user is already authenticated.
 */
void process_get_book(bool &authenticated);

/**
 * @brief Processes library book insertion.
 * 
 * @param authenticated Tells if the user is already authenticated.
 */
void process_add_book(bool &authenticated);

/**
 * @brief Processes library book deletion.
 * 
 * @param authenticated Tells if the user is already authenticated.
 */
void process_delete_book(bool &authenticated);

#endif  // CLIENT_FUNCS_H_