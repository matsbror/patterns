package com.embe;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.junit.Test;

/**
 @author Hive team
 */
class MainTest {

  @Test
  void map_seq() {

    Mapper mapper = new Mapper();

    List<Integer> arr1 = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6));
    List<Integer> arr2 = new ArrayList<>(Arrays.asList(2, 4, 6, 8, 10, 12));

    List<Integer> arr = mapper.map_seq(arr1, (Integer i) -> i*2);

    assert(arr.equals(arr2));


  }

  @Test
  void map_par() {

    Mapper mapper = new Mapper();

    List<Integer> arr1 = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6));
    List<Integer> arr2 = new ArrayList<>(Arrays.asList(2, 4, 6, 8, 10, 12));

    List<Integer> arr = mapper.map_par(arr1, (Integer i) -> i*2);

    assert(arr.equals(arr2));
  }
}