#ifndef GAME_H
#define GAME_H

// Possible game results
enum game_result {
    WIN_PLAYER_0,
    WIN_PLAYER_1,
    INFINITE_GAME
};

// Play a "stracciacamicia" game starting with [cards] configuration
// Return:
// 0: win player 0
// 1: win player 1
// 2: infinite game
enum game_result play_game(char *cards);

#endif