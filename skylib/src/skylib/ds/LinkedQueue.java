package skylib.ds;

public class LinkedQueue<Type> implements Queue<Type>{

	private Node<Type> head;
	private Node<Type> tail;
	private int size;
		
	@Override
	public Queue<Type> enqueue(Type element) {
		Node<Type> newNode = new Node<>(element);
		
		if (tail != null)
			tail.setNext(newNode);
		else
			head = newNode;
		
		tail = newNode;
		size++;
		return this;
	}

	@Override
	public Type dequeue() {
		if (!isEmpty()){
			Type element = head.getElement();
			size--;
			head = head.getNext();
			return element;
		}
		return null;
	}

	@Override
	public boolean isEmpty() {
		return size == 0;
	}

	@Override
	public int size() {
		return size;
	}

	@Override
	public Type peek() {
		if (!isEmpty())
			return head.getElement();
		return null;
	}
}
