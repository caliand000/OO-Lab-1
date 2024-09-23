#include <iostream>
#include "hash_map.h"
#include "hash_list.h"

int main (int argc, char*argv[])
{
    int keys1[5] = {0};
    int keys2[5] = {0};
    hash_map map(4);
    map.insert(3, 15);
    map.insert(5, 13);
    map.remove(3);
    map.remove(2);

    return 1;
}