#include<iostream>
#include<limits>
#include<stack>
#include<bits/stdc++.h>
using namespace std;
namespace skylarkgit{
	#define ll long long
	ll inf = std::numeric_limits<ll>::max();
	class Node;
	class Edge{
	public:
		Node *to;
		size_t toIndex;
		ll w;
		Edge(){}
		Edge(size_t ptoIndex,ll pw){w=pw;toIndex=ptoIndex;}
		Edge(Node *pto,ll pw){to=pto;w=pw;}
	};
	class Node{
	public:
		size_t myindex;
		ll distance;
		std::vector<Edge> edges;
		Node(){distance=inf;}
		void addEdge(size_t toIndex,ll w){edges.push_back(Edge(toIndex,w));}
		void addEdge(Node *to,ll w){edges.push_back(Edge(to,w));}
	};
	
	class IndexedGraph{
	public:
		std::vector<Node> nodes;
		std::vector<bool> flags;
		IndexedGraph(){}
		IndexedGraph(size_t n){nodes.resize(n);}
		void addEdge(size_t from,size_t to,ll w){nodes[from].addEdge(to,w);}
		void dfs(){
			flags.resize(nodes.size());
			std::stack<size_t> st;
			size_t curr=0;
			st.push(0);
			flags[0]=true;
			while(!st.empty()){
				curr=st.top();
				st.pop();
				cout<<curr<<endl;
				for(auto e :nodes[curr].edges){
					if(flags[e.toIndex]==false)
						st.push(e.toIndex);
				}
			}
			flags.clear();
		}
	};
}
int main(){
	skylarkgit::IndexedGraph G(5);
	G.addEdge(0,2,10);
	G.addEdge(2,1,20);
	G.addEdge(1,4,30);
	G.addEdge(4,3,40);
	G.addEdge(2,0,50);
	G.dfs();
}