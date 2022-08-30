#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <string.h>

#include "functs.h"
#include "httphandler.h"


#define PORT 4040

struct http_request {
    char * method;
    char * path;
    char * User_Agent;
};

int main(){

    /* define necessary variables */

    char * webroot = "www";

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


    char * path = malloc(1);

    char *test = malloc(1);

    char buffer[500];

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

        struct http_request data = http_read_request(buffer);

        path = realloc(path,(strlen(webroot) + strlen(data.path)));

        strcat(path, webroot);
        strcat(path, data.path);

        test = realloc(test, get_file_length(path));

        char response[500] = "HTTP/1.1 200 OK\nServer: WanServer/0.1\nContent-Type: text/html\nConnection: Closed\n\n";

        if(read_file(path, test) != 0)
        {
            strcat(response, "Error 404 File not found");
        } else {
            strcat(response, test);
        }



        write(connectionfd, response, sizeof(response));

        printf("Method: %s\nPath: %s\nUser-Agent: %s\n", data.method, data.path, data.User_Agent);

        if((shutdown(connectionfd, SHUT_RDWR)) == -1)
        {
            perror("Shutdown failed");
            close(connectionfd);
            close(socketfd);
            exit(EXIT_FAILURE);
        }

        memset(path,0,strlen(path));
        memset(test,0,strlen(test));

    }

    printf("%d", socketfd);

    close(socketfd);

    return 0;
}