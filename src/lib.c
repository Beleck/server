#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <lib.h>

#define CHAR_MAX 100

void set_sock_opt(int socket, int *opt) {
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, opt, sizeof(*opt))) {
        perror("\n Error setting socket options \n");
        exit(1);
    }
}

int accept_connection(int socket, struct sockaddr_in *addr) {
    int size = sizeof(*addr);
    int new_socket = accept(socket, (struct sockaddr *) addr, (socklen_t *) &size);
    if (new_socket < 0) {
        perror("\n Error accept connection\n");
        exit(1);
    }
    return new_socket;
}

void listen_port(int socket) {
    if (listen(socket, 3) < 0) {
        perror("\n Error listening\n");
        exit(1);
    }
}

void bind_port(int socket, struct sockaddr_in *addr) {
    if (bind(socket, (struct sockaddr *) addr, sizeof(*addr)) < 0) {
        perror("\n bind port error \n");
        exit(1);
    }
}

void get_addr(struct sockaddr_in *addr) {
    int port = get_port();

    memset(addr, '0', sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
}

void get_line(char *line) {
    if (fgets(line, CHAR_MAX, stdin) == NULL) {
        perror("\n Problem to read from stdin \n");
        exit(1);
    }
}

int get_port() {
    printf("port : ");
    char line[CHAR_MAX];
    get_line(line);
    return  atoi(line);
}

void get_ip_addr(void *addr) {
    printf("IP address : ");
    char line[CHAR_MAX];
    get_line(line);
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
    char line[CHAR_MAX] = {0};
    do {
        get_line(line);
    } while (send(sock, line, sizeof(line), 0) != -1);
}
