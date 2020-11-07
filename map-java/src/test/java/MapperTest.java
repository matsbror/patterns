import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.junit.Test;

/**
 @author Hive team
 */
public class MapperTest {

  @Test
  public void map_seq() {
    List<Integer> arr1 = new ArrayList<Integer>(Arrays.asList(1, 2, 3, 4, 5, 6));
    List<Integer> arr2 = new ArrayList<Integer>(Arrays.asList(2, 4, 6, 8, 10, 12));

    Mapper mapper = new Mapper();

    List<Integer> arr = mapper.map_seq(arr1, (i) -> i * 2);

    assert (arr.equals(arr2));
  }

  @Test
  public void map_par() {
    List<Integer> arr1 = new ArrayList<Integer>(Arrays.asList(1, 2, 3, 4, 5, 6));
    List<Integer> arr2 = new ArrayList<Integer>(Arrays.asList(2, 4, 6, 8, 10, 12));

    Mapper mapper = new Mapper();

    List<Integer> arr = mapper.map_par(arr1, (i) -> i * 2);

    assert (arr.equals(arr2));
  }
}