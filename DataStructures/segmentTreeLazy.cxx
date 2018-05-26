#include<iostream>
#include<bits/stdc++.h>
using namespace std;

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
	class segmentTree{

	protected:
		size_t 		maxSize,maxUserSize;
		size_t 		bitLength;
		std::vector<T> 	treeSpace;
		std::vector<T> 	update;
		T defval;
		T&			pushKernel(T &t,size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &currNode,T &thisNode));
		T			getKernel(size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &lNode,T &rNode));
	public:
				segmentTree(size_t size,T &defaultVal);
		void 	push(T &t,size_t a,size_t b,T (*f)(T &currNode,T &thisNode));
		T 		get	(size_t a,size_t b,T (*f)(T &currNode,T &thisNode));

	};

	template <typename T>
	segmentTree<T>::segmentTree(size_t size,T &defaultVal){
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
	void segmentTree<T>::push(T &t,size_t a,size_t b,T (*f)(T &left,T &right)){
		pushKernel(t,a,b,0,maxUserSize,1,f);
	}

	template <typename T>
	T segmentTree<T>::get(size_t a,size_t b,T (*f)(T &currNode,T &thisNode)){
		treeSpace[0]=getKernel(a,b,0,maxUserSize,1,f);
		return treeSpace[0];
	}

	//***********************KERNEL IMPLEMENTATION***************************//
	template <typename T>
	T& segmentTree<T>::pushKernel(T &t,size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &currNode,T &thisNode)){
		//if(lIdx<=lLimit&&rIdx>=rLimit)
		//cout<<" lIdx="<<lIdx<<" rIdx="<<rIdx<<" lLimit="<<lLimit<<" rLimit="<<rLimit<<" index="<<index<<" val="<<treeSpace[index]<<endl;
		if(lLimit!=rLimit) {
			if(rIdx>=rLimit&&lIdx<=lLimit) update[index]=f(update[index],t);
			else if(!(rIdx<ST_rightRangeLeft(lLimit,rLimit)))
				pushKernel(t,lIdx,rIdx,ST_rightRangeLeft(lLimit,rLimit),ST_rightRangeRight(lLimit,rLimit),ST_right(index),f);
			else if(!(lIdx>ST_leftRangeRight(lLimit,rLimit)))
				pushKernel(t,lIdx,rIdx,ST_leftRangeLeft(lLimit,rLimit),ST_leftRangeRight(lLimit,rLimit),ST_left(index),f);
			T a=f(treeSpace[ST_left(index)],update[ST_left(index)]);
			T b=f(treeSpace[ST_right(index)],update[ST_right(index)]);
			treeSpace[index]=f(a,b);
		}else{
			treeSpace[index]=f(treeSpace[index],t);
		}
		return treeSpace[index];
	}
	template <typename T>
	T segmentTree<T>::getKernel(size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &lNode,T &rNode)){
		T t=defval;
		//if(lIdx<=lLimit&&rIdx>=rLimit)
		//cout<<" lIdx="<<lIdx<<" rIdx="<<rIdx<<" lLimit="<<lLimit<<" rLimit="<<rLimit<<" index="<<index<<" val="<<treeSpace[index]<<endl;
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
			return f(t,update[index]);
		}
		return treeSpace[index];
	}
}
template <typename T>
inline T maxify(T &a,T &b){
	return max(a,b);
}

int main(){
	int p=0;
	skylarkgit::segmentTree<int> st(10,p);
	int t=10;
	while(t--) {int l=rand()%20;st.push(l,t,t,maxify);cout<<t<<"="<<l<<endl;}
	t=10;
	while(t--) cout<<"max(0,"<<t<<")="<<st.get(0,t,maxify)<<endl;
	t=10;
	while(t--) cout<<"max("<<t<<",9)="<<st.get(t,9,maxify)<<endl;
}