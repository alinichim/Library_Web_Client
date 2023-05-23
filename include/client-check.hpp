// Copyright (C) Alin Ichim 2023
#ifndef CLIENT_CHECK_HPP_
#define CLIENT_CHECK_HPP_

#include <string>

/**
 * @brief Checks if the credential is valid.
 * 
 * @param input The input credential.
 * @return True if the credential is good or False otherwise.
 */
bool client_check_credential(std::string input);

/**
 * @brief Checks if the input command is valid.
 * 
 * @param input The input command.
 * @return True if the command is good or False otherwise.
 */
bool client_check_command(std::string input);

/**
 * @brief Checks if the input book id is valid.
 * 
 * @param input The input book id.
 * @return True if the book id is good or False otherwise.
 */
bool client_check_book_id(std::string input);

/**
 * @brief Checks if the input book string attribute is valid.
 * 
 * @param input The input attribute.
 * @return True if the book attribute is good or False otherwise.
 */
bool client_check_book_attr(std::string input);

/**
 * @brief Checks if the input book `page_count` attribute is valid.
 * 
 * @param input The `page_count` book attribute.
 * @return True if the book attribute is good or False otherwise.
 */
bool client_check_book_page_count(std::string input);

#endif  // CLIENT_CHECK_HPP_