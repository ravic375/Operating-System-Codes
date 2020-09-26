#include<bits/stdc++.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
using namespace std;
int main() 
{ 
    int fd1,fd2,N; 
    const char * myfifo1 = "/tmp/myfifo1"; 
   const char * myfifo2 = "/tmp/myfifo2"; 
    mkfifo(myfifo1, 0666);
	mkfifo(myfifo2, 0666); 
  cin>>N;
    int arr1[N], arr2[N],arr3[N]; 
        for(int i=0;i<N;i++)
		cin>>arr1[i];
        fd1 = open(myfifo1, O_WRONLY); 
        write(fd1, arr1,sizeof(arr2)); 
        close(fd1); 

  	fd2 = open(myfifo2, O_WRONLY); 
        write(fd2, arr1,sizeof(arr2)); 
        close(fd2);

        fd1 = open(myfifo1, O_RDONLY); 
        read(fd1, arr2, sizeof(arr2)); 
	cout<<"From program 1:\n";
		for(int i=0;i<N;i++)
		cout<<arr2[i]<<" ";
		cout<<endl;
        close(fd1);
	fd2 = open(myfifo2, O_RDONLY); 
        read(fd2, arr3, sizeof(arr3)); 
	cout<<"From program 2:\n";
		for(int i=0;i<N;i++)
		cout<<arr3[i]<<" ";
		cout<<endl;
        close(fd2);
    return 0; 
} 
