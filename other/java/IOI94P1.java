import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class IOI94P1 {

    static int[][] triangle;
    static int[][] sums;

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Read in the triangle
        int n = Integer.parseInt(reader.readLine());
        // Triangle and sums are 2d arrays
        triangle = new int[n][];
        sums = new int[n][];
        for(int i = 0; i < n; i ++) {
            // Create each row
            triangle[i] = new int[i + 1];
            sums[i] = new int[i + 1];
            String[] line = reader.readLine().split(" ");
            // Convert every string to an int
            for(int j = 0; j < line.length; j ++) {
                triangle[i][j] = Integer.parseInt(line[j]);
                // Fill in sums with -1 to indicate they haven't been generated yet
                // As all the numbers are 0 or greater
                sums[i][j] = -1;
            }
        }

        // Just call triangleSum for answer
        System.out.println(triangleSum(0, 0));
    }
    
    // This does all the hard work
    // Takes in a row of the triangle and a column (0 based indexes)
    static int triangleSum(int row, int col) {
        // First check if the value has already been generated
        if(sums[row][col] != -1) {
            return sums[row][col];
        }
        int result;
        // Base case: bottom row
        if(row == triangle.length - 1) {
            // Result is just the number in this location
            result = triangle[row][col];
        }
        else {
            // Otherwise take the left and right sub-triangles' sums
            int leftSum = triangleSum(row + 1, col);
            int rightSum = triangleSum(row + 1, col + 1);
            result = Math.max(leftSum, rightSum) + triangle[row][col];
        }
        
        // First store the result away for reuse
        sums[row][col] = result;
        // Return the result
        return result;
    }
}
