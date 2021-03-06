#include "include/game.h"
#include "include/queue.h"
#include "include/common.h"

enum turn_result {
    TURN_PLAYER_0 = 0,              // win the turn but not the game
    TURN_PLAYER_1 = 1,
    TURN_INFINITE_GAME = 2,
    TURN_WIN_PLAYER_0 = 3,          // win the turn and the game
    TURN_WIN_PLAYER_1 = 4
};

static struct queue players[2];
static struct queue game_queue;

static int opposite_turn(int turn) {
    if (turn == 0) {
        return 1;
    }
    return 0;
}

// defend() is called when the opponent plays a 1, 2 or 3 card
enum turn_result defend(int turn, int card) {
    int opponent_turn = opposite_turn(turn);

    while (card != 0) {
        struct dequeue_result result = dequeue(&players[turn]);
        enqueue(&game_queue, result.output);
        if (!result.status) {       // empty queue, opponents win
            return opponent_turn +3;
        }

        if (result.output != '0') {
            return defend(opponent_turn, result.output - '0');
        }

        card--;
    }

    // if we arrive here, we have lost the turn
    // if our deck is empty, we have also lost the game
    if (players[turn].empty) {
        return opponent_turn +3;
    }
    return opponent_turn;
}

// Play a single turn
enum turn_result play_turn(int turn) {
    int opponent_turn = opposite_turn(turn);

    struct dequeue_result result = dequeue(&players[turn]);
    enqueue(&game_queue, result.output);
    if (!result.status) {       // empty queue, opponents win
        return opponent_turn +3;
    }

    if (result.output == '0') {
        return play_turn(opponent_turn);    
    }

    // the card was a 1, 2, or 3
    return defend(opponent_turn, result.output - '0');
}

enum game_result play_game(char *cards) {
    // init queues
    init_queue(&players[0]);
    init_queue(&players[1]);
    init_queue(&game_queue);
    for(size_t i = 0; i < DECK_SIZE; i++) {
        enqueue(&players[i / (DECK_SIZE /2)], cards[i]);
    }

    int turn = 0;
    size_t played_turns = 0;

    while (played_turns++ < MAX_TURNS) {
        switch (play_turn(turn)) {
            case TURN_PLAYER_0:
                transfer_queue(&players[0], &game_queue);
                turn = 0;
                break;
            case TURN_PLAYER_1:
                transfer_queue(&players[1], &game_queue);
                turn = 1;
                break;
            case TURN_WIN_PLAYER_0:
                return WIN_PLAYER_0;
            case TURN_WIN_PLAYER_1:
                return WIN_PLAYER_1;    
            default:
                break;
        }   
    }

    // if we reach this point, the game is likely to be infinite
    return INFINITE_GAME;

}
