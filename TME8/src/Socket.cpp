#include "Socket.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <ostream>
#include <arpa/inet.h>

namespace pr {

Socket::Socket():fd(-1){}
Socket::Socket(int fd):fd(fd){}

bool Socket::isOpen() const {return fd != -1;}
int Socket::getFD() { return fd ;}

void Socket::connect(const std::string & host, int port)
{
    struct in_addr ip;
    struct addrinfo * res;
    getaddrinfo(host.c_str(),nullptr,nullptr,&res);

    for(addrinfo* rp=res; rp ; rp = rp->ai_next)
    {
        if(rp->ai_family == AF_INET)
        {
            ip = ((struct sockaddr_in *) rp->ai_addr)->sin_addr;
            break;
        }
    }
    freeaddrinfo(res);
}

void Socket::connect(in_addr ipv4, int port)
{
    int fdsock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    
    if(fdsock<0)
    {
        perror("Socket");
        return;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = ipv4;

    if(::connect(fdsock,(struct sockaddr*) &addr,sizeof(struct sockaddr_in)) < 0)
    {
        perror("Connect");
        ::close(fdsock);
        return;
    }

    this->fd = fdsock;

    return;
}


void Socket::close()
{
    if(isOpen())
    {
        ::shutdown(fd,2); //SHUT_RDWR
        ::close(fd);
    }
}


std::ostream & operator<<(std::ostream & os, struct sockaddr_in * addr)
{
    char host[1024];

    if(!getnameinfo((sockaddr*) addr, sizeof(struct sockaddr_in),host,1024,nullptr,0,0))
        os << host << std::endl;

    os << inet_ntoa(addr->sin_addr) << ":" << ntohs(addr->sin_port) << std::endl;

    return os;
}

}