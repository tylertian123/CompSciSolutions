import java.io.*;
import java.util.*;

public class CCC19J5 {
    // In order to not time out, we have to utilize Dynamic Programming and keep a set of all failed cases
    // This set must have a key that has both a String and an Integer (the current state and the steps left)
    // The MultiKey class is simply a class that can hold two values.
    public static class MultiKey<T, U> {
        public T a;
        public U b;

        public MultiKey(T t, U u) {
            a = t;
            b = u;
        }

        // Override equals so that if two MultiKeys' elements are the same, they are considered equal
        // Without this the set would not work properly
        @Override
        public boolean equals(Object another) {
            if(!(another instanceof MultiKey)) {
                return false;
            }
            MultiKey<?, ?> k = (MultiKey<?, ?>) another;
            return a.equals(k.a) && b.equals(k.b);
        }
        // Override hashCode so that if two MultiKeys are equal, they would have the same hash.
        // As set relies on this to function, if left unimplemented it would not work properly
		@Override
		public int hashCode() {
			return a.hashCode() + b.hashCode();
		}
    }
    // A class that represents a step
    // According to the problem, each step keeps track of the rule applied, the position of the application, and the result
    public static class Step {
        int rule;
        int pos;
        String result;

        public Step(int r, int p, String result) {
            this.rule = r;
            this.pos = p;
            this.result = result;
        }
    }

    // All 3 rules are stored here as a 2D array
    public static String[][] rules = new String[3][2];
    // The end result is stored here
    public static String goal;
    // This set keeps track of all failed cases
    public static Set<MultiKey<String, Integer>> failed = new HashSet<>();
    public static ArrayList<Step> sub(String init, int steps) {
        // See if the case is a failed case
        if(failed.contains(new MultiKey<String, Integer>(init, steps))) {
            return null;
        }
        // If our current state is the end state, return an empty ArrayList to signify we found something
        if(init.equals(goal)) {
            return new ArrayList<Step>();
        }
        // Otherwise if we ran out of steps, add it to the failed list and return null
        else if(steps == 0) {
            failed.add(new MultiKey<String, Integer>(init, steps));
            return null;
        }
        // Loop through all 3 rules
        for(int i = 0; i < 3; i ++) {
            // Loop through each index of the string to apply the rule
            for(int j = 0; j < init.length(); j ++) {
                // Try to apply the rule at that index
                String r = applyRule(init, rules[i], j);
                // If the rule was applied successfully:
                if(r != null) {
                    // Get the result by recursively calling sub
                    ArrayList<Step> result = sub(r, steps - 1);
                    // If there is a result, add the last step to the result and return it
                    if(result != null) {
                        result.add(new Step(i + 1, j + 1, r));
                        return result;
                    }
                }
            }
        }
        // If no working combination was found, add it to the failed list and return null
        failed.add(new MultiKey<String, Integer>(init, steps));
        return null;
    }
    // Applies a rule to s at index
    public static String applyRule(String s, String[] rule, int index) {
        // First check if the string is long enough
        if(index + rule[0].length() > s.length()) {
            return null;
        }
        // Then look through every character in the rule and see if it matches the corresponding character in the string
        for(int i = 0; i < rule[0].length(); i ++) {
            if(rule[0].charAt(i) != s.charAt(index + i)) {
                return null;
            }
        }
        // If all test cases pass, return the result of the substitution
        return s.substring(0, index) + rule[1] + s.substring(index + rule[0].length());
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // Read in the rules
        String[] rule = in.readLine().split(" ");
        rules[0] = rule;
        rule = in.readLine().split(" ");
        rules[1] = rule;
        rule = in.readLine().split(" ");
        rules[2] = rule;
        // Read in the number of steps, the beginning and the end states
        String[] line = in.readLine().split(" ");
        int steps = Integer.parseInt(line[0]);
        String init = line[1];
        goal = line[2];
        // Compute the result
        ArrayList<Step> s = sub(init, steps);
        // Print out the result
        // Note that the order is reversed
        for(int i = s.size() - 1; i >= 0; i --) {
            System.out.printf("%d %d %s\n", s.get(i).rule, s.get(i).pos, s.get(i).result);
        }
    }
};


