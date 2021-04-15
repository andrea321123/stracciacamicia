#include "include/game.h"
#include "include/common.h"
#include "include/permutations.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void show_help_exit(void) {
    puts("Usage: stracciacamica [COFIGURATION] [OPTION] ... ");
    puts("straccicamica search for infinite games of the \"stracciacamica\" board game");
    puts("\nOptions:");
    puts("  -n NUM      set the number of games to try (default 1000000000)");
    puts("  -d COUNT    every COUNT games print debug information (default no debug)");

    puts("\n  -h, --help        display this help and exit");
    puts("  -v, --version     display version and exit");
    exit(0);
}

void show_version_exit(void) {
    puts("stracciacamicia version 1.0");
    puts("Author: andrea321123 <https://www.github.com/andrea321123>");
    exit(0);
}

int main(int argc, char *argv[]) {
    char *s = NULL;
    long count = 0;
    long steps = 1000000000;
    int debug = 0;
    int start_config_inserted = 0;

    if (argc == 1) {
        show_help_exit();
    }
    
    for(int i = 1; i < argc; i++) {
        if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
            show_help_exit();
        }
        if (strcmp("-v", argv[i]) == 0 || strcmp("--version", argv[i]) == 0) {
            show_version_exit();
        }
        if (strcmp("-n", argv[i]) == 0) {
            if (argc == ++i) {
                puts("Expected NUM argument");
                exit(1);
            }

            steps = strtol(argv[i], NULL, 10);
            if (!steps) {
                puts("Error during NUM conversion");
                exit(1);
            }
            if (steps < 0) {
                puts("NUM must be > 0");
                exit(1);
            }
        }
        else if (strcmp("-d", argv[i]) == 0) {
            if (argc == ++i) {
                puts("Expected COUNT argument");
                exit(1);
            }

            debug = 1;
            count = strtol(argv[i], NULL, 10);
            if (!count) {
                puts("Error during COUNT conversion");
                exit(1);
            }
            if (count < 0) {
                puts("COUNT must be > 0");
                exit(1);
            }
        }
        else {
            s = malloc(DECK_SIZE +1);
            strcpy(s, argv[i]);
            start_config_inserted = 1;

            // check validity of input start configuration
            if (strlen(s) != DECK_SIZE) {
                printf("Start configuration size must be of %d characters\n", DECK_SIZE);
                exit(1);
            }
            for (size_t i = 0; i < DECK_SIZE; i++) {
                char c = s[i];
                if (c != '0' && c != '1' && c != '2' && c != '3') {
                    puts("Start configuration can contain only '0', '1', '2', and '3' characters");
                    exit(1);
                }
            }
        }

        if (!start_config_inserted) {
            puts("You must insert a start configuration");
            exit(1);
        }
    }

    long game_counter = 0;
    long debug_counter = 0;
    do {
        enum game_result result = play_game(s);

        debug_counter++;
        if (debug && debug_counter == count) {
            printf("%s: winner: player %d\n", s, result);
            debug_counter = 0;
        }
    }
    while (next_permutation(s, DECK_SIZE) && game_counter++ < steps);

    return 0;
}