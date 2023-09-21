//
// Created by asnic on 8/30/2023.
//

#include <malloc.h>
#include "utils.h"
int sort(const struct dirent **a, const struct dirent **b) {
    return strcmp((*b)->d_name, (*a)->d_name);
}

void sigpipe_cb(evutil_socket_t sig, short events, void *user_data) {
    printf("Received SIGPIPE signal.\n");
}

int compute_type_list_size() {
    int size = 0;
    while (type_list[size].extension != NULL) {
        ++size;
    }
    return size;
}

void handle_http_space(char *file_name) {
    char *dest = file_name;

    while (*file_name) {
        if (*file_name == '%' && *(file_name + 1) == '2' && *(file_name + 2) == '0') {
            *dest = ' ';
            dest++;
            file_name += 3;
        } else {
            *dest = *file_name;
            ++dest;
            ++file_name;
        }
    }
    *dest = '\0';
}

void sigint_cb(evutil_socket_t sig, short events, void *user_data) {
    // free(buf);
    printf("SIGINT received, exiting safely...");
    event_base_loopexit(user_data, NULL);
    // event_base_free(user_data);
}

