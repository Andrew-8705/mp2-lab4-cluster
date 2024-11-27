#pragma once

#include <stdexcept>
#include <vector>

using namespace std;

const int MaxStackSize = 100;

template <class T>
class TStack
{
    vector<T> mem;
    int top;
    bool fixedSize;
    int maxSize;
public:
    TStack() : mem(), top(-1), fixedSize(false), maxSize(MaxStackSize) {}

    TStack(int _size) : mem(_size), top(-1), fixedSize(true), maxSize(_size) {
        if (_size < 1 || _size > MaxStackSize)
            throw invalid_argument("Size must be between 1 and MaxStackSize");
    }

    // we prohibit copying and assignment of the stack, since we use it as a service structure
    TStack(const TStack&) = delete; // Removing the copy constructor
    TStack& operator=(const TStack&) = delete; // Removing the assignment operator

    void Push(const T& val) {
        if (IsFull())
            throw overflow_error("Stack is full");

        if (!fixedSize) {
            mem.push_back(val);
            top++;
        }
        else {
            mem[++top] = val;
        }
    }

    void Pop() {
        if (IsEmpty())
            throw underflow_error("Stack is empty");
        top--;
    }

    T Top() const {
        if (IsEmpty())
            throw underflow_error("Stack is empty");
        return mem[top];
    }

    bool IsEmpty() const {
        return top == -1;
    }

    bool IsFull() const { return fixedSize ? (top == maxSize - 1) : (top + 1 == MaxStackSize); }

    int Size() const { return top + 1; }

    void Clear() {
        top = -1;
        if (fixedSize) mem = vector<T>(maxSize, T());
        else mem.clear();
    }
};
