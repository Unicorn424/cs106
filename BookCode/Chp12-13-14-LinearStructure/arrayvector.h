#ifndef ARRAYVECTOR_H
#define ARRAYVECTOR_H

#include <iostream>
#include <sstream>
#include "error.h"
#include <string>

template <class T>
class ArrayVector {
public:
    ArrayVector();
    ArrayVector(int n, const T value = T()); // T() default value of T
    ~ArrayVector();

    int size() const;
    bool isEmpty() const;
    std::string toString() const;
    T get(int index) const;

    void clear();
    void add(const T& val);
    void set(int index, const T& val);
    void insert(int index, const T& val);
    void remove(int index);

    // overriding []
    T& operator [](int index);

    ArrayVector(const ArrayVector<T>& src);
    ArrayVector<T>& operator =(const ArrayVector<T>& src);

    template <class M>
    friend std::ostream& operator <<(std::ostream& os, const ArrayVector<M>& val);
    template <class M>
    friend bool operator ==(const ArrayVector<M>& lhs, const ArrayVector<M>& rhs);

private:
    static const int INITIAL_CAPACITY = 10;
    static const int INCREAMENT = 10;

    int capacity = INITIAL_CAPACITY;
    int count = 0;
    T* array = nullptr;

    void deepCopy(const ArrayVector<T>& src);
    void expandCapacity();
};

template <class M>
std::ostream& operator <<(std::ostream& os, const ArrayVector<M>& val);
template <class M>
bool operator ==(const ArrayVector<M>& lhs, const ArrayVector<M>& rhs);
template <class M>
bool operator !=(const ArrayVector<M>& lhs, const ArrayVector<M>& rhs);

/* ****************************** *
 *       Implementation
 * ****************************** */

template <class T>
ArrayVector<T>::ArrayVector() {
    // Allocation for new space
    array = new T[capacity];
}

template <class T>
ArrayVector<T>::ArrayVector(int n, const T val) {
    array = new T[capacity];
    for (int i = 0; i < n; i++) {
        add(val);
    }
}

template <class T>
ArrayVector<T>::~ArrayVector<T>() {
    clear();
}

template <class T>
int ArrayVector<T>::size() const {
    return count;
}

template <class T>
bool ArrayVector<T>::isEmpty() const {
    return (count == 0);
}

template <class T>
std::string ArrayVector<T>::toString() const {
    std::string output;
    std::ostringstream os;
    os << "capacity: " << capacity << ", count: " << count << ", {";
    for (int i = 0; i < count; i++) {
        if (i == (count - 1)) {
            os << array[i];
        }
        else {
            os << array[i] << ", ";
        }
    }
    os << "}";

    output = os.str();
    return output;
}

template <class T>
T ArrayVector<T>::get(int index) const {
    if ((index < 0) || (index >= count)) {
        error("get: Try to access index out of the range of vector.");
    }
    return array[index];
}

template <class T>
T& ArrayVector<T>::operator [](int index) {
    if ((index < 0) || (index >= count)) {
        error("Try to access index out of the range of vector.");
    }
    return array[index];
}

template <class T>
void ArrayVector<T>::clear() {
    if (array != nullptr) {
        delete[] array;
        array = nullptr;
    }
    count = 0;
}

template <class T>
void ArrayVector<T>::add(const T& val) {
    if (count >= capacity) {
        expandCapacity();
    }
    array[count++] = val;
}

template <class T>
void ArrayVector<T>::set(int index, const T& val) {
    if ((index < 0) || (index >= count)) {
        error("set: Try to access index out of the range of vector.");
    }
    array[index] = val;
}

template <class T>
void ArrayVector<T>::insert(int index, const T& val) {
    if ((index < 0) || (index >= count)) {
        error("insert: Try to access index out of the range of vector.");
    }
    if (count >= capacity) {
        expandCapacity();
    }
    // TODO:
    // 1. move the elements from index to end forward by 1 element
    // 2. set element at index to be val
    for (int i = count; i > index; i--) {
        array[i] = array[i-1];
    }
    set(index, val);
    count++;
}

template <class T>
void ArrayVector<T>::remove(int index) {
    if ((index < 0) || (index >= count)) {
        error("remove: Try to access index out of the range of vector.");
    }
    if (isEmpty()) {
        error("remove: Try to remove from an empty vector.");
    }
    // TODO: move the elements from index+1 to end backward by 1 element;
    count--;
    for (int i = index; i < count; i++) {
        array[i] = array[i+1];
    }
}

template <class T>
ArrayVector<T>::ArrayVector(const ArrayVector<T>& src) {
    deepCopy(src);
}

template <class T>
ArrayVector<T>& ArrayVector<T>::operator =(const ArrayVector<T>& src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }

    return *this;
}

template <class T>
void ArrayVector<T>::deepCopy(const ArrayVector<T>& src) {
    capacity = src.capacity;
    array = new T[capacity];
    count = src.count;
    memcpy(array, src.array, sizeof(T) * count);
}

template <class T>
void ArrayVector<T>::expandCapacity() {
    capacity += INCREAMENT;
    T* old = array;
    array = new T[capacity];
    memcpy(array, old, sizeof(T) * count);

    delete[] old;
}


template <class M>
std::ostream& operator <<(std::ostream& os, const ArrayVector<M>& val) {
    os << val.toString();
    return os;
}

template <class M>
bool operator ==(const ArrayVector<M>& lhs, const ArrayVector<M>& rhs) {
    if (lhs.count != rhs.count) {
        return false;
    }
    for (int i = 0; i < lhs.count; i++) {
        if (lhs.array[i] != rhs.array[i]) {
            return false;
        }
    }

    return true;
}

template <class M>
bool operator !=(const ArrayVector<M>& lhs, const ArrayVector<M>& rhs) {
    return !(lhs == rhs);
}



#endif // ARRAYVECTOR_H
