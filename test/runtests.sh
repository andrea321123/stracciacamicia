#usr/bin/sh

# compilation phase
cc -o queue_test queue_test.c \
    ../src/queue.c
cc -o permutations_test permutations_test.c \
    ../src/permutations.c

# execute phase
./queue_test
./permutations_test

rm *test