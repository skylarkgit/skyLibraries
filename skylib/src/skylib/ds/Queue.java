package skylib.ds;

public interface Queue<Type> {
	Queue<Type> enqueue(Type element);
	Type dequeue();
	Type peek();
	boolean isEmpty();
	int size();
}
