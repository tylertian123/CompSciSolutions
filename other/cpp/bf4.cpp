#include <string>
#include <iostream>
#include <stddef.h>
#include <string.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::string t;
    std::getline(std::cin, s);
    std::getline(std::cin, t);
    if (t.length() >= s.length()) {
        std::cout << (t == s ? 0 : -1) << std::endl;
        return 0;
    }

    const int HASH_P = 29;
    size_t t_hash = 0;
    size_t hash = 0;
    size_t hash_multiplier = 1;
    for (int i = t.length() - 1; i >= 0; i --) {
        t_hash += t[i] * hash_multiplier;
        hash += s[i] * hash_multiplier;
        if (i != 0) {
            hash_multiplier *= HASH_P;
        }
    }
    if (hash == t_hash && !strncmp(s.c_str(), t.c_str(), t.length())) {
        std::cout << 0 << std::endl;
        return 0;
    }
    for (int i = 1; i <= s.length() - t.length(); i ++) {
        const char prev = s[i - 1];
        const char next = s[i + t.length() - 1];
        hash -= prev * hash_multiplier;
        hash *= HASH_P;
        hash += next;

        if (hash == t_hash && !strncmp(s.c_str() + i, t.c_str(), t.length())) {
            std::cout << i << std::endl;
            return 0;
        }
    }
    std::cout << -1 << std::endl;
}
