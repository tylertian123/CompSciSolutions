#include <bits/stdc++.h>

using namespace std;

// Custom struct for a rule
// a is the string to be replaced
// b is the string to replace with
struct rule {
    string a;
    string b;
};
// Custom struct for a "step"
// As the problem states, each step contains the rule number, the position at which it's applied at and the result.
struct step {
    int rule;
    int pos;
    string result;
};

// Globals that store the available substitution rules and the wanted result
rule rules[3];
string goal;

// Applies a rule to string s at index
// Returns empty string if not applicable
string apply_rule(const string &s, const rule &rule, int index) {
    // First check if the string is long enough
    if(index + rule.a.length() > s.length()) {
        return "";
    }
    // Then go through every character in the rule and see if it matches the corresponding character in the string
    for(int i = 0; i < rule.a.length(); i ++) {
        if(s[i + index] != rule.a[i]) {
            return "";
        }
    }
    // If all tests pass, return a part of the string from the beginning to the start of the replacement,
    // added to the replacement and a part of the string from the end of the replacement to the end of the string
    return s.substr(0, index) + rule.b + s.substr(index + rule.a.length());
}

// Use a set of pairs of a string and an integer to keep track of already known failed cases
// Any combination of a string and a number of steps in this set is known to fail
set<pair<string, int>> failed;
vector<step> sub(const string &init, int steps) {
    // If we ran out of steps, add it to the failed list and return an empty vector
    if(steps == 0) {
        failed.insert(make_pair(init, steps));
        return vector<step>();
    }
    // If the case can be found in the failed set, return an empty vector
    // Note that find returns an iterator at the end if it does not find the element
    if(failed.find(make_pair(init, steps)) != failed.end()) {
        return vector<step>();
    }
    // For each rule:
    for(int i = 0; i < 3; i ++) {
        // For each position in the string the rule can be applied:
        for(int j = 0; j < init.length(); j ++) {
            // Apply the rule
            string after_rule = apply_rule(init, rules[i], j);
            // If the rule and be applied:
            if(after_rule.length() > 0) {
                // See if we reached our goal
                if(after_rule == goal) {
                    // Document our last step and add it to a vector to return
                    step s = { i + 1, j + 1, after_rule };
                    vector<step> ss;
                    ss.push_back(s);
                    return ss;
                }
                else {
                    // Otherwise recursively call sub to get a solution
                    auto result = sub(after_rule, steps - 1);
                    // If a solution exists, add the last step to the result and return it
                    if(result.size() != 0) {
                        step s = { i + 1, j + 1, after_rule };
                        result.push_back(s);
                        return result;
                    }
                }
            }
        }
    }
    // If all fails, add it to the failing set and return an empty vector
    failed.insert(make_pair(init, steps));
    return {};
}

int main() {
    // Turn off sync with stdio
    // This makes iostream much faster
    ios::sync_with_stdio(false);
    string a, b;
    // Read in all the rules
    cin >> a >> b;
    rules[0] = { a, b };
    cin >> a >> b;
    rules[1] = { a, b };
    cin >> a >> b;
    rules[2] = { a, b };
    // Read in the number of steps, the init state and the end state
    int steps;
    string init;
    cin >> steps >> init >> goal;
    auto result = sub(init, steps);
    // Loop through the results and print each one
    // Note that the order is reversed
    for(int i = result.size() - 1; i >= 0; i --) {
        cout << result[i].rule << " " << result[i].pos << " " << result[i].result << endl;
    }
}

