/*************************************************************************
	> File Name: 4.4.2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月24日 星期三 22时11分29秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(void)
{
    char a[20],b[20],c[20]="nnn";
    fgets(a,sizeof(a),stdin);//代替gets()函数，更安全一点
    printf("a == ");
    puts(a);
    strncpy(b,a,sizeof(a));
    printf("b == ");
    puts(b);
    strncat(b,c,sizeof(c));
    printf("b == ");
    puts(b);
    printf("c == ");
    puts(c);
    printf("\n");
    return 0;
}
