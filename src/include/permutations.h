#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <stddef.h>

// Convert [perm] into the next permutation in lexicographic order of [perm].
// [perm_size] is the size of [perm] string, excluding the '\0' character.
// Return 0 if [perm] is the last permutation, 1 otherwise.
int next_permutation(char *perm, size_t perm_size);

#endif