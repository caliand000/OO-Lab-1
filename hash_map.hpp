#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <optional>
#include <stddef.h>
#include <stdlib.h>


// Definition of templated functions
template<typename K, typename V>
hash_map<K,V>::hash_map(size_t capacity, float upper_load_factor, float lower_load_factor) {
    _capacity = capacity;   
    _head = new hash_list<K, V>[_capacity];    // head becomes the pointer to a new array of hash_lists
    _size = 0;
    _upper_load_factor = upper_load_factor;
    _lower_load_factor = lower_load_factor;
}

// copy constructor
template<typename K, typename V>
hash_map<K, V>::hash_map(const hash_map<K, V> &other) {
    _capacity = other._capacity;
    _head = new hash_list<K,V>[other._capacity];
    _size = other._size;

    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];  // use copy constructor of hash_list
    }
}

//Assignment operator
template<typename K, typename V>
hash_map<K, V> &hash_map<K, V>::operator=(const hash_map<K, V> &other) {
    if (this != &other) // will swap the two if they are not the same
    {
        hash_map<K, V> temp = other;
        std::swap(_size, temp._size);
        std::swap(_capacity, temp._capacity);
        std::swap(_head, temp._head);
    }
    return * this;
}


// insert key and value into hash_map
template<typename K, typename V>
void hash_map<K, V>::insert(K key, V value) {
    // hashing function
    size_t index = _hash(key) % _capacity;
    if (index < 0)
        index *= -1;
    size_t prevSize = _head[index].get_size();
    //insert at the hashed key
    _head[index].insert(key, value);
    if (prevSize != _head[index].get_size())
        _size += 1;
}

// get value from hash_map
template<typename K, typename V>
std::optional<float> hash_map<K, V>::get_value(K key) const {
    // go to hashed key
    int index = key % _capacity;
    if (index < 0)
        index *= -1;
    hash_list<K, V> travel = _head[index];   // variable to go through hash_list
    travel.reset_iter();                // make sure iterator is at head
    std::optional<std::pair<const int *, float *>> keyAndVal;   // set up iterator to go through hash_list
    while (!(travel.iter_at_end())) // travel to the end
    {
        keyAndVal = travel.get_iter_value();    // update key and value to latest node
        if (*keyAndVal.value().first ==  key)   // if key is found, return the value
            return *keyAndVal.value().second;
        travel.increment_iter();
    }
    // function did not find key.
    return std::nullopt;
}



// remove key from hash_map
template<typename K, typename V>
bool hash_map<K, V>::remove (K key) {
    int index = key % (int)_capacity;
    if (index < 0)
        index *= -1;
    if (_head[index].remove(key))
    {
        _size -= 1;
        return true;
    }    
    else
        return false;
}

template<typename K, typename V>
size_t hash_map<K, V>::get_size() const {
    return _size;
}

template<typename K, typename V>
size_t hash_map<K, V>::get_capacity() const {
    return _capacity;
}


// get all keys from hash_map
template<typename K, typename V>
void hash_map<K, V>::get_all_keys(K *keys) {
    if (_capacity == 0)
        return;
    std::optional<std::pair<const int *, float *>> keyAndVal;
    hash_list<K, V> travel;   // variable to go through hash_map
    int keyIndex = 0;   // index of array with all keys
    for (size_t i = 0; i < _capacity; i++)
    {
        travel = _head[i];                  // set travel to be one of the hash_lists in the hash map
        travel.reset_iter();                // make sure iterator is at head
        while (!travel.iter_at_end())
        {
            keyAndVal = travel.get_iter_value();    // grab the key and value from iterator
            keys[keyIndex] = *keyAndVal.value().first;  // put the key into the array
            travel.increment_iter();    // increment the iterator
            keyIndex++;
        }
    }
}

template<typename K, typename V>
void hash_map<K, V>::get_bucket_sizes(size_t *buckets) {
    if (_capacity == 0)
    {
        for (size_t i = 0; i < _capacity; i++)
            buckets[i] = 0;
        return;
    }
    for (size_t i = 0; i < _capacity; i++)
    {
        buckets[i] = _head[i].get_size();
    }
}


template<typename K, typename V>
hash_map<K, V>::~hash_map() {
    // iterate through the hash_list array freeing all the hash_lists
    delete[] _head; // free head
}

#endif // HASH_MAP_HPP