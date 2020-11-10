import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.function.IntConsumer;
import java.util.function.IntUnaryOperator;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 @author Hive team
 */
public class Mapper {

  ForkJoinPool pool = new ForkJoinPool(4);

  Mapper() {

  }

  public List<Integer> map_seq_stream(List<Integer> arr, UnaryOperator<Integer> foo) {
    return arr.stream().map(foo).collect(Collectors.toList());
  }

  public List<Integer> map_par_stream(List<Integer> arr, UnaryOperator<Integer> foo) throws Exception {
    return pool.submit(() -> arr.stream().parallel().map(foo).collect(Collectors.toList())).get();
  }

  public int[] prim_map_seq_stream(int[] arr, IntUnaryOperator foo) {
    return IntStream.of(arr).map(foo).toArray();
  }

  public int[] prim_map_par_stream(int[] arr, IntUnaryOperator foo) throws Exception {
    return pool.submit(() -> IntStream.of(arr).parallel().map(foo).toArray()).get();
  }

  public List<Integer> map_seq_for(List<Integer> arr, IntUnaryOperator foo) {
    for (int i = 0; i < arr.size(); i++) {
      arr.set(i, foo.applyAsInt(arr.get(i)));
    }
    return arr;
  }

  public List<Integer> map_par_for(List<Integer> arr, IntUnaryOperator foo) {
    int procs = pool.getParallelism();
    List<RecursiveAction> tasks = new ArrayList<>();
    for (int p = 0; p < procs; p++) {
      LocalMap localMap = new LocalMap(arr, procs, p, foo);
      tasks.add(localMap);
      pool.execute(localMap);
    }

    for (RecursiveAction t : tasks) {
      t.join();
    }

    return arr;
  }


  private static class LocalMap extends RecursiveAction {

    List<Integer> arr;
    int procs;
    int p;
    IntUnaryOperator foo;

    public LocalMap(List<Integer> arr, int procs, int p, IntUnaryOperator foo) {
      this.arr = arr;
      this.procs = procs;
      this.p = p;
      this.foo = foo;
    }

    @Override
    protected void compute() {
      int from = p * arr.size() / procs;
      int to = p == procs - 1 ? arr.size() : (p + 1) * arr.size() / procs;
      for (int i = from; i < to; i++) {
        arr.set(i, foo.applyAsInt(arr.get(i)));
      }
    }
  }

  public int[] arr_map_seq_for(int[] arr, IntUnaryOperator foo) {
    for (int i = 0; i < arr.length; i++) {
      arr[i] = foo.applyAsInt(arr[i]);
    }
    return arr;
  }

  public int[] arr_map_par_for(int[] arr, IntUnaryOperator foo) {
    int procs = pool.getParallelism();
    List<RecursiveAction> tasks = new ArrayList<>();
    for (int p = 0; p < procs; p++) {
      ArrLocalMap localMap = new ArrLocalMap(arr, procs, p, foo);
      tasks.add(localMap);
      pool.execute(localMap);
    }

    for (RecursiveAction t : tasks) {
      t.join();
    }

    return arr;
  }


  private static class ArrLocalMap extends RecursiveAction {

    int[] arr;
    int procs;
    int p;
    IntUnaryOperator foo;

    public ArrLocalMap(int[] arr, int procs, int p, IntUnaryOperator foo) {
      this.arr = arr;
      this.procs = procs;
      this.p = p;
      this.foo = foo;
    }

    @Override
    protected void compute() {
      int from = p * arr.length / procs;
      int to = p == procs - 1 ? arr.length : (p + 1) * arr.length / procs;
      for (int i = from; i < to; i++) {
        arr[i] = foo.applyAsInt(arr[i]);
      }
    }
  }


}
