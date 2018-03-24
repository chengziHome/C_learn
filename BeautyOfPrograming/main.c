#include <stdio.h>
#include <stdlib.h>

int b2_1_findOnesInBin(int a)
{
    //the input a is a int8 number.
    //the point is that a is just a int8 instead of int16 or int32.
    //so this problem will be solved by hash map efficiently at a small space price
    // Remember:for search-like problem,the hash method will always be the fastest.
    //Mentions:what about int64?Yes,the answer is easy to get:we just need to cut the number.
}

void b2_2_factorial(int n)
{
    int res = 0,i;
    while(n>=5)
    {
        i = n;
        while(i%5==0)
        {
            res++;
            i=i/5;
        }
        n--;
    }
    printf("result:%d\n",res);
}

void b2_2_factorial2(int n)
{
    int ret = 0;
    while(n)
    {
        ret += n/5;
        n = n/5;
    }
    printf("result:%d\n",ret);

}

void b2_2_factorial3()
{
    //Problem 2,the point is factorization
}

void b2_3_tango(int a[],int n)
{
    //one side,learn the algorithmic;other side,learn the implement skills.

    int candidate;
    int i,nTimes;
    for(i=nTimes=0;i<n;i++)
    {
        if(nTimes==0)
        {
            candidate=a[i];
            nTimes=1;
        }
        else
        {
            if(candidate==a[i])
                nTimes++;
            else
                nTimes--;
        }
    }
    printf("The result is:%d\n'",candidate);
}


int main()
{

    int a[]={4,1,4,6,4,4,2,4,6};
    b2_3_tango(a,9);
//    b2_2_factorial(27);
//    b2_2_factorial2(27);

    return 0;
}
