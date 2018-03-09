#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <math.h>
#include <string.h>

void testSwitch()
{
    int i = 1;
    switch(i)
    {
        case 1:printf("%d",1);
        case 2:printf("%d",2);
            break;
        case 3:printf("%d",3);
        default:
            printf("else");
    }
}


void testArray()
{
    int n;
    int arr[n*2];
    printf("%d",arr[1]);
}

void findPrimeNum()
{
    int d,j,n=200;
    int mark[201] = {0};
    for(d=2;d<=sqrt(200);d++)
    {
        if(mark[d]==0)
        {
            for(j=d*2;j<=n;j+=d)
            {
                mark[j] = 1;
            }
        }
    }

    int k;
    int count = 0;
    for(k=2;k<=n;k++)
    {
        if(mark[k]==0)
        {
            printf("%d\t",k);
            count++;
            if(count%5==0)
                printf("\n");
        }
    }


}

void testString()
{
    char word[20];
    char word1[20];
    char word2[20];
//    scanf("%s",word);
    gets(word);
    puts(word);
    printf("len:%d\n",strlen(word));
    strcpy(word1,word);//copy
    printf("word1:%s\n",word1);
    strncpy(word2,word,4);//copy some
    printf("word2:%s\n",word2);
    strcat(word1,word2);//concat,the result will be put in the first array
    printf("word1:%s\n",word1);
    printf("%d\n",strcmp("c","b"));

    printf("%s",strstr("12345","223"));//search the subStr,return the first pointer or null;


}

struct point
{
    int x;
    int y;
    int z;
};

void testStruct()
{

    struct point points[2] ;
    points[0].x = 1;
    points[0].y = 2;
    points[1].x = 3;
    points[1].y = 4;
    printf("points[0].x:%x\n",&points[0]);
    printf("points[1].y:%x\n",&points[1]);
    // the memory will be allocated in order;
}

void bookSystem3()
{


    int cardno;
    char name[20];
    printf("***************************************");
    printf("************Welcome to books system***********");
    printf("***************************************");
    printf("~~~~~~~~~~~~~~~~\t\t\t\t~~~~~~~~~~~~~~~~~~\n");
    printf("Please input your card no:\n");
    scanf("%d",&cardno);
    printf("Please input your name:\n");
    scanf("%s",&name);
    printf("\n Welcome,%s! Your card no is:%d\n",name,cardno);


    char ch;
    while(1)
    {
        printf("\t\t Please select the operation:\n");
        printf("1: <List books>\n");
        printf("2: <Borrow books>\n");
        printf("3: <Management system>\n");
        printf("4: <Return books>\n");
        printf("0: <Exit>\n");

        scanf("%s",&ch);


        switch(ch)
        {
            case '1':
                printf("-----Welcome to List Books System-----\n");
                printf("Input any to return!\n");
                scanf("%s",&ch);
                break;
            case '2':
                printf("-----Welcome to Borrow Books System-----\n");
                printf("Input any to return!\n");
                scanf("%s",&ch);
                break;
            case '3':
                printf("-----Welcome to Management Books System-----\n");
                printf("Input any to return!\n");
                scanf("%s",&ch);
                break;
            case '4':
                printf("-----Welcome to Return Books System-----\n");
                printf("Input any to return!\n");
                scanf("%s",&ch);
                break;
            case '0':
                printf("-----Welcome to visit next time-----\n");
                break;
            default:
                printf("Input error!Please input 0-4.Please input again:\n");
                printf("Enter any key to restart!");
                scanf("%s",&ch);
        }


    }

}

void bookSystem4()
{
    char book[100][50],d[10];
    int num=0,i;

    printf("--------------------Welcome to Book System 4------------------------");

    while(1)
    {
        printf("--Please select your operation--\n");
        printf("1.Add a book\n");
        printf("2,List the books\n");
        printf("3,exit the system\n");

        scanf("%s",&d);






        if(strcmp(d,"1")==0)
        {
            do{
                printf("Please input the book's name:\n");
                scanf("%s",book[num++]);
                while(1){
                    printf("Continue to add book?\n");
                    printf("1,continue\n");
                    printf("2,end\n");
                    scanf("%s",&d);
                    if(strcmp(d,"1")==0 || strcmp(d,"2")==0)
                        break;
                    else
                        printf("\n Input error,please input again:\n");
                }
                if(strcmp(d,"2")==0)
                    break;
                i++;

            }while(i<=100);
        }
        else if(strcmp(d,"2")==0)
        {
            printf("List the books:\n");
            printf("Now,there are %d books.\n",num);
            if(num!=0){
                i = 0;
                printf("Here are the books:\n");
                while(i<num){
                    printf("%d:%s\n",i+1,book[i]);
                    i++;
                }
            }
            printf("Entry any key to return\n");
            scanf("%s",&d);

        }
        else if(strcmp(d,"3")==0)
        {
            printf("Good bye!\n");
            break;
        }
        else
        {
            printf("Input error,please input again!\n");
        }
    }

}

void bookSystem5()
{
    char book[100][50],bookname[50],d[10],*p,*query;

    int num=0,i=0;
    p = book;
    query = bookname;
    printf("--------------------Welcome to Book System 5------------------------\n");

    while(1)
    {
        printf("--Please select your operation--\n");
        printf("1.Add a book\n");
        printf("2,Search the books\n");
        printf("3,List the books\n");
        printf("4,exit the system\n");

        scanf("%s",d);
        if(strcmp(d,"1")==0)
        {
            do{
                printf("Please input the book's name:\n");
                scanf("%s",(book[num++]));
                printf("book:%s",(book[num-1]));
                while(1){
                    printf("Continue to add book?\n");
                    printf("1,continue\n");
                    printf("2,end\n");
                    scanf("%s",d);
                    if(strcmp(d,"1")==0 || strcmp(d,"2")==0)
                        break;
                    else
                        printf("\n Input error,please input again:\n");
                }
                if(strcmp(d,"2")==0)
                    break;
                i++;

            }while(i<=100);
        }
        else if(strcmp(d,"2")==0)
        {
            if(num==0)
            {
                printf("There are no book you need!\n");
                printf("Entry any key to continue.\n");
                scanf("%s",d);
                continue;
            }
            printf("Please input the keyword.\n",num);
            scanf("%s",query);
            for(i=0;i<num;i++)
            {
                printf("%s\n",query);

                if(strstr(book[i],query))
                {
                    printf("The book's no you search is:%d\n",i+1);
                    printf("Entry and key to continue!\n");
                    scanf("%s",d);
                    continue;
                }
            }
            if(i==num)
            {
                printf("Sorry,there are no book you want!\n");
                printf("Entry any key to continue\n");
                scanf("%s",d);
            }


        }
        else if(strcmp(d,"3")==0)
        {
            printf("List the books:\n");
            printf("Now,there are %d books.\n",num);
            if(num!=0){
                i = 0;
                printf("Here are the books:\n");
                while(i<num){
                    printf("%d:%s\n",i+1,book[i]);
                    i++;
                }
            }
            printf("Entry any key to return\n");
            scanf("%s",&d);
        }
        else if(strcmp(d,"4")==0)
        {
            printf("Good bye!\n");
            break;

        }
        else
        {
            printf("Input error,please input again!\n");
        }
    }

}



void testPointer()
{
    int *pi,*pj,a[5]={1,2,3,4,5};


    pi = &a[1];
    pj = &a[4];
    printf("pi=%x ,pj=%x\n",pi,pj);
    printf("pi-pj=%x",pj-pi);



}

void fibonacci()
{
    int f[15],i;
    int *p = f;
    *p=0;
    *(p+1) = 1;
    printf("%4d%4d",*p,*(p+1));
    p += 2;
    for(i=2;i<15;i++)
    {
        *p = *(p-1) + *(p-2);
        printf("%4d",*p);
        p++;
    }
}

void pointerStruct()
{
    struct point p,*pp;
    pp = &p;
    p.x = 1;
    (*pp).y= 2;
    pp->z = 3;
    printf("%d,%d,%d",p.x,p.y,p.z);


}

int getStrLen(char *s)
{
    char *p = s;
    while(*p!='\0')
    {
        p++;
    }
    return p-s;
}

//todo:after learn method;
char* concatStr(char *s1,char *s2)
{
    int len1 = getStrLen(s1),
        len2 = getStrLen(s2);
    char result[len1+len2],*s=result;
    while(*s1!='\0')
    {
        *s = *s1++;
        s++;
    }
    while(*s2!='\0')
    {
        *s = *s2++;
        s++;
    }
    return s;
}


void upperCase()
{
    char string[30],*p;
    p = string;
    printf("Please input a string\n");
    scanf("%s",string);
    printf("\n%s\n",string);

    while(*p!='\0')
    {
        if((*p>='a') && (*p<='z'))
        {
            *p += ('A'-'a');
        }
        p++;
    }

    printf("%s\n",string);


}

void testPointerArray()
{
    char *color[] =
    {
        "red",
        "yellow",
        "blue"
    };
    int i;
    printf("Enter a number\n");
    scanf("%d",&i);
    printf("i=%i\n\n",i);
    printf("%s\n",color[i-1]);

}


struct student
{
    int no;
    int score;
};

void t2016_5_1()
{
    struct student students[200],*p;
    p = students;

    int stu_num = 5;

    int i;
    for(i=0;i<stu_num;i++)
    {
        printf("Please input no.%d student's score.\n",i+1);
        (*(p+i)).no = i+1;
        scanf("%d",&(*(p+i)).score);

    }

    for(i=0;i<stu_num-1;i++)
    {
        int j;
        int min =i;
        for(j=i+1;j<stu_num;j++)
        {
            if((*(p+j)).score<(*(p+min)).score)
            {
                min = j;
            }
        }

        if(min!=i)
        {
            struct student tmp;
            tmp = *(p+i);
            *(p+min) = *(p+i);
            *(p+i) = tmp;
        }
    }

    int max_score = (*(p+stu_num-1)).score;
    printf("Below are the students who get the max score:%d\n",max_score);
    for(i=stu_num-1;i>=0;i--)
    {

        if((*(p+i)).score<max_score)
        {
            break;
        }
        printf("no.%d  student get the max socre:%d\n",(*(p+i)).no,(*(p+i)).score);

    }


}


struct node
{
    float val;
    struct node *next;
};

void t2016_5_2()
{
    int num = 5,i;
    struct node *head,*s;

    printf("Please input %d nums:\n",num);

    for(i=0;i<num;i++)
    {
        s = (struct node *)malloc(sizeof(struct node));
        scanf("%f",&((*s).val));
        (*s).next = head;
        head = s;
    }

    while(head!=NULL)
    {
        printf("%f\n",(*head).val);
        head = head->next;
    }

}


float t2015_1_2(int x,int n)
{
    float item = 1,sum = 1;
    int i;

    for(i=1;i<=n;i++)
    {
        item *= (-1)*x/i;
        sum += item;
    }

}

void t2015_2_1()
{
    int in,x,i=2;
    printf("Please input a number:\n");
    scanf("%d",&in);
    printf("The result is:\n");

    x = in;
    while(i<=x)
    {
        if((x%i)==0 && isPrime(i) && i!=in)
        {
            printf("%d\t",i);
            x = x/i;
            i=2;
            continue;
        }
        i++;
    }
}

int isPrime(int x)
{

    for(int i=2;i<=sqrt(x);i++)
    {
        if((x%i)==0)
        {
            return 0;
        }
    }
    return 1;
}

void t2015_2_2_Joseph()
{
    int n,m,k,a[100];
    int count,i,num;
    printf("Please input the number of people(<100):n=\n");
    scanf("%d",&n);
    printf("Please input the count:m=\n");
    scanf("%d",&m);
    printf("Please input the begin:k=\n");
    scanf("%d",&k);

    i = k-1;
    for(int j=0;j<n;j++)
    {
        a[j] = j+1;
    }

    num = n;
    while(num>1)
    {
        count=0;
        while(count<m)
        {

            while(a[i]==0)
            {
                i=(i+1)%n;
            }

            count++;
            i = (i+1)%n;
        }

        a[i==0?(n-1):i-1]=0;
        num--;
    }
    for(int j=0;j<n;j++)
    {
        if(a[j]!=0)
        {
            printf("The last person is no.%d\n",a[j]);
            break;
        }
    }


}


int str2int(char *p,int len)
{
    int res = 0;

    while(len>0)
    {
        res = res*10 + (*p-'0');
        p++;
        len--;
    }
    return res;
}

void t2015_3_1()
{
    char str[100],*s,*p;
    int i=0,arr[100];
    printf("Please input a str:\n");
    scanf("%s",str);
    s = str;
    while(*s != '#')
    {
        if(*s >= '0' && *s <='9')
        {
            p = s+1;
            while(*p >= '0' && *p <='9') p++;

            arr[i++] = str2int(s,p-s);
            s = p;
        }else{
            s++;
        }

    }
    arr[i] = -1;

    int j =0;
    while(arr[j]!=-1)
    {
        printf("%d\n",arr[j++]);
    }


}

void str_util()
{
    printf("%d",atoi("123"));
    printf("%f",atof("123"));

}

int isFloat(char *c)
{
    char *p = c;
    while(*p!='\0')
    {
        if(*p == '.') return 1;
        p++;
    }
    return 0;
}

void sort_int(int a[],int len)
{
    int i=0,j=0;
    for(i=0;i<len-1;i++)
    {
        int max = i;
        for(j=i+1;j<len;j++)
        {
            if(a[j]<a[max])
            {
                max = j;
            }
        }
        if(max!=i)
        {
            int tmp = a[i];
            a[i] = a[max];
            a[max] = tmp;
        }
    }
}

void sort_float(float a[],int len)
{
    int i=0,j=0;
    for(i=0;i<len-1;i++)
    {
        int max = i;
        for(j=i+1;j<len;j++)
        {
            if(a[j]<a[max])
            {
                max = j;
            }
        }
        if(max!=i)
        {
            int tmp = a[i];
            a[i] = a[max];
            a[max] = tmp;
        }
    }
}

void t2015_3_2()
{
    int int_arr[100],int_count=0,float_count=0,input_count=0;
    float float_arr[100];
    char str[20];
    printf("Please input your numbers:,use '#' to end\n");
    while(input_count<100)
    {
        scanf("%s",str);
        if(strcmp(str,"#")==0) break;
        if(isFloat(str))
            float_arr[float_count++] = atof(str);
        else
            int_arr[int_count++] = atoi(str);

    }
    sort_int(int_arr,int_count);
    sort_float(float_arr,float_count);

    int i=0;
    while(i<int_count)
    {
        printf("%d\t",int_arr[i++]);
    }

    while(float_count>0)
    {
        printf("%f\t",float_arr[float_count-1]);
        float_count--;
    }


}

// A set impliment

struct set
{
    int val;
    struct set *next;
};

struct set* init(int a[],int len)
{
    if(len==0) return NULL;
    struct set *head,*pre;
    int i=1;


    head = (struct set *)malloc(sizeof(struct set));
    head->val = a[0];
    pre = head;
    while(i<len)
    {
        struct set *tmp = (struct set *)malloc(sizeof(struct set));
        tmp->val = a[i];
        tmp->next = NULL;
        pre->next = tmp;
        pre = tmp;
        i++;
    }
    return head;
};

//if add successful,return 1;else return 0;
struct set* add(struct set *head,int val)
{
    if(head==NULL)
    {
        struct set *h = (struct set *)malloc(sizeof(struct set));
        h->val = val;
        return h;
    }
    struct set *p;
    p = head;
    while(p->next!=NULL)
    {
        if(p->val==val) return head;
        p = p->next;
    }
    if(p->val==val) return 0;
    struct set *tmp = (struct set *)malloc(sizeof(struct set));
    tmp->val = val;
    p->next = tmp;
    return head;

}

struct set* del(struct set *head,int val)
{
    if(head==NULL) return NULL;
    if(head->val == val)
    {
        return head->next;
    }

    struct set *p = head;
    while(p->next!=NULL)
    {
        if((p->next)->val==val)
        {
            p->next = (p->next)->next;
            return head;
        }
        p = p->next;
    }

    return head;

}

struct set * get(struct set *head,int val)
{
    struct set *p = head;
    while(p!=NULL)
    {
        if(p->val == val) return p;
        p = p->next;
    }
    return NULL;
};

struct set* inter_set(struct set *s1,struct set *s2)
{

    struct set *head,*pre,*p1,*p2;
    head = (struct set *)malloc(sizeof(struct set));
    pre = head;

    while(s1!=NULL)
    {
        if(get(s2,s1->val)!=NULL)
        {
            struct set *tmp = (struct set *)malloc(sizeof(struct set));
            tmp->val = s1->val;
            tmp->next = NULL;
            pre->next = tmp;
            pre = tmp;
        }
        s1 = s1->next;
    }
    return head->next;

};

struct set* union_set(struct set *s1,struct set *s2)
{
    if(s1==NULL) return s2;
    if(s2==NULL) return s1;
    struct set *head,*pre;
    head = (struct set *)malloc(sizeof(struct set));
    pre = head;
    while(s1!=NULL)
    {
        struct set *tmp = (struct set *)malloc(sizeof(struct set));
        tmp->val = s1->val;
        tmp->next = NULL;
        pre->next = tmp;
        pre = tmp;
        s1 = s1->next;
    }
    while(s2!=NULL)
    {
        if(get(head,s2->val)==NULL)
        {
            struct set *tmp = (struct set*)malloc(sizeof(struct set));
            tmp->val = s2->val;
            tmp->next = NULL;
            pre->next = tmp;
            pre = tmp;
        }

        s2 = s2->next;
    }
    return  head->next;

};

void printSet(struct set *head)
{
    struct set *p;
    p = head;
    printf("[");
    while(p!=NULL)
    {
        printf("%d,",p->val);
        p = p->next;
    }
    printf("]\n");
}

void t2015_3_3()
{

    struct set *head = NULL,*head1 = NULL,*head2=NULL;
    int a[] = {1,2,3};
    int b[] = {2,3,4,5};
    head1 = init(a,3);
    head2 = init(b,4);
    head1 = add(head1,5);
    head1 = del(head1,6);
    printSet(head1);
    head1 = get(head1,1);
    printSet(head1);
    printSet(head2);
    head = inter_set(head1,head2);
    printSet(head);
    head = union_set(head1,head2);
    printSet(head);

}


void swap_str1(char *p,char *q)
{
    char temp[100];
    strcpy(temp,p);
    strcpy(p,q);
    strcpy(q,temp);
}

/*
    Interesting
*/
void swap_str2(char **p,char **q)
{
    char *tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}

//　s1,s2 must not be:char* type.
void t2014_1_2()
{
    char s1[10] = "chengzi";
    char s2[20] = "jiazase";
    swap_str2(&s1,&s2);
    printf("str1:%s;str2:%s\n",s1,s2);

    swap_str1(s1,s2);
    printf("str1:%s;str2:%s\n",s1,s2);

}

void main()
{

//    t2014_1_2();


//    t2015_3_3();
//    t2015_3_2();
//    bookSystem5();

//    testArray();
//    findPrimeNum();
//    testString();
//    testStruct();
//    testPointer();
//    fibonacci();
//    pointerStruct();
//    printf("%d\n",getStrLen("chengzi"));
//    printf("%s\n",*concatStr("chengzi","123"));
//    upperCase();
//    testPointerArray();
//    char name[10];
//    char *str = name;
//    scanf("%s",str);
//    printf("%s\n",str);

//    t2015_2_1();

    t2015_2_2_Joseph();
//    t2015_3_1();

//    str_util();

}





