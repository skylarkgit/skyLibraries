#include<iostream>
#include<limits>
#include<stack>
#include<bits/stdc++.h>
using namespace std;
namespace skylarkgit{
	#define ll long long
	template <typename T>
	void inf(T &t){t=std::numeric_limits<T>::max();}
	template <typename T>
	bool isInf(const T &t){return (t==std::numeric_limits<T>::max());}
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
		Node(){inf(distance);}
		void addEdge(size_t toIndex,ll w){edges.push_back(Edge(toIndex,w));}
		void addEdge(Node *to,ll w){edges.push_back(Edge(to,w));}
		bool relax(size_t srcI,ll newDist){
			if(newDist<distance) {distance=newDist;srcIndex=srcI;return true;}
			return false;
		}
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
		bool bellmanFord(size_t src=0){
			resetNodes();
			nodes[src].distance=0;
			int t=size-1;
			while(t--){
				for(size_t i=0;i<size;i++){
					if(!isInf(nodes[i].distance))
					for(size_t j=0;j<size;j++){
						if(links[i][j])
							nodes[j].relax(i,links[i][j]+nodes[i].distance);
					}
				}
			}
			for(size_t i=0;i<size;i++){
				if(!isInf(nodes[i].distance))
				for(size_t j=0;j<size;j++){
					if(links[i][j]&&nodes[j].relax(i,links[i][j]+nodes[i].distance))
						return false;
				}
			}
			return true;
		}
		void resetNodes(){
			for(auto& n :nodes){
				inf(n.srcIndex);
				inf(n.distance);
			}
		}
		void printLinks(){
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++)
                    cout<<links[i][j]<<" ";
                cout<<endl;
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
	G.addEdge(0,3,20);
	//G.bfs();
	G.bellmanFord(2);
	cout<<"distance from 2 to 3 is "<<G.nodes[3].distance<<endl;
}