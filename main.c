#include <stdio.h>
#include <stdlib.h>
#include "./User/User.h"
#include "./Front/Front.h"
#include "./struct/struct.h"

int main()
{
    void index();
    void readRoom();
    readRoom();
    int i;
    index();
    scanf("%d",&i);
    while(i!=1&&i!=2)
    {
        printf("输入错误，请重输：");
        scanf("%d",&i);
    }
    switch(i)
    {
     //   case 2: getPassword();break;
        case 1: index2();break;
    }

    return 0;
}

void index()
{
    printf("=======================================\n");
    printf("1.客户\n");
    printf("2.前台\n");
    printf("=======================================\n");
    printf("请选择：");
}


