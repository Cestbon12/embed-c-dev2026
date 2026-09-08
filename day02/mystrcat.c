#include<stdio.h>
char *mystrcat(char *dest,const char *src){
int i =0;
int j=0;
while(dest[i]!='\0')
{
i++;
}
while(src[j]!='\0'){
dest[i]=src[j];
i++;
j++;
}
dest[i]='\0';
return dest;}
int main(){
char src[]="word";
char dest[50]="hello";
mystrcat(dest,src);
printf("%s\n",dest);
return 0;
}
