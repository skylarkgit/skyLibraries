package skylib.ds;

public class PriorityQueue<Type extends Comparable<Type>> {
	
	private MinHeap<PriorityElement<Type>> heap;
	private int size;
	
	public PriorityQueue(int size) {
		heap = new MinHeap<PriorityElement<Type>>(size);
	}

	public PriorityQueue<Type> enqueue(int priority, Type element) {
		heap.push(new PriorityElement<Type>(priority, element));
		size++;
		return this;
	}

	public Type dequeue() {
		if (!isEmpty()){
			Type element = heap.pop().getElement();
			size--;
			return element;
		}
		return null;
	}

	public boolean isEmpty() {
		return size == 0;
	}

	public int size() {
		return size;
	}

	public Type peek() {
		if (!isEmpty())
			return heap.top().getElement();
		return null;
	}
	
}
