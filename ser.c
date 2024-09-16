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
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, fromlen = sizeof(servizio), soa;
    char stringa[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));
    listen(socketfd, 10);
    for(;;){
        printf("Server in ascolto...\n");
        fflush(stdout);
        soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &fromlen);
        read(soa, stringa, sizeof(stringa));
        printf("ricevuta %s\n", stringa);
        write(soa, stringa, sizeof(stringa));
        close(soa);
    }

    return 0;
}

//assegnazione valori
//socketfd = socket
//bind
//listen
//for(;;)
//fflush
//accept
