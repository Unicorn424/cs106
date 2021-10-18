#ifndef HASHNODE_H
#define HASHNODE_H

#include <iostream>
#include <sstream>
#include <string>

template <class KeyType, class ValueType>
class HashNode {
public:
    HashNode();
    HashNode(KeyType key, ValueType val);

    std::string toString() const;

    template <class KT, class VT>
    friend std::ostream& operator <<(std::ostream& os, const HashNode<KT, VT>& val);
    template <class KT, class VT>
    friend bool operator ==(const HashNode<KT, VT>& lhs, const HashNode<KT, VT>& rhs);

    // Instance variable
    KeyType key;
    ValueType val;
    HashNode<KeyType, ValueType>* next = nullptr;
};

template <class KT, class VT>
std::ostream& operator <<(std::ostream& os, const HashNode<KT, VT>& val);
template <class KT, class VT>
bool operator ==(const HashNode<KT, VT>& lhs, const HashNode<KT, VT>& rhs);
template <class KT, class VT>
bool operator !=(const HashNode<KT, VT>& lhs, const HashNode<KT, VT>& rhs);


/* ****************************** *
 *        Implementation
 * ****************************** */

template <class KeyType, class ValueType>
HashNode<KeyType, ValueType>::HashNode() {
    // nothing to do
}

template <class KeyType, class ValueType>
HashNode<KeyType, ValueType>::HashNode(KeyType key, ValueType val) {
    this->key = key;
    this->val = val;
}

template <class KeyType, class ValueType>
std::string HashNode<KeyType, ValueType>::toString() const {
    std::string output;
    std::ostringstream os;
    os << "key: " << key << ", value: " << val;

    output = os.str();
    return output;
}

template <class KT, class VT>
std::ostream& operator <<(std::ostream& os, const HashNode<KT, VT>& val) {
    os << val.toString();
    return os;
}

template <class KT, class VT>
bool operator ==(const HashNode<KT, VT>& lhs, const HashNode<KT, VT>& rhs) {
    return (lhs.key == rhs.key) && (lhs.val == rhs.val);
}

template <class KT, class VT>
bool operator !=(const HashNode<KT, VT>& lhs, const HashNode<KT, VT>& rhs) {
    return !(lhs == rhs);
}


#endif // HASHNODE_H
