#include <Socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace pr {

	// tente de se connecter à l'hôte fourni
	void connect(const std::string & host, int port){
        struct addrinfo * addrinfo;
        if(getaddrinfo(host, nullptr, nullptr,&addrinfo) != 0){
            perror("getaddrinfo");
            return 1;
        };


        struct sockaddr_in *ipv4 = (struct sockaddr_in *)addrinfo->ai_addr;
        struct in_addr addr = &(ipv4->sin_addr);
        freeaddrinfo(addrinfo);
        connect(addr, port);
    }

	void connect(in_addr ipv4, int port){
        sockaddr_in addr;

        //on met nos valeur dans un sockaddr_in
        addr.sin_family = AF_INET;
        addr.sin_addr = port;
        addr.sin_addr = htons(ipv4); //on converti le host shot en network short (du au little endian)

    
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){//on recup un file descriptor 
            perror("Erreur creation socket");
            exit(1);}
    }   
    //les :: pour utiliser le bon connect 
    //le cast pour respecter le type 
    if (::connect(fd, (struct sockaddr *) &addr, sizeof addr) == -1){
        perror("Erreur connect");
        close(fd);
        exit(1);
        }


	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close(){
        if (fd != -1) {
            shutdown(fd,1);
            ::close(fd);
        }
    }
};

std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr);



