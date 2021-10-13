#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "error.h"
#include "string.h"
#include "strlib.h"
#include <iostream>

template <class T>
class ArrayStack;

template<class T>
bool operator==(const ArrayStack<T>& lhs, const ArrayStack<T>& rhs);
template<class T>
bool operator!=(const ArrayStack<T>& lhs, const ArrayStack<T>& rhs);

template <class T>
class ArrayStack
{
public:
    ArrayStack();

    // Dynamic Memory Management
    ~ArrayStack();

    int size() const;
    bool isEmpty() const;

    void clear();
    void push(T value);
    T pop();
    T peek() const;

    std::string toString() const;

    ArrayStack(const ArrayStack<T>& src);
    ArrayStack<T>& operator=(const ArrayStack<T>& src);

    // !!!: template for friend function:
    template<class U>
    friend bool operator==(const ArrayStack<U>& lhs, const ArrayStack<U>& rhs);
    template<class U>
    friend std::ostream& operator<<(std::ostream& os, const ArrayStack<U>& src);

private:
    static const int INITIAL_CAPICITY = 10;
    static const int INCREASEMENT = 10;

    T* array;
    int capacity;
    int top;

    void deepCopy(const ArrayStack<T>& src);
    void expandCapacity();
};

/* ****************************** *
 *        Implementation
 * ****************************** */

template<class T>
ArrayStack<T>::ArrayStack() {
    capacity = INITIAL_CAPICITY;
    top = 0;
    array = new T[capacity];
}

template<class T>
ArrayStack<T>::~ArrayStack() {
    delete[] array;
}

template<class T>
int ArrayStack<T>::size() const {
    return top;
}

template<class T>
bool ArrayStack<T>::isEmpty() const {
    return (top == 0);
}

template<class T>
void ArrayStack<T>::clear() {
    top = 0;
}

template<class T>
void ArrayStack<T>::push(T value) {
    if (top >= capacity) {
        expandCapacity();
    }
    else {
        array[top++] = value;
    }
}

template<class T>
T ArrayStack<T>::pop() {
    // !!!: check if stack is empty
    if (isEmpty()) {
        error("pop: Attempting to pop an empty stack");
    }

    // !!!: top points to the index where a new value will be placed.
    return array[--top];
}

template<class T>
T ArrayStack<T>::peek() const {
    // !!!: check if stack is empty
    if (isEmpty()) {
        error("pop: Attempting to peek at an empty stack");
    }
    return array[top-1];
}


template<class T>
std::string ArrayStack<T>::toString() const {
    std::string output;
    output += std::string("capacity: ") + integerToString(capacity) + ", size: " + integerToString(size());
    output += std::string("  {");
    for (int i = 0; i < top; i++) {
        if (i == top-1) {
            output += std::string(integerToString(array[i])) + "}";
        }
        else {
            output += std::string(integerToString(array[i])) + ", ";
        }
    }

    return output;
}

// operator <<: is defined outside of class
template<class T>
std::ostream& operator<<(std::ostream& os, const ArrayStack<T>& src) {
    os << src.toString();
    return os;
}

// ??
template<class T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& src) {
    deepCopy(src);
}

template<class T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& src) {
    if (this != src) {
        // Assuming that array has been allocated heap memory.
        delete[] array;
        deepCopy(src);
    }

    return *this;
}

template<class T>
void ArrayStack<T>::deepCopy(const ArrayStack<T>& src) {
    capacity = src.capacity;
    top = src.top;

    // Allocating new heap space and copy data.
    array = new T[capacity];
    for (int i = 0; i < src.top; i++) {
        array[i] = src.array[i];
    }
}

template<class T>
void ArrayStack<T>::expandCapacity() {
    capacity += INCREASEMENT;
    T* old = array; // use old as backup
    array = new T[capacity];

    for (int i = 0; i < top; i++) {
        array[i] = old[i];
    }

    delete[] old;
}

template<class T>
bool operator==(const ArrayStack<T>& lhs, const ArrayStack<T>& rhs) {
    if (lhs.capacity != rhs.capacity) {
        return false;
    }
    if (lhs.top != rhs.top) {
        return false;
    }

    for (int i = 0; i < lhs.top; i++) {
        if (lhs.array[i] != rhs.array[i]) {
            return false;
        }
    }

    return true;
}

template<class T>
bool operator!=(const ArrayStack<T>& lhs, const ArrayStack<T>& rhs) {
    return !(lhs == rhs);
}

#endif // ARRAYSTACK_H
