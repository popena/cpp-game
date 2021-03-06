#include "network.h"
#include "map.h"
#include "packetTypes.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;


bool Network::initClient(const char *host, int port)
{
	connected = false;
	int status = 0;

	if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		return false;
	}

	memset(&this->server, 0, sizeof(this->server));
	this->server.sin_family = AF_INET;
	this->server.sin_port = htons(port);
	if (inet_aton(host, &this->server.sin_addr) == 0) {
		perror(host);
		return false;
	}

	if (connect(this->sockfd, (const sockaddr*)&this->server, 
				sizeof(this->server)) == -1)
	{
		perror("Connect");
		return false;
	}

	recv(sockfd, &status, sizeof(int), 0);
	if (status == 0) {
		cerr << "Server is full!\n";
		return false;
	}
	connected = true;

	return true;
}

int Network::sendData(void *packetData, size_t packetSize)
{
	this->buffer[0] = ((uint8_t*)packetData)[0];
	memcpy(buffer + 1, packetData, packetSize);
	return send(this->sockfd, buffer, packetSize + 1, 0);
}

int Network::recvData(Map *m)
{
	ssize_t n;
	uint8_t buffer[256];
	uint8_t type;
	if (recv(this->sockfd, &type, sizeof(uint8_t), MSG_WAITALL)) {
		switch (type) {
		case TILECHANGE:
		{
			if ((n = recv(this->sockfd, (void*)buffer, sizeof(PACKET_TILECHANGE), MSG_WAITALL)) != -1) {
				if (!m) //FIXME: First packet will be ignored because m will be NULL
					return 0;
				PACKET_TILECHANGE *p = (PACKET_TILECHANGE*)(buffer);
				printf("recv:x,y,t:%d,%d,%d\n", p->x, p->y, p->type);
				if (m->insideBounds(p->x, p->y)) {
					m->tiles[p->x][p->y]->type = p->type;
				}
			}
			break;
		}
		case CHAT:
			//TODO: pass message to chat handler
			//TODO: create chat handler
			break;

		case PLAYERPOS:
			//TODO: update player's position
			break;

		case PLAYERS:
			//TODO: copy map to other players
			//TODO: new player joined or someone left?
			//TODO: how are other players represented?
			break;
		}

	}

	return 1;
}
