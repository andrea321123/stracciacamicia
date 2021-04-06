#include "../src/include/permutations.h"

#include <assert.h>
#include <stdio.h>
#include <stddef.h>

int main(void) {
    char t1[] = "12345";
    char t2[] = "0011122";
    size_t count = 1;

    while (next_permutation(t1, 5)) {
        count++;
    }
    assert(count == 120);
    count = 1;

    while (next_permutation(t2, 7)) {
        count++;
    }
    assert(count == 210);

    puts("permutations_test succeeded");
    return 0;
}