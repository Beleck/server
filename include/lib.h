#ifndef _LIB_H_
#define _LIB_H
#include <netinet/in.h>

void set_sock_opt(int socket, int *opt);
int accept_connection(int socket, struct sockaddr_in *addr);
void listen_port(int socket);
void bind_port(int socket, struct sockaddr_in *addr);
void get_addr(struct sockaddr_in *addr);
void get_line(char *line);
int get_port();
void get_ip_addr();
int new_socket();
void do_connect(int sock, struct sockaddr_in *addr);
void send_messages(int sock);

#endif
