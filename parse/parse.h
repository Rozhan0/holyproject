#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct param {
    char * key;
    char * value;
} typedef param;

struct param_list {
    param * params;
    unsigned short length;
} typedef param_list;

char * create_response(char * msg);

#endif
