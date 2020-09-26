#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>store;
void memory_allocator(vector< vector< pair<int,int> > >&pi,int mem_req){
	int mem_index = ceil(log10(mem_req)/log10(2));
	if(mem_index>=pi.size())
	{
		cout << "Invalid memory allocation" << endl;
		return;
	}
	else 
	{
		if(pi[mem_index].size()>0)
		{
			cout << "Memory allocated is" << pi[mem_index][pi[mem_index].size()-1].first << " " << pi[mem_index][pi       [mem_index].size()-1].second << endl;
			pi[mem_index].pop_back();
			return;
 		}
		else 
		{
			int i;
			for(i=mem_index+1;i<pi.size();i++)
			{
				if(pi[i].size()>0) break;
			}
			if(i==pi.size())
			{
				cout << "Memory cannot be allocated" << endl;
				return;			
			}
			else 
			{
				int high=pi[i][pi[i].size()-1].second,low=pi[i][pi[i].size()-1].first,mid;
				pi[i].pop_back();
				for(int j=i-1;j>=mem_index;j--)
				{
					mid = (high+low)/2;
					pi[j].push_back(make_pair(mid+1,high));
					high = mid;
				}
				cout << "Memory allocation:" << low << " " << high << endl; 			
				return;			
			}
		}
	}
}
int main()
{
	int size=128;
	//cin>>"Enter the amount of memory you have initially :-">>size;
	int nb = floor(log10(size)/log10(2)); //no lockas
	vector< vector< pair<int,int> > >pi(nb+1); //initialise as sizes zero.
	pi[nb].push_back(make_pair(0,size-1));
	while(1)
	{
		int mem_req;
		cout<<"Request memory:";
		cin>>mem_req;
		memory_allocator(pi,mem_req);
		for(int i=0;i<pi.size();i++){
				if(pi[i].size()>0) cout << "{"  << pi[i][0].first << ", " << pi[i][0].second << "}" << " ";
				else cout << "{}" << " ";
				}
		cout << endl;
		int cond;
		cout << "Want to free memory (1/0)" << endl;	
		cin >> cond;
		if()	
	}
}


