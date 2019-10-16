import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CCC16J2 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        
        int[][] square = new int[4][4];
        for(int i = 0; i < 4; i ++) {
            String[] nums = in.readLine().split(" ");
            for(int j = 0; j < 4; j ++) {
                square[i][j] = Integer.parseInt(nums[j]);
            }
        }
        
        int sum = 0;
        for(int i = 0; i < 4; i ++) {
            sum += square[0][i];
        }
        
        for(int i = 1; i < 4; i ++) {
            int rowSum = 0;
            for(int j = 0; j < 4; j ++) {
                rowSum += square[i][j];
            }
            
            if(rowSum != sum) {
                System.out.println("not magic");
                System.exit(0);
            }
        }
        
        for(int i = 0; i < 4; i ++) {
            int colSum = 0;
            for(int j = 0; j < 4; j ++) {
                colSum += square[j][i];
            }
            
            if(colSum != sum) {
                System.out.println("not magic");
                System.exit(0);
            }
        }
        
        System.out.println("magic");
    }
}
