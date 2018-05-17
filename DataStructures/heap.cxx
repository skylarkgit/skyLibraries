#include<iostream>
#include<bits/stdc++.h>

namespace skylarkgit{
	const bool minHeap=0,maxHeap=1;
	
	template <typename T>
	class heap
	{
		const bool style;
		const unsigned int maxSize;
		std::vector<T> heapSpace;
		size_t currSize;
	public:
		heap(size_t n,bool s);
		~heap();
		
		int push(T);
		T pop();
		void clear();
		size_t size();
	};
	
	template <typename T>
	heap<T>::heap(size_t n,bool s):style(s),maxSize(n){
		currSize=0;
		heapSpace.resize(n+1);
	}

	template <typename T>
	heap<T>::~heap(){
	}

	template <typename T>
	size_t heap<T>::size(){
		return currSize;
	}

	template <typename T>
	void heap<T>::clear(){
		heapSpace.clear();
	}

	template <typename T>
	int heap<T>::push(T t){
		if(currSize==maxSize) return currSize;
		heapSpace[++currSize]=t;
		int i=currSize;
		if(style==minHeap)
		while(i>1&&(heapSpace[i]<heapSpace[i>>1])) {
			std::swap(heapSpace[i],heapSpace[i>>1]);
			i>>=1;
		}
		else
		while(i>1&&(heapSpace[i]>heapSpace[i>>1])) {
			std::swap(heapSpace[i],heapSpace[i>>1]);
			i>>=1;
		}
		return currSize;
	}

	template <typename T>
	T heap<T>::pop(){
		//if(currSize==0) return NULL;
		T tmp(heapSpace[1]);
		std::swap(heapSpace[1],heapSpace[currSize]);
		currSize--;
		int i=1;
		if(style==minHeap)
		while((i<<1)<=currSize
			&&(heapSpace[i]>heapSpace[i<<1]
				||((((i<<1)|1)<=currSize)&&(heapSpace[i]>heapSpace[(i<<1)|1])))) {
				if(((i<<1)|1)>currSize||heapSpace[(i<<1)|1]>heapSpace[i<<1]) {std::swap(heapSpace[i<<1],heapSpace[i]);i<<=1;}
				else {std::swap(heapSpace[(i<<1)|1],heapSpace[i]);(i<<=1)|=1;}
		}
		else
		while((i<<1)<=currSize
			&&(heapSpace[i]<heapSpace[i<<1]
				||((((i<<1)|1)<=currSize)&&(heapSpace[i]<heapSpace[(i<<1)|1])))) {
				if(((i<<1)|1)>currSize||heapSpace[(i<<1)|1]<heapSpace[i<<1]) {std::swap(heapSpace[i<<1],heapSpace[i]);i<<=1;}
				else {std::swap(heapSpace[(i<<1)|1],heapSpace[i]);(i<<=1)|=1;}
		}
		return tmp;
	}
}

int main(){

	skylarkgit::heap<int> H(1000,skylarkgit::minHeap);
	for(int i=0;i<100;i++) H.push(rand()%2000);
	for(int i=0;i<100;i++) {
		int t=H.pop();
		std::cout<<t<<std::endl;
	}

	return 0;
}