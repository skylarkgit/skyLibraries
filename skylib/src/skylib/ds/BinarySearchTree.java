package skylib.ds;

import java.util.LinkedList;
import java.util.List;

class BinarySearchTree<Type extends Comparable<Type>> implements
		SearchTree<Type> {

	private int size;
	private BinaryNode<Type> root;

	public BinarySearchTree() {
		size = 0;
		root = null;
	}

	@Override
	public void insert(Type element) {
		root = insert(element, root);
		size++;
	}

	private BinaryNode<Type> insert(Type element, BinaryNode<Type> node) {
		if (node == null)
			return new BinaryNode<Type>(element);

		if (node.getElement().compareTo(element) > 0)
			node.setLeft(insert(element, node.getLeft()));
		else
			node.setRight(insert(element, node.getRight()));

		return node;
	}

	@Override
	public boolean remove(Type element) {
		root = remove(element, root);
		return false;
	}

	public BinaryNode<Type> remove(Type element, BinaryNode<Type> node) {
		if (node == null)
			return null;

		if (node.getElement().compareTo(element) == 0) {
			BinaryNode<Type> successor = removeSuccessor(node.getRight());
			if (successor == null)
				return node.getLeft();

			if (successor == node.getRight())
				node.setRight(successor.getRight());

			node.setElement(successor.getElement());
		} else if (node.getElement().compareTo(element) > 0)
			node.setLeft(remove(element, node.getLeft()));
		else
			node.setRight(remove(element, node.getRight()));

		return node;
	}

	private BinaryNode<Type> removeSuccessor(BinaryNode<Type> node) {

		if (node == null || node.getLeft() == null)
			return node;

		BinaryNode<Type> successor = removeSuccessor(node.getLeft());

		if (successor == node.getLeft())
			node.setLeft(successor.getRight());

		return successor;

	}

	@Override
	public int size() {
		return size;
	}

	@Override
	public boolean exists(Type element) {
		return exists(element, root);
	}

	private boolean exists(Type element, BinaryNode<Type> node) {
		if (node == null)
			return false;

		if (node.getElement().compareTo(element) == 0)
			return true;

		if (node.getElement().compareTo(element) > 0)
			return exists(element, node.getLeft());
		else
			return exists(element, node.getRight());
	}

	@Override
	public List<Type> inOrder() {
		List<Type> list = new LinkedList<Type>();
		inOrder(root, list);
		return list;
	}

	private void inOrder(BinaryNode<Type> node, List<Type> list) {
		if (node == null)
			return;
		inOrder(node.getLeft(), list);
		list.add(node.getElement());
		inOrder(node.getRight(), list);
	}

	@Override
	public List<Type> postOrder() {
		List<Type> list = new LinkedList<Type>();
		postOrder(root, list);
		return list;
	}

	private void postOrder(BinaryNode<Type> node, List<Type> list) {
		if (node == null)
			return;
		inOrder(node.getLeft(), list);
		inOrder(node.getRight(), list);
		list.add(node.getElement());
	}

	@Override
	public List<Type> preOrder() {
		List<Type> list = new LinkedList<Type>();
		preOrder(root, list);
		return list;
	}

	private void preOrder(BinaryNode<Type> node, List<Type> list) {
		if (node == null)
			return;
		list.add(node.getElement());
		inOrder(node.getLeft(), list);
		inOrder(node.getRight(), list);
	}
}