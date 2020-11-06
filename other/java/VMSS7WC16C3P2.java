import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

public class VMSS7WC16C3P2 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String[] line1 = in.readLine().split(" ");
        int n = Integer.parseInt(line1[0]);
        int m = Integer.parseInt(line1[1]);
        // Subtract 1 to use zero-based indexing internally
        int a = Integer.parseInt(line1[2]) - 1;
        int b = Integer.parseInt(line1[3]) - 1;

        // Declare and initialize adjacency list
        List<List<Integer>> adjList = new ArrayList<>();
        for (int i = 0; i < n; i ++) {
            adjList.add(new ArrayList<>());
        }
        // Fill in adjacency list
        for (int i = 0; i < m; i ++) {
            String[] line = in.readLine().split(" ");
            // Subtract 1 for zero-based indexing
            int x = Integer.parseInt(line[0]) - 1;
            int y = Integer.parseInt(line[1]) - 1;
            adjList.get(x).add(y);
            adjList.get(y).add(x);
        }

        Deque<Integer> toVisit = new ArrayDeque<>();
        toVisit.add(a);
        // Since our nodes are a range of integers, we can simply use an array of booleans
        // this saves a considerable amount of space and time
        boolean[] visited = new boolean[n];
        while (!toVisit.isEmpty()) {
            int next = toVisit.poll();
            // If found, print result and exit early
            if (next == b) {
                System.out.println("GO SHAHIR!");
                return;
            }
            // Add each connected house if it's not already visited
            for (int house : adjList.get(next)) {
                if (!visited[house]) {
                    visited[house] = true;
                    toVisit.add(house);
                }
            }
        }
        System.out.println("NO SHAHIR!");
    }
}