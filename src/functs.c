#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "functs.h"

int get_file_length(char filename[]){
    struct stat st;
    stat(filename, &st);
    int file_length = st.st_size;

    return file_length;
}

char * read_file(char filename[], char * buffer){
    int file_length = get_file_length(filename);

    FILE *fp;

    fp = fopen(filename, "r");

    if(fp==NULL)
    {
        perror("Opening file failed");
        exit(EXIT_FAILURE);
    }

    char content[file_length];
    char c = fgetc(fp);


    if(c==EOF)
    {
        printf("Error!");
    }

    while(c!=EOF){
        *buffer = c;
        ++buffer;
        c = fgetc(fp);
    }

    fclose(fp);

    return 0;
}