package skylib.ds;

public interface Heap<Type extends Comparable<Type>> {

	void push(Type element);
	Type pop();
	Type top();
	int size();

}