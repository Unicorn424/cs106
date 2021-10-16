#ifndef CQUEUE_H
#define CQUEUE_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "error.h"

template <class T>
class CQueue
{
public:
    CQueue();
    ~CQueue();

    int size() const;
    bool isEmpty() const;
    std::string toString() const;
    T peek() const;

    void enqueue(const T& val);
    T dequeue();
    void clear();

    // deepCopy
    CQueue(const CQueue<T>& src);
    CQueue<T>& operator =(const CQueue<T>& src);

    template <class M>
    friend std::ostream& operator <<(std::ostream& os, const CQueue<M>& val);
    template <class M>
    friend bool operator ==(const CQueue<M>& lhs, const CQueue<M>& rhs);

private:
    static const int INITIALIZE_CAPACITY = 10;
    static const int FACTOR = 2;

    int capacity = INITIALIZE_CAPACITY;
    int front = 0;
    int end = 0;
    T* array = nullptr;

    void deepCopy(const CQueue<T>& src);
    bool expandTrigger();
    void expandCapacity();
};

template <class M>
std::ostream& operator <<(std::ostream& os, const CQueue<M>& val);

template <class M>
bool operator ==(const CQueue<M>& lhs, const CQueue<M>& rhs);

template <class M>
bool operator !=(const CQueue<M>& lhs, const CQueue<M>& rhs);

/* ****************************** *
 *        Implementation
 * ****************************** */
template <class T>
CQueue<T>::CQueue() {
    array = new T[capacity];
}

template <class T>
CQueue<T>::~CQueue() {
    if (array != nullptr) {
        delete[] array;
    }
}

template <class T>
int CQueue<T>::size() const {
    return end - front >= 0 ? end - front : end + capacity - front;
}

template <class T>
bool CQueue<T>::isEmpty() const {
    return (size() == 0);
}

template <class T>
std::string CQueue<T>::toString() const {
    std::string output;
    std::ostringstream os;
    os << "capacity: " << capacity << ", front: " << front << ", end: " <<
          end << ", ";
    os << "{";
    for (int i = 0; i < size(); i++) {
        if (i == (size() - 1)) {
            os << array[(front + i) % capacity] << "}";
        }
        else {
            os << array[(front + i) % capacity] << ", ";
        }
    }

    output = os.str();
    return output;
}

template <class T>
T CQueue<T>::peek() const {
    return array[front];
}

template <class T>
void CQueue<T>::enqueue(const T& val) {
    if (expandTrigger()) {
        expandCapacity();
    }
    array[end] = val;
    end = (end + 1) % capacity; // go along a circle array
}

template <class T>
T CQueue<T>::dequeue() {
    if (isEmpty()) {
        error("dequeue: Attempting to dequeue an empty queue.");
    }
    T output = array[front];
    front = (front + 1) % capacity;

    return output;
}

template <class T>
void CQueue<T>::clear() {
    front = end = 0;
}

template <class T>
CQueue<T>::CQueue(const CQueue<T>& src) {
    deepCopy(src);
}

template <class T>
CQueue<T>& CQueue<T>::operator =(const CQueue<T>& src) {
    if (this != &src) {
        if (array != nullptr) {
            delete[] array;
            array = nullptr;
        }
        deepCopy(src);
    }

    return *this;
}

template <class T>
void CQueue<T>::deepCopy(const CQueue<T>& src) {
    capacity = src.capacity;
    front = src.front;
    end = src.end;
    if (array != nullptr) {
        delete[] array;
    }
    array = new T[capacity];
    // !!!: circle: end may be smaller than front. CANNOT for (i = front; i < end; i++)
    for (int i = 0; i < src.size(); i++) {
        int index = (front + i) % capacity;
        array[index] = src.array[index];
    }
}

template <class T>
bool CQueue<T>::expandTrigger() {
    if ((end == (front - 1)) ||
       (end == (front + capacity - 1))) { // when front = 0
        return true;
    }
    return false;
}

// 1. copy one by one 2. set environment variables
template <class T>
void CQueue<T>::expandCapacity() {
    int newCapacity = capacity * FACTOR;
    int oldSize = size();

    T* newArr = new T[newCapacity];
    for (int i = 0; i < oldSize; i++) {
        newArr[i] = array[(front + i) % capacity];
    }

    capacity = newCapacity;
    front = 0;
    end = oldSize;
    if (array != nullptr) {
        delete[] array;
    }
    array = newArr;
}

template <class M>
std::ostream& operator <<(std::ostream& os, const CQueue<M>& val) {
    os << val.toString();
    return os;
}

template <class M>
bool operator ==(const CQueue<M>& lhs, const CQueue<M>& rhs) {
    if ((lhs.capacity != rhs.capacity) ||
       (lhs.front != rhs.front) ||
       (lhs.end != rhs.end)) {
        return false;
    }

    for (int i = 0; i < lhs.size(); i++) {
        int index = (lhs.front + i) % lhs.capacity;
        if (lhs.array[index] != rhs.array[index]) {
            return false;
        }
    }

    return true;
}

template <class M>
bool operator !=(const CQueue<M>& lhs, const CQueue<M>& rhs) {
    return !(lhs == rhs);
}

#endif // CQUEUE_H
