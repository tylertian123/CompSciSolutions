import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class CCC00S4 {

    static int[] clubs;

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        int distance = Integer.parseInt(reader.readLine());
        int numClubs = Integer.parseInt(reader.readLine());
        // Read in all the clubs
        clubs = new int[numClubs];
        for(int i = 0; i < numClubs; i ++) {
            clubs[i] = Integer.parseInt(reader.readLine());
        }

        int result = fewestStrokes(distance);

        System.out.println(result == Integer.MAX_VALUE ? "Roberta acknowledges defeat." 
                : "Roberta wins in " + result + " strokes.");
    }

    // This map keeps track of all the distances for which the fewest strokes is known
    // This is so that we can reuse our previous results
    static Map<Integer, Integer> known = new HashMap<>();

    static int fewestStrokes(int distance) {
        // Base case
        if(distance == 0) {
            return 0;
        }

        // Check if we encountered this distance before
        if(known.containsKey(distance)) {
            return known.get(distance);
        }

        // Another base case
        // Check if any of the clubs have the exact same distance as requested
        for(int club : clubs) {
            if(club == distance) {
                return 1;
            }
        }

        // No matches found - break up the problem into sub-problems
        // Try out every club
        int min = Integer.MAX_VALUE;
        for(int club : clubs) {
            // Make sure the club hits a distance less than the distance left
            if(club <= distance) {
                // Recurse with the new distance after hitting with this club
                int result = fewestStrokes(distance - club);
                min = Math.min(result, min);
            }
        }

        // Now min should hold the fewest strokes possible after trying out one club
        // or Integer.MAX_VALUE if it's not possible
        // Add one to the result since we used a stroke above
        // But if it's not possible then don't add 1, as that would overflow the int and make it negative
        min = min == Integer.MAX_VALUE ? min : min + 1;
        // First put the result into the map for future use
        known.put(distance, min);
        return min;
    }
}
