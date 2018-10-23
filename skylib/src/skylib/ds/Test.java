package skylib.ds;

public class Test {
	public static void main(String[] args) {
		MinHeap<Integer> mh = new MinHeap<>(100);
		mh.push(7);
		System.out.println(mh.top());
		mh.push(8);
		System.out.println(mh.top());
		mh.push(4);
		System.out.println(mh.top());
		mh.push(6);
		System.out.println(mh.top());
		mh.push(2);
		System.out.println(mh.top());
		mh.push(1);
		System.out.println(mh.top());
	}
}
