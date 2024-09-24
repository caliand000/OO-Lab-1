#include "hash_map.h"

hash_map::hash_map(size_t capacity) {
    _capacity = capacity;   
    _head = new hash_list[capacity];    // head becomes the pointer to a new array of hash_lists
    _size = 0;
}

// copy constructor
hash_map::hash_map(const hash_map &other) {
    _capacity = other._capacity;
    _head = new hash_list[other._capacity];
    _size = other._size;

    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];  // use copy constructor of hash_list
    }
}

hash_map &hash_map::operator=(const hash_map &other) {
    if (this != &other) // will swap the two if they are not the same
    {
        hash_map temp = other;
        std::swap(_size, temp._size);
        std::swap(_capacity, temp._capacity);
        std::swap(_head, temp._head);
    }
    return * this;
}

void hash_map::insert(int key, float value) {
    // hashing function
    int mapInt = key % _capacity;
    if (mapInt < 0)
        mapInt *= -1;
    size_t prevSize = _head[mapInt].get_size();
    //insert at the hashed key
    _head[mapInt].insert(key, value);
    if (prevSize != _head[mapInt].get_size())
        _size += 1;
}

std::optional<float> hash_map::get_value(int key) const {
    // go to hashed key
    int mapInt = key % _capacity;
    if (mapInt < 0)
        mapInt *= -1;
    hash_list travel = _head[mapInt];   // variable to go through hash_list
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

bool hash_map::remove (int key) {
    int mapInt = key % (int)_capacity;
    if (mapInt < 0)
        mapInt *= -1;
    if (_head[mapInt].remove(key))
    {
        _size -= 1;
        return true;
    }    
    else
        return false;
    
}

size_t hash_map::get_size() const {
    return _size;
}

size_t hash_map::get_capacity() const {
    return _capacity;
}

void hash_map::get_all_keys(int *keys) {
    if (_capacity == 0)
        return;
    std::optional<std::pair<const int *, float *>> keyAndVal;
    hash_list travel;   // variable to go through hash_map
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

void hash_map::get_bucket_sizes(size_t *buckets) {
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

hash_map::~hash_map() {
    // iterate through the hash_list array freeing all the hash_lists
    delete[] _head; // free head
}