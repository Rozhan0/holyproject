#include "parse.h"

char * create_response(char * msg) {
    char * output = calloc(strlen(msg) + 200, sizeof(char));
    sprintf(output,
            "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\n"
            "Content-Type: text/html\nContent-Length: %ld\n\n%s",
            strlen(msg), msg);
    return output;
}

int parse_query(char * query, req_data * data) {
    /* this function parses a query string into an
    array of parameters which every one of them holds
    a key and a value */

    char * parameter, * rest = query;
    data->length = 0;
    data->params = calloc(0, sizeof(param));
    while(parameter = strtok_r(rest, "&", &rest)) {
        data->length++;
        data->params = realloc(data->params, data->length * sizeof(param));
        param * pr = data->params + data->length - 1;
        char * equal_mark = strchr(parameter, '=');
        if(equal_mark == 0) {
            puts("parse.c->parse_get_request-> Broken Query.");
            return 0;
        }
        *equal_mark = ' ';
        sscanf(parameter, "%s %s", pr->key, pr->value);
    }
    return 1;
}

int parse_get_request(const char * request, req_data * data) {
    /* this function parses a request to path and query.
    if query exists, it will be passed to parse_query */

    char path[129] = {0};
    char * querstion_mark = strchr(request, '?');
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
