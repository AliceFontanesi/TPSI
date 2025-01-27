#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 512 
#define SERVERPORT 1313

int main(int argc, char** argv) {
    struct sockaddr_in servizio;
    int socketfd;
    char str1[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    printf("Inserisci la stringa: ");
    scanf("%s", str1);
    write(socketfd, str1, sizeof(str1));

    char response[DIM];
    read(socketfd, response, sizeof(response));
    printf("Messaggio dal server: %s\n", response);

    close(socketfd);

    return 0;
}