#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <netinet/ip.h>
#include <string>
#include <iosfwd>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>


namespace pr {

class Socket {
	int fd;

public :
	Socket():fd(-1){}
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect(const std::string & host, int port);
	//void connect(in_addr ipv4, int port);
	void connect(sockaddr addr, socklen_t addr_len);

	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close();
};

std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
	char hname[1024];
	if(!getnameinfo((struct sockaddr *) addr, sizeof(*addr),hname,1024,nullptr,0,0)){
		os << std::string(hname);
	}
	os << std::string(inet_ntoa(addr->sin_addr)) << std::string(".") << std::to_string(ntohs(addr->sin_port));
	return os;
}


void Socket::connect(const std::string & host, int port){
	struct addrinfo* res, *rp;
	int s = getaddrinfo(host.c_str(),std::to_string(port).c_str(),AF_UNSPEC,&res);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	for (rp = res; rp != NULL; rp = rp->ai_next) {
		fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (fd == -1)
			continue;

		if (::connect(fd, rp->ai_addr, rp->ai_addrlen) != -1)
			break; /* Success */

		::close(fd);
	}

	freeaddrinfo(res); /* No longer needed */
}

void Socket::connect(sockaddr addr, socklen_t addr_len){
	fd = socket(AF_UNSPEC, SOCK_STREAM, 0);
	if(!fd){
		perror("socket error");
		exit(-1);
	}
	if(::connect(fd,&addr, addr_len)){
		::close(fd);
		perror("connection error");
		exit(-2);
	}
}

void Socket::close(){
	shutdown(fd,SHUT_RDWR);
	::close(fd);
}

}

#endif /* SRC_SOCKET_H_ */
