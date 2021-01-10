#include <cstdio>
#include <cstring>
#include <array>
#include <unordered_set>

char needle[200001];
char haystack[200001];
int len_needle;
int len_haystack;

// Wrapper for a distinct permutation
// Stores both the hash and the string itself
// The string is simply stored as an index in the haystack
class permutation {
public:
    const std::size_t hash;
    const int index;

    bool operator==(const permutation &p) const {
        if (p.index == index) {
            return true;
        }
        return std::strncmp(haystack + index, haystack + p.index, len_needle) == 0;
    }
};

// Custom hash function for permutation
// Simply uses the stored hash value
namespace std {
    template <>
    struct hash<permutation> {
        std::size_t operator()(const permutation &p) const {
            return p.hash;
        }
    };
}

int main() {
    // Magic values used for polynomial rolling hash
    constexpr unsigned long long HASH_P = 29;
    constexpr unsigned long long HASH_M = 1000000009;
    
    std::scanf("%s", needle);
    std::scanf("%s", haystack);
    len_needle = std::strlen(needle);
    len_haystack = std::strlen(haystack);

    // Handle edge case
    if (len_needle > len_haystack) {
        printf("0\n");
        return 0;
    }
    // Make character indexes start at 0 for the haystack
    // The same is done for the needle in another loop
    for (int i = 0; i < len_haystack; i ++) {
        haystack[i] -= 'a';
    }

    // Compute a table of character frequencies and the hash
    std::array<int, 26> needle_freq = { 0 };
    std::array<int, 26> haystack_freq = { 0 };
    std::size_t hash = 0;
    std::size_t hash_multiplier = 1;
    // The last character has the lowest power in this hash
    // This is so that moving the window to the right does not involve division
    for (int i = len_needle - 1; i >= 0; i --) {
        needle[i] -= 'a';
        needle_freq[needle[i]] ++;
        haystack_freq[haystack[i]] ++;

        hash += haystack[i] * hash_multiplier % HASH_M;
        // hash_multiplier is the p^n value for the largest power
        // so don't multiply again after the last term
        if (i != 0) {
            hash_multiplier = hash_multiplier * HASH_P % HASH_M;
        }
    }
    hash %= HASH_M;
    // Initialize and account for a possible initial match
    std::unordered_set<permutation> seen;
    long long count = 0;
    if (needle_freq == haystack_freq) {
        count ++;
        seen.insert({hash, 0});
    }
    // Start the rolling window
    for (int i = 1; i <= len_haystack - len_needle; i ++) {
        // Char that just left the window
        const int prev = haystack[i - 1];
        // Char that just entered the window
        const int end = haystack[i + len_needle - 1];
        // Compute new frequency table
        haystack_freq[prev] --;
        haystack_freq[end] ++;
        // Compute new hash
        size_t h = prev * hash_multiplier % HASH_M;
        if (h > hash) {
            hash += HASH_M;
        }
        hash -= h;
        hash *= HASH_P;
        hash += end;
        hash %= HASH_M;
        // Check
        if (needle_freq == haystack_freq && seen.insert({hash, i}).second) {
            count ++;
        }
    }
    std::printf("%lld\n", count);
}
