package skylib.ds;

import java.util.List;

public class MinHeap<Type extends Comparable<Type>> implements Heap<Type> {

	private Object[] storage;
	private int size;
	
	
	
	public MinHeap(int size) {
		this.size = 0;
		this.storage = new Object[size];
	}

	@SuppressWarnings("unchecked")
	@Override
	public void push(Type element) {
		storage[size] = element;
		int index = size;
		while(index > 0){
			int parentIndex = (index-1)>>1;
			if (((Type)storage[index]).compareTo((Type) storage[parentIndex]) < 0){
				Object temp;
				temp = storage[index];
				storage[index] = storage[parentIndex];
				storage[parentIndex] = temp;
			}
			else break;
			index = parentIndex;
		}
		size++;
	}
	
	@SuppressWarnings("unchecked")
	@Override
	public Type pop() {
		if (isEmpty())
			return null;
		Type min = (Type) storage[0];
		storage[0] = storage[size-1]; 
		int index = 0;
		while(index < (size-1)) {
			int childIndex = ((index+1)<<1) - 1;
			if (((Type)storage[index]).compareTo((Type) storage[childIndex]) > 0
					|| (childIndex + 1 < size && ((Type)storage[index]).compareTo((Type) storage[childIndex + 1]) > 0)){
				
				if (childIndex + 1 < size && ((Type)storage[childIndex]).compareTo((Type) storage[childIndex + 1]) > 0)
					childIndex = childIndex + 1;
				
				Object temp;
				temp = storage[childIndex];
				storage[childIndex] = storage[index];
				storage[index] = temp;
				index = childIndex;
			} else
				break;
		}
		size--;
		return min;
	}

	@SuppressWarnings("unchecked")
	@Override
	public Type top() {
		return (Type) storage[0];
	}

	@Override
	public int size() {
		return size;
	}

	@Override
	public boolean isEmpty() {
		return size == 0;
	}
}