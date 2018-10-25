package skylib.ds;
import java.util.List;

interface SearchTree<Type extends Comparable<Type>> {
	void insert(Type element);
	boolean remove(Type element);
	int size();
	boolean exists(Type element);
	List<Type> inOrder();
	List<Type> postOrder();
	List<Type> preOrder();
}