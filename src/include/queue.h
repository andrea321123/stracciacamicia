#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

#include <stddef.h>

// Return value of dequeue() function
struct dequeue_result {
    int status;
    char output;
};

// Queue implemented as circular buffer of size [DECK_SIZE]
struct queue {
    char buffer[DECK_SIZE];
    size_t front;
    size_t back;
    int empty;
};

// Initialize  the queue
void init_queue(struct queue *q);

// Insert [c] in the queue.
// Return 0 if the queue is full (because it is implemented as a ring buffer),
// 1 otherwise
int enqueue(struct queue *q, char c);

// Remove a char from the queue.
// Return 0 if the queue is empty, 1 otherwise
struct dequeue_result dequeue(struct queue *q);

// Print the content of a queue
void print_queue(struct queue *q);

#endif