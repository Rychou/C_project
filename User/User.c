#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"

Room room[9];
int gNum;//预定某房间的人数
int rNum;//存储用户预定的房间号
int Day;//入住天数
int aLength=0;//统计User.txt文件导入数组后的数组长度
Guest guest[9];

void User(){//输出用户界面
    system("cls");
    printf("=======================================\n");
    printf("1.预定\n");
    printf("2.取消预定\n");
    printf("=======================================\n");
    int i;
    scanf("%d",&i);
    while(i!=1&&i!=2)
    {
        printf("输入错误，请重输：");
        scanf("%d",&i);
    }
    switch(i){
        case 1 : Reserve();break;
        case 2 : cancelReservation();break;
    }
}
void Reserve(){
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
void cancelReservation(){
    char ID[20];//用户身份证号，用于验证用户信息，避免退别人房间的情况
    Guest gst1[20],gst2[20];//gst1[]用来读入User.txt数据，gst2[]用来储存gst1[]中去掉取消预定的用户信息的信息
    readGuest(gst1);
    int r;//房间号
    printf("请输入您要取消预定的房间号：");
    scanf("%d",&r);
    while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
        printf("输入错误，请重新输入:");
        scanf("%d",&r);
    }
    /*复制用户结构数组再从新写入文件 实现退订删除用户数据功能*/
    int count=0;//记录预订同一房间的人数
    for(int k=0;k<20;k++){
        if(gst1[k].num ==r)
            count++;
    }
    for(int j=0;j<aLength;j++){
        if(gst1[j].num!=r){
                gst2[j] = gst1[j];
        }
        else {
            gst2[j]=gst1[j+count];
        }
    }
    int length = aLength-count;//gst2[]数组的长度
    printf("请输入身份证号进行验证：");
    scanf("%s",ID);
    for(int i=0;i<aLength;i++){
            if(strcmp(ID,gst1[i].ID)==0){
                printf("验证成功,正在退房......\n");
                changeRStatusTo_0(r);
                deleteGuest(gst2,length);
                printf("退房成功！欢迎再次光临!");
            }
    }
}
void isLeft(int i){//查询某种房型房间余量，输出用户可预定房号
    switch(i){
    case 1:
        printf("您选择的房型为单人房,以下房间可预订\n");
        for(int k=0;k<3;k++)
            if(room[k].roomStatus==0)
                printf("%d ",room[k].num);
        printf("\n");
        break;
    case 2:
        printf("您选择的房型为双人房,以下房间可预订:\n");
        for(int k=3;k<6;k++)
            if(room[k].roomStatus==0)
                printf("%d ",room[k].num);
        printf("\n");
        break;
    case 3:
        printf("您选择的房型为VIP房,以下房间可预订\n");
        for(int k=6;k<9;k++)
            if(room[k].roomStatus==0)
                printf("%d ",room[k].num);
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
    char ID[30];//身份证
    char name[30];//名字
    int phone;//电话
    for(int k=0;k<gNum;k++){
        guest[k].num = rNum;
        printf("请输入第%d个客人的信息\n",k+1);
        printf("身份证号:");
        scanf("%s",ID);
        //判断ID输入是否规范
        while(1){
            if(strlen(ID)==18||strlen(ID)==15){
                    strcpy(guest[k].ID,ID);//将获取的信息复制到全局变量guest[k].ID中
                    break;
            }
            else {
                printf("输入长度不符，请重新输入(15位或者18位):");
                scanf("%s",ID);
            }
        }
        printf("名字:");
        scanf("%s",name);
        strcpy(guest[k].name,name);
        printf("电话号：");
        scanf("%d",&phone);
        guest[k].phone = phone;
    }
    printf("预定成功，您预定的房号为:%d",rNum);
    changeRStatusTo_1();
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
    fclose(fp);
}
//读取User.txt
void readGuest(Guest array[]){
    FILE *fp;
    int i=0;
    if((fp=fopen("data/User.txt","rb"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    while(!feof(fp)&&i<20){
        if(fscanf(fp,"%s%s%d%d",&array[i].ID,&array[i].name,&array[i].phone,&array[i].num)!=EOF){
                aLength++;
        }

        i++;
    }
    fclose(fp);
}
//改变房间状态为1
void changeRStatusTo_1(){
    for(int i=0;i<9;i++){
        if(room[i].num==rNum)
            room[i].roomStatus = 1;
    }
    FILE *fp1;
    if((fp1=fopen("data/Room.txt","w"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    for(int i=0;i<9;i++){
        fprintf(fp1,"%d %d %d %d \r\n",room[i].num,room[i].rank,room[i].price,room[i].roomStatus);
    }
    fclose(fp1);
}
//修改房间状态为0
void changeRStatusTo_0(int roomNum){
    for(int i=0;i<9;i++){
        if(room[i].num==roomNum)
            room[i].roomStatus = 0;
    }
    FILE *fp;
    if((fp=fopen("data/Room.txt","w"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    for(int i=0;i<9;i++){
        fprintf(fp,"%d %d %d %d \r\n",room[i].num,room[i].rank,room[i].price,room[i].roomStatus);
    }
    fclose(fp);
}
//用户取消预定删除特定用户信息
void deleteGuest(Guest gst2[],int length){
    FILE *fp;
    if((fp=fopen("data/User.txt","w"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    for(int i=0;i<length;i++){
        fprintf(fp,"%s %s %d %d \r\n",gst2[i].ID,gst2[i].name,gst2[i].phone,gst2[i].num);
    }
    fclose(fp);
}
//追加写入客户信息
void writeGuest(){
    FILE *fp;
    if((fp=fopen("data/User.txt","a"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    for(int i=0;i<gNum;i++){
        fprintf(fp,"%s %s %d %d \r\n",guest[i].ID,guest[i].name,guest[i].phone,guest[i].num);
    }
    fclose(fp);
}
