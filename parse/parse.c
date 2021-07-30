#include "parse.h"

char * create_response(char * msg) {
    char * output = calloc(strlen(msg) + 200, sizeof(char));
    sprintf(output,
            "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\n"
            "Content-Type: text/html\nContent-Length: %ld\n\n%s",
            strlen(msg), msg);
    return output;
}
