#pragma once

#include "stack.h"
#include <stdexcept>

using namespace std;

const int MaxQueueSize = MaxStackSize;

template<typename T>
class TQueue
{
private:
	TStack<T> left_st;
	TStack<T> right_st;
	int maxSize;
	int sz;

public:

	TQueue() : sz(0), maxSize(MaxQueueSize), left_st(MaxQueueSize), right_st(MaxQueueSize) {}

	TQueue(int sz_) : sz(0), maxSize(sz_), left_st(sz_), right_st(sz_) {
		if (sz_ < 1 || sz_> MaxQueueSize)
			throw invalid_argument("Size must be between 1 and MaxQueueSize");
	}

	// we prohibit copying and assignment of the queue, since we use it as a service structure
	TQueue(const TQueue&) = delete; // Removing the copy constructor
	TQueue& operator=(const TQueue&) = delete; // Removing the assignment operator

	int Size() const { return sz; };

	bool IsEmpty() const { return sz == 0; };

	bool IsFull() const { return sz == maxSize; }

	void Push(const T& val) {
		if (IsFull()) {
			throw overflow_error("Queue is full");
		}
		left_st.Push(val);
		sz++;
	}

	T Front() {
		if (IsEmpty())
			throw out_of_range("Queue is empty");
		if (right_st.IsEmpty()) {
			while (!left_st.IsEmpty()) {
				right_st.Push(left_st.Top());
				left_st.Pop();
			}
		}
		T val = right_st.Top();
		return val;
	}

	void Pop() {
		if (IsEmpty())
			throw out_of_range("Queue is empty");
		if (right_st.IsEmpty()) {
			while (!left_st.IsEmpty()) {
				right_st.Push(left_st.Top());
				left_st.Pop();
			}
		}
		right_st.Pop();
		sz--;
	}
};
