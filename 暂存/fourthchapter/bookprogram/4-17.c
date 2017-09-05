/*************************************************************************
	> File Name: 4-17.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月24日 星期三 21时39分17秒
 ************************************************************************/

#include<stdio.h>
int main(void)
{
    char a[]="Linux C Program ",b[20],c[20];
    char *p1,*p2;
    int i;
    for(i= 0;*(a+i); i++)
    {
        *(b+i)= *(a+i);
    }
    *(b+i)='\0';
    p1= a;
    p2= c;
    for(i = 0;*p1;p1++,p2++)
    {
        *p2=*p1;
    }
    *p2='\0';
    printf("a == %s\n",a);
    printf("b == %s\n",b);
    printf("c == %s\n",c);
    printf("p1 == %c\n",p1);
    printf("p2 == %c\n",p2);
    return 0;


}
