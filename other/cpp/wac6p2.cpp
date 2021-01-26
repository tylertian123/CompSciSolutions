#include <iostream>

using namespace std;

bool lights[200000];
int changes[200000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    int on = 0;
    for (int i = 0; i < n; i ++) {
        char c;
        cin >> c;
        if (c == '1') {
            lights[i] = true;
            on ++;
        }
    }
    if (on == 0) {
        cout << 0 << "\n";
        return 0;
    }
    for (int i = 0; i < m; i ++) {
        int j;
        cin >> j;
        changes[i] = j - 1;
    }

    int t = 1;
    int t_req = on;
    for (; t <= t_req && t <= m; t ++) {
        int change = changes[t - 1];
        if (lights[change]) {
            t_req --;
        }
        else {
            t_req ++;
        }
        lights[change] = !lights[change];
        //cout << "time: " << t << " req: " << t_req << endl;
    }
    cout << max(t - 1, t_req) << "\n";
}
