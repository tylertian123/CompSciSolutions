import java.io.*;
import java.util.*;

public class Main {
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(in.readLine());

        String[] contestants = new String[n];

        for(int i = 0; i < n; i ++) {
            contestants[i] = in.readLine();
        }

        Map<String, Integer> ran = new HashMap<>();

        for(int i = 0; i < n - 1; i ++) {
            String s = in.readLine();
            ran.put(s, ran.getOrDefault(s, 0) + 1);
        }

        for(String name : contestants) {
            if(ran.containsKey(name)) {
                if(ran.get(name) == 0) {
                    System.out.println(name);
                    System.exit(0);
                }
                else {
                    ran.put(name, ran.get(name) - 1);
                }
            }
            else {
                System.out.println(name);
                System.exit(0);
            }
        }
        System.out.print("ERROR!");
    }
}
