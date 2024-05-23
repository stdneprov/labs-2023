#ifndef SERVER
#define SERVER

typedef struct Server {
    char name[30];
    long int ip;
    char active;
} Server;

#endif