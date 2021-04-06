#ifndef QUEUE_H
#define QUEUE_H

#include "include/common.h"

#include <stddef.h>

// Return value of dequeue() function
struct dequeue_result {
    int status;
    char output;
};

// Queue implemented as circular buffer of size [DECK_SIZE]
struct queue {
    static char buffer[DECK_SIZE];
    static size_t front;
    static size_t back;
    static int empty;
};

// Initialize  the queue
void init_queue(queue *q);

// Insert [c] in the queue.
// Return 0 if the queue is full (because it is implemented as a ring buffer),
// 1 otherwise
int enqueue(struct queue *q, char c);

// Remove a char from the queue.
// Return 0 if the queue is empty, 1 otherwise
struct dequeue_result dequeue(struct queue *q);

#endif