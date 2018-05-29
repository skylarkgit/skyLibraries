#include<iostream>
#include<bits/stdc++.h>
using namespace std;

namespace skylarkgit{
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
		void		pushKernel(T &t,size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &currNode,T &thisNode));
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
	void segmentTreeLazy<T>::pushKernel(T &t,size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &currNode,T &thisNode)){
		if(rIdx<lLimit||lIdx>rLimit) return;
		if(lLimit==rLimit) {treeSpace[index]=f(treeSpace[index],t);return;}
		if(rIdx>=rLimit&&lIdx<=lLimit) {update[index]=f(update[index],t);return;}
		//if(lIdx<=lLimit&&rIdx>=rLimit)
		size_t lrl=ST_leftRangeLeft(lLimit,rLimit),
				lrr=ST_leftRangeRight(lLimit,rLimit),
				rrl=ST_rightRangeLeft(lLimit,rLimit),
				rrr=ST_rightRangeRight(lLimit,rLimit);
		pushKernel(t,lIdx,rIdx,rrl,rrr,ST_right(index),f);
		pushKernel(t,lIdx,rIdx,lrl,lrr,ST_left(index),f);
		T a=getKernel(lrl,lrr,lrl,lrr,ST_left(index),f);
		T b=getKernel(rrl,rrr,rrl,rrr,ST_right(index),f);
		treeSpace[index]=f(a,b);
		//cout<<"push lIdx="<<lIdx<<" rIdx="<<rIdx<<" lLimit="<<lLimit<<" rLimit="<<rLimit<<" index="<<index<<" val="<<treeSpace[index]<<"+"<<update[index]<<" t="<<t<<endl;
	}
	template <typename T>
	T segmentTreeLazy<T>::getKernel(size_t lIdx,size_t rIdx,size_t lLimit,size_t rLimit,size_t index,T (*f)(T &lNode,T &rNode)){
		if(rIdx<lLimit||lIdx>rLimit) return defval;
		if(lLimit==rLimit) return treeSpace[index];
		T t;
		if(rIdx>=rLimit&&lIdx<=lLimit) t=treeSpace[index];
		else {
			T b=getKernel(lIdx,rIdx,ST_rightRangeLeft(lLimit,rLimit),ST_rightRangeRight(lLimit,rLimit),ST_right(index),f);
			T a=getKernel(lIdx,rIdx,ST_leftRangeLeft(lLimit,rLimit),ST_leftRangeRight(lLimit,rLimit),ST_left(index),f);
			t=f(a,b);
		}
		T k=(min(rLimit,rIdx)-max(lLimit,lIdx)+1)*update[index];
		return f(t,k);
	}
}
#define ll long long
template <typename T>
inline T sumify(T &a,T &b){
	return a+b;
}

int main(){
	ll p=0;
	skylarkgit::segmentTreeLazy<ll> stl(10,p);
	int t=0,n,c,nn,cc,type,from,to;
	ll upd,res;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&c);
		stl.init(n,p);
		cc=c;
		while(cc--){
			scanf("%d",&type);
			if(type){
				scanf("%d%d",&from,&to);
				--from;--to;
				printf("%lld\n",stl.get(from,to,sumify));
			}else{
				scanf("%d%d%lld",&from,&to,&upd);
				--from;--to;
				stl.push(upd,from,to,sumify);
			}
		}
	}
}