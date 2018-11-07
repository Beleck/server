#include <stdlib.h>
#include <stdio.h>
#include <lib.h>
#include <unistd.h>
#include <string.h>

#define NB_CHAL 6
#define C_1 "Welcome to our game !!!\n"\
"In this game you'll find pretty fun levels.\n\n"\
"Enjoy !!\n\n"\
"For this level just send \"copy\\n\"\n"


char *challenges[NB_CHAL] = {
    C_1,
    "La réponse est Paris\n",
    "La réponse est Madrid\n",
    "Caesar just sent me this message: aol huzdly av aopz johsslunl pz: yvtl aol nylha help me understand what it means! I only know that his favorite number is 7 \n",
    "Qué criatura tiene 4 patas a la mañana, 2 patas al mediodía y 3 patas a la noche?\n",
    "222 666 6 444 3 2\n"
};

char *responses[NB_CHAL] = {
    "copy",
    "Paris",
    "Madrid",
    "Rome the great",
    "El hombre",
    "comida"

};

int challenge(int index, int socket) {
    printf("%s\n", challenges[index]);
    char buffer[100] = {0};

    while (1) {
        if (recv(socket, buffer, 100, 0) <= 0) {
            return -1;
        }
        buffer[strlen(buffer) - 1] = '\0';
        if (strcmp(buffer, responses[index]) != 0) {
            printf("Seriously ? That's really your response : %s\n", buffer);
            sleep(2);
            printf("\033[A\33[2K\r");
            fflush(stdout);
        } else {
            return 0;
        }
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
       if (challenge(i, new_socket) == -1) {
           break;
       }
    } 
    printf("\e[1;1H\e[2J");
    printf("Congratulations you finished the game !\n");
    close(new_socket);
    close(socket);

    return 0;
}
