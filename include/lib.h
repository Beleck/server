#ifndef _LIB_H_
#define _LIB_H
#include <netinet/in.h>

void get_line(char *line);
int get_port();
void get_ip_addr();
int new_socket();
void do_connect(int sock, struct sockaddr_in *addr);
void send_messages(int sock);

#endif
