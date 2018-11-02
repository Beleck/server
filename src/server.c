#include <stdlib.h>
#include <stdio.h>
#include <lib.h>
#include <unistd.h>

int main() {
    struct sockaddr_in addr;
    get_addr(&addr);
    addr.sin_addr.s_addr = INADDR_ANY;

    int socket = new_socket();

    bind_port(socket, &addr);

    listen_port(socket);

    int new_socket = accept_connection(socket, &addr);

    char buffer[100] = {0};
    read(new_socket, buffer, 100);
    printf("%s\n", buffer);
    
    return 0;
}
