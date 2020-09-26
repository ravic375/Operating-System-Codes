#include <bits/stdc++.h>
using namespace std; 
typedef struct page_table{
int pages[8];
}page_table;

void create_process(page_table *process[], int memory[256]){
	int i,j,r,n;
	for(i=0;i<8&&process[i]!=NULL;i++){}
	if(i==8){
		cout << "You reached MAX Process Limit\n";
		return;
	}
	n=i;
	process[n]=new page_table;
	cout << "Enter required number of pages(</=8):";
	cin >> r;
	cout << "Process " << n <<  " created\n";
	for(i=0,j=10;i<r&&i<8;j++){
		if(memory[j]==0){
			process[n]->pages[i]=j;
			cout << "Allocating " << j << "\n";
			memory[j]=1;
			i++;
		}
	}
	for(;i<8;i++){
		process[n]->pages[i]=-1;
	}
}

void remove_process(page_table *process[], int memory[256]){
	int n,i;
	cout << "Enter Process number to eliminate:";
	cin >> n;
	for(i=0;i<8;i++){
		if(memory[process[n]->pages[i]]==1){
			cout << "DeAllocating " << process[n]->pages[i];
			memory[process[n]->pages[i]]=0;
		}
	}
	delete process[n];
	process[n]=NULL;
	return;
}
class LRUCache { 
	list<int> dq;
	map<int, list<int>::iterator> ma; 
	int csize;
public: 
	LRUCache(int); 
	void refer(int); 
	void display(); 
}; 
LRUCache::LRUCache(int n) 
{ 
	csize = n; 
} 
void LRUCache::refer(int x) 
{ 
	if (ma.find(x) == ma.end()) { 
		if (dq.size() == csize) { 
			int last = dq.back(); 
			dq.pop_back(); 
			ma.erase(last); 
		} 
	} 
	else
		dq.erase(ma[x]); 
	dq.push_front(x); 
	ma[x] = dq.begin(); 
}
void LRUCache::display() 
{ 
	for (list <int>::iterator it = dq.begin(); it != dq.end(); it++) 
		cout << (*it) << " "; 
	cout << endl; 
} 
LRUCache add_pages(page_table *process[], int memory[], LRUCache ca, int n){
	int p_no,i;
	cin >> p_no;
	for(i=0;i<8;i++){
		if(process[p_no]->pages[i]!=-1){
			ca.refer(process[p_no]->pages[i]);
		}
	}
	cout << "LRUCache: ";
	ca.display();
	return ca;
}
int main() 
{ 
	page_table *process[8];
	int n, memory[256];
	for(n=0;n<256;n++){
		memory[n]=0;
	}
	for(n=0;n<8;n++){
		process[n]=NULL;
	}
	int page, q;
	cout << "Enter the capacity of LRUCache:";
	cin >> n;
	LRUCache ca(n);
	cout << "Press 1 to create process\nPress 2 to remove process\nPress 3 to add necessory pages of the process\n";
	while(1){
		cin >> q;
		switch (q)
		{
		    case 1: create_process(process, memory);
			break;
		    case 2: remove_process(process, memory);
			break;
		    case 3: ca = add_pages(process, memory, ca, n);
			break;
		}
	}
	return 0; 
}

