#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int port = get_port();

    struct sockaddr_in addr;
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    get_ip_addr(&addr.sin_addr);
    
    int socket = new_socket();

    do_connect(socket, (void *) &addr);
    
    send_messages(socket);

    return 0;
}
