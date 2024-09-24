#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <vector>
#include <list>
#include <utility>

template<typename K, typename V>
class hash_map {
public:
    hash_map(size_t capacity);
    void insert(K key, V value);
    bool find(K key, V& value);
    void remove(K key);
    size_t get_size() const;

private:
    size_t _size;
    size_t _capacity;
    hash_list *_head;
};

// Implementation of templated functions

template<typename K, typename V>
hash_map<K, V>::hash_map(size_t capacity) : _capacity(capacity), _size(0) {
    _table.resize(_capacity);
}

template<typename K, typename V>
void hash_map<K, V>::insert(K key, V value) {
    int hash = key % _capacity;
    if (hash < 0) hash *= -1;
    auto& cell = _table[hash];
    for (auto& pair : cell) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    cell.emplace_back(key, value);
    ++_size;
}

template<typename K, typename V>
bool hash_map<K, V>::find(K key, V& value) {
    int hash = key % _capacity;
    if (hash < 0) hash *= -1;
    auto& cell = _table[hash];
    for (auto& pair : cell) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
void hash_map<K, V>::remove(K key) {
    int hash = key % _capacity;
    if (hash < 0) hash *= -1;
    auto& cell = _table[hash];
    for (auto it = cell.begin(); it != cell.end(); ++it) {
        if (it->first == key) {
            cell.erase(it);
            --_size;
            return;
        }
    }
}

template<typename K, typename V>
size_t hash_map<K, V>::get_size() const {
    return _size;
}

#endif // HASH_MAP_HPP