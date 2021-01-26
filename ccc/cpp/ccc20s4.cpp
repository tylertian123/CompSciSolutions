#include <iostream>
#include <limits>

constexpr int MLEN = 1000000;

int len = 0;
char str[MLEN + 1];
int psa_a[MLEN], psa_b[MLEN], psa_c[MLEN];
int ca = 0, cb = 0, cc = 0;

// Perform query on a PSA (start inclusive, end exclusive)
// start and end can be greater than the array length
int psa(int *arr, int start, int end) {
    if (start >= len) {
        start -= len;
    }
    if (end > len) {
        end -= len;
    }

    if (end >= start) {
        if (start == 0) {
            return arr[end - 1];
        }
        return arr[end - 1] - arr[start - 1];
    }
    else {
        return psa(arr, start, len) + psa(arr, 0, end);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> std::noskipws;

    for (; ; len ++) {
        std::cin >> str[len];
        if (str[len] == '\n') {
            str[len] = '\0';
            break;
        }
        if (len != 0) {
            psa_a[len] = psa_a[len - 1];
            psa_b[len] = psa_b[len - 1];
            psa_c[len] = psa_c[len - 1];
        }

        if (str[len] == 'A') {
            psa_a[len] ++;
            ca ++;
        }
        else if (str[len] == 'B') {
            psa_b[len] ++;
            cb ++;
        }
        else {
            psa_c[len] ++;
            cc ++;
        }
    }

    int result = std::numeric_limits<int>::max();
    for (int i = 0; i < len; i ++) {
        // Number of non A in A + Number of non B in B - min(A in B, B in A)
        // Assume next section is B:
        int b = (ca - psa(psa_a, i, i + ca)) + (cb - psa(psa_b, i + ca, i + ca + cb))
            - std::min(psa(psa_a, i + ca, i + ca + cb), psa(psa_b, i, i + ca));
        // Assume next section is C:
        int c = (ca - psa(psa_a, i, i + ca)) + (cb - psa(psa_b, i + ca + cc, i + len))
            - std::min(psa(psa_a, i + ca + cc, i + len), psa(psa_b, i, i + ca));
        result = std::min(std::min(b, c), result);
    }
    std::cout << result << "\n";
}
