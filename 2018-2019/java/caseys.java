import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Caseys {

    /**
     * The state class represents an order state. The internal integer array
     * describes how much of each menu item was ordered.
     */
    public static class State implements Cloneable {
        public int[] counts;

        // hashCode has to be overridden for HashSets
        @Override
        public int hashCode() {
            // Use Arrays.hashCode()
            return Arrays.hashCode(counts);
        }

        // equals has to be overridden for HashSets
        @Override
        public boolean equals(Object other) {
            if (!(other instanceof State)) {
                return false;
            }
            State otherState = (State) other;
            // Use Arrays.equals()
            return Arrays.equals(otherState.counts, counts);
        }

        // clone is used later to duplicate the instance
        @Override
        public State clone() {
            State s = new State();
            // Use Arrays.copyOf()
            s.counts = Arrays.copyOf(counts, counts.length);
            return s;
        }
    }

    /**
     * This class represents a menu item, which has a name and a price.
     */
    public static class MenuItem {
        public String name;
        public int price;
    }

    // Array containing all available menu items
    public static MenuItem[] menu;
    // ArrayList containing all the solutions
    // They're all stored here so they can be printed later
    public static ArrayList<State> solutions = new ArrayList<State>();
    // Keep a Set of all the states that we've solved
    // This avoids duplicate cases and speeds up execution with Dynamic Programming
    public static Set<State> solved = new HashSet<>();

    // This a recursive function that generates the solutions
    public static void solve(State state, int money) {
        // Check if the state has already been solved
        if (solved.contains(state)) {
            return;
        }
        if (money == 0) {
            // If we come across a solution, make a copy of the state
            // And then add it to the solved ArrayList and Set
            State copy = state.clone();
            solved.add(copy);
            solutions.add(copy);
        } else {
            // If there's still money left go through every menu item
            for (int i = 0; i < menu.length; i++) {
                // If we can afford the item:
                if (menu[i].price <= money) {
                    // Update the state
                    state.counts[i]++;
                    // Recursively call solve with the updated state and new money
                    solve(state, money - menu[i].price);
                    // Reset the state
                    // This way we avoid expensive copy operations
                    state.counts[i]--;
                }
            }
        }
        // Finally mark the state as already visited for DP
        State copy = state.clone();
        solved.add(copy);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        // Read in goal and item count
        int goal = Integer.parseInt(in.readLine());
        int itemCount = Integer.parseInt(in.readLine());
        menu = new MenuItem[itemCount];
        // Read in all menu items
        for (int i = 0; i < itemCount; i++) {
            menu[i] = new MenuItem();
            String[] input = in.readLine().split(" ");
            menu[i].price = Integer.parseInt(input[1]);
            menu[i].name = input[0];
        }

        // Create initial state and call solve
        int[] stateArray = new int[itemCount];
        State state = new State();
        state.counts = stateArray;
        solve(state, goal);
        // If solution exists:
        if (solutions.size() > 0) {
            for (State solution : solutions) {
                System.out.println("------------------");
                for (int i = 0; i < solution.counts.length; i++) {
                    if (solution.counts[i] > 0) {
                        // Use printf to print out each item
                        System.out.printf("%s\tx%d\n", menu[i].name, solution.counts[i]);
                    }
                }
            }
            System.out.println("------------------");
        } else {
            // Otherwise mock the user
            System.out.println("How was your dinner?");
        }
    }
}
