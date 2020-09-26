#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define LRUCacheSize 10 //set size of LRU Cache
typedef struct process{
	int lop; //lop means levels of paging.
	int myframe;
	int totalpages;
}process;
int memory[1024][9]; // 1024 physical frames

/*** To see the allocation of memory ***/
void showmem(){
    int i,j;
    for(i=0;i<100;i++){
        for(j=0;j<9;j++){
            cout<< memory[i][j] << "\t";
        }
        cout << endl;
    }
    return;
}

/*** To search for free frame and return ***/
int search(){
    int j;
	for(j=1;j<1024;j++){
		if(memory[j][0]==0){
			memory[j][0]=1;
			//cout << "Frame " << j << " allocated " << memory[j][0] << endl;
			return j;
		}
	}
	return 0;
}

/*** Allocate frames to process as pages ***/
int alocator(int x, int lop){
    	if(x==0)
        	return 0;
	int i;
	i = search();
	if(i == 0)
		return i;
	if(lop == 0)
		return i;
	int n=i;
	for(i=0; i<(x>>(3*(lop-1))); i++){
		memory[n][i+1] = alocator(1<<(3*(lop-1)), lop-1);
		//cout << memory[n][i+1] << endl;
	}
	if(i+1<8){
		memory[n][i+1] = alocator(x-((x>>((lop-1)*3))<<((lop-1)*3)), lop-1);
		//cout << memory[n][i+1] << endl;
	}
    return n;
}
void create_process(process *myprocess[]){
	int i,j,r,n;
	for(i=0;i<8&&myprocess[i]!=NULL;i++){}
	if(i==8){
		cout << "You reached MAX Process Limit\n";
		return;
	}
	n=i;
	myprocess[n]=new process;
	myprocess[n]->lop=0;
	cout << "Enter required number of pages:";
	cin >> r;
	myprocess[n]->totalpages = r;
	j=r-1;
	while(j){
		myprocess[n]->lop++;
		j = j>>3;
	}
	myprocess[n]->myframe = alocator(r, myprocess[n]->lop);
	cout << "Process " << n <<  " created with page table in " << myprocess[n]->myframe << endl;
	return;
}
void dealocator(int frame){
    if(memory[frame][0] == 0)
        return;
    else{
        int i;
        for(i=0;i<8;i++){
            dealocator(memory[frame][i+1]);
            memory[frame][i+1] = 0;
        }
        memory[frame][0] = 0;
    }
    return;
}
class LRUCache {
	list<int> dq;
	map<int, list<int>::iterator> ma;
	unsigned int csize;
public:
	LRUCache();
	void refer(int);
	void display();
	void clr();
};
void remove_process(process *myprocess[], LRUCache ca[8]){
	int n;
	cout << "Enter Process number to eliminate:";
	cin >> n;
	if(myprocess[n]==NULL){
	    cout << "No such process\n";
	}
	dealocator(myprocess[n]->myframe);
	delete myprocess[n];
	myprocess[n]=NULL;
	ca[n].clr();
	cout << "Process " << n << " removed\n";
	return;
}
LRUCache::LRUCache()
{
	csize = LRUCacheSize;
}
void LRUCache::clr(){
	dq.clear();
	ma.clear();
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
int translate(process *myprocess[],int p_no, int va){
	if(va >= myprocess[p_no]->totalpages)
		return -1;
	int t = myprocess[p_no]->lop;
	int temp = myprocess[p_no]->myframe;
	while(t--){
		int x = va>>(t*3);
		temp = memory[temp][1+x];
		va = va - (x<<(t*3));
	}
	return temp;
}
void add_pages(process *myprocess[], LRUCache ca[]){
	int p_no,i;
	cout << "Enter a process number: ";
	cin >> p_no;
	cout << "Referring 5 random pages from the process to its local LRUCache\n";
	for(i=0;i<5;i++){
		ca[p_no].refer(translate(myprocess, p_no, rand()%myprocess[p_no]->totalpages));
	}
	cout << "LRUCache: ";
	ca[p_no].display();
	return;
}
int main()
{
	process *myprocess[8];
	int n, p_no, va;
	memset(&memory, 0, sizeof(memory));
	for(n=0;n<8;n++){
		myprocess[n]=NULL;
	}
	int q;
	LRUCache ca[8];
	cout << "Press 1 to create process\nPress 2 to remove process\nPress 3 to add necessory pages of the process\nPress 4 to Translate address\nPress 5 to show memory\n";
	while(1){
		cin >> q;
		switch (q)
		{
		    case 1: create_process(myprocess);
			break;
		    case 2: remove_process(myprocess, ca);
			break;
		    case 3: add_pages(myprocess, ca);
			break;
		    case 4: {cout << "What Process' address would you like to translate(starts from 0): ";
		    	cin >> p_no;
		    	cout << "Virtual address of page(starts from 0): ";
		    	cin >> va;
		    	cout << translate(myprocess,p_no,va);
		    	break;}
		    case 5: showmem();
		    	break;
		    case 6:{cout << myprocess[1]->lop << " " << myprocess[1]->myframe << " " << myprocess[1]->totalpages << endl;
		    }
		}
	}
	return 0;
}
