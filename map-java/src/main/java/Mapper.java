import java.util.List;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;

/**
 @author Hive team
 */
public class Mapper {

  public List<Integer> map_seq(List<Integer> arr, UnaryOperator<Integer> foo) {
    return arr.stream().map(foo).collect(Collectors.toList());
  }

  public List<Integer> map_par(List<Integer> arr, UnaryOperator<Integer> foo) {
    return arr.stream().parallel().map(foo).collect(Collectors.toList());
  }


}
