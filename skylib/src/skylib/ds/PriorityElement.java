package skylib.ds;

public class PriorityElement<Type extends Comparable<Type>> implements Comparable<PriorityElement<Type>> {
	
	private int priority;
	private Type element;
	
	
	
	/**
	 * @param priority
	 * @param element
	 */
	public PriorityElement(int priority, Type element) {
		this.priority = priority;
		this.element = element;
	}

	/** @return the priority */
	public int getPriority() {
		return priority;
	}
	
	/** @param priority the priority to set */
	public void setPriority(int priority) {
		this.priority = priority;
	}
	
	/** @return the element */
	public Type getElement() {
		return element;
	}
	
	/** @param element the element to set */
	public void setElement(Type element) {
		this.element = element;
	}

	@Override
	public int compareTo(PriorityElement<Type> node) {
		if (((Integer)priority).compareTo(node.priority) == 0)
			return element.compareTo(node.element);
		return ((Integer)priority).compareTo(node.priority);
	}
}
