#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "Socket.h"

namespace pr {

class ServerSocket {
	int socketfd;

public :
	// Demarre l'ecoute sur le port donne
	ServerSocket(int port) : socketfd(-1){
		if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){//on recup un file descriptor 
            perror("Erreur creation socket");
            exit(1);}  

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htonl(port);
		addr.sin_addr = htonl(INADDR_ANY);
		if(bind(socketfd, (struct sockaddr *) &addr ,sizeof addr) == -1){
			perror("Erreur Bind");
			::close(socketfd);
			return 1;
		}


		if (listen(socketfd, 50) == -1){
			perror("listen");
			::close(fd);
			return 1;
		}
	}
	
	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	Socket accept(){
		struct sockaddr_in addr;
		if(::accept(socketfd,(struct sockaddr *) &addr, &addr) == -1){
			perror("accept");
		}
		return addr
	}

	void close(){
		if (socketfd != -1) {
			shutdown(socketfd,1);
			::close(socketfd);
			}
	}
};

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
