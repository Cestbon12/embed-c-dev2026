#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>


#define MAX_LINE 1024
#define MAX_ARGS 64
int main(void)
{
char line[MAX_LINE];
char *args[MAX_ARGS];
while(1)
{
printf("myshell:");
fflush(stdout);
if(fgets(line,MAX_LINE,stdin)==NULL)
{
break;
}
line[strcspn(line,"\n")]='\0';
int argc=0;
char *token=strtok(line," ");
while(token!=NULL&&argc<MAX_LINE-1)
{
args[argc++]=token;
token=strtok(NULL," ");
}
args[argc]=NULL;
pid_t pid =fork();
if(pid<0)
{
perror("fork");
continue;
}
else if(pid==0){
	execvp(args[0],args);
	perror("execvp");
	exit(1);
}
else{
wait(NULL);
}
}
return 0;
}


