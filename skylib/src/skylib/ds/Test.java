package skylib.ds;

import java.util.Arrays;

public class Test {
	public static void main(String[] args) {
		BinarySearchTree<Integer> bst = new BinarySearchTree<Integer>();
		bst.insert(5);
		bst.insert(10);
		bst.insert(25);
		bst.insert(9);
		bst.insert(3);
		bst.insert(4);
		bst.insert(-1);
		bst.insert(23423);
		bst.insert(8);
		System.out.println(bst.inOrder());

		bst.remove(-1);
		bst.remove(-1);
		bst.remove(23423);
		bst.remove(8);
		System.out.println(bst.inOrder());
		bst.remove(5);
		System.out.println(bst.inOrder());
		bst.remove(10);
		System.out.println(bst.inOrder());
		bst.remove(25);
		System.out.println(bst.inOrder());
		bst.remove(3);
		System.out.println(bst.inOrder());
		bst.remove(4);
		System.out.println(bst.inOrder());
		bst.remove(9);
		System.out.println(bst.inOrder());
		bst.remove(8);
		System.out.println(bst.inOrder());
		
		System.out.println("Graph");
		Graph graph = new Graph(5);
		graph.addEdge(0, 1, 0);
		graph.addEdge(0, 2, 0);
		graph.addEdge(0, 3, 0);
		graph.addEdge(0, 4, 0);
		graph.addEdge(2, 4, 0);
		System.out.println(graph.bfs(0));
		System.out.println(graph.dfs(0));
		
		MinHeap<Integer> mh = new MinHeap<>(15);
		mh.push(7);
		System.out.println(mh.top());
		mh.push(8);
		System.out.println(mh.top());
		mh.push(4);
		System.out.println(mh.top());
		mh.push(6);
		System.out.println(mh.top());
		mh.push(2);
		System.out.println(mh.top());
		mh.push(1);
		System.out.println(mh.top());
		
		System.out.println(mh.pop());
		
		System.out.println(mh.pop());
		
		System.out.println(mh.pop());
		
		System.out.println(mh.pop());
		
		System.out.println(mh.pop());
		
		System.out.println(mh.pop());
		
		System.out.println(mh.pop());
		
		System.out.println("Queue");
		Queue<Integer> q = new LinkedQueue<>();
		q.enqueue(1)
		.enqueue(2)
		.enqueue(3)
		.enqueue(4)
		.enqueue(5);
		
		System.out.println(q.dequeue());
		System.out.println(q.dequeue());
		System.out.println(q.dequeue());
		q.enqueue(1)
		.enqueue(2)
		.enqueue(3)
		.enqueue(4)
		.enqueue(5);
		System.out.println(q.dequeue());

		System.out.println(q.dequeue());
		System.out.println(q.dequeue());
		System.out.println(q.dequeue());

		System.out.println(q.dequeue());
		System.out.println(q.dequeue());
		System.out.println(q.dequeue());

		System.out.println(q.dequeue());
		System.out.println(q.dequeue());
		System.out.println(q.dequeue());
		
		PriorityQueue<Integer> pq = new PriorityQueue<Integer>(100);
		pq.enqueue(10, 10);
		System.out.println(pq.peek());
		pq.enqueue(0, 0);
		System.out.println(pq.peek());
		pq.enqueue(20, 20);
		System.out.println(pq.peek());
		pq.enqueue(5, 5);
		System.out.println(pq.peek());
		pq.enqueue(6, 6);
		System.out.println(pq.peek());
		pq.enqueue(-1, 6);
		System.out.println(pq.peek());

		System.out.println(pq.dequeue());
		System.out.println("size=" + pq.size());
		pq.enqueue(-1, 5);
		System.out.println(pq.peek());
		
		System.out.println(pq.dequeue());
		System.out.println("size=" + pq.size());
		System.out.println(pq.dequeue());
		System.out.println("size=" + pq.size());
		System.out.println(pq.dequeue());
		System.out.println("size=" + pq.size());
		System.out.println(pq.dequeue());
		System.out.println("size=" + pq.size());
		System.out.println(pq.dequeue());
		System.out.println("size=" + pq.size());
		System.out.println(pq.dequeue());
		System.out.println("size=" + pq.size());
		System.out.println(pq.dequeue());
		System.out.println("size=" + pq.size());
		
		graph = new Graph(5);
		graph.addEdge(0, 1, 1);
		graph.addEdge(0, 2, 1);
		graph.addEdge(0, 3, 2);
		graph.addEdge(0, 4, 5);
		graph.addEdge(2, 4, 1);
		
		System.out.println(graph.dijkstra(0));
		
	}
}
