#include <iostream>

using namespace std;

long long arr[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char c;
    int x;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i ++) {
        cin >> x;
        arr[x] ++;
    }
    for (int i = 0; i < q; i ++) {
        cin >> c >> x;
        if (c == '1') {
            if (x % 2 == 0) {
                arr[x / 2] += 2 * arr[x];
                arr[x] = 0;
            }
            else {
                arr[x / 2] += arr[x];
                arr[x / 2 + 1] += arr[x];
                arr[x] = 0;
            }
        }
        else {
            cout << arr[x] << "\n";
        }
    }
}
