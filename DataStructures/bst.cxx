#include<bits/stdc++.h>

int height;

namespace skylarkgit{

	template <typename T>
	class node{
	public:
		T data;
		node<T> *left;
		node<T> *right;
		node(T t){data=t;}
	};

	template <typename T>
	class bst{
	protected:
		node<T> *head;
	public:
		bst(){head=NULL;}
		void insert(T d){
			node<T> **temp=&head,t(d);
			while((*temp)!=NULL){
				if((*temp)->data<t.data) temp=&((*temp)->right);
				else temp=&((*temp)->left);
			}
			(*temp)=new node<T>(d);
		}
		void traverse(){traverse(head);}
		void traverse(node<T> *temp){
			if(temp==NULL) return;
			height++;
			traverse(temp->left);
			std::cout<<temp->data<<"("<<height<<")"<<std::endl;
			traverse(temp->right);
			height--;
		}
		void clear(){clear(head);}
		void clear(node<T> *temp){
			if(temp==NULL) return;
			clear(temp->left);
			clear(temp->right);
			delete temp;
			temp=NULL;
		}
		void remove(T d){
			node<T> **temp=&head,t(d);
			while((*temp)!=NULL){
				if((*temp)->data<t.data) temp=&((*temp)->right);
				else if((*temp)->data>t.data) temp=&((*temp)->left);
				else return del(temp);
			}
		}
		bool exists(T d,node<T> *&res){
			node<T> **temp=&head,t(d);
			while((*temp)!=NULL){
				if((*temp)->data<t.data) temp=&((*temp)->right);
				else if((*temp)->data>t.data) temp=&((*temp)->left);
				else {
					res=(*temp);
					return true;
				}
			}
			return false;
		}
		void del(node<T> **temp){
			while((*temp)!=NULL){
				if((*temp)->right!=NULL) {
					(*temp)->data=(*temp)->right->data;
					temp=&((*temp)->right);
				}
				else if((*temp)->left!=NULL){
					(*temp)->data=(*temp)->left->data;
				 	temp=&((*temp)->left);
				 }
				else break;
			}
			delete (*temp);
			(*temp)=NULL;
		}
		~bst(){clear(head);}
	};
}

using namespace std;

int main(int argc, char const *argv[])
{
	skylarkgit::bst<int> tree;
	skylarkgit::node<int> *temp;
	int t=10,k;
	while(t--) {
		cout<<"inserting "<<(k=(rand()%100))<<endl;
		tree.insert(k);
	}
	tree.remove(92);
	height=0;
	tree.traverse();
	tree.exists(15,temp);
	cout<<"data="<<(temp->data)<<endl;
	tree.clear();
	return 0;
}
