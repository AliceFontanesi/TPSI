#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define SERVERPORT 1313
#define DIM 50

//10.0.2.15 
int main(int argc, char **argv){
    if(argc != 3){
        printf("Numero argomenti sbagliato\n");
        exit(0);
    }
    struct sockaddr_in servizio;
    int socketfd;
    char stringa[DIM];
    char risposta[DIM];

    memset((char*)&servizio, 0, sizeof(servizio));
    servizio.sin_addr.s_addr = inet_addr(argv[1]);
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(atoi(argv[2]));

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    printf("Inserisci una stringa \n");
    scanf("%s", stringa);

    write(socketfd, stringa, sizeof(stringa));
    char prova[DIM];
    read(socketfd, risposta, sizeof(risposta));
    strcpy(prova, risposta);
    printf("%s", risposta);
    close(socketfd);

    return 0;
}