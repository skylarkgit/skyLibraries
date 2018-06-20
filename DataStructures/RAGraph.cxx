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
				cout<<curr<<endl;
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
				cout<<curr<<endl;
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
				n.srcIndex=inf;
				n.distance=inf;
			}
		}
	};
}
int main(){
	skylarkgit::RandomAccessGraph G(6);
	G.addEdge(0,2,10);
	G.addEdge(2,1,20);
	G.addEdge(1,4,30);
	G.addEdge(1,5,30);
	G.addEdge(4,3,40);
	G.addEdge(2,0,50);
	//G.bfs();
	G.bfs(2,3);
	cout<<"distance from 2 to 3 is "<<G.nodes[3].distance<<endl;
	G.dfs(2,3);
	cout<<"distance from 2 to 3 is "<<G.nodes[3].distance<<endl;
}