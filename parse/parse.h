#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct param {
    char key[30];
    char value[20];
} typedef param;

struct req_data {
    param * params;
    char * path;
    unsigned short length;
} typedef req_data;

char * create_response(char * msg);
int parse_query(char * query, req_data * pl);
int parse_get_request(const char * request, req_data * pl);

#endif
