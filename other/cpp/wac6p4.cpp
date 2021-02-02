#include <iostream>
#include <cstring>

using ui = unsigned long long;

constexpr ui m = 998244353;

// modifies b
void mul44(ui a[4][4], ui b[4][4]) {
    ui c[4][4];
    c[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0]) % m;
    c[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] + a[1][3] * b[3][0]) % m;
    c[2][0] = (a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] + a[2][3] * b[3][0]) % m;
    c[3][0] = (a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] + a[3][3] * b[3][0]) % m;

    c[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] + a[0][3] * b[3][1]) % m;
    c[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] + a[1][3] * b[3][1]) % m;
    c[2][1] = (a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] + a[2][3] * b[3][1]) % m;
    c[3][1] = (a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] + a[3][3] * b[3][1]) % m;

    c[0][2] = (a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] + a[0][3] * b[3][2]) % m;
    c[1][2] = (a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] * b[3][2]) % m;
    c[2][2] = (a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] + a[2][3] * b[3][2]) % m;
    c[3][2] = (a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] + a[3][3] * b[3][2]) % m;

    c[0][3] = (a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] + a[0][3] * b[3][3]) % m;
    c[1][3] = (a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] + a[1][3] * b[3][3]) % m;
    c[2][3] = (a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] + a[2][3] * b[3][3]) % m;
    c[3][3] = (a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] + a[3][3] * b[3][3]) % m;

    std::memcpy(b, c, sizeof(ui) * 16);
}

// Who needs O(log N) exponentiation anyway

ui w_mat[4][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
};
ui a_mat[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 1},
};
ui c_mat[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
};
ui mat[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
};
ui temp[4][4];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    for (int i = 0; i < n; i ++) {
        char c;
        std::cin >> c;
        if (c == 'W') {
            mul44(w_mat, mat);
        }
        else if (c == 'A') {
            mul44(a_mat, mat);
        }
        else if (c == 'C') {
            mul44(c_mat, mat);
        }
    }
    std::memcpy(temp, mat, sizeof(ui) * 16);
    for (int i = 0; i < k - 1; i ++) {
        mul44(temp, mat);
    }
    std::cout << mat[3][0] << "\n";
}