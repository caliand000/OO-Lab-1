#ifndef HASH_LIST_HPP
#define HASH_LIST_HPP

#include <optional>
#include <stddef.h>
#include <stdlib.h>


template<typename K, typename V>
hash_list<K, V>::hash_list() {
    head = nullptr;
    size = 0;
}


// insert key and value into hash_map
template<typename K, typename V>
void hash_list<K, V>::insert(K key, V value) {

    node* curr;
    if (size == 0)   // assign the head
   {
    node* insert = new node();
    head = insert;
    insert -> key = key;
    insert -> value = value;
    insert -> next = NULL;
    size += 1;
    curr = head;
   } 
   else // check for duplicate, if not then add a new node
   {
    curr = head;
    while (curr -> next != NULL)
    { 
        if(curr -> key == key)  //check duplicate
        {
            curr -> value = value;
            return;
        }
        curr = curr->next;
    }
    if(curr -> key == key)  //check duplicate at the end of the list
        {
            curr -> value = value;
            return;
        }
    node* insert = new node();
    insert-> key = key;
    insert-> value = value;
    insert-> next = NULL;   // inserting at the end of the list
    curr->next = insert;
    size += 1;
   }
}


// get value from hash_map
template<typename K, typename V>
std::optional<V> hash_list<K, V>::get_value(K key) const { 
    node* curr = head;

    // case where there are no values
    if(curr == NULL)
        return std::nullopt; 
    // travel through the list, stop when the key is found, or if at the end of the list
    while(curr->next != NULL && curr->key != key){
        curr = curr->next;
    }
    // if the key has been found, return the value
    if(curr->key == key){
        return curr->value;
    }
    // else, return no
    else{
        return std::nullopt; 
    }
}


// remove key from hash_map
template<typename K, typename V>
bool hash_list<K, V>::remove(K key) {
    node *curr = head;
    node* prev = curr;
    node* temp;

    if(head == NULL)
        return false;

    while(curr->next != NULL && curr->key != key){
        prev = curr;
        curr = curr->next;
    }
    if(curr->key != key)
        return false; // key doesn't exist in linked list
    else{
        temp = curr;
        if(prev == curr && curr->next != NULL)  // removal of head but there is another node in the list
            head = curr->next;
        else if(prev == curr && curr->next == NULL) // removal of head and it was the last node in the list
            head = NULL;
        else    
        {
            if(curr->next == NULL)  // removal of tail
                prev->next = NULL;
            else
                prev->next = curr->next;    // removal of node in the middle of list
        }
        size -= 1;
        delete temp;
        return true; 
    }
}


template<typename K, typename V>
size_t hash_list<K, V>::get_size() const { 
    return size; 
}   


template<typename K, typename V>
hash_list<K, V>::~hash_list() {
    node* curr = head;
    node* temp;

    if(head == NULL)
        return;
    
    while(curr->next != NULL){
        temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete curr;
}



// copy constructor
template<typename K, typename V>
hash_list<K, V>::hash_list(const hash_list &other) {
    // check to make sure other list has nodes. If no nodes, make an empty list.
    if (other.head == NULL)
    {
        head = NULL;
        size = 0;
    }
    else {
        // create and assign the new head
        head = new node;
        head->key = other.head->key;
        head->value = other.head->value;
        head->next = NULL;
        size = 1;

        // setup traveling pointers
        node * ogList = other.head -> next;
        node * newList = head;
        // travel through the original list copying nodes
        while (ogList != NULL)  // when ogList is null, the end of the list has been reached
        {
            node* insert = new node;
            insert->key = ogList->key;
            insert->value = ogList->value;
            insert->next = NULL;    // assign NULL for now in case that was the last node.
            newList->next = insert;

            newList = newList->next;
            ogList = ogList->next;
            size += 1;
        }
    }
}


//Assignment operator
template<typename K, typename V>
hash_list<K, V> &hash_list<K, V>::operator=(const hash_list &other) {
    if (this != &other) // swapping 'other' hash_list to current hash_list
    {
        hash_list temp = other;
        std::swap(head, temp.head);
        std::swap(size, temp.size);
    }
    // if this == &other, then no swapping needs to be done
    return * this;
}


template<typename K, typename V>
void hash_list<K, V>::reset_iter() {
    iter_ptr = head;
}


template<typename K, typename V>
void hash_list<K, V>::increment_iter() {
    if(iter_ptr != NULL)
        iter_ptr = iter_ptr->next;
}


template<typename K, typename V>
std::optional<std::pair<const K *, V *>> hash_list<K, V>::get_iter_value() {
    // obtain iter_ptr node key/value address
    const K * keyPtr = &(iter_ptr->key);
    V * valPtr = &(iter_ptr->value);
    if (iter_ptr == NULL)   // iter_value is not at a node
        return std::nullopt;
    else
        return std::pair(keyPtr, valPtr);   // return the pointers to the key/value address
}


template<typename K, typename V>
bool hash_list<K, V>::iter_at_end() {
    if(iter_ptr == NULL)
        return true;
    else
        return false;
}

#endif