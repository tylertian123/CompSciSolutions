#include <iostream>

typedef long long ll;
ll ones[1000001];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n, k;
    std::cin >> n >> k;
    for (ll i = 0; i < k; i ++) {
        std::cin >> ones[i];
    }

    ll total = 0;
    for (ll i = 0; i < k - 2; i ++) {
        ll start = ones[i];
        ll end = ones[i + 2];
        ll prev = i != 0 ? ones[i - 1] + 1 : 1;

        total += (n - end + 1) * (start - prev + 1);
    }
    std::cout << total << std::endl;
}
