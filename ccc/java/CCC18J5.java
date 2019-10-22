import java.util.*;
import java.io.*;

public class CCC18J5 {

    // Adjacency list
    static int[][] adjList;

    public static void main(String[] args) throws IOException {
        // Create BufferedReader to read input because Scanner is slow
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        // Read in the number of pages
        int n = Integer.parseInt(input.readLine());
        // Create outer array
        adjList = new int[n][];

        for(int i = 0; i < n; i ++) {
            // Read in the pages connected to this page
            String[] line = input.readLine().split(" ");
            // Create inner array with the correct number of items
            adjList[i] = new int[Integer.parseInt(line[0])];
            // Loop over all the connected pages
            // Skip the first number
            for(int j = 0; j < line.length - 1; j ++) {
                // Subtract 1 since we want 0-based instead of 1-based indexing
                adjList[i][j] = Integer.parseInt(line[j + 1]) - 1;
            }
        }

        // This queue holds the nodes we're going to visit next
        Queue<Integer> next = new ArrayDeque<>();
        // Add 0 since it's our starting point
        next.add(0);
        // Keep track of what we already visited to prevent infinite loops
        boolean[] visited = new boolean[n];
        // Keep track of what we already added to the queue but not yet visited
        // to avoid visiting a node multiple times
        boolean[] added = new boolean[n];
        // Keep track of where we came from for each node so that we can find the shortest path later
        int[] parent = new int[n];
        while(!next.isEmpty()) {
            // Get the next node to visit
            int current = next.poll();
            // Set the node to visited
            visited[current] = true;
            // For each of its children
            for(int child : adjList[current]) {
                // If child is not visited or already added
                if(!visited[child] && !added[child]) {
                    // Add child to the queue
                    next.add(child);
                    // Mark child as added
                    added[child] = true;
                    // Set the child's parent
                    parent[child] = current;
                }
            }
        }

        // Now see if every page was visited
        boolean visitable = true;
        for(boolean b : visited) {
            // If any page was not visited then not all pages can be reached
            if(!b) {
                visitable = false;
                break;
            }
        }
        System.out.println(visitable ? "Y" : "N");

        // Find the shortest path
        int shortest = Integer.MAX_VALUE;
        for(int i = 0; i < n; i ++) {
            // See if this page is an ending page and that it is visitable
            if(adjList[i].length == 0 && visited[i]) {
                // Find the length of the path
                int current = i;
                // Note that every path is at least 1 page long
                int len = 1;
                // While we have not reached the starting page
                while(current != 0) {
                    // Go back one edge
                    current = parent[current];
                    // Increase the length
                    len ++;
                }
                // Find shortest
                shortest = Math.min(len, shortest);
            }
        }
        System.out.println(shortest);
    }
}
