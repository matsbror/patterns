import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;

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

  public List<Integer> map_par_stream(List<Integer> arr, UnaryOperator<Integer> foo) {
    try {
      return pool.submit(() -> arr.stream().parallel().map(foo).collect(Collectors.toList())).get();
    } catch (Exception e) {
      System.out.println(e.getMessage());
      e.printStackTrace();
      return new ArrayList<Integer>();
    }
  }

  public List<Integer> map_seq_for(List<Integer> arr, UnaryOperator<Integer> foo) {
    for (int i = 0; i < arr.size(); i++) {
      arr.set(i, foo.apply(arr.get(i)));
    }
    return arr;
  }

  public List<Integer> map_par_for(List<Integer> arr, UnaryOperator<Integer> foo) {
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
    UnaryOperator<Integer> foo;

    public LocalMap(List<Integer> arr, int procs, int p, UnaryOperator<Integer> foo) {
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
        arr.set(i, foo.apply(arr.get(i)));
      }
    }
  }

}
