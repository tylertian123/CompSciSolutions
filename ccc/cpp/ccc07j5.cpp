#include <algorithm>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

constexpr size_t init_motel_size = 14;
const unsigned int init_motels[init_motel_size] = {0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};

long options(unsigned int m, unsigned int *motels, unsigned int size, unsigned int a, unsigned int b, long *cache) {
    if (cache[m] != -1) {
        return cache[m];
    }
    long sum = 0;
    for (unsigned int i = m + 1; i < size; i ++) {
        unsigned int d = motels[i] - motels[m];
        if (d < a) {
            continue;
        }
        if (d > b) {
            break;
        }
        sum += options(i, motels, size, a, b, cache);
    }
    cache[m] = sum;
    return sum;
}

int main() {
    unsigned int a, b, n;
    scanf("%u%u%u", &a, &b, &n);
    const unsigned int size = n + init_motel_size;
    unsigned int *motels = (unsigned int*) malloc(sizeof(unsigned int) * size);
    memcpy(motels, init_motels, sizeof(unsigned int) * init_motel_size);

    unsigned int *ptr = motels + init_motel_size;
    for (unsigned int i = 0; i < n; i ++, ptr ++) {
        scanf("%u", ptr);
    }
    std::sort(motels, ptr);
    
    long *cache = (long*) malloc(sizeof(long) * size);
    for (unsigned int i = 0; i < size; i ++) {
        cache[i] = -1;
    }
    cache[size - 1] = 1;
    printf("%ld\n", options(0, motels, size, a, b, cache));

    free(cache);
    free(motels);
    return 0;
}
