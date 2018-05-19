#include<iostream>
#include<bits/stdc++.h>

namespace skylarkgit{
	
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

int main(){

	skylarkgit::limitList<int> H(1000);
	/*for(int i=0;i<100;i++) H.push(rand()%2000);
	for(int i=0;i<100;i++) {
		std::cout<<H.getByIndex(rand()%100)<<std::endl;
	}
	*/
	try{
    	H.push(5);
		H.push(10);
		H.push(20);
		H.push(23);
		std::cout<<H.getByIndex(2)<<std::endl;
		std::cout<<H.get(2)<<std::endl;
		H.remove(2);
		std::cout<<H.get(2)<<std::endl;
	
	} catch (const std::exception& ex) {
    	std::cout<<ex.what()<<std::endl;
	}
	return 0;
}