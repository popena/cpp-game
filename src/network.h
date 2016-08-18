#ifndef NETWORK_H
#define NETWORK_H
#include "utils.h"
#include "map.h"
#include <netinet/in.h>

class Map;
class Network {
	public:
		bool connected = false;
		bool initClient(const char *host, int port);
		int sendData(uint8_t packetType, void *packetData, size_t packetSize);
		int recvData(Map *map);

		enum packetTypes {
			TILECHANGE=0,
			CHAT,
			PLAYERPOS,
			PLAYERS
		};

	private:
		int sockfd;
		struct sockaddr_in server;
};

#endif
