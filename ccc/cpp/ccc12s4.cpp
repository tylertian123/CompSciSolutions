/*
 * C++ solution for CCC '12 S4 - A Coin Game
 */

#include <set>
#include <vector>
#include <queue>
#include <stdio.h>
#include <stdint.h>

typedef uint64_t Stack;

void push(Stack &stack, uint8_t value) {
    stack <<= 8;
    stack |= value;
}

void pop(Stack &stack) {
    stack >>= 8;
}

uint8_t top(Stack &stack) {
    return stack & 0xFF;
}

bool empty(Stack &stack) {
    return stack == 0;
}

typedef std::vector<Stack> State;

struct Step {
    State state;
    int moves;
};

int solve(State &state) {
    std::queue<Step> q;
    std::set<State> v;
    v.insert(state);
    q.push({state, 0});

    while(!q.empty()) {
        Step &s = q.front();
        bool valid = true;
        int prev = 0;
        for(Stack &i : s.state) {
            if(empty(i) || top(i) < prev) {
                valid = false;
                break;
            }
            prev = top(i);
        }
        if(valid) {
            return s.moves;
        }

        for(int i = 0; i < s.state.size(); i ++) {
            Stack &stack = s.state[i];
            if(empty(stack)) {
                continue;
            }
            int coin = top(stack);
            pop(stack);

            if(i > 0 && (empty(s.state[i - 1]) || coin < top(s.state[i - 1]))) {
                push(s.state[i - 1], coin);
                
                if(v.count(s.state) == 0) {
                    v.insert(s.state);
                    q.push({s.state, s.moves + 1});
                }
                pop(s.state[i - 1]);
            }

            if(i < s.state.size() - 1 > 0 && (empty(s.state[i + 1]) || coin < top(s.state[i + 1]))) {
                push(s.state[i + 1], coin);
                
                if(v.count(s.state) == 0) {
                    v.insert(s.state);
                    q.push({s.state, s.moves + 1});
                }
                pop(s.state[i + 1]);
            }

            push(stack, coin);
        }
        q.pop();
    }
    return -1;
}

int main() {
    while(true) {
        int coins;
        scanf(" %d", &coins);
        if(coins == 0) {
            return 0;
        }

        State s;
        for(int i = 0; i < coins; i ++) {
            int value;
            scanf(" %d", &value);
            Stack stack = 0;
            push(stack, value);
            s.push_back(stack);
        }

        int moves = solve(s);
        if(moves == -1) {
            printf("IMPOSSIBLE\n");
        }
        else {
            printf("%d\n", moves);
        }
    }
}
