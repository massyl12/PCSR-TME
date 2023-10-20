#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <cstdlib>
#include <mutex>

namespace pr {

// MT safe version of the Queue, non blocking.
template <typename T>
class Queue {
	T ** tab;
	const size_t allocsize;
	size_t begin;
	size_t sz;
	mutable std::mutex m;
	bool is_Blocking;
	std::condition_variable cv_push; 
	std::condition_variable cv_pop; 

	// fonctions private, sans protection mutex
	bool empty() const {
		return sz == 0;
	}
	bool full() const {
		return sz == allocsize;
	}
public:
	Queue(size_t size) :allocsize(size), begin(0), sz(0) {
		tab = new T*[size];
		memset(tab, 0, size * sizeof(T*));
	}
	size_t size() const {
		std::unique_lock<std::mutex> lg(m);
		return sz;
	}
	T* pop() {
		std::unique_lock<std::mutex> lg(m);
		if (empty()) {
			return nullptr;
		}
		while(empty())
		{
			cv_pop.wait(lg);
		}
		auto ret = tab[begin];
		tab[begin] = nullptr;
		sz--;
		begin = (begin + 1) % allocsize;
		return ret;
	}
	bool push(T* elt) {
		std::unique_lock<std::mutex> lg(m);
		if (full()) {
			return false;
		}
		while(full())
		{
			cv_push.wait(lg);
		}
		if(!is_Blocking && empty())
		{
			return ptr;
		}

		tab[(begin + sz) % allocsize] = elt;
		sz++;
		return true;

	bool setBlocking(bool b){
		std::unique_lock<std::mutex> lg(m);
		is_Blocking = b;
		cv.pop.notify.all();
	}
	}
	~Queue() {
		// ?? lock a priori inutile, ne pas detruire si on travaille encore avec
		for (size_t i = 0; i < sz; i++) {
			auto ind = (begin + i) % allocsize;
			delete tab[ind];
		}
		delete[] tab;
	}
};

}

#endif /* SRC_QUEUE_H_ */
