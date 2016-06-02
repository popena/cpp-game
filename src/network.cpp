#include "network.h"
#include <SDL/SDL_net.h>
#include <iostream>

using namespace std;

bool Network::connect(const char* ipAddress, int port)
{
	if(SDLNet_ResolveHost(&ip, ipAddress, port)==-1)
        {
                printf("failed to resolve");
                return false;
        }
	sock = SDLNet_TCP_Open(&ip);
	if(!sock)
	{
		printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
                return false;
	}
        return true;
}

int Network::sendMsg(const char* msg)
{
	uint32_t res, len = strlen(msg) + 1;
	
	res = SDLNet_TCP_Send(sock, &len, sizeof(len));
	if (res < sizeof(len)) {
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		SDLNet_TCP_Close(sock);
		return -1;
	}

	res = SDLNet_TCP_Send(sock, msg, len);
	if (res < len) {
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		SDLNet_TCP_Close(sock);
		return -1;
	}

	return res;
}

int Network::recvMsg(char *&buf)
{
	uint32_t res, len;

	if (buf) 
        {
	 	free(buf);
                buf = NULL;
        }
	
	res = SDLNet_TCP_Recv(sock, &len, sizeof(len));
	if (res < sizeof(len))
		goto error;

	buf = (char*)malloc(len);
	if (!(buf))
		return -1;
	
	res = SDLNet_TCP_Recv(sock, buf, len);
	if (res < len)
		goto error;

	return res;
error:
	if (buf)
		free(buf);
	fprintf(stderr, "SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
	SDLNet_TCP_Close(sock);
	return -1;
}
