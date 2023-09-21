//
// Created by asnic on 8/30/2023.
//

#include "http_server.h"


void show_file(char *path, struct bufferevent *event, int size) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("whats happening?");
    }

    const char *extension = strrchr(path, '.') + 1;
    const char *http_type = NULL;

    for (int i = 0; i < compute_type_list_size(); ++i) {
        if (strcmp(extension, type_list[i].extension) == 0) {
            http_type = type_list[i].http_type;
        }
    }

    if (http_type == NULL) {
        http_type = "application/octet-stream";
    }

    send_response_header(event, 200, "OK", http_type, size);
    int n;
    char buff[BUFSIZ] = {0};
    while ((n = read(fd, buff, sizeof(buff))) > 0) {
        bufferevent_write(event, buff, n);
    }
    printf("transmission finished!\n");
}

void show_folder(char *path, struct bufferevent *event) {
    /*
    DIR *dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "open dir failed, whats happening?");
        exit(-1);
    }*/

    struct dirent **files;
    int n = scandir(path, &files, NULL, sort);

    path += 1;
    if (*(path + strlen(path) - 1) == '/') {
        *(path + strlen(path) - 1) = '\0';
    }
    // bufferevent_write(event, upper_html, strlen(upper_html));
    sprintf(buf, upper_html);
    sprintf(buf + strlen(buf), "<h1>Files in the directory: %s</h1>\n<ul>\n", path);
    // bufferevent_write(event, buf, strlen(buf));
    // struct dirent *entry;


    /*
    while ((entry = readdir(dir)) != NULL) {
        printf("path is: %s\n", path);
        printf("file name is: %s\n", entry->d_name);
        sprintf(buf + strlen(buf),  "<li><a href=\"%s/%s\">%s</a></li>\n", path, entry->d_name, entry->d_name);
        // bufferevent_write(event, buf, strlen(buf));
    }
    */


    while (n--) {
        sprintf(buf + strlen(buf),  "<li><a href=\"%s/%s\">%s</a></li>\n", path, files[n]->d_name, files[n]->d_name);
        free(files[n]);
    }

    free(files);


    sprintf(buf + strlen(buf), lower_html);
    // bufferevent_write(event, lower_html, strlen(lower_html));
    int buflen = strlen(buf);
    send_response_header(event, 200, "OK", "text/html", buflen);
    bufferevent_write(event, buf, buflen);
}

void send_response_header(struct bufferevent *event, int no, char *discriptor, const char *file_type, int size) {
    char buff[1024] = {0};
    sprintf(buff, "HTTP/1.1 %d %s\r\n", no, discriptor);
    sprintf(buff + strlen(buff), "Content-Type: %s\r\n", file_type);
    sprintf(buff + strlen(buff), "Content-Length:%d\r\n\r\n", size);
    printf("%s\n", buff);
    bufferevent_write(event, buff, strlen(buff));
}

static void conn_eventcb(struct bufferevent *bev, short events, void *user_data) {
    if (events & BEV_EVENT_EOF) {
        printf("Connection closed.\n");
    } else if (events & BEV_EVENT_ERROR) {
        printf("Got an error on the connection: %s\n", strerror(errno));
    }
    bufferevent_free(bev);
}

void wizard_cb(struct evconnlistener *wizard, evutil_socket_t newfd,
               struct sockaddr *client_addr, int client_addr_size, void *vbase) {

    struct event_base *base = vbase;
    struct bufferevent *buf = bufferevent_socket_new(base, newfd, BEV_OPT_CLOSE_ON_FREE);
    if (!buf) {
        fprintf(stderr, "failed to initialize bufferent, exiting...");
        exit(-1);
    }
    bufferevent_setcb(buf, readcb, NULL, conn_eventcb, NULL);
    bufferevent_enable(buf, EV_WRITE | EV_READ);
}

void show_err(int err_no, struct bufferevent *event) {
    send_response_header(event, err_no, "Not Found", "text/html", 4);
    bufferevent_write(event, "404", 4);
}

void readcb(struct bufferevent *event, void *data) {
    char buff[HTTP_HEADER_SIZE];
    size_t readSize = bufferevent_read(event, buff, sizeof(buff));
    if (readSize <= 0) {
        fprintf(stderr, "unknown err, whats happening");
    }
    buff[readSize] = '\0';

    char exbuff[BUFSIZ];
    size_t exsize;
    int flag = 0;
    while (exsize = bufferevent_read(event, exbuff, sizeof(exbuff))) {
        flag = 1;
    }
    if (flag) {
        fprintf(stderr, "the data written by the clinet is bigger than the maximum allowed size");
    }

    char *token = strtok(buff, "\r\n");

    printf("the first line is: %s\n", token);

    char method[16];
    char path[128];
    char protocol[32];

    sscanf(token, "%s %s %s", method, path + 1, protocol);
    *path = '.';

    handle_http_space(path);
    printf("updated path is: %s\n", path);


    struct stat st;
    if (stat(path, &st) == -1) {
        show_err(404, event);
    } else if(S_ISREG(st.st_mode)) {
        show_file(path, event, st.st_size);
    } else if (S_ISDIR(st.st_mode)) {
        show_folder(path, event);
    } else {
    }

}
