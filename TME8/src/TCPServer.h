#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <thread>
#include <vector>
#include "ServerSocket.h"
#include "ConnectionHandler.h"

namespace pr {

// un serveur TCP, la gestion des connections est déléguée
class TCPServer {
	ServerSocket * ss; // la socket d'attente si elle est instanciee
	ConnectionHandler * handler; // le gestionnaire de session passe a la constru
	std::vector<std::thread> threads;


public :
	TCPServer(ConnectionHandler * handler): ss(nullptr),handler(handler) {
	}
	// Tente de creer une socket d'attente sur le port donné
	bool startServer (int port){
		int i;
		pr::ServerSocket serv = ServerSocket(port);
		if(!serv.isOpen()){
			exit(-1);
		}
		while(true){
			std::cout << "En attente" << std::endl;
			pr::Socket sc = serv.accept();
			handler->handleConnection(sc);
			threads.emplace_back([](pr::Socket sc,pr::ConnectionHandler* handler){
				handler->handleConnection(sc);
			},sc,handler);
		}
	}

	// stoppe le serveur
	void stopServer () {
		ss->close();


		fd_set set;
		FD_ZERO(&set);
		FD_SET(ss->getFD(),&set);
		FD_SET(STDIN_FILENO,&set);

		while(true){
			fd_set tmpSet = set;
			int result = select(STDIN_FILENO + 1, &tmpSet, nullptr, nullptr, nullptr);
			if (result == -1) {
				perror("select");
				break;
			} else if (result > 0) {
				// Parcourir tous les descripteurs de fichiers et vérifier leur état
				for (int fd : fileDescriptors) {
					if (FD_ISSET(fd, &tmpReadSet)) {
						std::cout << "FD " << fd << " is ready" << std::endl;
					}
				}
			} else {
				// result == 0 signifie qu'aucun descripteur de fichier n'est prêt à être lu
				// Vous pouvez ajouter un traitement ici si nécessaire
			}

			// Vous pouvez ajouter une condition pour arrêter la boucle
			// par exemple, si un descripteur de fichier atteint un état spécifique
			}
		}
	}

	~TCPServer(){
		for(auto& t: threads){
			t.join();
		}
	}
};

} // ns pr

#endif /* SRC_TCPSERVER_H_ */
