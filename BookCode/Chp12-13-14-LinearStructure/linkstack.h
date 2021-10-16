#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "node.h"
#include "error.h"
#include "strlib.h"

template <class T>
class LinkStack
{
public:
    LinkStack();
    ~LinkStack();

    int size() const;
    bool isEmpty() const;
    T peek() const;
    std::string toString() const;

    void clear();
    void push(const T& val);
    T pop();

    // using deep copy
    LinkStack(const LinkStack<T>& src);
    LinkStack<T>& operator =(const LinkStack<T>& src);

    template <class M>
    friend bool operator ==(const LinkStack<M>& lhs, const LinkStack<M>& rhs);
    template <class M>
    friend std::ostream& operator <<(std::ostream& os, const LinkStack<M>& src);

private:
    Node<T>* top;
    int count;
    // there is no need for 'capacity', I can insert as many nodes as I wish.

    void deepCopy(const LinkStack<T>& src);
};

template <class M>
bool operator ==(const LinkStack<M>& lhs, const LinkStack<M>& rhs);

template <class M>
bool operator !=(const LinkStack<M>& lhs, const LinkStack<M>& rhs);

template <class M>
std::ostream& operator <<(std::ostream& os, const LinkStack<M>& src);

/* ****************************** *
 *        Implementation
 * ****************************** */
template <class T>
LinkStack<T>::LinkStack() {
    count = 0;
    top = nullptr;
}

template <class T>
LinkStack<T>::~LinkStack() {
    clear();
}

template <class T>
int LinkStack<T>::size() const {
    return count;
}

template <class T>
bool LinkStack<T>::isEmpty() const {
    return (count == 0);
}

template <class T>
void LinkStack<T>::clear() {
    if (!isEmpty()) {
        // TODO: pop until stack is empty
        pop();
    }
}

template <class T>
void LinkStack<T>::push(const T& val) {
    Node<T>* newNode = new Node<T>(val);
    newNode->next = top;
    top = newNode;

    count++;
}

// Note: always checking if the next is nullptr.
template <class T>
T LinkStack<T>::pop() {
    // check check check!!!
    if (isEmpty()) {
        error("pop: Attempting to pop an empty stack");
    }

    T record = top->data;
    // free the node top point to from the memory
    // !!!: when there is only one node here?
    Node<T>* del = top;
    if (del->next != nullptr) {
        top = del->next;
    }
    else { // when delete the last one node
        top = nullptr;
    }
    delete del;

    count--;
    return record;
}

template <class T>
T LinkStack<T>::peek() const{
    // check check check!!!
    if (isEmpty()) {
        error("peek: Attempting to peek an empty stack");
    }
    return top->data;
}

// deep copy
template <class T>
LinkStack<T>::LinkStack(const LinkStack<T>& src) {
    // copy from scratch
    deepCopy(src);
}

template <class T>
LinkStack<T>& LinkStack<T>::operator =(const LinkStack<T>& src) {
    // copy from scratch or by overwriting
    if (this != &src) {
        clear(); // free old memory
        deepCopy(src);
    }

    return *this;
}

template <class T>
void LinkStack<T>::deepCopy(const LinkStack<T>& src) {
    count = src.count;

    // copy all nodes (node chain) from src, noting the order of node matters
    // which means we cannot copy from src to this directly.
    Node<T>* front = nullptr;
    Node<T>* tail = nullptr; // track the last node copied
    for (Node<T>* p = src.top; p != nullptr; p = p->next) {
        Node<T>* newNode = new Node<T>(p->data);
        if (tail == nullptr) { // it's the first node
            front = newNode;
        }
        else {
            tail->next = newNode; // point to new end node
        }
        tail = newNode; // move the tail to the end node
    }

    top = front;
    front = nullptr;
    tail = nullptr;
}

template <class M>
bool operator ==(const LinkStack<M>& lhs, const LinkStack<M>& rhs) {
    if (lhs.count != rhs.count) {
        return false;
    }

    Node<M>* lp = lhs.top;
    Node<M>* rp = rhs.top;
    while ((lp != nullptr) && (rp != nullptr)) {
        if (lp->data != rp->data) {
            return false;
        }
        lp = lp->next;
        rp = rp->next;
    }

    return true;
}

template <class M>
bool operator !=(const LinkStack<M>& lhs, const LinkStack<M>& rhs) {
    return !(lhs == rhs);
}

template <class T>
std::string LinkStack<T>::toString() const {
    std::string output;
    std::ostringstream os;
    os << "count: " << integerToString(count) << ", top: " << std::hex << top << "; {";
    Node<T>* p = top;
    if (p != nullptr) {
        while (true) {
            if (p->next != nullptr) {
                os << *p << ", ";
            }
            else { // for the last node
                os << *p << "}";
                break;
            }
            p = p->next;
        }
    }
    else {
        os << "}";
    }

    output = os.str();
    return output;
}

template <class M>
std::ostream& operator <<(std::ostream& os, const LinkStack<M>& src) {
    os << src.toString();
    return os;
}

#endif // LISTSTACK_H
