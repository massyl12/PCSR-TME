#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "Socket.h"
#include <sys/socket.h>
#include <iostream>

namespace pr {

class ServerSocket {
	int socketfd;

public :
	// Demarre l'ecoute sur le port donne
	ServerSocket(int port);

	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	Socket accept();

	void close();
};

ServerSocket::ServerSocket(int port){
	struct sockaddr_in sin;
	sin.sin_family = AF_UNSPEC;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	int fd=socket(AF_UNSPEC, SOCK_STREAM, 0);
	if(!fd){
		perror("socket error");
		exit(-1);
	}

	if(bind(fd, (struct sockaddr*) &sin, sizeof(sin))){
		::close(fd);
	}
	listen(fd,5);
	socketfd = fd;
}

Socket ServerSocket::accept(){
	int clientfd = ::accept(socketfd,0,0);
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	if((clientfd=::accept(socketfd,(struct sockaddr*) &addr,&len))){
		perror("accept socket error");
		exit(-1);
	}
	std::cout << "Connexion de " << &addr << std::endl;
	return clientfd;

}
} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */

