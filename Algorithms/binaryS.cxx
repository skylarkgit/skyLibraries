#include<iostream>
#include<bits/stdc++.h>

namespace skylarkgit{
	#define llu long long unsigned	
	/*template <class Iterator,typename T>
	Iterator binaryS(const Iterator &first,const Iterator &last,T &k){
		if(first==last) return first;
		Iterator mid=((first+last)>>1);
		return mid;
	}*/
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

using namespace std;
int main(){
	char a='e';
	std::vector<char> v;
	v.push_back('a');
	v.push_back('b');
	v.push_back('c');
	v.push_back('d');
	v.push_back('e');
	v.push_back('f');
	size_t s=skylarkgit::binaryS(v,0,6,a);
	cout<<"pos="<<s<<endl;
	return 0;
}