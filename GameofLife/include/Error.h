/**
 * @file Error.h
 * @brief This file contains error handling macros and functions.
 */

#ifndef ERROR_H
#define ERROR_H

#include <SDL2/SDL.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Checks if the test is true and if so, triggers an error with the provided message.
 * @param test The condition to check.
 * @param error_msg The error message to display if the test is true.
 */
#define ErrorIFtrue(test, error_msg) ErrorIFtrue_with_params(test, error_msg, __FILE__, __LINE__);

/**
 * @brief Checks if the pointer is null and if so, triggers an error with the provided message.
 * @param ptr The pointer to check.
 * @param error_msg The error message to display if the pointer is null.
 */
#define ErrorIFnull(ptr, error_msg) ErrorIFtrue_with_params(ptr == NULL, error_msg, __FILE__, __LINE__);

/**
 * @brief Checks if the SDL function returned a negative error code and if so, triggers an SDL error.
 * @param func_with_negative_error The SDL function to check.
 */
#define ErrorIFsdl(func_with_negative_error) ErrorIFtrue_with_params(func_with_negative_error < 0, "SDL hiba!", __FILE__, __LINE__);

/**
 * @brief Checks if the pointer is null due to insufficient memory and if so, triggers an error.
 * @param ptr The pointer to check.
 */
#define ErrorIFnoMemory(ptr) ErrorIFtrue_with_params(ptr == NULL, "Nincs eleg memoria!", __FILE__, __LINE__);

/**
 * @brief Checks if the test is true and if so, triggers an error with the provided message, file name, and line number.
 * @param test The condition to check.
 * @param error_msg The error message to display if the test is true.
 * @param FILE The file name where the error occurred.
 * @param LINE The line number where the error occurred.
 */
void ErrorIFtrue_with_params(bool test, char* error_msg, char* FILE, int LINE);

/**
 * @brief Displays a warning message box and logs an error message.
 * @param error_msg The error message to be displayed.
 */
void ErrorWarning(char* error_msg);
#endif