#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>
#include <condition_variable>
#include <iostream>
namespace pr {

class Barrier{
		std::mutex mutex_;
		std::condition_variable condition_;
		const size_t totalThreads_;
		size_t waitingThreads_; //
	public:
		explicit Barrier(int nbThreads):totalThreads_(nbThreads),waitingThreads_(0) {}

		void test(){ std::cout << "Le nombre de threads arrivé : " << waitingThreads_ << std::endl;}

		void await() {
			std::unique_lock<std::mutex>
			lock(mutex_);
			++waitingThreads_;
			test();
			if (waitingThreads_ < totalThreads_) {
				condition_.wait(lock);
			} else {
				waitingThreads_ = 0; 
				condition_.notify_all();
				lock.unlock();
			}
	}
};
}
