#include "../src/include/queue.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    struct queue test;
    init_queue(&test);

    for (size_t i = 0; i < DECK_SIZE -2; i++) {
        enqueue(&test, '1');
    }
    
    assert(dequeue(&test).status);

    enqueue(&test, '2');
    enqueue(&test, '2');
    enqueue(&test, '2');

    assert(!enqueue(&test, '1'));

    puts("queue_test succeeded");
    return 0;
}