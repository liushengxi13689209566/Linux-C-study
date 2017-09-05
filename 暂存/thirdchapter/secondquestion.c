#include<stdio.h>
int main(void)
{
    int a,b,c,d,e;
    for(a= 1;a<= 5;a++)
        for(b= 1; b<= 5;b++)
            for(c=  1;c<= 5;c++)
                for(d= 1;d<= 5;d++)
                    for(e= 1;e<= 5;e++)
                     {
                         if((a == 3)+(b == 1) == 1 && (b== 2)+(e == 4) == 1&& (c == 1)+  (d ==  2) == 1 &&(d == 3)+(c == 5) == 1&&(e == 4)+(a == 1) == 1 )                                                                         //等于号之间不能有空格，如： = =
                         {
                             printf("a== %d,b== %d,c== %d,d== %d,e== %d \n",a,b,c,d,e);
                             break;
                         }
                     }
    return 0;
}
