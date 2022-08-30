#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functs.h"

int get_file_length(char filename[]){
    struct stat st;
    if((stat(filename, &st)) != 0)
    {
        perror("Stat failed");
        return EXIT_FAILURE;
    }
    int file_length = st.st_size;

    return file_length;
}

int read_file(char filename[], char * buffer){
    int file_length = get_file_length(filename);

    FILE *fp;

    fp = fopen(filename, "r");

    if(fp==NULL)
    {
        perror("Opening file failed");
        return EXIT_FAILURE;
    }
    
    char c = fgetc(fp);

    while(c!=EOF){
        *buffer = c;
        ++buffer;
        c = fgetc(fp);
    }

    fclose(fp);

    return 0;
}

char *sliceString(char *str, int start, int end)
{

    int i;
    int size = (end - start) + 2;
    char *output = (char *)malloc(size * sizeof(char));

    for (i = 0; start <= end; start++, i++)
    {
        output[i] = str[start];
    }

    output[size] = '\0';

    return output;
}

char * append_char_to_string(char *str, char appendage){
    int len = strlen(str);
    char * str2 = (char *) malloc(len + 1);

    strcpy(str2, str);

    str2[len] = appendage;

    return str2;
}
