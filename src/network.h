#ifndef NETWORK_H
#define NETWORK_H
#include "utils.h"
#include <netinet/in.h>

class Network {
	public:
		bool initClient(const char *host, int port);
		int sendData(int packetType, void *packetData, size_t packetSize);
		int recvData(void);

		typedef struct packet_t {
			uint8_t type;
			void *data; //FIXME: no void pointers
		} packet_t;

		enum packetTypes {
			TILEMINE = 0,
			TILECHANGE,
			CHAT,
			PLAYERPOS,
			PLAYERS
		};

	private:
		int sockfd;
		struct sockaddr_in server;
};

#endif
