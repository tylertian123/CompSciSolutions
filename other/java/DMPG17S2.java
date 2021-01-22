import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class DMPG17S2 {

    /**
     * Make n subsets containing the numbers 0 to n - 1.
     * 
     * @param n Number of subsets to make
     * @return Disjoint sets represented as an array
     */
    static int[] makeSets(int n) {
        int[] ds = new int[n];
        for (int i = 0; i < n; i ++) {
            ds[i] = i;
        }
        return ds;
    }

    /**
     * Find the representative element of x's subset.
     * 
     * @param set All sets
     * @param x The element to find
     * @return The representative element
     */
    static int find(int[] set, int x) {
        if (set[x] != x) {
            set[x] = find(set, set[x]);
        }
        return set[x];
    }

    /**
     * Merge the subsets of x and y.
     * 
     * @param set All sets
     * @param x First subset
     * @param y Second subset
     */
    static void union(int[] set, int x, int y) {
        set[find(set, y)] = find(set, x);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(reader.readLine());
        int n = Integer.parseInt(st.nextToken());
        int q = Integer.parseInt(st.nextToken());
        int[] sets = makeSets(n);
        for (int i = 0; i < q; i ++) {
            st = new StringTokenizer(reader.readLine());
            String op = st.nextToken();
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            if (op.equals("A")) {
                union(sets, a - 1, b - 1);
            }
            else {
                System.out.println(find(sets, a - 1) == find(sets, b - 1) ? "Y" : "N");
            }
        }
    }
}