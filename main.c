#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>

/**
 * Given a hostname ("localhost", "mac1231231.local", etc.) tries to resolve it with getaddrinfo.
 * @param hostname The host name.
 * @return 0 iff success.
 */
int print_host_info(const char * hostname) {
    fprintf(stdout, "getaddrinfo(\"%s\", NULL, hints, &res);\n", hostname);
    fprintf(stdout, "  hints={AF_INET, SOCK_STREAM, IPPROTO_TCP}\n");

    struct addrinfo hints, *res = NULL;
    uint32_t addr;
    int err = 0;
    char host[512];

    memset((void *) &hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    err = getaddrinfo(hostname, NULL, &hints, &res);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo returned error %d ('%s')\n", err, gai_strerror(err));
        return err;
    }

    int i = 0;
    for (struct addrinfo * p = res; p != NULL; p = p->ai_next, i++) {
        err = getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof (host), NULL, 0, 0);
        if (err < 0) {
            fprintf(stderr, "Error in getnameinfo %d\n", err);
            break;
        }
        fprintf(stdout, "  %s ", host);

        err = getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof (host), NULL, 0, NI_NUMERICHOST);
        if (err < 0) {
            fprintf(stderr, "Error in getnameinfo %d\n", err);
            break;
        }
        fprintf(stdout, ": %s\n", host);
    }

    freeaddrinfo(res);
    return err;
}

int main(int argc, char** argv) {
    int err = 0;
    if (argc == 1) {
        return print_host_info("localhost");
    } else {
        for(int i=1; i<argc; i++) {
            err = print_host_info(argv[i]);
            if (err != 0) {
                return (err);
            }
        }
    }
    return (0);
}

