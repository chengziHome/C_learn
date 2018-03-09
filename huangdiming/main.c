#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// print the multiplication table
void b3_7()
{
    printf("   *");
    int i,j;
    for(i=1;i<=9;i++){
        printf("%4d",i);
    }
    printf("\n");
    for(i=1;i<=9;i++){
        printf("%4d",i);
        for(j=1;j<=i;j++)
        {
            printf("%4d",j*i);
        }
        printf("\n");
    }
}


// convert a unsigned integer(0<...<2^16-1) to binary
void b3_8()
{
    unsigned int number,temp,i;
    printf("Please input a number:\n");
    scanf("%u",&number);
    printf("%4x\n",number);
    for(i=0;i<=15;i++)
    {
        temp = number&0x8000;
        temp >>= 15;
        printf("%1d",temp);
        number <<=1;
    }
    printf("\n");
}

// the number and its square has the same k;
void b3_10()
{
    int d,i,j,k,flag1,flag2;
    printf("Please input d:\n");
    scanf("%d",&d);
    printf("d=%d\n",d);
    for(i=1;i<=100;i++)
    {
        flag1=0;
        j=i;
        while((j>0)&&(flag1==0))
        {
            k = j%10;
            j = j/10;
            if(k==d) flag1=1;
        }
        if(flag1==1)
        {
            flag2=0;
            j = i*i;
            while((j>0)&&(flag2==0))
            {
                k = j%10;
                j = j/10;
                if(k==d) flag2=1;
            }
            if(flag2==1) printf("%-4d %-4d\n",i,i*i);
        }

    }
}

// print the kth element of a number's hexadecimal
void b3_13()
{
    int num,k,i,j,tmp;
    char ch;
    printf("Please input the num:\n");
    scanf("%d",&num);
    printf("Please input the k:\n");
    scanf("%d",&k);
    j = num;
    i=0;
    do{
        tmp = j%16;
        j /= 16;
        i++;
    }while((j>0)&&(i<k));
    tmp = i<k?0:tmp;
    ch = tmp<10?tmp+'0':tmp-10+'a';
    printf("the %dth digit of the hexadecimal number 0x%04x is %c.\n",k,num,ch);
}

// this fun can be used to delete the duplicated chars in a string.
void b3_15()
{
    char ch_old,ch_new;
    ch_old='.';
    do{
        scanf("%c",&ch_new);
        if(ch_new==ch_old) continue;
        ch_old = ch_new;
        printf("%c",ch_new);
    }while(ch_new!='.');
    printf("\n");

}

void b4_1()
{
    //You'd better do anything required in one loop
}


//screen　the primes in range(200)
void b4_2()
{
    int prime[201] = {0};
    int i,j,count;

    for(i=2;i<sqrt(200);i++)
    {
        if(prime[i]==0)
            for(j=i*2;j<=200;j+=i)
                prime[j] = 1;
    }

    count = 0;
    printf("The primes in range(200) are below:\n");
    for(i=2;i<=200;i++)
        if(prime[i]==0)
        {
            printf("%-7d",i);
            count++;
            if(count%5==0) printf("\n");
        }
}

// bubble sort,with a guard;
void b4_3()
{
    int a[100],count,i,j,tmp;
    int n = 8,changed=0;

    printf("Please input the array \n");
    for(i=0;i<n;i++)
    {
        printf("a[%d]=\n",i);
        scanf("%d",&a[i]);
    }

    for(i=1;i<n;i++)
    {
        changed==0;
        for(j=0;j<n-1;j++)
        {
            if(a[j]>a[j+1])
            {
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                changed==1;
            }
        }
        if(changed==0) break;
    }

    printf("The result is:\n");
    for(i=0;i<n;i++)
    {
        printf("%-5d",a[i]);
    }

}


void b4_str_fun()
{
    char str[10] = "chengzi";
    char *p = str;
    char *q = "Sichuan";
    printf("%d\n",strlen(str));
    printf("%d\n",strlen(p));
    printf("%d\n",strlen(q));
//
//    strcpy(str,q);
//    printf("%s\n",str);
//    strcpy(p,q);
//    printf("%s\n",p);
//
//    strncpy(str,q,2);
//    printf("%s\n",str);

//    strcat(str,q);
//    printf("%s\n",str);


    printf("cmp:%d\n",strcmp(str,"chengzi"));

    printf("strchr:%s\n",strchr(str,'z'));

    printf("strstr:%s\n",strstr(str,"e"));

    printf("atof:%f\n",atof("12"));

    printf("atoi:%d\n",atoi("12"));

//    itoa(123,str,10);
//
//    printf("itoa:%s\n",str);

}

void b4_5()
{
    char word[20];
    int len;

    printf("Please input a word:\n");
    scanf("%s",word);
    len = strlen(word);
    if(len>1 && word[len-1]=='y' && word[len-2]!='a' && word[len-2]!='e' && word[len-2]!='i'
       && word[len-2]!='o' && word[len-2]!='u')
    {
        word[len-1] = 'i';
        word[len] = 'e';
        word[len+1] = 's';
        word[len+2] = '\0';
    }
    else if(len>1 && (word[len-1]=='s' || word[len-1]=='x' || (word[len-1]=='h' && (word[len-2]=='c' && word[len-2]=='s'))))
    {
        word[len] = 'e';
        word[len+1] = 's';
        word[len+2] = '\0';
    }
    else if(word[len-1] == 'o')
    {
        word[len] = 'e';
        word[len+1] = 's';
        word[len+2] = '\0';
    }
    else
    {
        word[len] = 's';
        word[len+1] = '\0';
    }

    printf("The result is:%s\n",word);

}

void b5_6_fibonacci(int n)
{
    int f[n],i,*p;
    p = f;
    *p = 0;
    *(p+1) = 1;
    i=2;
    p += 2;
    while(i<n)
    {
        *p = *(p-1) + *(p-2);
        i++;
        p++;
    }
    for(i=0;i<n;i++)
    {
        printf("%-4d\n",f[i]);
    }

}

void b5_10_str()
{
    char str1[30],str2[30];
    char *p1,*p2;
    printf("Please input a string:\n");
    scanf("%s",str1);
    printf("Please input another string:\n");
    scanf("%s",str2);

    p1 = str1;
    p2 = str2;

    while((*p1)!='\0')
    {
        p1++;
    }
    while(*p2!='\0')
    {
        *p1 = *p2;
        p1++;
        p2++;
    }

    *p1 = '\0';
    printf("The result is:%s\n",str1);

}

void b5_11_strlen()
{
    char s[20];
    char *p = s;
    printf("please input a string:\n");
    scanf("%s",s);
    while(*p!='\0')
    {
        p++;
    }

    printf("The string's len is:%d\n",p-s);

}

void b5_22()
{
    char *p1,*p2,s1[20],s2[20];
    scanf("%s%s",s1,s2);
    p1 = s1;
    p2 = s2;
    printf("s1=%s,s2=%s\n",s1,s2);
    int i,j,k;
    k = 0;
    for(i=0;*(p1+i)!='\0';i++)
    {
        for(j=0;*(p2+j)!='\0' && *(p2+j)!=*(p1+i);j++)
            ;
        if(*(p2+j)=='\0')
        {
            *(p1+k) = *(p1+i);
            k++;
        }

    }
    *(p1+k) = '\0';
    printf("The result is :%s\n",p1);

}

void b5_23()
{
    char *point;
    long int b_addr,e_addr;

    printf("Please input two address:\n");
    scanf("%lx%lx",&b_addr,&e_addr);
    for(int i = b_addr;i<e_addr;i+=16)
    {
        printf("%05lx:",i);
        point = (char*)i;
        for(int j=0;j<16;j++)
        {
            if(j==8)
                printf("   ");
            printf("%02x",*point);
            point++;
        }
        printf("\n");
    }
}

int main()
{

    b5_23();
//    b5_22();
//    b5_11_strlen();
//    b5_10_str();
//    b5_6_fibonacci(33);
//    b4_5();
//    b4_str_fun();
//    b4_3();
//    b4_2();
//    b3_15();
//    b3_13();
//    b3_10();
//    b3_8();
//    b3_7();
    return 0;







}








