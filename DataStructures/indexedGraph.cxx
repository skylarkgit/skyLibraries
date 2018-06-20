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
		size_t myindex,srcIndex;
		ll distance;
		std::vector<Edge> edges;
		Node *src;
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
		bool bfs(size_t src=0,size_t to=-1){
			bool result=false;
			resetNodes();
			flags.resize(nodes.size());
			std::queue<size_t> q;
			size_t curr=0;
			q.push(src);
			nodes[src].distance=0;
			flags[src]=true;
			while(!q.empty()){
				curr=q.front();
				q.pop();
				cout<<curr<<endl;
				for(auto& e :nodes[curr].edges){
					if(flags[e.toIndex]==false){
						flags[e.toIndex]=true;
						q.push(e.toIndex);
						nodes[e.toIndex].distance=nodes[curr].distance+1;
						nodes[e.toIndex].srcIndex=curr;
						if(e.toIndex==to) result=true;
					}
				}
			}
			flags.clear();
			return result;
		}
		bool dfs(size_t src=0,size_t to=-1){
			bool result=false;
			resetNodes();
			flags.resize(nodes.size());
			std::stack<size_t> st;
			size_t curr=0;
			st.push(src);
			nodes[src].distance=0;
			flags[src]=true;
			while(!st.empty()){
				curr=st.top();
				st.pop();
				cout<<curr<<endl;
				//OPTIMIZATION CAN BE FORCED HERE BY SKIPPING PREVOIUS PROGRESS
				for(auto& e :nodes[curr].edges){
					if(flags[e.toIndex]==false){
						flags[e.toIndex]=true;
						st.push(curr);
						st.push(e.toIndex);
						nodes[e.toIndex].distance=nodes[curr].distance+1;
						nodes[e.toIndex].srcIndex=curr;
						if(e.toIndex==to) result=true;
						break;
					}
				}
			}
			flags.clear();
			return result;
		}
		void resetNodes(){
			for(auto& n :nodes){
				n.srcIndex=inf;
				n.distance=inf;
			}
		}
	};
}
int main(){
	skylarkgit::IndexedGraph G(6);
	G.addEdge(0,2,10);
	G.addEdge(2,1,20);
	G.addEdge(1,4,30);
	G.addEdge(1,5,30);
	G.addEdge(4,3,40);
	G.addEdge(2,0,50);
	G.bfs();
	G.bfs(2,3);
	cout<<"distance from 2 to 3 is "<<G.nodes[3].distance<<endl;
}