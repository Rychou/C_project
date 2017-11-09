#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"
#include "time.h"

Room room[9];
int gNum;//预定某房间的人数
int rNum;//存储用户预定的房间号
int Day;//入住天数
int aLength=0;//统计User.txt文件导入数组后的数组长度
extern Date now;//当前时间
Date pre;//预约的时间
Guest guest[9];
Guest allGuest[56];
int emptyRoom[3];

void User(){//输出用户界面
    system("cls");
    printf("\n");
    printf(" @@@@@@@@@@@@@@用户@@@@@@@@@@@@@@@@@\n");
    printf("@                                   @\n");
    printf("@      1.预约                       @\n");
    printf("@      2.取消预约                   @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("请输入指令：");
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



void Reserve(){//输出预约界面
    system("cls");
    printf("\n");
    printf(" @@@@@@@@@@@@@@前台@@@@@@@@@@@@@@@@@\n");
    printf("@                                   @\n");
    printf("@      1.单人间（68元/天）          @\n");
    printf("@      2.双人间（168元/天）         @\n");
    printf("@      3.VIP套房（268元/天）        @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("请输入您需要预定的房型:");
    int k;
    scanf("%d",&k);
    while(k!=1&&k!=2&&k!=3)
    {
        printf("输入错误，请重输：");
        scanf("%d",&k);
    }
    if(isLeft(k)!=0){
        getRNum();
        getGNum();
        inputMsg(pre,2);
    }

}

int isLeft(int i){//查询某种房型房间余量，输出用户可预定房号
    int k;
    int j = 0;
    printf("预约年份：");
    scanf("%d",&pre.year);
    printf("预约月份：");
    scanf("%d",&pre.month);
    printf("预约日：");
    scanf("%d",&pre.day);
    while(1){
        if(judgeDate()==1) break;
        printf("预约时间不正确，请重新输入\n");
        printf("预约年份：");
        scanf("%d",&pre.year);
        printf("预约月份：");
        scanf("%d",&pre.month);
        printf("预约日：");
        scanf("%d",&pre.day);
    }
    printf("预订天数：");
    scanf("%d",&Day);
    switch(i){
        case 1:
            for(k=0;k<3;k++)
                if(room[k].roomStatus==0){
                        emptyRoom[j]= room[k].num;
                        j++;
                }else{
                    if(judgeOrder(k)){
                        emptyRoom[j]= room[k].num;
                        j++;
                    }
                }
            if(j!=0){
                printf("您选择的房型为单人房,以下房间可预订\n");
                int z;
                for(z=0;z<j;z++)
                    printf("%d ",emptyRoom[z]);
                    printf("\n");
            }else {
                printf("单人房已满！\n");
            }
            break;
        case 2:
            for(k=3;k<6;k++)
                if(room[k].roomStatus==0){
                        emptyRoom[j]= room[k].num;
                        j++;
                }else{
                    if(judgeOrder(k)){
                        emptyRoom[j]= room[k].num;
                        j++;
                    }
                }
            if(j!=0){
                printf("您选择的房型为双人房,以下房间可预订\n");
                int z;
                for(z=0;z<j;z++)
                    printf("%d ",emptyRoom[z]);
                    printf("\n");
            }else {
                printf("双人房已满！\n");
            }
            break;
        case 3:
            for(k=6;k<9;k++)
                if(room[k].roomStatus==0){
                        emptyRoom[j]= room[k].num;
                        j++;
                }else{
                    if(judgeOrder(k)){
                        emptyRoom[j]= room[k].num;
                        j++;
                    }
                }
            if(j!=0){
                printf("您选择的房型为VIP房,以下房间可预订\n");
                int z;
                for(z=0;z<j;z++)
                    printf("%d ",emptyRoom[z]);
                    printf("\n");
            }else {
                printf("VIP房已满！\n");
            }
            break;
    }
    int t = j;
    for(;j<3;j++){
        emptyRoom[j]=0;
    }
    return t;
}

int judgeDate(){//判断日期是否满足要求
    int monthday = MonthHas(now.year,now.day);//这个月有几天
    if(now.day+7>monthday){
        if(now.month == 12){
            if(pre.year == now.year){
                if(pre.month == now.month){
                    if(pre.day >= now.day&&pre.day <= monthday)
                        return 1;
                }
            }else if(pre.year == now.year+1){
                    if(pre.month == 1){
                        if(pre.day <= 7-(monthday-now.day))
                            return 1;
                    }
                }
        }else {
            if(pre.year == now.year){
                if(pre.month == now.month){
                    if(pre.day >= now.day&&pre.day <= monthday)
                        return 1;
                }else if(pre.month == now.month+1){
                    if(pre.day <= 7-(monthday-now.day))
                        return 1;
                }
            }
        }
    }else {
        if(pre.year == now.year){
            if(pre.month == now.month){
                if(pre.day >= now.day&&pre.day <= now.day+7)
                    return 1;
            }
        }

    }
    return 0;
}

int judgeLast(Date dt,int d,int i){//判断时间有无空余
    Date date = allGuest[i].time;
    int day = allGuest[i].day;
    Date last = getLastDt(date,day);
    Date orderLast = getLastDt(dt,d);
    if(bigger(dt,last)){
        return 1;
    }
    if(bigger(date,orderLast)){
        return 1;
    }
    return 0;
}

int judgeOrder(int k){//判断房间可不可以预约
    int i;
    for(i = 0;i < aLength;i++){
        if(allGuest[i].num == room[k].num){
            if(!judgeLast(pre,Day,i)){
                return 0;
            }
        }
    }
    return 1;
}

void getRNum(){//在isLeft（）打印出可预定房号后 获取用户指令
    printf("请输入您要选择的房号:");
    scanf("%d",&rNum);
    while(1){
        if(rNum !=0){
            if(emptyRoom[0] == rNum){
                break;
            }else if(emptyRoom[1] == rNum){
                break;
            }else if(emptyRoom[2] == rNum){
                break;
            }
        }
        printf("请重新输入您要选择的房号:");
        scanf("%d",&rNum);
    }
}

void getGNum(){//获取预定某房间的人数
    printf("请输入人数:");
    scanf("%d",&gNum);
    printf("\n");
}

void inputMsg(Date date,int i){//输入入住客户的信息，可以多个客户
    char ID[30];//身份证
    char name[30];//名字
    int phone;//电话
    int k;
    for(k=0;k<gNum;k++){
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
        guest[k].time = date;
        guest[k].day = Day;
        guest[k].status = i;
    }
    printf("操作成功，您选择的房号为:%d\n",rNum);
    changeRStatusTo_1();
    writeGuest();
}

void changeRStatusTo_1(){//改变房间状态为1
    int i;
    for(i=0;i<9;i++){
        if(room[i].num==rNum)
            room[i].roomStatus = 1;
    }
    FILE *fp1;
    if((fp1=fopen("data/Room.txt","w"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    for(i=0;i<9;i++){
        fprintf(fp1,"%d %d %d %d \r\n",room[i].num,room[i].rank,room[i].price,room[i].roomStatus);
    }
    fclose(fp1);
}

void writeGuest(){//追加写入客户信息
    FILE *fp;
    if((fp=fopen("data/User.txt","a"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    int i;
    for(i=0;i<gNum;i++){
        fprintf(fp,"%s %s %d %d %d %d %d %d %d \r\n",guest[i].ID,guest[i].name,guest[i].phone,guest[i].num,guest[i].status,guest[i].time.year,guest[i].time.month,guest[i].time.day,guest[i].day);
    }
    fclose(fp);
}



void cancelReservation(){//输出取消预约界面
    char ID[20];//用户身份证号，用于验证用户信息，避免退别人房间的情况
    Guest gst2[56];//gst1[]用来读入User.txt数据，gst2[]用来储存gst1[]中去掉取消预定的用户信息的信息
    int r;//房间号
    int b = 0;
    printf("请输入您要取消预定的房间号：");
    scanf("%d",&r);
    while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
        printf("输入错误，请重新输入:");
        scanf("%d",&r);
    }
    printf("请输入身份证号进行验证：");
    scanf("%s",ID);
    /*复制用户结构数组再从新写入文件 实现退订删除用户数据功能*/
    int count=0;//记录预订同一房间的人数
    int k;
    Guest temp;
    for(k=0;k<aLength;k++){
        if(strcmp(ID,allGuest[k].ID)==0&&allGuest[k].num==r&&allGuest[k].status==2){
            temp = allGuest[k];
            b = 1;
            break;
        }
    }
    int c = 0;//统计订了这间房的人数
    if(b){
        int j = 0;
        k = 0;
        while(k<aLength&&j<aLength){
            if(allGuest[k].num ==r){
                c++;
                if(allGuest[k].time.year == temp.time.year&&allGuest[k].time.month == temp.time.month&&allGuest[k].time.day == temp.time.day&&allGuest[k].status==2){
                    k++;
                    count++;
                    continue;
                }

            }
            gst2[j]=allGuest[k];
            j++;
            k++;
        }
        int length = aLength-count;//gst2[]数组的长度
        if(c==count){
            changeRStatusTo_0(r);
        }
        deleteGuest(gst2,length);
        printf("验证中......");
        Sleep(3000);
        printf("\n");
        printf("取消预订成功！欢迎再次光临!\n");
    }else {
        printf("验证中......");
        Sleep(3000);
        printf("\n");
        printf("取消预订失败!\n");
    }
    readGuest();
}

void changeRStatusTo_0(int roomNum){//修改房间状态为0
    int i;
    for(i=0;i<9;i++){
        if(room[i].num==roomNum)
            room[i].roomStatus = 0;
    }
    FILE *fp;
    if((fp=fopen("data/Room.txt","w"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    for(i=0;i<9;i++){
        fprintf(fp,"%d %d %d %d \r\n",room[i].num,room[i].rank,room[i].price,room[i].roomStatus);
    }
    fclose(fp);
}

void deleteGuest(Guest gst2[],int length){//用户取消预定删除特定用户信息
    FILE *fp;
    if((fp=fopen("data/User.txt","w"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    int i;
    for(i=0;i<length;i++){
        fprintf(fp,"%s %s %d %d %d %d %d %d %d \r\n",gst2[i].ID,gst2[i].name,gst2[i].phone,gst2[i].num,gst2[i].status,gst2[i].time.year,gst2[i].time.month,gst2[i].time.day,gst2[i].day);
        //printf("%s %s %d %d %d %d %d %d %d \r\n",gst2[i].ID,gst2[i].name,gst2[i].phone,gst2[i].num,gst2[i].status,gst2[i].time.year,gst2[i].time.month,gst2[i].time.day,gst2[i].day);
    }
    fclose(fp);
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

void readGuest(){//读取User.txt
    FILE *fp;
    int i=0;
    aLength = 0;
    if((fp=fopen("data/User.txt","rb"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    while(!feof(fp)&&i<56){
        if(fscanf(fp,"%s%s%d%d%d%d%d%d%d",&allGuest[i].ID,&allGuest[i].name,&allGuest[i].phone,&allGuest[i].num,&allGuest[i].status,&allGuest[i].time.year,&allGuest[i].time.month,&allGuest[i].time.day,&allGuest[i].day)!=EOF){
                aLength++;
        }

        i++;
    }
    fclose(fp);
}
