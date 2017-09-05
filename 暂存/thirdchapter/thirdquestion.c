/*************************************************************************
	> File Name: thirdquestion.c
	> Author: 
	> Mail: 
	> Created Time: 2017年05月24日 星期三 21时13分04秒
 ************************************************************************/

#include<stdio.h>
int main(void)
{
    int sum= 7;
    while(1)
    {
        if(sum%2 == 1&& sum%3 == 2 &&sum%5 == 4&&sum%6 == 5&&sum%7 == 0)
        {
            printf("The stair's count is %d \n",sum);
            break;
        }
        sum++;
    }
    return 0;
}
