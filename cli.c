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

#define DIM 10
#define SERVERPORT 1313

int main(){
    struct sockaddr_in servizio;
    int socketfd;
    char stringa[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));
    printf("Inserisci una stringa\n");
    scanf("%s", stringa);
    write(socketfd, stringa, sizeof(stringa));
    char risposta[DIM];
    read(socketfd, risposta, sizeof(risposta));
    printf("Stringa ricevuta %s\n", risposta);
    close(socketfd);
    return 0;
}

//struct
//assegnazione valori
//socketfd = socket
//connect