import java.io.*;
import java.util.*;

public class CCC12S3 {
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(in.readLine());

        int[] readings = new int[1001];
        for(int i = 0; i < n; i ++) {
            readings[Integer.parseInt(in.readLine())] ++;
        }

        int maxFreq = 0;
        int secondMaxFreq = 0;
        for(int i = 1; i < 1001; i ++) {
            if(readings[i] >= maxFreq) {
                secondMaxFreq = maxFreq;
                maxFreq = readings[i];
            }
            else if(readings[i] >= secondMaxFreq) {
                secondMaxFreq = readings[i];
            }
        }

        List<Integer> max = new ArrayList<>();
        List<Integer> secondMax = new ArrayList<>();
        for(int i = 1; i < 1001; i ++) {
            if(readings[i] == secondMaxFreq) {
                secondMax.add(i);
            }
            else if(readings[i] == maxFreq) {
                max.add(i);
            }
        }

        if(max.size() >= 2) {
            System.out.println(Math.abs(max.get(max.size() - 1) - max.get(0)));
        }
        else {
            int maxR = max.size() > 0 ? max.get(0) : secondMax.get(secondMax.size() - 1);
            System.out.println(Math.max(
                Math.abs(maxR - secondMax.get(0)),
                Math.abs(maxR - secondMax.get(secondMax.size() - 1))
            ));
        }
    }
}
