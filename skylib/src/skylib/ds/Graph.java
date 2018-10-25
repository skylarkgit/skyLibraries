package skylib.ds;
import java.util.LinkedList;
import java.util.List;
public class Graph {
	
	private List<GraphNode>[] edge;
	private int size;
	
	@SuppressWarnings("unchecked")
	public Graph(int size) {
		edge = new LinkedList[size];
		this.size = size;
		while (size-->0)
			edge[size] = new LinkedList<GraphNode>();
	}
	
	public void addEdge(int from, int to, int weight){
		edge[from].add(new GraphNode(weight, from, to));
		edge[to].add(new GraphNode(weight, to, from));
	}

	public List<Integer> bfs(int index) {
		boolean listed[] = new boolean[size];
		listed[index] = true;
		
		List<Integer> visitedList = new LinkedList<Integer>();
		List<Integer> remainingList = new LinkedList<Integer>();
		
		remainingList.add(index);
		
		while (!remainingList.isEmpty()){
			int visitedNode = remainingList.remove(0);
			
			for (GraphNode connectedNode: edge[visitedNode]){
				if (listed[connectedNode.getTo()])
					continue;
				remainingList.add(connectedNode.getTo());
				listed[connectedNode.getTo()] = true;
			}
			
			visitedList.add(visitedNode);
		}
		return visitedList;
	}

	public List<Integer> dfs(int index) {
		boolean listed[] = new boolean[size];
		List<Integer> visitedList = new LinkedList<Integer>();
		
		dfs(index, listed, visitedList);
		return visitedList;
	}
	
	public void dfs(int index, boolean listed[], List<Integer> visitedList ) {
		listed[index] = true;
		visitedList.add(index);
		
		for (GraphNode connectedNode: edge[index]){
			if (listed[connectedNode.getTo()])
				continue;
			dfs(connectedNode.getTo(), listed, visitedList);
		}
	}
	
	public List<GraphNode> dijkstra(int root){
		
		List<GraphNode> path = new LinkedList<>();
		Heap<GraphNode> heap = new MinHeap<>(1000);
		
		boolean[] reached = new boolean[size];
		int nodesRemaining = size;
		
		int weight[] = new int[size];
		
		heap.push(new GraphNode(0, root, root));
		while(nodesRemaining > 0){
			GraphNode nearestNode = heap.pop();
			if (reached[nearestNode.getTo()])
				continue;
			reached[nearestNode.getTo()] = true;
			weight[nearestNode.getTo()] = nearestNode.getWeight();
			nodesRemaining--;
			path.add(nearestNode);
			for (GraphNode connectedNode: edge[nearestNode.getTo()]){
				if (reached[connectedNode.getTo()])
					continue;
				heap.push(new GraphNode(weight[nearestNode.getTo()] + connectedNode.getWeight(), nearestNode.getTo(), connectedNode.getTo()));
			}
		}
		return path;
	}
}
