#include<bits/stdc++.h>
int hght;
namespace skylarkgit{

	#define height short

	template <typename T>
	class node{
	public:
		T data;
		height l,r;
		node<T> *left;
		node<T> *right;
		node(T t){data=t;l=r=1;left=right=NULL;}
		height balance(){return l-r;}
	};

	template <typename T>
	inline void lrotate(node<T> *&x){
		//std::cout<<"l at "<<(x->data)<<"("<<(x->l)<<","<<(x->r)<<") "<<std::endl;
		node<T> *y=x->right;
		x->right=y->left;x->r=(y->l);
		y->left=x;y->l=std::max(x->l,x->r)+1;
		x=y;
		//std::cout<<"l at "<<(x->data)<<"("<<(x->l)<<","<<(x->r)<<") "<<std::endl;
	}
	template <typename T>
	inline void rrotate(node<T> *&x){
		//std::cout<<"r at "<<(x->data)<<"("<<(x->l)<<","<<(x->r)<<") "<<std::endl;
		node<T> *y=x->left;
		x->left=y->right;x->l=y->r;
		y->right=x;y->r=std::max(x->l,x->r)+1;
		x=y;
		//std::cout<<"r at "<<(x->data)<<"("<<(x->l)<<","<<(x->r)<<") "<<std::endl;
	}

	template <typename T>
	void rl(node<T> *&x){
		//std::cout<<"rl at "<<(x->data)<<"("<<(x->l)<<","<<(x->r)<<") "<<std::endl;
		rrotate(x->right);
		lrotate(x);
	}
	template <typename T>
	void rr(node<T> *&x){
		//std::cout<<"rr at "<<(x->data)<<"("<<(x->l)<<","<<(x->r)<<") "<<std::endl;
		lrotate(x);
	}
	template <typename T>
	void ll(node<T> *&x){
		//std::cout<<"ll at "<<(x->data)<<"("<<(x->l)<<","<<(x->r)<<") "<<std::endl;
		rrotate(x);
	}
	template <typename T>
	void lr(node<T> *&x){
		//std::cout<<"lr at "<<(x->data)<<"("<<(x->l)<<","<<(x->r)<<") "<<std::endl;
		lrotate(x->left);
		rrotate(x);
	}

	template <typename T>
	height fix(node<T> *&temp){
		if(temp==NULL) return 0;
		if(abs((temp->l)-(temp->r))<2) 
			return std::max((temp->l),(temp->r));
		if((temp->l)<(temp->r)){
			if(temp->right->balance()<0) rr(temp);
			else rl(temp);
		}else{
			if(temp->left->balance()<0) lr(temp);
			else ll(temp);
		}
		return std::max((temp->l),(temp->r));
	}

	template <typename T>
	class bst{
	protected:
		node<T> *head;
	public:
		bst(){head=NULL;}

		void insert(T d){
			insert(d,head);	
		}
		height insert(T &d,node<T> *&temp){
			if(temp!=NULL){
				if(temp->data<d) temp->r=insert(d,temp->right)+1;
				else temp->l=insert(d,temp->left)+1;
				return fix(temp);
			}
			temp=new node<T>(d);
			return 1;
		}

		void traverse(){traverse(head);std::cout<<std::endl;}
		void traverse(node<T> *temp){
			if(temp==NULL) return;
			traverse(temp->left);
			std::cout<<temp->data<<"("<<(temp->l)<<","<<(temp->r)<<") ";
			traverse(temp->right);
		}

		void clear(){clear(head);}
		void clear(node<T> *&temp){
			if(temp==NULL) return;
			clear(temp->left);
			clear(temp->right);
			delete temp;
			temp=NULL;
		}

		void remove(T d){
			remove(d,head);
		}
		height remove(T &d,node<T> *&temp){
			//std::cout<<temp->data<<std::endl;
			if(temp!=NULL){
				if(temp->data<d) temp->r=remove(d,temp->right)+1;
				else if(temp->data>d) temp->l=remove(d,temp->left)+1;
				else del(temp);
				//std::cout<<"Deleted "<<temp->data<<std::endl;
			}else return 0;
			return fix(temp);
		}
		height del(node<T> *&temp){
			if(temp==NULL) return 0;
			node<T> *toDel=temp,*succ;
			T d;
			if(temp->right!=NULL) {
				temp->r=delSucc(temp->right,succ)+1;
				d=succ->data;
				(*succ)=(*temp);
				succ->data=d;
				temp=succ;
			}
			else temp=temp->left;
			delete toDel;
			return fix(temp);
		}
		height delSucc(node<T> *&temp,node<T> *&succ){
			if(temp==NULL||((temp->left)==NULL&&(temp->right)==NULL)){
				succ=temp;
				temp=NULL;
				return 0;
			}
			if(temp->left!=NULL)
					temp->l=delSucc(temp->left,succ)+1;
			else temp->r=delSucc(temp->right,succ)+1;
			return fix(temp);
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
		tree.traverse();
	}
	cout<<"removing"<<endl;
	tree.remove(83);
	tree.traverse();
	tree.exists(15,temp);
	cout<<"data="<<(temp->data)<<endl;
	tree.clear();
	return 0;
}
