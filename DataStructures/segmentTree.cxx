#include<iostream>
#include<bits/stdc++.h>

namespace skylarkgit{
	#define llu long long unsigned	
	#define PENDING 	true
	#define COMPLETE	false
	template <typename T>
	class segmentTree{

	protected:
		size_t 		root;
		size_t 		maxSize,maxUserSize;
		size_t 		bitLength;
		vector<T> 	treeSpace;
		vector<T> 	status;
	
	public:
				segmentTree(size_t size);
		void 	push(T &t,size_t a,size_t b,T (*f)(T &left,T &right),size_t leftIndex=0,size_t rightIndex=maxUserSize);
		T& 		get	(size_t a,size_t b);

	};

	template <typename T>
	segmentTree<T>::segmentTree(size_t size){
		maxUserSize=--size;
		bool flag=false;
		bitLength=8*sizeof(size);
		size_t mask=(1<<(bitLength-1));
		while(bitLength--){
			if(mask&size) flag=true;
			if(flag) ((maxSize<<=1)|=1);
			(size<<=1);
		}
		treeSpace.resize(((maxSize<<1)|1));	//2n+1
		root=((maxSize<<1)|1)-1;
	}

	template <typename T>
	void segmentTree<T>::push(T &t,size_t n,T (*f)(T &left,T &right)){
		size_t node=n,mask=(1<<(bitLength-1));
		treeSpace[n]=t;
		while(node!=root){
			node=mask|(node>>1);

		}
	}