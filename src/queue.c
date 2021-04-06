#include "include/common.h"
#include "include/queue.h"

void init_queue(struct queue *q) {
    q->back = 0;
    q ->front = 0;
    q->empty = 1;
}

int enqueue(struct queue *q, char c) {
    // check if the queue is not full
    if (q->front == q->back && !q->empty) {
        return 0;
    }

    q->empty = 0;
    q->buffer[q->back++] = c;
    q->back %= DECK_SIZE;
    return 1;
}

struct dequeue_result dequeue(struct queue *q) {
    // check if the queue is not empty
    if (q->empty) {
        struct dequeue_result ret = {
            .status = 0,
            .output = '0'
        };
        return ret;
    }

    char c = q->buffer[q->front++];
    q->front %= DECK_SIZE;

    // update empty variable
    if (q->front == q->back) {
        q->empty = 1;
    }

    struct dequeue_result ret = {
            .status = 1,
            .output = c
        };
    return ret;
}