/* httphandler.h */

#ifndef _HTTPHANDLER_H
#define _HTTPHANDLER_H

#include "functs.h"

struct http_request http_read_request(char request[]);

int httphandle(int connectionfd);

struct http_request;

#endif