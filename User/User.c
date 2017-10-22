#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"
Room room[9];
int gNum;//预定某房间的人数
int rNum;//存储用户预定的房间号
Guest guest[9];
void index2(){//输出用户界面
    system("cls");
    printf("=======================================\n");
    printf("1.单人间（68元/天）\n");
    printf("2.双人间（168元/天）\n");
    printf("3.VIP套房（268元/天）\n");
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
    getRNum();
    getGNum();
    inputMsg();
}
void isLeft(int i){//查询某种房型房间余量，输出用户可预定房号
    switch(i){
    case 1:
        printf("您选择的房型为单人房,以下房间可预订\n");
        for(int i=0;room[i].roomStatus!=1&&i<3;i++)
            printf("%d ",room[i].num);
        printf("\n");
        break;
    case 2:
        printf("您选择的房型为双人房,以下房间可预订:\n");
        for(int i=3;room[i].roomStatus!=1&&i<6;i++)
            printf("%d ",room[i].num);
        printf("\n");
        break;
    case 3:
        printf("您选择的房型为VIP房,以下房间可预订\n");
        for(int i=6;room[i].roomStatus!=1&&i<9;i++)
            printf("%d ",room[i].num);
        printf("\n");
        break;
    }
}
void getRNum(){//在isLeft（）打印出可预定房号后 获取用户指令
    printf("请输入您要预定的房号\n");
    scanf("%d",&rNum);
}
void getGNum(){//获取预定某房间的人数
    printf("请输入预定人数:");
    scanf("%d",&gNum);
    printf("\n");
}
void inputMsg(){//输入入住客户的信息，可以多个客户
    char ID[18];//身份证
    char name[10];//名字
    int phone;//电话
    for(int k=0;k<gNum;k++){
        printf("请输入第%d个客人的信息\n",k+1);
        printf("身份证号:");
        scanf("%s",ID);
        strcpy(guest[k].ID,ID);//将获取的信息复制到全局变量guest[k].ID中
        printf("\n");
        printf("名字:");
        scanf("%s",name);
        strcpy(guest[k].name,name);
        printf("\n");
        printf("电话号：");
        scanf("%d",&phone);
        guest[k].phone = phone;
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
void writeGuest(){//追加写入客户信息
    FILE *fp;
    if((fp=fopen("data/User.txt","a"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    for(int i=0;i<gNum;i++){
        fprintf(fp,"%s %s %d \r\n",guest[i].ID,guest[i].name,guest[i].phone);
    }
    fclose(fp);

}
