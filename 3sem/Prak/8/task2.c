#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

typedef struct RandomGenerator RandomGenerator;
const typedef struct RandomOperations
{
    int (*next)(struct RandomGenerator *);
    void (*destroy)(struct RandomGenerator *);
}RandomOperations;

typedef struct RandomGenerator
{
    unsigned int prev;
    unsigned int factor;
    unsigned int inc;
    unsigned int mod;
    RandomOperations *ops;
} RandomGenerator;
static int get_next(RandomGenerator *rr);
static void destroy(RandomGenerator *rr);
RandomOperations op = {.next = &get_next, .destroy = &destroy};

static int
get_next(RandomGenerator *rr)
{
    unsigned int tmp = ((unsigned) (rr->prev * rr->factor) + rr->inc) % (rr->mod);
    rr->prev = tmp;
    return tmp;
}

static void
destroy(RandomGenerator *rr)
{
    free(rr);
}

RandomGenerator
*random_create(int seed)
{
    RandomGenerator *rr = (RandomGenerator *) calloc(1, sizeof(RandomGenerator));
    if (rr == NULL) {
        fprintf(stderr, "calloc erorr\n");
        return 0;
    }
    rr->ops = &op;
    rr->prev = seed;
    rr->mod = 2147483648;
    rr->inc = 12345;
    rr->factor = 1103515245;
    return rr;
}
