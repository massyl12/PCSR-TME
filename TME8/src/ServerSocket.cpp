#include "Socket.h"
#include "ServerSocket.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

namespace pr {

ServerSocket::ServerSocket(int port): socketfd(-1){
    int sockfd = ::socket(AF_INET,SOCK_STREAM, 0);
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY; //à vérifier

    if(::bind(sockfd,(struct sockaddr *)& addr, sizeof(addr)) < 0)
    {
        ::close(sockfd);
        perror("Bind");
        return;
    }

    if(::listen(sockfd,10) < 0)
    {
        perror("listen");
        return;
    }

    this->socketfd = sockfd;
}

int ServerSocket::getFD() { return socketfd;}
bool ServerSocket::isOpen() const {return socketfd != -1;}

Socket ServerSocket::accept()
{
    struct sockaddr_in exp;
    socklen_t exp_len = sizeof(exp);
    int fdcom = ::accept(this->socketfd, (struct sockaddr*) &exp,&exp_len);
    
    if(fdcom<0)
        std::cout << "Connection de" << &exp << std::endl;

    return Socket(fdcom);
}

void ServerSocket::close()
{
    if(isOpen())
    {
        ::close(socketfd);
        socketfd = -1;
    }
}


} // ns pr
