import static java.lang.Math.sqrt;
import static java.lang.Thread.sleep;

import java.util.List;
import java.util.Random;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 @author Hive team
 */
public class Main {

  public static double delay(int n) {
    double acc = 0.0;
    for (int i = 0; i < n; i++) {
      acc += sqrt(n);
    }
    return acc;
  }

  public static void main(String[] args) throws Exception {

    Mapper mapper = new Mapper();
    Random randNum = new Random();

    // array of primitive ints
    int[] prim_arr = new int[50000000];
    for (int i = 0; i < 50000000; i++) {
      prim_arr[i] = randNum.nextInt();
    }

    // List of Integers
    List<Integer> arr = IntStream.range(0, 50000000)
        .boxed()
        .map((i) -> randNum.nextInt())
        .collect(Collectors.toList());

    long start = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.arr_map_seq_for(prim_arr, (int n) -> n*2);
    }
    long arr_seq_for_end = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.arr_map_par_for(prim_arr, (int n) -> n*2);
    }
    long arr_par_for_end = System.currentTimeMillis();

    double arr_seq_for_duration = (arr_seq_for_end - start) / 10000.0;
    double arr_par_for_duration = (arr_par_for_end - arr_seq_for_end) / 10000.0;
    System.out.println("Seq prim for map took: " + arr_seq_for_duration + "s");
    System.out
        .println("Par prim for map took: " + arr_par_for_duration + "s, speedup: "
            + arr_seq_for_duration / arr_par_for_duration);

    start = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_seq_for(arr, (int n) -> n*2);
    }
    long seq_for_end = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_par_for(arr, (int n) -> n*2);
    }
    long par_for_end = System.currentTimeMillis();

    double seq_for_duration = (seq_for_end - start) / 10000.0;
    double par_for_duration = (par_for_end - seq_for_end) / 10000.0;
    System.out.println("Seq for map took: " + seq_for_duration + "s");
    System.out
        .println("Par for map took: " + par_for_duration + "s, speedup: "
            + seq_for_duration / par_for_duration);

    start = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.prim_map_seq_stream(prim_arr, (int n) -> n*2);
    }
    long prim_seq_stream_end = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.prim_map_par_stream(prim_arr, (int n) -> n*2);
    }
    long prim_par_stream_end = System.currentTimeMillis();

    double prim_seq_stream_duration = (prim_seq_stream_end - start) / 10000.0;
    double prim_par_stream_duration = (prim_par_stream_end - prim_seq_stream_end) / 10000.0;
    System.out.println("Seq prim stream map took: " + prim_seq_stream_duration + "s");
    System.out
        .println("Par prim stream map took: " + prim_par_stream_duration + "s, speedup: "
            + prim_seq_stream_duration / prim_par_stream_duration);

    start = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_seq_stream(arr, (n) -> n*2);
    }
    long seq_stream_end = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_par_stream(arr, (n) -> n*2);
    }
    long par_stream_end = System.currentTimeMillis();

    double seq_stream_duration = (seq_stream_end - start) / 10000.0;
    double par_stream_duration = (par_stream_end - seq_stream_end) / 10000.0;
    System.out.println("Seq stream map took: " + seq_stream_duration + "s");
    System.out
        .println("Par stream map took: " + par_stream_duration + "s, speedup: "
            + seq_stream_duration / par_stream_duration);



  }
}
