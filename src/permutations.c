#include "include/permutations.h"

#include <stdio.h>

int next_permutation(char *perm, size_t perm_size) {
    // References:
    // https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order
    //https://en.cppreference.com/w/cpp/algorithm/next_permutation

    size_t k, l;
    int found_next = 0;

    for (size_t i  = perm_size -1; i > 0; i--) {
        if (perm[i] > perm[i -1]) {
            k = i -1;
            found_next = 1;
            break;
        }
    }

    // if [perm] is already sorted, there's no next permutation
    if (!found_next) {
        return 0;
    }

    char k_char = perm[k];
    for (size_t i = perm_size -1; i > k; i--) {
        if (k_char  < perm[i]) {
            l = i;
            break;
        }
    }

    // swap perm[k] and perm[l]
    perm[k] = perm[l];
    perm[l] = k_char;

    // reverse the string from perm[k +1] to perm[perm_size -1]
    ++k;
    for (size_t i = k; i < ((perm_size - k) /2) + k; i++) {
        char tmp = perm[perm_size -1 - i + k];
        perm[perm_size -1 - i + k] = perm[i];
        perm[i] = tmp;
    }

    return 1;
}

