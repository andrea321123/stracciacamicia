#include "include/game.h"
#include "include/common.h"
#include "include/permutations.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void show_help_exit(void) {
    puts("Usage: stracciacamica [START_GAME] [OPTION] ... ");
    puts("straccicamica search for infinite games of the \"stracciacamica\" board game");
    puts("If [START_GAME] is not given, read from stdin");
    puts("\nOptions:");
    puts("  -n NUM            set the number of games to try (default 1000000)");
    puts("  -d COUNT          every COUNT games print debug information (default no debug)");

    puts("\n  -h, --help        display this help and exit");
    puts("  -v, --version     display version and exit");

    puts("\nExample:");
    puts("stracciacamicia -d 100 -c 1000 1001200230030000000010012002300300000000");
    exit(0);
}

void show_version_exit(void) {
    puts("stracciacamicia version 1.0");
    puts("Author: andrea321123 <https://www.github.com/andrea321123>");
    exit(0);
}

void validate_input(const char *s) {
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

int main(int argc, char *argv[]) {
    char *s = malloc(DECK_SIZE +1);
    long count = 0;
    long steps = 1000000;
    int debug = 0;
    int start_config_inserted = 0;

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
            strcpy(s, argv[i]);
            start_config_inserted = 1;
        }
    }

    if (!start_config_inserted) {
        // read from stdin
        if (fgets(s, DECK_SIZE +1, stdin) == NULL) {
            puts("Error while reading input");
            exit(1);
        }
    }

    validate_input(s);

    long game_counter = 0;
    long debug_counter = 0;
    int next;
    do {
        enum game_result result = play_game(s);

        debug_counter++;
        if (debug && debug_counter == count) {
            if (result == INFINITE_GAME) {
                printf("%s might be infinite\n", s); 
            }
            else {   
                printf("%s: winner: player %d\n", s, result);
            }
            debug_counter = 0;
        }

        if (result == INFINITE_GAME) {
            // we append to the infinite games file this configuration
            FILE *file = fopen("infinite_games.txt", "a");
            if (file == NULL) {
                puts("Error while writing into the file");
                exit(1);
            }
            fprintf(file, "%s\n", s);
            fclose(file);
        }
    }
    while ((next = next_permutation(s, DECK_SIZE)) && ++game_counter < steps);

    // at the end we print the next configuration to be played
    if (next) {
        printf("%s\n", s);
    }

    return 0;
}
