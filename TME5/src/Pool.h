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
	Pool(int qsize) : queue(qsize) {}
	void start (int nbthread) {
		threads.reserve(nbthread);
		for (int i=0 ; i < nbthread ; i++) {
			threads.emplace_back(poolWorker, &queue);
			}
		}
	void submit (Job * job) {
		queue.push(job);
	}
	void stop(){
		queue.setBlocking(false);
		for (auto & t : threads) {
		t.join();
		}
		threads.clear();
	}
	void poolWorker(Queue<Job> & queue) {
		while (true) {
			Job * j = queue.pop();
			if (j == nullptr) return;
			j->run();
			delete j;
		}
	}
	~Pool() {
		stop();
	};
};

class Barier {
	std::mutex m;
	int cpt;
	const int N;
	std::condition_variable cv;
	Barier(int n) : cpt(0), N(n) {}

	void done(){
		std::unique_lock<std::mutex> lg(m);
		cpt++;
		if(cpt >=N)
		cv.notify_all();
	}

	void waitFor(){
		std::unique_lock<std::mutex> lg(m);
		while(cpt != N){
			cv.wait(lg);
		}
	}

	
	
};

}
