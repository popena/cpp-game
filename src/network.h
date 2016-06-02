#ifndef NETWORK_H
#define NETWORK_H
#include "utils.h"
#include <cstdlib>
#include <cstdio>
#include <SDL/SDL_net.h>

class Network {
        public:
                int sendMsg(const char* msg);
                int recvMsg(char *&msg);
                bool connect(const char* ipAddress, int port);
                IPaddress ip;
                TCPsocket sock;
        private:
};
#endif
