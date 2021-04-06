#usr/bin/sh

# compilation phase
cc -o queue_test queue_test.c \
    ../src/queue.c

# execute phase
./queue_test