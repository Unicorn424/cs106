#ifndef NODE_H
#define NODE_H

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

template <class T>
class Node {
public:
    Node();
    Node(const T& val);

    // output
    std::string toString() const;

    template <class M>
    friend std::ostream& operator<<(std::ostream& os, const Node<M>& node);

    // member variables
    T data;
    Node<T>* next;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node);

/* ****************************** *
 *         Implementation
 * ****************************** */

template <class T>
Node<T>::Node() {
    next = nullptr;
}

template <class T>
Node<T>::Node(const T& val) {
    data = val;
    next = nullptr;
}

// data has to support "<<"
template <class T>
std::string Node<T>::toString() const {
    std::string output;
    std::ostringstream os;
    os << "data: " << data << ", next: " << std::hex << next;
    output = os.str();

    return output;
}

template <class M>
std::ostream& operator<<(std::ostream& os, const Node<M>& node) {
    os << node.toString();

    return os;
}

#endif // NODE_H
