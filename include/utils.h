//
// Created by asnic on 8/30/2023.
//

#ifndef RE_FILE_SERVER_UTILS_H
#define RE_FILE_SERVER_UTILS_H

#include "constants.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <event2/util.h>
#include <event2/event.h>
// extern char *buf;


/*
 * a: pointer to the string pointer, pointing at the first string to be compared
 *
 * b: pointer to the string pointer, pointing at the second string to be compared
 *
 * this function defines a way to compare the string used to sort the file names retrieved
 * from a directory
 */
int sort(const struct dirent **a, const struct dirent **b);

/*
 * NOTE: this function's prototype is being defined by the libevent library
 *
 * sig: the file descriptor of the socket encountered SIGPIPE signal
 *
 * user_data: not being used
 *
 * this function is a call back function that will be invoked after a function receives
 * signal SIGPIPE, this is usually due to the client rapidly refresh the web page, in this case
 * we do nothing (blocking default behaviour which is exit the program) except to print some log.
 */
void sigpipe_cb(evutil_socket_t sig, short events, void *user_data);

void sigint_cb(evutil_socket_t sig, short events, void *user_data);

/*
 * this function computes the number of elements in the array type_list
 * defined ub rge constants.c. this function is needed because the main.c cannot directly
 * access the definition of the array until linking, and therefore cannot statically compute its size
 * using operator sizeof
 */
int compute_type_list_size();

/*
 * file_name: the string that needs to be processed
 *
 * this function converts %20 to ' ', the browser will automatically convert any user inputted space in the request header
 * (such as when there is a space in the file name) with %20, this function converts it back so that the system
 * can find corresponding file
 */
void handle_http_space(char *file_name);

#endif //RE_FILE_SERVER_UTILS_H
