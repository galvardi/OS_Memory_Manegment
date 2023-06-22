#include "../VirtualMemory.h"

#include <cstdio>
#include <cassert>

int main(int argc, char **argv) {
    VMinitialize();
    uint64_t iter = (2 * NUM_FRAMES);
    for (uint64_t i = 0; i < iter; ++i) {
        printf("writing to %llu\n", (long long int) i);
        VMwrite(5 * i * PAGE_SIZE, i);
//        word_t value;
//        VMread(5 * i * PAGE_SIZE, &value);
//        assert (uint64_t (value) == i);
//        break;
    }
    for (uint64_t i = 0; i < iter; ++i) {
        word_t value;
        VMread(5 * i * PAGE_SIZE, &value);
        printf("reading from %llu %d\n", (long long int) i, value);
        assert(uint64_t(value) == i);
    }
    printf("success\n");

    return 0;
}
