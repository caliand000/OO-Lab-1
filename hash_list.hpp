
#include "hash_list.h"


struct node {
    int key;
    float value;
    node *next;
};


template<typename K, typename V>
class hash_list {
public:
    hash_list();
    void insert(K key, V value);
    bool find(K key, V& value);
    void remove(K key);
    std::optional<V> get_value(K key) const;
    size_t get_size() const;
    ~hash_list();

private:
    size_t _size;
    node *head;
    node *iter_ptr;
};

// template<typename K, typename V>
// hash_list::hash_list() {
//     head = nullptr;
//     size = 0;
// }

template<typename K, typename V>
void hash_list<K, V>::insert(K key, V value){
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

template<typename K>
std::optional<float> hash_list<K>::get_value(K key) const { 
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

template<typename K>
bool hash_list<K>::remove(K key) {
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

size_t hash_list::get_size() const { 
    return size; 
}   

hash_list::~hash_list() {
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

