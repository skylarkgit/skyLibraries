package skylib.ds;

public class BinaryNode<Type> {

	private BinaryNode<Type> left;
	private BinaryNode<Type> right;
	private Type element;

	public BinaryNode(Type element) {
		this.element = element;
	}
	public BinaryNode<Type> getLeft() {
		return left;
	}
	public void setLeft(BinaryNode<Type> left) {
		this.left = left;
	}
	public BinaryNode<Type> getRight() {
		return right;
	}
	public void setRight(BinaryNode<Type> right) {
		this.right = right;
	}
	public Type getElement() {
		return element;
	}
	public void setElement(Type element) {
		this.element = element;
	}
	
	
}