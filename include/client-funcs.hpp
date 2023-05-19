// Copyright (C) Alin Ichim 2023
#ifndef CLIENT_FUNCS_H_
#define CLIENT_FUNCS_H_

#include <string>

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
 * @param sockfd Connection socket.
 */
void process_register();

/**
 * @brief Processes user authentication.
 * 
 */
void process_login();

/**
 * @brief Processes user deauthentication.
 * 
 */
void process_logout();

/**
 * @brief Processes user library access.
 * 
 */
void process_enter_library();

/**
 * @brief Processes library query.
 * 
 */
void process_get_books_list();

/**
 * @brief Processes library query on a single book.
 * 
 */
void process_get_book();

/**
 * @brief Processes library book insertion.
 * 
 */
void process_add_book();

/**
 * @brief Processes library book deletion.
 * 
 */
void process_delete_book();

#endif  // CLIENT_FUNCS_H_