#include<iostream>
#include<limits>
#include<stack>
#include<bits/stdc++.h>
using namespace std;
namespace skylarkgit{
	#define ll long long
	template<typename T>
	inline T inf(){return std::numeric_limits<T>::max();}
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
		Node(){distance=inf<ll>();}
		void addEdge(size_t toIndex,ll w){edges.push_back(Edge(toIndex,w));}
		void addEdge(Node *to,ll w){edges.push_back(Edge(to,w));}
	};
	
	class RandomAccessGraph{
	public:
		const int size;
		std::vector<Node> nodes;
		std::vector<std::vector<ll> > links;
		std::vector<bool> flags;
		RandomAccessGraph():size(0){}
		RandomAccessGraph(size_t n):size(n){
			nodes.resize(n);
			links.resize(n);
			int i=n;
			while(i--) links[i].resize(n);
		}
		void addEdge(size_t from,size_t to,ll w){links[from][to]+=w;}
		bool bfs(size_t src=0,size_t to=-1){
			bool result=false;
			resetNodes();
			flags.resize(size);
			std::queue<size_t> q;
			size_t curr=0;
			q.push(src);
			nodes[src].distance=0;
			flags[src]=true;
			while(!q.empty()){
				curr=q.front();
				q.pop();
				//cout<<curr<<endl;
				for(int i=0;i<size;i++){
					if(links[curr][i]&&flags[i]==false){
						flags[i]=true;
						q.push(i);
						nodes[i].distance=nodes[curr].distance+1;
						nodes[i].srcIndex=curr;
						if(i==to) result=true;
					}
				}
			}
			flags.clear();
			return result;
		}
		bool dfs(size_t src=0,size_t to=-1){
			bool result=false;
			resetNodes();
			flags.resize(size);
			std::stack<size_t> st;
			size_t curr=0;
			st.push(src);
			nodes[src].distance=0;
			flags[src]=true;
			while(!st.empty()){
				curr=st.top();
				st.pop();
				//cout<<curr<<endl;
				//OPTIMIZATION CAN BE FORCED HERE BY SKIPPING PREVOIUS PROGRESS
				for(int i=0;i<size;i++){
					if(links[curr][i]&&flags[i]==false){
						flags[i]=true;
						st.push(curr);
						st.push(i);
						nodes[i].distance=nodes[curr].distance+1;
						nodes[i].srcIndex=curr;
						if(i==to) result=true;
						break;
					}
				}
			}
			flags.clear();
			return result;
		}
		void resetNodes(){
			for(auto& n :nodes){
				n.srcIndex=inf<size_t>();
				n.distance=inf<ll>();
			}
		}
	};

	ll maxFlow(RandomAccessGraph &G,size_t src,size_t sink){
		size_t node,prevnode;
		ll flow,netFlow=0;
		while(G.bfs(src,sink)){
			flow=inf<ll>();
			node=sink;
			while(node!=src){
				prevnode=G.nodes[node].srcIndex;
				flow=min(flow,G.links[prevnode][node]);
				node=prevnode;
			}
			netFlow+=flow;
			node=sink;
			while(node!=src){
				prevnode=G.nodes[node].srcIndex;
				G.links[prevnode][node]-=flow;
				G.links[node][prevnode]+=flow;
				node=prevnode;
			}
		}
		return netFlow;
	}
}
int main(){
	skylarkgit::RandomAccessGraph G(8);
	G.addEdge(0,1,15);
	G.addEdge(0,2,11);
	
	G.addEdge(2,5,skylarkgit::inf<ll>());
	G.addEdge(2,6,skylarkgit::inf<ll>());
	
	G.addEdge(1,4,skylarkgit::inf<ll>());
	G.addEdge(1,5,skylarkgit::inf<ll>());
	G.addEdge(1,3,skylarkgit::inf<ll>());

	G.addEdge(3,7,1);
	
	G.addEdge(5,7,8);

	G.addEdge(4,7,7);
	
	G.addEdge(6,7,9);
	/*G.bfs();
	G.bfs(2,3);
	cout<<"distance from 2 to 3 is "<<G.nodes[3].distance<<endl;
	G.dfs(2,3);
	cout<<"distance from 2 to 3 is "<<G.nodes[3].distance<<endl;
	*/
	cout<<"maxFlow is "<<maxFlow(G,0,7)<<endl;

	long long res=0;
	for(int i=0;i<G.size;i++) res+=G.links[0][i];
	cout<<"remaining "<<res<<endl;
}