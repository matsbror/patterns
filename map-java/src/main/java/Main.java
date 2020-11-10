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

  public static void main(String[] args) {

    Mapper mapper = new Mapper();
    Random randNum = new Random();

    int[] arrr = new int[50000000];
    for (int i = 0; i < 50000000; i++) {
      arrr[i] = randNum.nextInt();
    }

    List<Integer> arr = IntStream.range(0, 50000000)
        .boxed()
        .map((i) -> randNum.nextInt())
        .collect(Collectors.toList());

    UnaryOperator<Integer> foo = (Integer n) -> {
      return n * 2;
    };

    long start = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_seq_for(arr, foo);
    }
    long arr_seq_for_end = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_par_for(arr, foo);
    }
    long arr_par_for_end = System.currentTimeMillis();

    double arr_seq_for_duration = (arr_seq_for_end - start) / 10000.0;
    double arr_par_for_duration = (arr_par_for_end - arr_seq_for_end) / 10000.0;
    System.out.println("Seq for map took: " + arr_seq_for_duration + "s");
    System.out
        .println("Par for map took: " + arr_par_for_duration + "s, speedup: "
            + arr_seq_for_duration / arr_par_for_duration);

    start = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_seq_for(arr, foo);
    }
    long seq_for_end = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_par_for(arr, foo);
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
      mapper.map_seq_stream(arr, foo);
    }
    long seq_stream_end = System.currentTimeMillis();
    for (int i = 0; i < 10; i++) {
      mapper.map_par_stream(arr, foo);
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
