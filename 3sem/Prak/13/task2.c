#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
enum { BASE_MAXSIZE1 = 256 };//2^8
int64_t
Min(int64_t a, int64_t b)
{
    if (a < b) {
        return a;
    } else {
        return b;
    }
}
int64_t
mul_overflow_check(int64_t a, int64_t b)
{
    long long mul;
    if (__builtin_smulll_overflow((long long) a, (long long) b, &mul)) {
        return 0;
    } else {
        return mul;
    }
}
int64_t
add_overflow_check(int64_t a, int64_t b)
{
    long long sum;
    if (__builtin_saddll_overflow((long long) a, (long long) b, &sum)) {
        return 0;
    } else {
        return sum;
    }
}
int64_t
calc_max_size(int64_t block_size, int64_t block_num_size, int64_t inode_direct_block_count)
{
    int overflow_flag[2] = {0,0};

    int64_t max_size1 = BASE_MAXSIZE1;
    int64_t max_size2 = inode_direct_block_count;
    for (int i = 0;i < block_num_size - 1;i++) {
        if ((max_size1 = mul_overflow_check(BASE_MAXSIZE1, max_size1)) == 0) {
            overflow_flag[0] = 1;
            break;
        }
    }
    if ((max_size1 = mul_overflow_check(block_size, max_size1)) == 0) {
        overflow_flag[0] = 1;
    }

    int64_t amount_of_blocks = block_size / block_num_size;
    int64_t temp = amount_of_blocks;
    for (int i = 0;i < 3;i++) {
        if ((max_size2 = add_overflow_check(max_size2, temp)) == 0) {
            overflow_flag[1] = 1;
        }
        if ((temp = mul_overflow_check(temp, amount_of_blocks)) == 0) {
            overflow_flag[1] = 1;
        }
    }
    if ((max_size2 = mul_overflow_check(block_size, max_size2)) == 0) {
        overflow_flag[1] = 1;
    }
    if (overflow_flag[0] == 1 && overflow_flag[1] == 0) {
        return max_size2;
    } else if (overflow_flag[0] == 0 && overflow_flag[1] == 1) {
        return max_size1;
    } else if (overflow_flag[0] == 1 && overflow_flag[1] == 1) {
        return -1;
    } else {
        return Min(max_size1, max_size2);
    }
}
int main()
{
    int64_t block_size,
        block_num_size,
        inode_direct_block_count;
    int64_t max = 0;
    int64_t max_number = 0;
    scanf("%lld%lld%lld", &block_size, &block_num_size, &inode_direct_block_count);
    printf("%lld\n", calc_max_size(block_size, block_num_size, inode_direct_block_count));
    for (int64_t i = 1;i <= block_size;i++) {
        int64_t temp = calc_max_size(block_size, i, inode_direct_block_count);
        if (temp == -1) {
            max_number = i;
            printf("%lld -1\n", max_number);
            return 0;
        } else if (temp > max) {
            max = temp;
            max_number = i;
        }
    }
    printf("%lld %lld\n", max_number, max);
    return 0;
}