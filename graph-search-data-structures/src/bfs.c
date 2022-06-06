#include <stdio.h>

#include "utils.h"
#include "ds.h"

int main(int argc, char const *argv[])
{

    bits_t * visited = bitarray_init(200);
    
    for(size_t j = 0; j < 10; j++)
        bitarray_set(visited, arc4random() % 200, true);
    
    for(size_t i = 0; i < visited->blocks; i++)
    {
        bitblock_print(visited->bits[i]);
        printf(" ");
    }

    return EXIT_SUCCESS;
}
