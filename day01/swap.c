#include<stdio.h>
void swap(int *x,int *y){
int temp;
temp= *y;
*y=*x;
*x=temp;
}
int main(){
int a=10;int b=20;
 swap(&a,&b);
printf("a:%d,b:%d",a,b);
return 0;}
