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
				cout<<setw(2)<<i<<"  "<<table[i]<<endl;
		}
};

int main()
{
	cout<<"[ Setup 10 key in default ]"<<endl;
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
	return 0;
}