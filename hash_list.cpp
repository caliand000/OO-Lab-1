#include "hash_list.h"

hash_list::hash_list() {
    head = nullptr;
    size = 0;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) {

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
    if(curr -> key == key)  //check duplicate
        {
            curr -> value = value;
            return;
        }
    node* insert = new node();
    insert-> key = key;
    insert-> value = value;
    insert-> next = NULL;
    curr->next = insert;
    size += 1;
   }
}
// Check for duplicates, reset head and tail pointers after insertion


std::optional<float> hash_list::get_value(int key) const { 
    node* curr = head;
    while(curr->next != NULL && curr->key != key){
        curr = curr->next;
    }
    if(curr->key == key){
        return curr->value;
    }
    else{
        return std::nullopt; 
    }
}

bool hash_list::remove(int key) { 
    node* curr = head;
    node* prev = curr;
    node* temp;
    while(curr->next != NULL && curr->key != key){
        prev = curr;
        curr = curr->next;
    }
    if(curr->key != key)
        return false; // key doesn't exist in linked list
    else{
        temp = curr;
        if(prev == curr && curr->next != NULL)
            head = curr->next;
        else if(prev == curr && curr->next == NULL)
            head = NULL;
        else
        {
            if(curr->next == NULL)
                prev->next = NULL;
            else
                prev->next = curr->next;
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

     while (curr->next != NULL)
    {
        temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete curr;
}

/**----------------------------
 * -------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other) {}

hash_list &hash_list::operator=(const hash_list &other) { return *this; }

void hash_list::reset_iter() {}


void hash_list::increment_iter() {}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { return std::nullopt; }


bool hash_list::iter_at_end() { return false; }
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
