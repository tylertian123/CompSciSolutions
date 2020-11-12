import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CCC17J3 {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        int startX = Integer.parseInt(line[0]);
        int startY = Integer.parseInt(line[1]);
        line = reader.readLine().split(" ");
        int endX = Integer.parseInt(line[0]);
        int endY = Integer.parseInt(line[1]);
        int t = Integer.parseInt(reader.readLine());

        int total = Math.abs(startX - endX) + Math.abs(startY - endY);
        if (t < total) {
            System.out.println("N");
        }
        else {
            if ((t - total) % 2 == 0) {
                System.out.println("Y");
            }
            else {
                System.out.println("N");
            }
        }
    }
}