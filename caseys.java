import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Caseys {
    
    public static class State implements Cloneable {
        public int[] counts;
        
        @Override
        public int hashCode() {
            return Arrays.hashCode(counts);
        }
        @Override
        public boolean equals(Object other) {
            if(!(other instanceof State)) {
                return false;
            }
            State otherState = (State) other;
            return Arrays.equals(otherState.counts, counts);
        }
        @Override
        public State clone() {
            State s = new State();
            s.counts = Arrays.copyOf(counts, counts.length);
            return s;
        }
    }

    public static class MenuItem {
        public String name;
        public int price;
    }

    public static MenuItem[] menu;
    public static ArrayList<State> solutions = new ArrayList<State>();
    public static Set<State> solved = new HashSet<>();

    public static void solve(State state, int money) {
        if(solved.contains(state)) {
            return;
        }
        if(money == 0) {
            State copy = state.clone();
            solved.add(copy);
            solutions.add(copy);
        }
        else {
            for(int i = 0; i < menu.length; i ++) {
                if(menu[i].price <= money) {
                    state.counts[i] ++;
                    solve(state, money - menu[i].price);
                    state.counts[i] --;
                }
            }
        }
        State copy = state.clone();
        solved.add(copy);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        int goal = Integer.parseInt(in.readLine());
        int itemCount = Integer.parseInt(in.readLine());
        menu = new MenuItem[itemCount];

        for(int i = 0; i < itemCount; i ++) {
            menu[i] = new MenuItem();
            String[] input = in.readLine().split(" ");
            menu[i].price = Integer.parseInt(input[1]);
            menu[i].name = input[0];
        }

        int[] stateArray = new int[itemCount];
        State state = new State();
        state.counts = stateArray;
        solve(state, goal);

        if(solutions.size() > 0) {
            for(State solution : solutions) {
                System.out.println("------------------");
                for(int i = 0; i < solution.counts.length; i ++) {
                    if(solution.counts[i] > 0) {
                        System.out.printf("%s\tx%d\n", menu[i].name, solution.counts[i]);
                    }
                }
            }
            System.out.println("------------------");
        }
        else {
            System.out.println("How was your dinner?");
        }
    }
}
