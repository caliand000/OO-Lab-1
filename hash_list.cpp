#include "hash_list.h"

hash_list::hash_list() {}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) {

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
   else // add a new node
   {
    while (head -> next != NULL)
    {
        curr = curr -> next; 
        if(curr -> key == key)  //check duplicate
            curr -> value = value;
    }
    // check duplicate

   }
}
// Check for duplicates, reset head and tail pointers after insertion


std::optional<float> hash_list::get_value(int key) const { return std::nullopt; }

bool hash_list::remove(int key) { return false; }

size_t hash_list::get_size() const { return 0; }

hash_list::~hash_list() {}

/**-----------------------------------------------------------------------------------
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
