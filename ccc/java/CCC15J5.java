import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

/**
 * Java solution for CCC '15 J5 - Pi-day
 */
public class CCC15J5 {

    static Map<Integer, Integer> known = new HashMap<>();

    /**
     * Calculate the solution.
     * 
     * @param n The number of pieces left to distribute
     * @param k The number of people left in line
     * @param m The minimum number of pieces to give out
     * @return The solution
     */
    static int pie(int n, int k, int m) {
        // Base case #0: Distribution is not possible
        if (n / k < m) {
            return 0;
        }
        // Other base cases, mentioned in the problem description
        if (k == 1 || k == n) {
            return 1;
        }
        // Combine into 32-bit integer for better hashing
        int key = n << 16 | k << 8 | m;
        if (known.containsKey(key)) {
            return known.get(key);
        }
        // Try every possible number of pieces to give out
        int sum = 0;
        for (int p = m; p < n + 1; p ++) {
            // Give out p pieces
            // (n - p) pieces still left, (k - 1) people still left, and a min of p must be given to the next person
            int ways = pie(n - p, k - 1, p);
            // If distribution is no longer possible, we gave out too many pieces
            // Skip trying the rest
            if (ways == 0) {
                break;
            }
            sum += ways;
        }
        known.put(key, sum);
        return sum;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println(pie(Integer.parseInt(reader.readLine()), Integer.parseInt(reader.readLine()), 1));
    }
}