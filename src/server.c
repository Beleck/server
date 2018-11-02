#include <stdlib.h>
#include <stdio.h>
#include <lib.h>
#include <unistd.h>
#include <string.h>

#define NB_CHAL 2

char *challenges[NB_CHAL] = {
    "La réponse est Paris",
    "La réponse est Madrid"
};

char *responses[NB_CHAL] = {
    "Paris",
    "Madrid"
};

void challenge(int index, int socket) {
    printf("%s\n", challenges[index]);
    char buffer[100] = {0};

    while (strcmp(buffer, responses[index]) != 0) {
        read(socket, buffer, 100);
        buffer[strlen(buffer) - 1] = '\0';
    }
}


int main() {
    struct sockaddr_in addr;
    get_addr(&addr);
    addr.sin_addr.s_addr = INADDR_ANY;

    int socket = new_socket();

    int opt = 1;
    set_sock_opt(socket, &opt);

    bind_port(socket, &addr);

    listen_port(socket);

    int new_socket = accept_connection(socket, &addr);

    for (int i = 0; i < NB_CHAL; i++) {
       printf("\e[1;1H\e[2J");
       printf("-------------------- Challenge %d --------------------\n", i);
       challenge(i, new_socket);
    } 
    return 0;
}
