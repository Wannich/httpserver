#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <string.h>

#include "functs.h"

#define PORT 4040

int main(){

    /* define necessary variables */

    int socketfd, connectionfd;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    /* initialize socket (error checking is missing) */

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    /* bind socket and check for errors */

    if((bind(socketfd, (struct sockaddr *)&address, sizeof(address))) != 0)
    {
        perror("Bind failed");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    /* set socket to listen and check for errors */

    if ((listen(socketfd, 10)) != 0)
    {
        perror("Listen failed");
        close(socketfd);
        exit(EXIT_FAILURE);
    }


    int file_length = get_file_length("index.html");

    printf("File is %d bytes long.\n", file_length);

    char *test = malloc(file_length);

    read_file("index.html", test);

    printf("%s", test);

    char buffer[500];

    char response[500] = "HTTP/1.1 200 OK\nServer: WanServer/0.1\nContent-Type: text/html\nConnection: Closed\n\n";

    strcat(response, test);

    /* listen to requests in a loop and quit if there is any errors */

    for(;;) {
        connectionfd = accept(socketfd, NULL, NULL);

        if(connectionfd == -1)
        {
            perror("Accept failed");
            close(socketfd);
            exit(EXIT_FAILURE);
        }



        read(connectionfd, buffer, sizeof(buffer));

        write(connectionfd, response, sizeof(response));

        printf("%s", buffer);

        if((shutdown(connectionfd, SHUT_RDWR)) == -1)
        {
            perror("Shutdown failed");
            close(connectionfd);
            close(socketfd);
            exit(EXIT_FAILURE);
        }

    }

    printf("%d", socketfd);

    close(socketfd);

    return 0;
}