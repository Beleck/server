#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in addr;
    get_addr(&addr);

    int socket = new_socket();

    do_connect(socket, (void *) &addr);
    
    send_messages(socket);

    return 0;
}
