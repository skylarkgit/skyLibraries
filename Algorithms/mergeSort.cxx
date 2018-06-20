#include<iostream>
#include<bits/stdc++.h>

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

using namespace std;
int main(){
	int k;
	std::vector<int> v;
	for(int i=0;i<20;i++){
		k=rand()%100;
		cout<<k<<" ";
		v.push_back(k);
	}
	cout<<"\nSORT:"<<endl;
	skylarkgit::mergeSort(v,20);
	cout<<"SORTED:"<<endl;
	for(int i=0;i<20;i++){
		cout<<v[i]<<endl;
	}
	return 0;
}