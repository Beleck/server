#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in addr;
    get_addr(&addr);
    get_ip_addr(&addr.sin_addr);

    int socket = new_socket();

    do_connect(socket, (void *) &addr);
    
    send_messages(socket);

    return 0;
}
