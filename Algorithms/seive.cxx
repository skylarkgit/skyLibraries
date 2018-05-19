#include<iostream>
#include<bits/stdc++.h>

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

int main(){
	long long unsigned k=9,l=89;
	skylarkgit::seive s(k,l);
	for(int i=0;i<s.prime.size();i++) printf("s : %llu\n",s.prime[i]);
	skylarkgit::seive ss(l);
	for(int i=0;i<ss.prime.size();i++) printf("ss : %llu\n",ss.prime[i]);
}