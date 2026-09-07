#include<stdio.h>
#include<string.h>
#define MAX 100
char stack[MAX];
int top=-1;
void push(char c){
	stack[++top]=c;
}
char pop(){
	if (top==-1)return '\0';
	return stack[top--];
	
}
int isEmpty(){
	return top==-1;
}
int isMatch(char left,char right){
	return(left=='('&&right==')')||
	   	  (left=='['&&right==']')||
	   	  (left=='{'&&right=='}');
}
int isValid(char *s){
	int i;
	for(i=0;s[i]!='\0';i++)
	{
		char ch=s[i];
		if (ch=='('||ch=='['||ch=='{'){
			push(ch);
		}
		else if(ch==')'||ch==']'||ch=='}'){
			if(isEmpty())return 0;
			char left =pop();
			if(!isMatch(left,ch))return 0;
		}
	}
	return isEmpty();
}
int main()
{
	char s1[]="()[]{}";
	char s2[]="([)]";
	printf("%s:%d\n",s1,isValid(s1));
	printf("%s:%d\n",s2,isValid(s2));
	return 0;
}
