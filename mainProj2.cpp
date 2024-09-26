#include <iostream>
#include "hash_map.h"
#include "hash_list.h"

int main (int argc, char*argv[])
{
    // hash_map<int, int> map(4, 0, 0);
    // map.insert(3, 15);
    // map.insert(5, 13);
    // map.remove(3);
    // map.remove(2);


    //*********Testing Rehash**************
    hash_map<int, int> map(1, 2, 1);
    for(int i = 0; i < 10; i++)
    {
        map.insert(i, 10 - i);
        if(i == 4|| i == 7 || i == 8) {
            std::cout << "Map after inserting " << i + 1 << " elements:" << std::endl;
            int* keys = new int[map.get_size()];
            map.get_all_keys(keys);
            for (size_t j = 0; j < map.get_size(); ++j) {
                auto value = map.get_value(keys[j]);
                if (value.has_value()) {
                    std::cout << "{" << keys[j] << ": " << value.value() << "} ";
                }
            }
            std::cout << std::endl;
            delete[] keys;
        }
    }

    return 1;
}