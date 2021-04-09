#include "include/game.h"
#include "include/common.h"
#include "include/permutations.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    char s[] = "0000000000000000000100000000011122223333";
    int count = 0;

    while (next_permutation(s, DECK_SIZE)) {
        if (count++ == 10000000) {
            printf("%s: vincitore: giocatore %d\n", s, play_game(s));
            count = 0;
        }
    }
    
    return 0;
}