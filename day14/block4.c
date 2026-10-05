#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
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
if(strlen(line)==0)
{
continue;
}
int argc=0;
char *token=strtok(line," ");
while(token!=NULL&&argc<MAX_ARGS-1)
{
args[argc++]=token;
token=strtok(NULL," ");
}
args[argc]=NULL;
char *infile=NULL;
char *outfile=NULL;

for(int i=0;args[i]!=NULL;i++){
	if(strcmp(args[i],">")==0){
		outfile=args[i+1];
		args[i]=NULL;
		break;
	}else if(strcmp(args[i],"<")==0){
		infile=args[i+1];
		args[i]=NULL;
		break;
		}
	}

if(strcmp(args[0],"exit")==0)
{
break;
}
if(strcmp(args[0],"cd")==0)
{
	if(args[1]==NULL){
		chdir(getenv("HOME"));
	}else{
		if(chdir(args[1])!=0)
		{
		perror("cd");
		}
	}
	continue;
}
pid_t pid = fork();
if (pid < 0) {
    perror("fork");
    continue;
} else if (pid == 0) {
    // 子进程：先改 fd，再 exec
    if (infile != NULL) {
        int fd = open(infile, O_RDONLY);
        if (fd < 0) { perror("open"); exit(1); }
        dup2(fd, 0);
        close(fd);
    }
    if (outfile != NULL) {
        int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) { perror("open"); exit(1); }
        dup2(fd, 1);
        close(fd);
    }
    execvp(args[0], args);
    perror("execvp");
    exit(1);
} else {
    // 父进程：等待
    wait(NULL);
}
}
return 0;
}
