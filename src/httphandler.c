#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "httphandler.h"
#include "functs.h"


struct http_request {
    char * method;
    char * path;
    char * User_Agent;
};

/* write your code here */


struct http_request http_read_request(char request[]){
    
    request = append_char_to_string(request, '\n');
    
    char * ptr = request;

    char * line = (char *) malloc(1);

    struct http_request req;

    int count = 0;

    int len;

    while((ptr = strstr(ptr, "\n")) != NULL)
    {
        ptr += 1;

        len = (((char*) ptr) - ((char *)request));

        line = (char *) realloc(line, len);

        // Load line into line string

        line = sliceString(request, 0, (len - 1));

        request = ptr;

        if(line[0] != '\n')
        {
            count++;
            if(count == 1)
            {
                // Filter out the path and http method from the first line of the request

                if(strstr(line, "GET") != NULL) {req.method = "GET"; req.path = sliceString(line, 4, ((((char *)strstr(line+4, " ") - (char *)line))-1));}
                else if(strstr(line, "POST") != NULL) {req.method = "POST"; req.path = sliceString(line, 5, (char *)strstr(line+5, " ") - (char *)line);}
                else printf("Error: Wrong method");

            } else if(strstr(sliceString(line, 0, 10),"User-Agent:") != NULL) {
                req.User_Agent = sliceString(line, 12, strlen(line));
            } 

        }
    }
    return req;
}

int httphandle(int connectionfd){
    
    return 0;
}