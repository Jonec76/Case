#include<iostream>
#include<vector>
#include <iomanip>
using namespace std;


class SymbolTable1{
	public:
		int size;
		vector<string> table;
		SymbolTable1(){
			size = 26;
			for(int i=0;i<size;i++)
				table.push_back("");
		}
		void insert(string key){
			int idx = int(key[0]) - 97;
			int ptr = idx;
			while(table[ptr]!=""){
				ptr = (ptr+1)%size;
			}
			table[ptr] = key;
		}

		void search(string key){
			cout<<"\n[ Search key: "<<key<<" ]"<<endl;
			int idx = int(key[0]) - 97;
			int ptr = idx;
			while(table[ptr]!=key){
				if(table[ptr] == ""){
					cout<<"  No search result"<<endl;
					return;
				}
				cout<<"  Collision: "<<table[ptr]<<endl;
				ptr = (ptr+1)%size;
			}

			if(table[ptr]==key)
				cout<<"  Find key (index, key): ("<<ptr<<", "<<table[ptr]<<")"<<endl;
		}

		void display(){
			cout<<"[ Display table ]"<<endl;
			for(int i=0;i<size;i++)
				cout<<setw(4)<<i<<"  "<<table[i]<<endl;
		}
};

struct node{
	string key;
	struct node* next;
};
typedef struct node node;

class SymbolTable2{
	public:
		int size;
		vector<node*>table;
		SymbolTable2(){
			size=26;
			for(int i=0;i<size;i++)
				table.push_back(NULL);

		}

		void insert(string key){
			int idx = int(key[0]) - 97;
			if(table[idx]==NULL){
				node* n = (node*)malloc(sizeof(node));
				n->key = key;
				n->next = NULL;
				table[idx] = n;
				return;
			}

			node* tmp = table[idx];
			while(tmp->next != NULL)
				tmp = tmp->next;
			
			node* n = (node*)malloc(sizeof(node));
			n->key = key;
			n->next = NULL;
			tmp->next = n;
		}

		void search(string key){
			cout<<"\n[ Search key: "<<key<<" ]"<<endl;
			int idx = int(key[0]) - 97;
			node* n =table[idx];
			int ctr = 0;

			while(n){
				if(n->key == key){
					cout<<"  Find key (chain index, key): ("<<ctr<<", "<<n->key<<")"<<endl;
					return;
				}else{
					cout<<"  Collision: "<<n->key<<endl;
				}
				n = n->next;
				ctr++;
			}
			cout<<"  No search result"<<endl;
		}

		void display(){
			cout<<"[ Display table ]"<<endl;
			for(int i=0;i<size;i++){
				cout<<setw(4)<<i<<"  ";
				node* tmp = table[i];
				while(tmp){
					if(tmp->next)
						cout<<tmp->key<<" -> ";
					else
						cout<<tmp->key;

					tmp = tmp->next;
				}
				cout<<endl;
			}


		}
};


int main()
{
	cout<<" ========= Linear probing =========\n";
	cout<<"[ Setup 10 keys in default ]"<<endl;
	SymbolTable1 d1;
	d1.insert("apple");
	d1.insert("abc");
	d1.insert("ayoooo");
	d1.insert("almost");
	d1.insert("zero");
	d1.insert("hero");
	d1.insert("hahaha");
	d1.insert("xampp");
	d1.insert("ok");
	d1.insert("yoo");
	d1.insert("bboy");
	d1.display();
	d1.search("almost");
	d1.search("notfound");
	d1.search("anotfoundkey");
	d1.search("bboy");
	d1.search("hahaha");

	cout<<"\n\n ========= Chain =========\n";
	cout<<"[ Setup 15 keys in default ]"<<endl;
	SymbolTable2 d2;
	d2.insert("apple");
	d2.insert("abc");
	d2.insert("ayoooo");
	d2.insert("almost");
	d2.insert("zero");
	d2.insert("hero");
	d2.insert("hahaha");
	d2.insert("xampp");
	d2.insert("xray");
	d2.insert("xdd");
	d2.insert("ok");
	d2.insert("yoo");
	d2.insert("bboy");
	d2.insert("beach");
	d2.insert("bitcoin");
	d2.display();
	d2.search("almost");
	d2.search("notfound");
	d2.search("anotfoundkey");
	d2.search("bboy");
	d2.search("hahaha");

	return 0;
}