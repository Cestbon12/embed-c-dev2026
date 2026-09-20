#include<stdio.h>
#include<unistd.h>
int main(){
	printf("before fork\n");
	pid_t pid=fork();
	if(pid==0){
		printf("I am child,pid=%d\n",getpid());
	}else{
		printf("I am parent,pid=%d,child=%d\n",getpid(),pid);
	}
	printf("after fork\n");
	return 0;
}

