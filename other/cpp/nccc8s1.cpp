#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string alph, s;
    getline(cin, alph);
    getline(cin, s);

    unordered_set<string> seen;
    seen.insert(s);
    for (char c : alph) {
        for (int i = 0; i <= s.length(); i ++) {
            seen.insert(s.substr(0, i) + c + s.substr(i));
        }
    }
    for (char c : alph) {
        for (int i = 0; i < s.length(); i ++) {
            if (c != s[i]) {
                string s2 = s;
                s2[i] = c;
                seen.insert(s2);
            }
        }
    }
    for (int i = 0; i < s.length(); i ++) {
        seen.insert(s.substr(0, i) + s.substr(i + 1));
    }
    vector<string> strs;
    for (const string &str : seen) {
        if (str != s && str != "") {
            strs.emplace_back(str);
        }
    }
    std::sort(strs.begin(), strs.end());
    for (const string &s : strs) {
        std::cout << s << "\n";
    }
}
