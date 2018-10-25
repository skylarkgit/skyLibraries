package skylib.ds;

public class GraphNode implements Comparable<GraphNode>{
	
	private Integer weight;
	private Integer from;
	private Integer to;
	/** @return the weight */
	public Integer getWeight() {
		return weight;
	}
	/** @param weight the weight to set */
	public void setWeight(Integer weight) {
		this.weight = weight;
	}
	/** @return the from */
	public Integer getFrom() {
		return from;
	}
	/** @param from the from to set */
	public void setFrom(Integer from) {
		this.from = from;
	}
	/** @return the to */
	public Integer getTo() {
		return to;
	}
	/** @param to the to to set */
	public void setTo(Integer to) {
		this.to = to;
	}
	/**
	 * @param weight
	 * @param from
	 * @param to
	 */
	public GraphNode(Integer weight, Integer from, Integer to) {
		this.weight = weight;
		this.from = from;
		this.to = to;
	}
	@Override
	public int compareTo(GraphNode gNode) {
		return weight.compareTo(gNode.weight);
	}
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "GraphNode [weight=" + weight + ", from=" + from + ", to=" + to
				+ "]";
	}
}
