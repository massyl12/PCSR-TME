#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {
void poolWorker(Queue<Job>& queue){
	while(true){
		Job* j = queue.pop();
		if(!j){
			return;
		}
		j->run();
		delete j;
	}
}

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) ;
	void start (int nbthread);
	void submit (Job * job) ;
	void stop() ;
	~Pool() ;
};

Pool::Pool(int qsize): queue(qsize){
}

void Pool::start (int nbthread){
	for(int i=0;i<nbthread;i++){
		threads.emplace_back(poolWorker,std::ref(queue));
	}
}

void Pool::submit(Job* job){
	queue.push(job);
}


void Pool::stop(){
	queue.setBlocking(false);
	for(auto& t : threads){
		t.join();
	}
	threads.clear();
}

Pool::~Pool() {}

}
