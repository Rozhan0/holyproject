#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif

struct saddr{
    int sockid;
    struct sockaddr_in address;
} typedef saddr;

saddr initialize_server();
int get_client(saddr s, char *buffer);
void respond(int client_socket, char *message);
void close_socket(saddr s);

#endif
