#include "http_server.h"
#include "utils.h"
#include "signal.h"

int port;
char *buf;
int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "usage: server port_number directory_path\n");
        exit(-1);
    }

    port = atoi(argv[1]);

    if (port == 0) {
        fprintf(stderr, "please input a valid port numbear\n");
        exit(-1);
    }

    char *path = argv[2];
    printf("the path is: %s\n", path);

    if (chdir(path) != 0) {
        fprintf(stderr, "failed to load the specified path\n");
        exit(-1);
    }

    buf = malloc(sizeof(char) * 10240);



    // initialize event_base
    struct event_base *base = event_base_new();
    if (!base) {
        fprintf(stderr, "error on initializing event_base, exiting!\n");
        return -1;
    }

    struct event *sigpipe_event = evsignal_new(base, SIGPIPE, sigpipe_cb, (void *)base);
    if (!sigpipe_event || event_add(sigpipe_event, NULL) < 0) {
        fprintf(stderr, "Could not create/add a signal event for SIGPIPE!\n");
        return -1;
    }

    
    struct event *sigint_event = evsignal_new(base, SIGINT, sigint_cb, (void *)base);

    if (!sigint_event || event_add(sigint_event, NULL) < 0) {
        fprintf(stderr, "Could not create/add a signal event for SIGINT!\n");
        return -1;
    }

    // set the listeniong port on the server side
    struct sockaddr_in sin;
    bzero(&sin, sizeof(sin));
    sin.sin_port = htons(port); // convert to big endine
    sin.sin_family = AF_INET; // use TCP protocol

    // set the callback function to add more TCP connections to the eventbase, and skip the 2ml waiting
    struct evconnlistener *wizard = evconnlistener_new_bind(base, wizard_cb,
                                                            (void *)base, LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                                            (struct sockaddr*)&sin, sizeof(sin));


    event_base_dispatch(base);

    evconnlistener_free(wizard);
    event_free(sigpipe_event);
    event_free(sigint_event);
    event_base_free(base);

}
