#include <stdio.h>
#include <windows.h>

void index2(){
    system("cls");
    printf("=======================================\n");
    printf("1.���˼�\n");
    printf("2.˫�˼�\n");
    printf("3.VIP�׷�\n");
    printf("=======================================\n");
    printf("����������ҪԤ���ķ���:\n");
    int k;
    scanf("%d",&k);
    while(k!=1&&k!=2&&k!=3)
    {
        printf("������������䣺");
        scanf("%d",&k);
    }
}
