#include "memory-user.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long int mem = 10;
    memory_user(mem * 1024 * 1024 * 1024);
    return 0;
}