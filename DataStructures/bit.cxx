#include<iostream>
#include<bits/stdc++.h>
using namespace std;

namespace skylarkgit{
	#define BIT_parent(x)	(((x)^((~x)+1))&x)
	#define BIT_next(x)		(((x)&((~x)+1))+x)

	template <typename T>
	class fenwickTree{

	protected:
		size_t 		maxSize;
		std::vector<T> 	treeSpace;
	public:
				fenwickTree(size_t size,T &defaultVal);
		void 	update(T &t,size_t a,T (*f)(T &currNode,T &thisNode));
		T 		get	(size_t a,T (*f)(T &currNode,T &thisNode));
	};

	template <typename T>
	fenwickTree<T>::fenwickTree(size_t size,T &defaultVal){
		maxSize=size;
		treeSpace.resize(maxSize+1);
		int t=maxSize+1;
		while(t--) treeSpace[t]=defaultVal;
	}

	template <typename T>
	void fenwickTree<T>::update(T &t,size_t a,T (*f)(T &currNode,T &thisNode)){
		++a;
		while(a<=maxSize){
			treeSpace[a]=f(treeSpace[a],t);
			a=BIT_next(a);
		}
	}

	template <typename T>
	T fenwickTree<T>::get(size_t a,T (*f)(T &currNode,T &thisNode)){
		++a;
		treeSpace[0]=treeSpace[a];
		a=BIT_parent(a);
		while(a){
			treeSpace[0]=f(treeSpace[0],treeSpace[a]);
			a=BIT_parent(a);
		}
		return treeSpace[0];
	}
}
template <typename T>
inline T sumify(T &a,T &b){
	return a+b;
}

int main(){
	int p=0;
	skylarkgit::fenwickTree<int> ft(10,p);
	int t=10;
	while(t--) {int l=rand()%20;ft.update(l,t,sumify);cout<<" "<<l;}cout<<endl;
	t=10;
	while(t--) cout<<"sum(0,"<<t<<")="<<ft.get(t,sumify)<<endl;
	
}