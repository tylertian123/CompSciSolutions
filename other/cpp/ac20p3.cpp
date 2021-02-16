#include <iostream>
#include <vector>

using namespace std;

char s[500001], t[500001];
vector<int> occur[26];

int find_greater(vector<int> &arr, int v) {
    int begin = 0;
    int end = arr.size();
    while (end > begin) {
        int mid = (begin + end) / 2;
        
        if (arr[mid] <= v) {
            begin = mid + 1;
        }
        else {
            if (mid == 0) {
                return arr[mid];
            }
            if (arr[mid - 1] <= v) {
                return arr[mid];
            }
            end = mid;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ls, lt;
    cin >> ls >> lt;
    cin >> ws;
    cin.getline(s, 500001);
    cin.getline(t, 500001);

    for (int i = 0; i < ls; i ++) {
        occur[s[i] - 'a'].push_back(i);
    }

    long long len = 0;
    int index = -1;
    for (char *c = t; *c; ++c) {
        int greater_idx = find_greater(occur[*c - 'a'], index);
        if (greater_idx != -1) {
            len += greater_idx - index;
            index = greater_idx;
        }
        else {
            // Try looping around
            len += (ls - index - 1);
            index = -1;
            greater_idx = find_greater(occur[*c - 'a'], index);
            if (greater_idx == -1) {
                cout << -1 << "\n";
                return 0;
            }
            else {
                len += greater_idx - index;
                index = greater_idx;
            }
        }
    }
    cout << len << "\n";
}