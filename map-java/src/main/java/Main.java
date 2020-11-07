import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 @author Hive team
 */
public class Main {

  public static void main(String [] args) {

      Mapper mapper = new Mapper();
      Random randNum = new Random();

      List<Integer> arr = IntStream.range(0, 200000000)
          .boxed()
          .map((i) -> randNum.nextInt())
          .collect(Collectors.toList());

      long start = System.currentTimeMillis();
      for (int i = 0; i < 10; i++) {
        mapper.map_seq(arr, (Integer j) -> j*2);
      }
      long seq_end = System.currentTimeMillis();
      for (int i = 0; i < 10; i++) {
        mapper.map_par(arr, (Integer j) -> j*2);
      }
      long par_end = System.currentTimeMillis();

      double seq_duration = (seq_end - start)/10000.0;
      double par_duration = (par_end - seq_end)/10000.0;
      System.out.println("Seq map took: " + seq_duration + "s");
      System.out.println("Par map took: " + par_duration + "s, speedup: " + seq_duration/par_duration);

    }
}
