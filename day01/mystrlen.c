#include<stdio.h>
#include<stddef.h>
size_t my_strlen(const char *s){
size_t len =0;
while(s[len]!='\0')
{
len++;
}
return len;
}
int main(){
const char *str="hello";
printf("length of '%s' is %zu\n",str,my_strlen(str));
return 0;}
