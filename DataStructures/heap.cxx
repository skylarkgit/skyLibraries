#include<iostream>
#include<bits/stdc++.h>

namespace skylarkgit{
	const bool minHeap=0,maxHeap=1;
	
	template <typename T>
	class heap
	{
		const bool style;
		const unsigned int maxSize=0;
		std::vector<T> heapSpace;
		unsigned int currSize=0;
	public:
		heap(unsigned int n,bool s);
		~heap();
		
		int push(T);
		T& pop(T);
		int clear();
	};
	
	template <typename T>
	heap<T>::heap(unsigned int n,bool s):style(s){
		heapSpace.resize(n);
	}

	template <typename T>
	heap<T>::~heap(){
	}

	template <typename T>
	int heap<T>::push(T t){
		heapSpace[currsize++]=t;
		int i=currSize-1;
		if(minHeap)
		while(i&&(heapSpace[i]<heapSpace[(i-1)>>1])) {
			std::swap(heapSpace[i],heapSpace[(i-1)>>1]);
			i=((i-1)>>1);
		}
		else
		while(i&&(heapSpace[i]>heapSpace[(i-1)>>1])) {
			std::swap(heapSpace[i],heapSpace[(i-1)>>1]);
			i=((i-1)>>1);
		}
		return currsize;
	}

	template <typename T>
	T& heap<T>::pop(T t){
		if(currsize==0) return NULL;
		T tmp(heapSpace[0]);
		currsize--;
		heapSpace[0]=heapSpace[currsize];
		
		int i=0;
		if(minHeap)
		while(i<currsize) {
			if(heapSpace[i]>heapSpace[i<<1]||heapSpace[i]<heapSpace[(i<<1)|1]){
				if(heapSpace[i<<1]<heapSpace[(i<<1)|1]) std::swap(heapSpace[i<<1],heapSpace[i]);
			}
			
			std::swap(heapSpace[i],heapSpace[(i-1)>>1]);
			i=((i-1)>>1);
		}
		else
		while(i&&(heapSpace[i]<heapSpace[(i-1)>>1])) {
			std::swap(heapSpace[i],heapSpace[(i-1)>>1]);
			i=((i-1)>>1);
		}
		return tmp;
	}
}