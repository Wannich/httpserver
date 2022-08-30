/* functs.h */

#ifndef _FUNCTS_H
#define _FUNCTS_H

#include <string.h>

int get_file_length(char filename[]);

int read_file(char filename[], char * buffer);

char *sliceString(char *str, int start, int end);

char * append_char_to_string(char *str, char appendage);

#endif