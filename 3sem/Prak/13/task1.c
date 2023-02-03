#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int main(int argc, char *argv[])
{
    enum
    {
        BASE = 10,
        SIZE = 2
    };

    long miss_count = 0;

    int cahe_size = strtol(argv[2], NULL, BASE);
    int block_size = strtol(argv[3], NULL, BASE);
    int amount_of_blocks = cahe_size / block_size;
    int *block_array = (int *) calloc(amount_of_blocks, sizeof(int));
    for (int i = 0;i < amount_of_blocks;i++) {
        block_array[i] = INT_MAX;
    }
    char buff[SIZE];
    int addr,
        size,
        value;
    while (scanf("%c%c %x %d %d\n", &buff[0], &buff[1], &addr, &size, &value) != EOF) {
        //printf("%c%c %x %d %d\n", buff[0], buff[1], addr, size, value);
        int number_of_block = addr / block_size;
        if (buff[0] == 'W') {
            block_array[number_of_block % amount_of_blocks] = number_of_block;
        }
        if (buff[0] == 'R') {
            if (block_array[number_of_block % amount_of_blocks] != INT_MAX) {
                if (block_array[number_of_block % amount_of_blocks] != number_of_block) {
                    miss_count++;
                }
            }
            block_array[number_of_block % amount_of_blocks] = number_of_block;
        }
    }
    printf("%ld\n", miss_count);
    return 0;
}