#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <iostream>
#include <string>
#include <sstream>
#include "error.h"
#include "node.h"

template <class T>
class LinkQueue {
public:
    LinkQueue();
    ~LinkQueue();

    int size() const;
    bool isEmpty() const;
    T peek() const;
    std::string toString() const;

    void enqueue(const T& val);
    T dequeue();
    void clear();

    // deepCopy
    LinkQueue(const LinkQueue<T>& src);
    LinkQueue<T>& operator =(const LinkQueue<T>& src);

    template <class M>
    friend bool operator ==(const LinkQueue<M>& lhs, const LinkQueue<M>& rhs);
    template <class M>
    friend std::ostream& operator <<(std::ostream& os, const LinkQueue<M>& val);

private:
    Node<T>* front = nullptr;
    Node<T>* end = nullptr;
    int length = 0;

    void deepCopy(const LinkQueue<T>& src);
};

template <class M>
bool operator ==(const LinkQueue<M>& lhs, const LinkQueue<M>& rhs);
template <class M>
bool operator !=(const LinkQueue<M>& lhs, const LinkQueue<M>& rhs);
template <class M>
std::ostream& operator <<(std::ostream& os, const LinkQueue<M>& val);

#endif // LINKQUEUE_H


/* ****************************** *
 *       Implementation
 * ****************************** */

template <class T>
LinkQueue<T>::LinkQueue() {
    // nothing to do but initialization
}

template <class T>
LinkQueue<T>::~LinkQueue() {
    clear();
}

template <class T>
int LinkQueue<T>::size() const {
    return length;
}

template <class T>
bool LinkQueue<T>::isEmpty() const {
    return (length == 0);
}

template <class T>
T LinkQueue<T>::peek() const {
    return front->data;
}

template <class T>
std::string LinkQueue<T>::toString() const {
    std::string output;
    std::ostringstream os;
    os << "length = " << length << ", {";
    Node<T>* p = front;
    if (p != nullptr) { // if there is at least one node in the queue
        while (true) {
            os << p->data;
            if (p->next == nullptr) {
                os << "}";
                break;
            }
            else {
                os << ", ";
            }
            p = p->next;
        }
    }
    else {
        os << '}';
    }

    output = os.str();
    return output;
}

template <class T>
void LinkQueue<T>::enqueue(const T& val) {
    // encapsulate val into node
    Node<T>* node = new Node<T>(val);
    // 2 cases:
    //     1. the first node to enqueue
    //     2. there is nodes in the queue before
    if (end != nullptr) {
        end->next = node;
        end = node;
    }
    else { // first node
        front = end = node;
    }

    length++;
}

template <class T>
T LinkQueue<T>::dequeue() {
    if (isEmpty()) {
        error("dequeue: Attempting to dequeue an empty queue.");
    }
    const T record = front->data;
    Node<T>* del = front;
    // 2 cases:
    //     1: one node left;
    //     2: more than one node left;
    if (front->next == nullptr) {
        front = nullptr;
        end = nullptr;
    }
    else {
        front = front->next;
    }

    delete del;
    length--;

    return record;
}

template <class T>
void LinkQueue<T>::clear() {
    while (length != 0) {
        dequeue();
    }
}

// deepCopy
template <class T>
LinkQueue<T>::LinkQueue(const LinkQueue<T>& src) {
    // called when define a new entity
    deepCopy(src);
}

template <class T>
LinkQueue<T>& LinkQueue<T>::operator =(const LinkQueue<T>& src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }

    return *this;
}

template <class T>
void LinkQueue<T>::deepCopy(const LinkQueue<T>& src) {
    // given: front = end = nullptr, count = 0
    Node<T>* p = src.front;
    while (p != nullptr) {
        enqueue(p->data);
        p = p->next;
    }
}

template <class M>
bool operator ==(const LinkQueue<M>& lhs, const LinkQueue<M>& rhs) {
    if (lhs.length != rhs.length) {
        return false;
    }
    Node<M>* pl = lhs.front;
    Node<M>* pr = rhs.front;
    while (pl != nullptr) {
        if (pl->data != pr->data) {
            return false;
        }
        pl = pl->next;
        pr = pr->next;
    }

    return true;
}

template <class M>
bool operator !=(const LinkQueue<M>& lhs, const LinkQueue<M>& rhs) {
    return !(lhs == rhs);
}

template <class M>
std::ostream& operator <<(std::ostream& os, const LinkQueue<M>& val) {
    os << val.toString();
    return os;
}
