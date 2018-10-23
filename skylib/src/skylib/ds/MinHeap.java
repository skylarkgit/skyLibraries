package skylib.ds;

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
		Type min = (Type) storage[0];
		int index = 0;
		while(index<(size-1)) {
			int childIndex = ((index+1)>>1) - 1;
			if (((Type)storage[index]).compareTo((Type) storage[childIndex]) > 0
					|| ((Type)storage[index]).compareTo((Type) storage[childIndex + 1]) > 0){
				if (((Type)storage[childIndex]).compareTo((Type) storage[childIndex + 1]) < 0)
					childIndex = childIndex;
				else
					childIndex = childIndex + 1;
				
				Object temp;
				temp = storage[childIndex];
				storage[index] = storage[childIndex];
				storage[childIndex] = temp;
				index = childIndex;
			}
		}
		
		return min;
		return null;
	}

	@Override
	public Type top() {
		return (Type) storage[0];
	}

	@Override
	public int size() {
		return size;
	}

}