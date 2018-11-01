#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int get_port() {
    printf("In which port do you want to connect ? : ");
    char line[100];
    if (fgets(line, 100, stdin) == NULL) {
        perror("\n Problem to read from stdin \n");
        exit(1);
    }
    
    return  atoi(line);
}

void get_ip_addr(void *addr) {
    printf("What's the address of server you want to connect ? : ");
    char line[100];
    if (fgets(line, 100, stdin) == NULL) {
        perror("\n Problem to read from stdin \n");
        exit(1);
    }
    line[strlen(line)-1] = '\0';
    if (inet_pton(AF_INET, line, addr) <= 0) {
        perror("\n Error during address conversion \n");
        exit(1);
    }
}

int new_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <= 0) {
        perror("\n Socket creation error\n");
        exit(1);
    }
    return sock;
}

void do_connect(int sock, struct sockaddr_in *addr) {
    if (connect(sock, (struct sockaddr *) addr, sizeof(*addr)) < 0) {
        perror("\n Error connecting to server \n");
        exit(1);
    }
}

void send_messages(int sock) {
    char line[100];
    do {
        if (fgets(line, 100, stdin) == NULL) {
            perror("\n Problem to read from stdin \n");
            exit(1);
        }
    } while (send(sock, line, sizeof(line), 0) != -1);
}

int main() {
    int port = get_port();

    struct sockaddr_in addr;
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    get_ip_addr(&addr.sin_addr);
    
    int socket = new_socket();

    do_connect(socket, &addr);
    
    send_messages(socket);

    return 0;
}
