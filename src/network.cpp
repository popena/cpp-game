#include "network.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;


bool Network::initClient(const char *host, int port)
{
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
		fprintf(stderr, "Server is full!\n");
		return false;
	}

	return true;
}

int Network::sendData(int packetType, void *packetData, size_t packetSize)
{
	return send(this->sockfd, packetData, packetSize, 0);
}

int Network::recvData(void)
{
	ssize_t n;
	uint8_t buffer[256], type;

	//FIXME: set non-blocking flag??
	if ((n = recv(this->sockfd, (void*)buffer, 256, 0)) != -1) {
		type = buffer[0];

		switch (type) {
		case TILEMINE:
			//TODO: tile was mined, update map
			break;

		case TILECHANGE:
			//TODO: pass data to tileSprites(?)
			break;

		case CHAT:
			//TODO: pass message to chat handler
			//TODO: create chat handler
			break;

		case PLAYERPOS:
			//TODO: update player's position
			break;

		case PLAYERS:
			//TODO: new player joined or someone left?
			//TODO: how are other players represented?
			break;
		}

	}

	return 1;
}
