package skylib.classics;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import skylib.ds.Heap;
import skylib.ds.MinHeap;

/**
 * You are given N numbers and need to make all numbers to be >= K. For this you need to 
 * repeatedly add two smallest numbers from given N numbers like new_number = 2* smallest_number + second_smallest_number. 
 * Need to repeat this until all numbers are greater than or equal to K. Implement this in O(nlogn) or better.
 * @author Abhay
 *
 */
public class Six {
	
	private static List<Integer> minify(int k, List<Integer> list) {
		Heap<Integer> mh = new MinHeap<>(list.size());
		for (int listItem: list)
			mh.push(listItem);
		while (mh.size() > 1 && mh.top() < k){
			int a = mh.pop();
			int b = mh.pop();
			mh.push(2*a + b);
		}
		
		if (mh.top() < k)
			return null;
		
		List<Integer> result = new LinkedList<>();
		while (!mh.isEmpty())
			result.add(mh.pop());
		
		return result;
	}
	
	public static void main(String[] args) {
		System.out.println(minify(100, Arrays.asList(new Integer[] {3,8,2,9,4,8,4,9})));
		System.out.println(minify(10, Arrays.asList(new Integer[] {3,8,2,9,4,8,4,9})));
		System.out.println(minify(200, Arrays.asList(new Integer[] {3,8,2,9,4,8,4,9})));
		System.out.println(minify(50, Arrays.asList(new Integer[] {3,8,2,9,4,8,4,9})));
	}
}
