#include<stdio.h>
#include<string.h>

#define MAX_LINE 1024

int main(void)
{
char line[MAX_LINE];
while(1)
{
printf("myshell:");
fflush(stdout);
if(fgets(line,MAX_LINE,stdin)==NULL)
{
break;
}
else
{
line[strcspn(line,"\n")]='\0';
printf("scanf:%s\n",line);
}
}
return 0;
}
