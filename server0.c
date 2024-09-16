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

#define SERVERPORT 1313
#define DIM 50

void contaVocCons(char str[], char risposta[]){
    int contaVoc = 0;
    int contaCons = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if(str[i] == 'a' || str[i] == 'e'|| str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
            contaVoc++;
        else
            contaCons++;
    }
    sprintf(risposta, "La stringa contiene %d vocali e %d consonanti\n", contaVoc, contaCons);
}

int main(int argc, char **argv){
    struct sockaddr_in servizio, ind_rem;
    int socketfd, soa, fromlen = sizeof(servizio);
    char stringa[DIM];
    char risposta[DIM];

    memset((char*)&servizio, 0, sizeof(servizio));
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));
    listen(socketfd, 10);

    for(;;){
        printf("Server in ascolto...\n");
        fflush(stdout);
        soa = accept(socketfd, (struct sockaddr*) &ind_rem, &fromlen);
        read(soa, stringa, sizeof(stringa));
        printf("Ricevuto %s\n", stringa);
        contaVocCons(stringa, risposta);
        printf("%s", risposta);
        write(soa, risposta, sizeof(risposta));
        close(soa);
    }

    return 0;
}