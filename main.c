#include <stdio.h>
#include <stdlib.h>
#include "./User/User.h"
#include "./Front/Front.h"
#include "./struct/struct.h"

int main()
{
    void index();
    index();
    readRoom();
    int i;
    scanf("%d",&i);
    while(i!=1&&i!=2)
    {
        printf("������������䣺");
        scanf("%d",&i);
    }
    switch(i)
    {
        case 2: getPassword();break;
        case 1: User();break;
    }
    writeGuest();
    return 0;
}

void index()
{
    printf("=======================================\n");
    printf("1.�ͻ�\n");
    printf("2.ǰ̨\n");
    printf("=======================================\n");
    printf("��ѡ��");
}


