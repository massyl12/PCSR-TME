#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) : queue(qsize){}
	void start (int nbthread){
		for(int i =0 ; i < nbthread ; ++i){
			threads.emplace_back(worker,std::ref(queue));
		}
	}
	static void worker(Queue<Job> &queue){
		while(true){
			Job *job = queue.pop();
			if(job == nullptr)return ;
			job->run();
			delete job;
		}
	}
	bool submit (Job * job){return queue.push(job);}
	void stop(){
		queue.setBlocking(false);
		for(std::thread & t : threads ){
			t.join();
		}
		threads.clear();
	}

	~Pool(){}

};

}
