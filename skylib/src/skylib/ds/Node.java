package skylib.ds;

public class Node<Type> {
	
	private Node<Type> next;
	private Node<Type> prev;
	private Type element;
	
	
	
	/**
	 * @param next
	 * @param prev
	 * @param element
	 */
	public Node(Type element) {
		this.next = null;
		this.prev = null;
		this.element = element;
	}
	/** @return the next */
	public Node<Type> getNext() {
		return next;
	}
	/** @param next the next to set */
	public void setNext(Node<Type> next) {
		this.next = next;
	}
	/** @return the prev */
	public Node<Type> getPrev() {
		return prev;
	}
	/** @param prev the prev to set */
	public void setPrev(Node<Type> prev) {
		this.prev = prev;
	}
	/** @return the element */
	public Type getElement() {
		return element;
	}
	/** @param element the element to set */
	public void setElement(Type element) {
		this.element = element;
	}
	
	
}
