#pragma once
#include<iostream>
#include<bits/stdc++.h>

namespace skylarkgit{
	#define llu long long unsigned	
	template <typename T>
	size_t binaryS(std::vector<T> obj,size_t Start,size_t End,T &k){
		size_t mid=((Start+End-1)>>1);
		//std::cout<<Start<<" "<<mid<<" "<<End<<std::endl;
		if(Start==(End-1)) return Start;
		if(obj[mid]==k) return mid;
		if(obj[mid]>k) return binaryS(obj,Start,mid+1,k);
		return binaryS(obj,mid,End,k);
	}
	class seive
	{
	public:
		std::vector<llu> prime;
		std::vector<bool> nonPrimality;
		seive(llu a);
		seive(llu a,llu b);
	};
	seive::seive(llu a):nonPrimality(a+1){
		if(2<=a) prime.push_back(2);
		nonPrimality[1]=true;
		for(int i=3,j=0;i<=a;i+=2){
			if(nonPrimality[i]==false){
			 	prime.push_back(i);
				for(j=(i*3);j<=a;j+=(i<<1)) nonPrimality[j]=true;
			}
		}
	}
	seive::seive(llu a,llu b):nonPrimality(b+1){
		if(2>=a&&2<=b) prime.push_back(2);
		nonPrimality[1]=true;
		for(int i=3,j=0;i<=b;i+=2){
			if(nonPrimality[i]==false){ 
				if(i>=a&&i<=b) prime.push_back(i);
				for(j=(i*3);j<=b;j+=(i<<1)) nonPrimality[j]=true;
			}
		}
	}
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
		heapSpace.resize(maxSize+1);
		currSize=0;
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
		if(currSize==0) throw std::logic_error("remove<T> : List is Empty");
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

	template <typename T>
	class limitList
	{
		const unsigned int maxSize;
		std::vector<T> listSpace;
		std::vector<int> next;
		std::vector<int> prev;
		std::vector<bool> doesExists;
		size_t currSize,netSize,head,toe;
	public:
		limitList(size_t n);
		~limitList();
		
		size_t push(T);
		T remove(size_t n);
		void clear();
		size_t size();
		T getByIndex(size_t n);
		T get(size_t n);
		bool exists(size_t n);
	};
	
	template <typename T>
	limitList<T>::limitList(size_t n):maxSize(n){
		currSize=0;
		netSize=0;
		head=toe=n;
		next.resize(n+1);
		prev.resize(n+1);
		doesExists.resize(n+1);
		listSpace.resize(n+1);
	}

	template <typename T>
	limitList<T>::~limitList(){
	}

	template <typename T>
	size_t limitList<T>::size(){
		return currSize;
	}

	template <typename T>
	bool limitList<T>::exists(size_t n){
		if(n<0||n>=currSize) throw std::out_of_range("remove<T> : Index out of range");
		return doesExists[n];
	}

	template <typename T>
	void limitList<T>::clear(){
		head=toe=maxSize;
		netSize=currSize=0;
		next.clear();
		prev.clear();
		doesExists.clear();
		listSpace.clear();
		next.resize(maxSize+1);
		prev.resize(maxSize+1);
		doesExists.resize(maxSize+1);
		listSpace.resize(maxSize+1);
	}

	template <typename T>
	size_t limitList<T>::push(T t){
		if(currSize==maxSize) return currSize;
		listSpace[currSize]=t;
		if(netSize==0) {
			head=toe=currSize;
			prev[currSize]=maxSize;
			next[currSize]=maxSize;
		}
		else{
			next[toe]=currSize;
			next[currSize]=maxSize;
			prev[currSize]=toe;
			toe=currSize;
		}
		doesExists[currSize]=true;
		currSize++;
		netSize++;
		return currSize;
	}

	template <typename T>
	T limitList<T>::remove(size_t n){
		if(currSize==0) throw std::logic_error("remove<T> : List is Empty");
		if(n<0||n>=currSize) throw std::out_of_range("remove<T> : Index out of range");
		if(!doesExists[n]) throw std::logic_error("remove<T> : Element does not doesExists");
		T tmp(listSpace[n]);
		size_t pr=prev[n],nx=next[n];
		if (doesExists[nx]) prev[nx]=pr;
		if (doesExists[pr]) next[pr]=nx;
		if (nx==maxSize) toe=pr;
		if (pr==maxSize) head=nx;
		netSize--;
		if (netSize==0) toe=head=maxSize;
		return tmp;
	}

	template <typename T>
	T limitList<T>::getByIndex(size_t n){
		if(n<0||n>=currSize) throw std::out_of_range("getByIndex<T> : Index out of range");
		if(!doesExists[n]) throw std::logic_error("getByIndex<T> : Element does not doesExists");
		
		return listSpace[n];
	}

	template <typename T>
	T limitList<T>::get(size_t n){
		if(n<0||n>=currSize) throw std::out_of_range("get<T> : Index out of range");
		size_t k=head,index=0;
		for (int i = 0; i < netSize&&k<=toe&&index<n; ++i) {
			k=next[k];
			index++;
		}
		if(index<n) throw std::out_of_range("get<T> : Index out of range");
		if(!doesExists[k]) throw std::logic_error("get<T> : Element does not doesExists");
		return listSpace[k];
	}
}