
#include<bits/stdc++.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
using namespace std;
int main() 
{ 
    int fd3; 
  
    // FIFO file path 
    const char * myfifo = "/tmp/myfifo1"; 
    mkfifo(myfifo, 0666); 
int N;
cin>>N;
int ARR2[N];
        fd3 = open(myfifo,O_RDONLY); 
        read(fd3, ARR2,  sizeof(ARR2)); 
        close(fd3); 
sort(ARR2,ARR2+N);
        fd3 = open(myfifo,O_WRONLY); 
        write(fd3, ARR2, sizeof(ARR2)); 
        close(fd3); 
    return 0; 
} 

