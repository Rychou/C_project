#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"
Room room[9];
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
    isLeft(k);
}
void isLeft(int i){//查询某种房型房间余量，输出用户可预定房号
    switch(i){
    case 1:
        printf("您选择的房型为单人房,以下房间可预订\n");
        for(int i=0;room[i].roomStatus!=1&&i<3;i++)
            printf("%d ",room[i].num);
        break;
    case 2:
        printf("您选择的房型为双人房,以下房间可预订:\n");
        for(int i=3;room[i].roomStatus!=1&&i<6;i++)
            printf("%d ",room[i].num);
        break;
    case 3:
        printf("您选择的房型为VIP房,以下房间可预订\n");
        for(int i=6;room[i].roomStatus!=1&&i<9;i++)
            printf("%d ",room[i].num);
        break;
    }

}

void readRoom(){ //读取房间文件
    FILE *fp;
    int i=0;
    if((fp=fopen("data/Room.txt","rb"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    while(!feof(fp)&&i<9){
        fscanf(fp,"%d%d%d%d",&room[i].num,&room[i].rank,&room[i].price,&room[i].roomStatus);
        i++;
    }
}
