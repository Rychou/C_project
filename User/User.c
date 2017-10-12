#include <stdio.h>
#include <windows.h>

void index2(){
    system("cls");
    printf("=======================================\n");
    printf("1.单人间\n");
    printf("2.双人间\n");
    printf("3.VIP套房\n");
    printf("=======================================\n");
    printf("请输入您需要预定的房型:\n");
    int k;
    scanf("%d",&k);
    while(k!=1&&k!=2&&k!=3)
    {
        printf("输入错误，请重输：");
        scanf("%d",&k);
    }
}
