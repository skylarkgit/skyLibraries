#pragma once
#include<iostream>
#include<bits/stdc++.h>

namespace skylarkgit{
	#define llu long long unsigned	
	#define PENDING 	true
	#define COMPLETE	false
	#define ST_left(x)	((x)<<1)
	#define ST_right(x)	(((x)<<1)|1)
	#define ST_leftRangeLeft(x,y)	(x)
	#define ST_leftRangeRight(x,y)	(x+((y-x)>>1))
	#define ST_rightRangeLeft(x,y)	(x+((y-x)>>1)+1)
	#define ST_rightRangeRight(x,y)	(y)

	template <typename T>
	class segmentTreeLazy{

	protected:
		size_t 		maxSize,maxUserSize;
		size_t 		bitLength;
		std::vector<T> 	treeSpace;
		std::vector<T> 	update;
		T defval;
		T&			pushKernel(T &t,size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &currNode,T &thisNode));
		T			getKernel(size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &lNode,T &rNode));
	public:
				segmentTreeLazy(size_t size,T &defaultVal);
		void	init(size_t size,T &defaultVal);
		void 	push(T &t,size_t a,size_t b,T (*f)(T &currNode,T &thisNode));
		T 		get	(size_t a,size_t b,T (*f)(T &currNode,T &thisNode));

	};

	template <typename T>
	segmentTreeLazy<T>::segmentTreeLazy(size_t size,T &defaultVal){
		init(size,defaultVal);	
	};

	template <typename T>
	void segmentTreeLazy<T>::init(size_t size,T &defaultVal){
		defval=defaultVal;
		maxUserSize=size-1;
		maxSize=0;
		bool flag=false;
		bitLength=8*sizeof(size);
		size_t mask=1;
		(mask<<=(bitLength-1));
		//cout<<bitset<64>(mask>>60)<<endl;
		while(bitLength--){
			if(mask&size) flag=true;
			if(flag) ((maxSize<<=1)|=1);
			(size<<=1);
			//cout<<"bl="<<bitLength<<" maxSize="<<maxSize<<endl;
		}
		treeSpace.resize(((maxSize<<1)|1));	//2n+1
		update.resize(((maxSize<<1)|1));
		int t=((maxSize<<1)|1);
		while(t--) update[t]=treeSpace[t]=defaultVal;
	}

	template <typename T>
	void segmentTreeLazy<T>::push(T &t,size_t a,size_t b,T (*f)(T &left,T &right)){
		pushKernel(t,a,b,0,maxUserSize,1,f);
	}

	template <typename T>
	T segmentTreeLazy<T>::get(size_t a,size_t b,T (*f)(T &currNode,T &thisNode)){
		treeSpace[0]=getKernel(a,b,0,maxUserSize,1,f);
		return treeSpace[0];
	}

	//***********************KERNEL IMPLEMENTATION***************************//
	template <typename T>
	T& segmentTreeLazy<T>::pushKernel(T &t,size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &currNode,T &thisNode)){
		//if(lIdx<=lLimit&&rIdx>=rLimit)
		if(lLimit!=rLimit) {
			size_t lrl=ST_leftRangeLeft(lLimit,rLimit),
				lrr=ST_leftRangeRight(lLimit,rLimit),
				rrl=ST_rightRangeLeft(lLimit,rLimit),
				rrr=ST_rightRangeRight(lLimit,rLimit);
				
			if(rIdx>=rLimit&&lIdx<=lLimit) update[index]=f(update[index],t);
			else{
				if(!(rIdx<rrl))
					pushKernel(t,lIdx,rIdx,rrl,rrr,ST_right(index),f);
				if(!(lIdx>lrr))
					pushKernel(t,lIdx,rIdx,lrl,lrr,ST_left(index),f);
				T a=getKernel(lrl,lrr,lrl,lrr,ST_left(index),f);
				T b=getKernel(rrl,rrr,rrl,rrr,ST_right(index),f);
				treeSpace[index]=f(a,b);
			}	
		}else{
			treeSpace[index]=f(treeSpace[index],t);
		}
		//cout<<"push lIdx="<<lIdx<<" rIdx="<<rIdx<<" lLimit="<<lLimit<<" rLimit="<<rLimit<<" index="<<index<<" val="<<treeSpace[index]<<"+"<<update[index]<<" t="<<t<<endl;
		return treeSpace[index];
	}
	template <typename T>
	T segmentTreeLazy<T>::getKernel(size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &lNode,T &rNode)){
		T t=defval;
		//if(lIdx<=lLimit&&rIdx>=rLimit)
		if(lLimit!=rLimit) {
			if(rIdx>=rLimit&&lIdx<=lLimit) t=treeSpace[index];
			else if(rIdx<ST_rightRangeLeft(lLimit,rLimit))
				t=getKernel(lIdx,rIdx,ST_leftRangeLeft(lLimit,rLimit),ST_leftRangeRight(lLimit,rLimit),ST_left(index),f);
			else if(lIdx>ST_leftRangeRight(lLimit,rLimit))
				t=getKernel(lIdx,rIdx,ST_rightRangeLeft(lLimit,rLimit),ST_rightRangeRight(lLimit,rLimit),ST_right(index),f);
			else {
				T b=getKernel(lIdx,rIdx,ST_rightRangeLeft(lLimit,rLimit),ST_rightRangeRight(lLimit,rLimit),ST_right(index),f);
				T a=getKernel(lIdx,rIdx,ST_leftRangeLeft(lLimit,rLimit),ST_leftRangeRight(lLimit,rLimit),ST_left(index),f);
				t=f(a,b);
			}
			T k=(min(rLimit,rIdx)-max(lLimit,lIdx)+1)*update[index];
			//cout<<"getKernel lIdx="<<lIdx<<" rIdx="<<rIdx<<" lLimit="<<lLimit<<" rLimit="<<rLimit<<" index="<<index<<" val="<<treeSpace[index]<<"+"<<update[index]<<" t="<<t<<" k="<<k<<endl;
			return f(t,k);
		}
		return treeSpace[index];
	}
}


namespace skylarkgit{
	#define llu long long unsigned	
	#define PENDING 	true
	#define COMPLETE	false
	#define BIT_parent(x)	(((x)^((~x)+1))&x)
	#define BIT_next(x)		(((x)&((~x)+1))+x)

	template <typename T>
	class fenwickTree{

	protected:
		size_t 		maxSize,maxUserSize;
		size_t 		bitLength;
		std::vector<T> 	treeSpace;
	public:
				fenwickTree(size_t size,T &defaultVal);
		void 	update(T &t,size_t a,T (*f)(T &currNode,T &thisNode));
		T 		get	(size_t a,T (*f)(T &currNode,T &thisNode));
	};

	template <typename T>
	fenwickTree<T>::fenwickTree(size_t size,T &defaultVal){
		maxUserSize=size;
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
}


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


namespace skylarkgit{
	#define llu long long unsigned	
	#define PENDING 	true
	#define COMPLETE	false
	#define ST_left(x)	((x)<<1)
	#define ST_right(x)	(((x)<<1)|1)
	#define ST_leftRangeLeft(x,y)	(x)
	#define ST_leftRangeRight(x,y)	(x+((y-x)>>1))
	#define ST_rightRangeLeft(x,y)	(x+((y-x)>>1)+1)
	#define ST_rightRangeRight(x,y)	(y)

	template <typename T>
	class segmentTreeLazy{

	protected:
		size_t 		maxSize,maxUserSize;
		size_t 		bitLength;
		std::vector<T> 	treeSpace;
		std::vector<T> 	update;
		T defval;
		T&			pushKernel(T &t,size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &currNode,T &thisNode));
		T			getKernel(size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &lNode,T &rNode));
	public:
				segmentTreeLazy(size_t size,T &defaultVal);
		void	init(size_t size,T &defaultVal);
		void 	push(T &t,size_t a,size_t b,T (*f)(T &currNode,T &thisNode));
		T 		get	(size_t a,size_t b,T (*f)(T &currNode,T &thisNode));

	};

	template <typename T>
	segmentTreeLazy<T>::segmentTreeLazy(size_t size,T &defaultVal){
		init(size,defaultVal);	
	};

	template <typename T>
	void segmentTreeLazy<T>::init(size_t size,T &defaultVal){
		defval=defaultVal;
		maxUserSize=size-1;
		maxSize=0;
		bool flag=false;
		bitLength=8*sizeof(size);
		size_t mask=1;
		(mask<<=(bitLength-1));
		//cout<<bitset<64>(mask>>60)<<endl;
		while(bitLength--){
			if(mask&size) flag=true;
			if(flag) ((maxSize<<=1)|=1);
			(size<<=1);
			//cout<<"bl="<<bitLength<<" maxSize="<<maxSize<<endl;
		}
		treeSpace.resize(((maxSize<<1)|1));	//2n+1
		update.resize(((maxSize<<1)|1));
		int t=((maxSize<<1)|1);
		while(t--) update[t]=treeSpace[t]=defaultVal;
	}

	template <typename T>
	void segmentTreeLazy<T>::push(T &t,size_t a,size_t b,T (*f)(T &left,T &right)){
		pushKernel(t,a,b,0,maxUserSize,1,f);
	}

	template <typename T>
	T segmentTreeLazy<T>::get(size_t a,size_t b,T (*f)(T &currNode,T &thisNode)){
		treeSpace[0]=getKernel(a,b,0,maxUserSize,1,f);
		return treeSpace[0];
	}

	//***********************KERNEL IMPLEMENTATION***************************//
	template <typename T>
	T& segmentTreeLazy<T>::pushKernel(T &t,size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &currNode,T &thisNode)){
		//if(lIdx<=lLimit&&rIdx>=rLimit)
		if(lLimit!=rLimit) {
			size_t lrl=ST_leftRangeLeft(lLimit,rLimit),
				lrr=ST_leftRangeRight(lLimit,rLimit),
				rrl=ST_rightRangeLeft(lLimit,rLimit),
				rrr=ST_rightRangeRight(lLimit,rLimit);
				
			if(rIdx>=rLimit&&lIdx<=lLimit) update[index]=f(update[index],t);
			else{
				if(!(rIdx<rrl))
					pushKernel(t,lIdx,rIdx,rrl,rrr,ST_right(index),f);
				if(!(lIdx>lrr))
					pushKernel(t,lIdx,rIdx,lrl,lrr,ST_left(index),f);
				T a=getKernel(lrl,lrr,lrl,lrr,ST_left(index),f);
				T b=getKernel(rrl,rrr,rrl,rrr,ST_right(index),f);
				treeSpace[index]=f(a,b);
			}	
		}else{
			treeSpace[index]=f(treeSpace[index],t);
		}
		//cout<<"push lIdx="<<lIdx<<" rIdx="<<rIdx<<" lLimit="<<lLimit<<" rLimit="<<rLimit<<" index="<<index<<" val="<<treeSpace[index]<<"+"<<update[index]<<" t="<<t<<endl;
		return treeSpace[index];
	}
	template <typename T>
	T segmentTreeLazy<T>::getKernel(size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &lNode,T &rNode)){
		T t=defval;
		//if(lIdx<=lLimit&&rIdx>=rLimit)
		if(lLimit!=rLimit) {
			if(rIdx>=rLimit&&lIdx<=lLimit) t=treeSpace[index];
			else if(rIdx<ST_rightRangeLeft(lLimit,rLimit))
				t=getKernel(lIdx,rIdx,ST_leftRangeLeft(lLimit,rLimit),ST_leftRangeRight(lLimit,rLimit),ST_left(index),f);
			else if(lIdx>ST_leftRangeRight(lLimit,rLimit))
				t=getKernel(lIdx,rIdx,ST_rightRangeLeft(lLimit,rLimit),ST_rightRangeRight(lLimit,rLimit),ST_right(index),f);
			else {
				T b=getKernel(lIdx,rIdx,ST_rightRangeLeft(lLimit,rLimit),ST_rightRangeRight(lLimit,rLimit),ST_right(index),f);
				T a=getKernel(lIdx,rIdx,ST_leftRangeLeft(lLimit,rLimit),ST_leftRangeRight(lLimit,rLimit),ST_left(index),f);
				t=f(a,b);
			}
			T k=(min(rLimit,rIdx)-max(lLimit,lIdx)+1)*update[index];
			//cout<<"getKernel lIdx="<<lIdx<<" rIdx="<<rIdx<<" lLimit="<<lLimit<<" rLimit="<<rLimit<<" index="<<index<<" val="<<treeSpace[index]<<"+"<<update[index]<<" t="<<t<<" k="<<k<<endl;
			return f(t,k);
		}
		return treeSpace[index];
	}
}

namespace skylarkgit{
	#define llu long long unsigned	
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
}

namespace skylarkgit{
	#define llu long long unsigned	
	template <typename T>
	void mergeSort(std::vector<T> &obj,size_t End,size_t Start=0){
		if(Start==(End-1)) return;
		size_t mid=((Start+End)>>1),v1s,v2s,i=0,k1=0,k2=0;
		//std::cout<<"start="<<Start<<" End="<<End<<" v1s="<<v1s<<" v2s="<<v2s<<" mid="<<mid<<std::endl;
		mergeSort(obj,mid,Start);
		mergeSort(obj,End,mid);
		std::vector<T> v1,v2;
		v1.insert(v1.end(),obj.begin()+Start,obj.begin()+mid);
		v2.insert(v2.end(),obj.begin()+mid,obj.begin()+End);
		for(int j=0;j<v1.size();j++)std::cout<<v1[j]<<" ";std::cout<<std::endl;
		for(int j=0;j<v2.size();j++)std::cout<<v2[j]<<" ";std::cout<<std::endl;
		v1s=v1.size();
		v2s=v2.size();
		std::cout<<"start="<<Start<<" End="<<End<<" v1s="<<v1s<<" v2s="<<v2s<<" mid="<<mid<<std::endl;
		while((k1<v1s&&k2<v2s)){
			if(v1[k1]>v2[k2])
				obj[Start+(i++)]=v2[k2++];
			else
				obj[Start+(i++)]=v1[k1++];
		}
		while(k1<v1s) obj[Start+(i++)]=v1[k1++];
		while(k2<v2s) obj[Start+(i++)]=v2[k2++];
	}
}

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
}

