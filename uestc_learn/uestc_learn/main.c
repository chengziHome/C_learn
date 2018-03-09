#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

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

void main()
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

        ch = getch();


        switch(ch)
        {
            case '1':
                printf("-----Welcome to List Books System-----\n");
                printf("Input any to exit!\n");
                getch();
                continue;
            case '2':
                printf("-----Welcome to Borrow Books System-----\n");
                printf("Input any to exit!\n");
                getch();
                continue;
            case '3':
                printf("-----Welcome to Management Books System-----\n");
                printf("Input any to exit!\n");
                getch();
                continue;
            case '4':
                printf("-----Welcome to Return Books System-----\n");
                printf("Input any to exit!\n");
                getch();
                continue;
            case '0':
                printf("-----Welcome to visit next time-----\n");
                break;
            default:
                printf("Input error!Please input 0-4.Please input again:\n");
                printf("Enter any key to restart!");
                getch();
        }


    }

}






