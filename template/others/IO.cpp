template<class T> inline void RD(T &x){  
    char c; 
	for (c = getchar(); c < '0' || c > '9'; c = getchar());
	x = c - '0'; 
	for (c = getchar(); '0' <= c && c <= '9'; c = getchar()) x = x * 10 + c - '0';  
}  

void getInt(int &num){  
    char in;    
    while((in=getchar())>'9'||in<'0');   
    num=in-'0';     
    while(in=getchar(),in>='0'&&in<='9')     
        num*=10,num+=in-'0';  
}   
