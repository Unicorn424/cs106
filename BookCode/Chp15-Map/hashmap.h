#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <sstream>
#include <string>
#include "error.h"
#include "hashnode.h"

template <class KeyType, class ValueType>
class HashMap {
public:
    HashMap();
    ~HashMap();

    int size() const;
    bool isEmpty() const;

    std::string toString() const;

    void clear();
    ValueType get(KeyType key) const;
    bool containsKey(KeyType key) const;
    void put(KeyType key, ValueType val);
    ValueType remove(KeyType key);

    // deepCopy
    HashMap(const HashMap<KeyType, ValueType>& src);
    HashMap<KeyType, ValueType>& operator =(const HashMap<KeyType, ValueType>& src);

    template <class KT, class VT>
    friend std::ostream& operator <<(std::ostream& os, const HashMap<KT, VT>& map);

    template <class KT, class VT>
    friend bool operator ==(const HashMap<KT, VT>& lhs, const HashMap<KT, VT>& rhs);

private:
    static const int INITIAL_BUCKET_SIZE = 5;
    static const int EXPAND_FACTOR = 2;

    HashNode<KeyType, ValueType>** buckets = nullptr;
    int nBuckets = INITIAL_BUCKET_SIZE;
    int count = 0;
    double lambda = 0.0;

    static const int HASH_SEED = 5319;
    static const int HASH_MULTIPLIER = 33;
    static const int HASH_MASK = unsigned(-1) >> 1; // -1 = 1111 1111  >>  1  == 0111 1111
    int hashCode(const std::string& key) const;

    HashNode<KeyType, ValueType>* find(int bucket, const KeyType& key) const;
    std::string keyToString(KeyType key) const;
    void deepCopy(const HashMap<KeyType, ValueType>& src);
    void rehash();
};

template <class KT, class VT>
std::ostream& operator <<(std::ostream& os, const HashMap<KT, VT>& map);

template <class KT, class VT>
bool operator ==(const HashMap<KT, VT>& lhs, const HashMap<KT, VT>& rhs);

template <class KT, class VT>
bool operator !=(const HashMap<KT, VT>& lhs, const HashMap<KT, VT>& rhs);


/* ****************************** *
 *       Implementation
 * ****************************** */

template <class KeyType, class ValueType>
HashMap<KeyType, ValueType>::HashMap() {
    buckets = new HashNode<KeyType, ValueType>*[nBuckets];
    // Initialize all pointers in buckets to be nullptr
    memset(buckets, 0, sizeof(HashNode<KeyType, ValueType>*) * nBuckets);
    count = 0;
    lambda = 0;
}

template <class KeyType, class ValueType>
HashMap<KeyType, ValueType>::~HashMap() {
    clear();
}

template <class KeyType, class ValueType>
int HashMap<KeyType, ValueType>::size() const {
    return count;
}

template <class KeyType, class ValueType>
bool HashMap<KeyType, ValueType>::isEmpty() const {
    return (count == 0);
}

template <class KeyType, class ValueType>
std::string HashMap<KeyType, ValueType>::toString() const {
    std::string output;
    std::ostringstream os;
    int cnt = 0;;
    os << "nBucket: " << nBuckets << ", count: " << count << ", {";
    for (int i = 0; i < nBuckets; i++) {
        HashNode<KeyType, ValueType>* p = buckets[i];
        while (p != nullptr) {
            cnt++;
            if (cnt == count ) {
                os << "<" << p->key << ", "<< p->val << ">}";
            }
            else {
                os << "<" << p->key << ", "<< p->val << ">, ";
            }
            p = p->next;
        }
    }

    output = os.str();
    return output;
}

template <class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::clear() {
    for (int i = 0; i < nBuckets; i++) {
        HashNode<KeyType, ValueType>* p = buckets[i];
        while (p != nullptr) {
            HashNode<KeyType, ValueType>* old = p;
            p = p->next;
            delete old;
        }
        buckets[i] = nullptr;
    }
    count = 0;
    lambda = 0;
}

/*
 * Function: get
 * ------------------------------------
 * The get will return matching value of the given key.
 * 1. transfer key to string. (requirement for hash)
 * 2. calculate hashcode.
 * 3. search if key exists along the list with hash code
 */
template <class KeyType, class ValueType>
ValueType HashMap<KeyType, ValueType>::get(KeyType key) const {
    std::string str = keyToString(key);
    int bucket = hashCode(str) % nBuckets; // which bucket to search
    HashNode<KeyType, ValueType>* target = find(bucket, key); // search along list of hashnode

    return (target == nullptr) ? "" : target->val;
}

/*
 * Function: put
 * ------------------------------------
 * The put method will put <key, value> into hash map.
 * 1. calculate hash code.
 * 2. search along the list to see if the key exists.
 *    > if so, update with new value.
 *    > if not, insert new node with <key, value> at the front of the list.
 */
template <class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::put(KeyType key, ValueType val) {
    // if lambda > 0.7, then rehash
    if (lambda > 0.7) {
        rehash();
    }
    std::string str = keyToString(key);
    int bucket = hashCode(str) % nBuckets;
    HashNode<KeyType, ValueType>* target = find(bucket, key);
    if (target != nullptr) {
        target->val = val;
    }
    else {
        HashNode<KeyType, ValueType>* node = new HashNode<KeyType, ValueType>(key, val);
        node->next = buckets[bucket];
        buckets[bucket] = node;
    }

    count++;
    lambda = double(count) / nBuckets;
}

template <class KeyType, class ValueType>
bool HashMap<KeyType, ValueType>::containsKey(KeyType key) const {
    if (isEmpty()) {
        return false;
    }
    std::string str = keyToString(key);
    int bucket = hashCode(str) % nBuckets;
    HashNode<KeyType, ValueType>* target = find(bucket, key);

    return (target == nullptr) ? false : true;
}

/*
 * Function: remove
 * ------------------------------------
 * The function will remove the given key and value from map.
 *
 * 1. if key-value exists, remove.
 *    > target is the only one node left in the list.
 *    > there is at least one node left in the list except target.
 * 2. else throw error: key is not found.
 */
template <class KeyType, class ValueType>
ValueType HashMap<KeyType, ValueType>::remove(KeyType key) {
    if (isEmpty()) {
        error("remove: Attempting to remove from an empty map.");
    }
    ValueType val;
    std::string str = keyToString(key);
    int bucket = hashCode(str) % nBuckets;
    HashNode<KeyType, ValueType>* target = find(bucket, key);
    if (target == nullptr) {
        error("remove: Attempting to remove a key not found in the map.");
    }
    // target exists:
    if ((buckets[bucket] == target) && (target->next == nullptr)) { // only one
        buckets[bucket] = nullptr;
    }
    else {
        HashNode<KeyType, ValueType>* pre = buckets[bucket];
        while (pre->next != target) {
            pre = pre->next;
        }
        // 1. pre is front 2. pre is not front
        if (pre == buckets[bucket]) {
            buckets[bucket] = target->next;
        }
        else {
            pre->next = target->next;
        }
    }
    val = target->val;
    delete target;
    count--;

    return val;
}

// deepCopy
template <class KeyType, class ValueType>
HashMap<KeyType, ValueType>::HashMap(const HashMap<KeyType, ValueType>& src)
    :HashMap() {
    deepCopy(src);
}

template <class KeyType, class ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::operator =(const HashMap<KeyType, ValueType>& src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }

    return *this;
}


/*
 * Function: find
 * Usage: HashNode<KeyType, ValueType>* target = find(bucket, key)
 * ------------------------------------
 * The function will find given key in #bucket list of hash node. If nothing found, return null pointer.
 *
 * @param bucket: the number of bucket to search.
 * @param key: search node with 'key' as key.
 */
template <class KeyType, class ValueType>
HashNode<KeyType, ValueType>* HashMap<KeyType, ValueType>::find(int bucket, const KeyType& key) const {
    HashNode<KeyType, ValueType>* p = buckets[bucket];
    while ((p != nullptr) && (p->key != key)) {
        p = p->next;
    }
    return p;
}

/*
 * Function: hashCode
 * Usage: int hash = hashCode(key)
 * ------------------------------------
 * The function will return a hash code according to key.
 *
 * @param key: a string key or any key can be transferred into string.
 * @param HASH_SEED: start point;
 * @param HASH_MASK: all 1 bits except the sign, making sure the result is non-negative.
 *
 * Anytime before calling the function, transfer key into string form.
 */
template <class KeyType, class ValueType>
int HashMap<KeyType, ValueType>::hashCode(const std::string& key) const {
    unsigned hash = HASH_SEED;
    int n = key.length();
    for (int i = 0; i < n; i++) {
        hash = HASH_MULTIPLIER * hash + key[i];
    }

    return int(hash & HASH_MASK);
}

template <class KeyType, class ValueType>
std::string HashMap<KeyType, ValueType>::keyToString(KeyType key) const {
    std::string str;
    std::ostringstream os;
    os << key;
    str = os.str();

    return str;
}

// before doing deep copy, the instance has to be clear();
template <class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::deepCopy(const HashMap<KeyType, ValueType>& src) {
    nBuckets = src.nBuckets;
    count = src.count;
    lambda = src.lambda;
    // TODO: copy each list to this->buckets
    for (int i = 0; i < nBuckets; i++) {
        if (src.buckets[i] != nullptr) {
            HashNode<KeyType, ValueType>* newFront = nullptr; // create new list, the front of new list
            HashNode<KeyType, ValueType>* newEnd = nullptr;   // the end of new list
            HashNode<KeyType, ValueType>* p = src.buckets[i]; // track src
            while (p != nullptr) {
                if (newFront == nullptr) { // first node
                    HashNode<KeyType, ValueType>* node = new HashNode<KeyType, ValueType>(p->key, p->val);
                    newFront = newEnd = node;
                }
                else {
                    HashNode<KeyType, ValueType>* node = new HashNode<KeyType, ValueType>(p->key, p->val);
                    newEnd->next = node;
                    newEnd = node;
                }
                p = p->next;
            }
            buckets[i] = newFront;
        }
    }
}

/*
 * Function: rehash
 * ------------------------------------
 * The function will rehash all members in the map when lambda > 0.7.
 *
 * 1. create a new hashmap.
 * 2. put all elements in buckets to newBuckets.
 * 3. meanwhile, delete the element which has been copied.
 * 4. update buckets, nBuckets, lambda.
 */
template <class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::rehash() {
    int newNBuckets = nBuckets * EXPAND_FACTOR;
    HashNode<KeyType, ValueType>** newBuckets = new HashNode<KeyType, ValueType>*[newNBuckets];
    // initialization
    memset(newBuckets, 0, sizeof(int*) * newNBuckets);

    for (int i = 0; i < nBuckets; i++) {
        if (buckets[i] != nullptr) {
            HashNode<KeyType, ValueType>* p = buckets[i];
            while (p != nullptr) {
                // TODO: insert <key, val> to new buckets == put()
                HashNode<KeyType, ValueType>* node = new HashNode<KeyType, ValueType>(p->key, p->val);
                std::string str = keyToString(p->key);
                int bucket = hashCode(str) % (newNBuckets);
                node->next = newBuckets[bucket];
                newBuckets[bucket] = node;

                HashNode<KeyType, ValueType>* del = p;
                p = p->next;
                delete del; // delete members of old map
            }
        }
    }
    delete[] buckets;

    buckets = newBuckets;
    nBuckets = newNBuckets;
    lambda = (double)count / nBuckets;
}

template <class KT, class VT>
std::ostream& operator <<(std::ostream& os, const HashMap<KT, VT>& map) {
    os << map.toString();
    return os;
}

template <class KT, class VT>
bool operator ==(const HashMap<KT, VT>& lhs, const HashMap<KT, VT>& rhs) {
    if ((lhs.count != rhs.count) ||
        (lhs.nBuckets != rhs.nBuckets) ||
        (lhs.lambda != rhs.lambda)) {
        return false;
    }
    for (int i = 0; i < lhs.nBuckets; i++) {
        HashNode<KT, VT>* pl = lhs.buckets[i];
        HashNode<KT, VT>* pr = rhs.buckets[i];
        if (((pl != nullptr) && (pr == nullptr)) ||
            ((pl == nullptr) && (pr != nullptr))) {
            return false;
        }
        while ((pl != nullptr) && (pr != nullptr)) {
            if ((pl->key != pr->key) || (pl->val != pr->val)) {
                return false;
            }
            pl = pl->next;
            pr = pr->next;
        }
    }

    return true;
}

template <class KT, class VT>
bool operator !=(const HashMap<KT, VT>& lhs, const HashMap<KT, VT>& rhs) {
    return !(lhs == rhs);
}

#endif // HASHMAP_H
