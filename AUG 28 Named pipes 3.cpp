
#include<bits/stdc++.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
using namespace std;
int main() 
{ 
    int fd4; 
  
    // FIFO file path 
    const char * myfifo = "/tmp/myfifo2"; 
    mkfifo(myfifo, 0666); 
int N;
cin>>N;
int ARR3[N];
        fd4 = open(myfifo,O_RDONLY); 
        read(fd4, ARR3, sizeof(ARR3)); 
        close(fd4); 
        fd4 = open(myfifo,O_WRONLY); 
        write(fd4, ARR3, sizeof(ARR3)); 
        close(fd4); 
    return 0; 
} 

