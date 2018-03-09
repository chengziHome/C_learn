#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

int listLen(struct ListNode *head)
{
    int len = 0;
    while(head!=NULL)
    {
        len++;
        head = head->next;
    }
}

struct ListNode* initList(int arr[],int len)
{
    if(len==0) return NULL;
    struct ListNode *head,*pre;
    head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = arr[0];
    pre = head;

    int i = 1;
    while(i<len)
    {
        struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode*));
        node->val = arr[i];
        node->next = NULL;
        pre->next =node;
        pre = node;
        i++;
    }

    return head;

};

void printList(struct ListNode *head)
{
    struct ListNode *p;
    p = head;
    printf("[");
    while(p!=NULL)
    {
        printf("%d,",p->val);
        p = p->next;
    }
    printf("]\n");
    free(p);
}

void chooseSort(struct ListNode *head)
{
    int len = listLen(head);
    struct ListNode *p,*q,*min;
    p = head;
    while(p->next!=NULL)
    {
        min = p;
        q = p->next;
        while(q!=NULL)
        {
            if(q->val < min->val)
            {
                min = q;
            }
            q = q->next;
        }
        // For simplicity,just swap the val,not the node
        if(p!=min)
        {
            int tmp = p->val;
            p->val = min->val;
            min->val = tmp;
        }
        p = p->next;
    }
}

void t2014_3_1()
{
    int a[10] = {1,2,3,2,3,6};
    struct ListNode *head = initList(a,6);
    chooseSort(head);
    printList(head);
}

void exch(int* nums,int i,int j)
{
    if(i!=j)
    {
        int tmp = *(nums+i);
        *(nums+i) = *(nums+j);
        *(nums+j) = tmp;
    }
}

int partition(int* nums,int lo,int hi)
{
    int i = lo,j = hi+1;
    while(1)
    {
        while(*(nums+(++i)) <= *(nums+lo)) if(i==hi) break;
        while(*(nums+(--j)) >= *(nums+lo)) if(j==lo) break;
        if(i>=j) break;
        exch(nums,i,j);
    }
    exch(nums,lo,j);
    return j;
}

void quickSort(int* nums,int lo,int hi)
{
    if(lo>=hi) return;
    int j = partition(nums,lo,hi);
    quickSort(nums,lo,j);
    quickSort(nums,j+1,hi);
}

void printIntArray(int *a,int len)
{
    printf("[");
    int i =0;
    while(i<len)
    {
        printf("%d,",*(a+i));
        i++;
    }
    printf("]\n");
}

int quickSelect(int* nums,int lo,int hi,int k)
{
    if(lo==hi) return *(nums+lo);
    int j = partition(nums,lo,hi);
    if(j==k-1) return *(nums+j);
    else if(j<k-1) return quickSelect(nums,j+1,hi,k);
    else return quickSelect(nums,lo,j-1,k);
}

int findKthLargest(int* nums,int size,int k)
{
    return quickSelect(nums,0,size-1,k);
}

void t2014_3_2()
{
    int arr[9] = {1,5,7,3,7,2,4,9,2};
    int kth_num = findKthLargest(arr,9,4);
    printf("kth_num:%d\n",kth_num);
    quickSort(arr,0,8);
    printIntArray(arr,9);
}

void t2014_3_4()
{
    int a,b,c;
    for(int i=100;i<1000;i++)
    {
        a = i/100;
        b = (i%100)/10;
        c = i%10;
        if(a!=b && b!=c && a!=c && a*b==c)
            printf("%d\t",i);
    }
}

void reverse(char *s)
{
    int len = strlen(s);
    int i = 0,j = len-1;
    while(i<j)
    {
        char tmp = *(s+i);
        *(s+i) = *(s+j);
        *(s+j) = tmp;
        i++;
        j--;
    }
}

void t2014_4_1()
{
    char str[100];
    printf("Please input a string:\n");
    scanf("%s",str);
    printf("Before reserve:%s\n",str);
    reverse(str);
    printf("After reserve:%s\n",str);
}

// return 1:ID1>ID2;0:ID1==ID2;-1:ID1<ID2;
int birthdaycmp(char *ID1,char *ID2)
{
    int lo = 6,hi = 13;
    while(lo<=hi)
    {
        if(*(ID1+lo)>*(ID2+lo)) return 1;
        else if(*(ID1+lo)<*(ID2+lo)) return -1;
        else lo++;
    }
    return 0;
}

void t2014_4_2()
{
    char ID1[19],ID2[19];
    printf("Please input ID1:\n");
    scanf("%s",ID1);
    printf("Please input ID2:\n");
    scanf("%s",ID2);
    printf("%d\n",birthdaycmp(ID1,ID2));

}

void t2014_4_3()
{
    int i,n;
    float x,item = 1,sum = 1;
    printf("Please input float x:\n");
    scanf("%f",&x);
    printf("Please input integer n(>0):\n");
    scanf("%d",&n);

    for(i=1;i<=n;i++)
    {
        item = -1*(item*x/i);
        sum += item;
    }

    printf("sum:%f\n",sum);
}


void movemax(struct ListNode *head)
{
    if(head == NULL) return;
    struct ListNode *max,*p,*pre;

    pre=head;
    p = head->next;
    max=head;
    while(p!=NULL)
    {
        if(p->val > max->val) max = p;
        pre = p;
        p = p->next;
    }
    int tmp = max->val;
    max->val = pre->val;
    pre->val = tmp;

}

void t2014_4_4()
{
    int a[6] = {2,5,8,2,4,1};
    struct ListNode *list = initList(a,6);
    printList(list);
    movemax(list);
    printList(list);
}

void dePrime(int a)
{

    printf("primes is :\n");
    int i = 2;
    while(i<a)
    {
        if(a%i==0)
        {
            printf("%d\t",i);
            a = a/i;
            i =2;
        }
        i++;
    }
    printf("%d\n",a);

}

void t2013_1()
{
    int x;
    printf("Please input a number to dePrime:\n");
    scanf("%d",&x);
    dePrime(x);


}

void t2013_2()
{
    int sum =1,item = 1,n,x,i=1;
    printf("Please input the x:\n");
    scanf("%d",&x);
    printf("Please input the n:\n");
    scanf("%d",&n);
    while(i<=n)
    {
        item = -1 * (item*x/i);
        sum = sum + item;
        i++;
    }
    printf("sum is :%d",sum);

}

void delNumAlp(char *str)
{
    char *slow,*fast;
    slow = str;
    fast = str;
    while(*fast!='\0')
    {
        if(*fast>='0' && *fast<='9' || *fast>='A' && *fast<='Z' || *fast>='a' && *fast<='z')
        {
            fast++;
        }else{
            *slow = *fast;
            slow++;
            fast++;
        }
    }
    *slow = '\0';
}

void t2013_3()
{
    char str[100];
    printf("Please input a string:\n");
    scanf("%s",str);
    printf("%s\n",str);
    delNumAlp(str);
    printf("%s\n",str);

}

void t2013_4()
{
    printf("Please input integers ,end with '#'\n");
    char x[10];
    struct ListNode *pre=NULL;
    while(1)
    {
        printf("Please input a integer:\n");
        scanf("%s",x);
        if(strcmp(x,"#")==0) break;
        struct ListNode *tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp->val = atoi(x);
        tmp->next = pre;
        pre = tmp;
    }
    printf("The result is:\n");
    printList(pre);
}

struct ListNode* reserveList(struct ListNode *head)
{
    if(head==NULL) return NULL;
    struct ListNode *pre,*cur,*after;
    pre = NULL;
    cur = head;
    after = head->next;
    while(after!=NULL)
    {
        cur->next = pre;

        pre = cur;
        cur = after;
        after = after->next;
    }
    cur->next = pre;
    return cur;
}

void t2013_5()
{
    int a[10] = {1,2,3,4,5,6};
    struct ListNode *list = initList(a,6);
    printList(list);
    struct ListNode *new_list = reserveList(list);
    printList(new_list);
}


// Interesting!
void t2012_1_2()
{
    char pa[] = "ASDFG";
    char *pb = "ABC";
//    pb[1] = 'C';
    pa[2] = 'Y';

    printf("%s\n",pa);
}

void t2012_3_3()
{
    char str[50],*p;
    int nums[10] = {0};
    printf("Please input a String:\n");
    scanf("%s",str);
    p = str;
    while(*p!='\0')
    {
        nums[*p-'0']++;
        p++;
    }
    printf("The result is:\n");
    for(int i=0;i<10;i++)
    {
        printf("%d:%d\n",i,nums[i]);
    }
}

struct student
{
  int no;
  int score;
};


// the point is:you should do anything in the first loop;
void t2012_3_4()
{
    int std_num = 10,i=0,max=-1,min=200,tmp_score;
    struct student stds[std_num],*p;
    p = stds;


    while(i<std_num)
    {
        printf("Please input %dth student's score:\n",i+1);
        scanf("%d",&tmp_score);
        if(tmp_score<min) min = tmp_score;
        if(tmp_score>max) max = tmp_score;

        (p+i)->no = i;
        (p+i)->score = tmp_score;
        i++;
    }

    for(i=0;i<std_num;i++)
    {
        if((p+i)->score ==max)
            printf("%dth student get the max score:%d\n",(p+i)->no+1,(p+i)->score);
    }

    for(i=0;i<std_num;i++)
    {
        if((p+i)->score ==min)
            printf("%dth student get the min score:%d\n",(p+i)->no+1,(p+i)->score);
    }


}

void t2017_3_2()
{
    float d;

    scanf("%f",&d);
    if(d == 3.25)
        printf("Y");
    else
        printf("N");
}




int main()
{

    int a = 5;
    printf("%d,%d\n",a,a++);
//    t2017_3_2();
//    t2012_3_4();
//    t2012_3_3();
//    t2012_1_2();
//    t2013_5();
//    t2013_4();
//    t2013_3();
//    t2013_2();
//    t2013_1();
//    t2014_4_4();
//    t2014_4_3();
//    t2014_4_2();
//    t2014_4_1();
//    t2014_3_4();
//    t2014_3_2();
//    t2014_3_1();
    return 0;
}
