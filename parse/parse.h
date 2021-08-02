#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct param {
    char key[30];
    char value[20];
    struct param * next;
} typedef param;

struct req_data {
    param * param_list_head;
    param * param_list_top;
    char * path;
} typedef req_data;

char * create_response(char * msg);
int push_param(param * pr, req_data * data);
int parse_query(char * query, req_data * pl);
int parse_get_request(const char * request, req_data * pl);
void free_req_data(req_data * data);

#endif
