#include "parse.h"

#define DEBUG 1

char * create_response(char * msg) {
    char * output = calloc(strlen(msg) + 200, sizeof(char));
    sprintf(output,
            "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\n"
            "Content-Type: text/html\nContent-Length: %ld\n\n%s",
            strlen(msg), msg);
    return output;
}

int push_param(param * pr, req_data * data) {
    /* this function pushes a param structure to linked list
    inside req_data structure */

    if(pr != 0 && data != 0) {
        if(data->param_list_top)
            data->param_list_top->next = pr;
        else
            data->param_list_head = pr;
        data->param_list_top = pr;
        return 1;
    } else return 0;
}

int parse_query(char * query, req_data * data) {
    /* this function parses a query string into an
    array of parameters which every one of them holds
    a key and a value */

    char * parameter, * rest = query;
    while(parameter = strtok_r(rest, "&", &rest)) {
        param * pr = calloc(1, sizeof(param));
        char * equal_mark = strchr(parameter, '=');
        if(equal_mark == 0) {
            DEBUG && puts("parse.c->parse_query-> Broken Query.");
            return 0;
        }
        *equal_mark = ' ';
        sscanf(parameter, "%s %s", pr->key, pr->value);
        if(!push_param(pr, data)) {
            DEBUG && puts("parse.c->parse_query-> null pointer.");
        }
    }
    return 1;
}

int parse_get_request(const char * request, req_data * data) {
    /* this function parses a request to path and query.
    if query exists, it will be passed to parse_query */

    data->param_list_head = 0;
    data->param_list_top = 0;
    data->path = 0;
    char path[64] = {0};
    char * querstion_mark = memchr(request, '?', 80);
    if(querstion_mark) {
        *querstion_mark = ' ';
        char query[129] = {0};
        sscanf(request, "GET %s %s ", path, query);
        if(parse_query(query, data) == 0) return 0;
    } else {
        sscanf(request, "GET %s ", path);
    }
    data->path = calloc(strlen(path) + 1, sizeof(char));
    strcpy(data->path, path);
    return 1;
}

void free_req_data(req_data * data) {
    /* this function, does free memory allocated for
    the linked list and path in req_data structure */

    param * pr1 = data->param_list_head;
    param * pr2;
    do {
        pr2 = pr1->next;
        free(pr1);
    } while(pr1 = pr2);

    free(data->path);
}
