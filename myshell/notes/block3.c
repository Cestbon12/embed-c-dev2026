#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

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
while(token!=NULL&&argc<MAX_ARGS-1)
{
args[argc++]=token;
token=strtok(NULL," ");
}
args[argc]=NULL;

if(strcmp(args[0],"exit")==0)
{
break;
}
if(strcmp(args[0],"cd")==0)
{
	if(args[1]==NULL)
	{chdir(getenv("HOME"));
	}else{
		if(chdir(args[1])!=0){
			perror("cd");
		}
	}
	continue;
}

pid_t pid=fork();
if(pid<0)
{
perror("fork");
continue;
}
else if(pid==0)
{
execvp(args[0],args);
perror("execvp");
}
else{
NULL;
}
}
return 0;
}


