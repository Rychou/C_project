#define PWDLEN 20
#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "../struct/struct.h"
#include "../User/User.h"
#include "../User/time.h"
extern int gNum;
extern Room room[9];
extern int emptyRoom[3];
extern Guest allGuest[56];
extern int aLength;
extern int Day;
extern Date now;
extern void pause();


/**
* 获取用户输入的密码
* @param  pwd     char*  保存密码的内存的首地址
* @param  pwdlen  int    密码的最大长度
**/

void getPassword(){//密码输入界面
    system("cls");
    char pwd[20];
    int count = 3;
    printf("请输入登录密码：\n");
    getpwd(pwd, PWDLEN);
    while(comparePwd(pwd) != 1 && count > 0)
    {
        printf("密码错误，请重输：\n");
        getpwd(pwd, PWDLEN);
        -- count;
    }
    if(comparePwd(pwd) == 1)
    {
        front();
    }
}

void getpwd(char *pwd, int pwdlen){//得到密码
    char ch = 0;
    int i = 0;
    while(i<pwdlen){
        ch = getch();
        if(ch == '\r'){  //回车结束输入
            printf("\n");
            break;
        }

        if(ch=='\b' && i>0){  //按下删除键
            i--;
            printf("\b \b");
        }else if(isprint(ch)){  //输入可打印字符
            pwd[i] = ch;
            printf("*");
            i++;
        }
    }
    pwd[i] = '\0';
}

int comparePwd(char *pwd){//验证密码
    int i = 0;
    if(strlen(pwd)!=6){
        return -1;
    }
    char passWd[6] ={'1','2','3','4','5','6'};
    for(;i < 6; i++)
    {
        if(*(pwd+i) != passWd[i])
            return -1;
    }
    return 1;
}



void front(){//前台功能函数
    front_index();
    int i = 0;
     while((i=getch())!= 0x1B)
    {
        readGuest();
        readRoom();
        switch(i)
        {
            case 49:
                printf("\n");
                checkIn();
                pause();
                front_index();
                continue;
            case 50:
                printf("\n");
                checkOut();
                pause();
                front_index();
                continue;
            case 51:
                printf("\n");
                search();
                printf("查询");
                pause();
                front_index();
                continue;
        }
    }
}

void front_index(){//打印前台功能页面
    system("cls");
    printf("\n");
    printf(" @@@@@@@@@@@@@@前台@@@@@@@@@@@@@@@@@\n");
    printf("@                                   @\n");
    printf("@      1.入住                       @\n");
    printf("@      2.结账                       @\n");
    printf("@      3.查询                       @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("请输入指令：");
}



void checkIn(){//入住功能函数

    system("cls");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@1.预定入住                         @\n");
    printf("@2.单人间                           @\n");
    printf("@3.双人间                           @\n");
    printf("@4.VIP房                            @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("请输入指令:");
    int k;
    scanf("%d",&k);
    while(k!=1&&k!=2&&k!=3)
    {
        printf("输入错误，请重输：");
        scanf("%d",&k);
    }
    switch(k){
        case 1: checkReserve();
                break;
        case 2:
        case 3:
        case 4: if(front_isLeft(k)!=0){
                    getRNum();
                    getGNum();
                    inputMsg(now,1);
                }
                break;
    }
}

int checkReserve(){//预约变入住功能

    int check = -1;
    char ID[20];
    int r;
    printf("请输入房间号：");
    scanf("%d",&r);
    while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
        printf("输入错误，请重新输入:");
        scanf("%d",&r);
    }
    printf("请输入身份证号：");
    scanf("%s",ID);
    while(1)
    {
           int i;
           for(i = 0; i < 56; i++)
           {
               if(allGuest[i].num == r){
                    if(strcmp(ID,allGuest[i].ID)==0)
                    {
                        check = 1;
                        changeGStatusTo_1(i);
                        break;
                    }
               }
           }
           if(check != 1){
                printf("查无此预约！\n");
                printf("请输入房间号：");
                scanf("%d",&r);
                while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
                    printf("输入错误，请重新输入:");
                    scanf("%d",&r);
                }
                printf("请输入身份证号：");
                scanf("%s",ID);
           }else break;
    }

    printf("办理成功！\n");
    return check;
}

void changeGStatusTo_1(int i){//更改客人的status，由预约到入住
    Guest g = allGuest[i];
    int j = 0;
    for(;j<aLength;j++){
        if(allGuest[j].num==g.num&&allGuest[j].time.year==g.time.year&&allGuest[j].time.month==g.time.month&&allGuest[j].time.day==g.time.day){
            allGuest[j].status = 1;
        }
    }
    writeAllGuest();
}

void writeAllGuest(){//重新写入全部客户信息
    FILE *fp;
    if((fp=fopen("data/User.txt","w"))==NULL){
        printf("无法读取文件");
        exit(0);
    }
    int i;
    for(i=0;i<aLength;i++){
        fprintf(fp,"%s %s %d %d %d %d %d %d %d \r\n",allGuest[i].ID,allGuest[i].name,allGuest[i].phone,allGuest[i].num,allGuest[i].status,allGuest[i].time.year,allGuest[i].time.month,allGuest[i].time.day,allGuest[i].day);
    }
    fclose(fp);
}

int front_isLeft(int i){//查询某种房型房间余量，输出可选择房号
    int k;
    int j = 0;
    printf("入住天数：");
    scanf("%d",&Day);
    switch(i){
    case 2:
        for(k=0;k<3;k++)
            if(room[k].roomStatus==0){
                    emptyRoom[j]= room[k].num;
                    j++;
            }else{
                if(front_judgeOrder(k)){
                    emptyRoom[j]= room[k].num;
                    j++;
                }
            }
        if(j!=0){
            printf("您选择的房型为单人房,以下房间可入住\n");
            int z;
            for(z=0;z<j;z++)
                printf("%d ",emptyRoom[z]);
                printf("\n");
        }else {
            printf("单人房已满！\n");
        }
        break;
    case 3:
        for(k=3;k<6;k++)
            if(room[k].roomStatus==0){
                    emptyRoom[j]= room[k].num;
                    j++;
            }else{
                if(front_judgeOrder(k)){
                    emptyRoom[j]= room[k].num;
                    j++;
                }
            }
        if(j!=0){
            printf("您选择的房型为双人房,以下房间可入住\n");
            int z;
            for(z=0;z<j;z++)
                printf("%d ",emptyRoom[z]);
                printf("\n");
        }else {
            printf("双人房已满！\n");
        }
        break;
    case 4:
        for(k=6;k<9;k++)
            if(room[k].roomStatus==0){
                    emptyRoom[j]= room[k].num;
                    j++;
            }else{
                if(front_judgeOrder(k)){
                    emptyRoom[j]= room[k].num;
                    j++;
                }
            }
        if(j!=0){
            printf("您选择的房型为VIP房,以下房间可入住\n");
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

int front_judgeOrder(int k){//判断房间可不可以入住
    int i;
    for(i = 0;i < 56;i++){
        if(allGuest[i].num == room[k].num){
            if(!judgeLast(now,Day,i)){
                return 0;
            }
        }
    }
    return 1;
}



void checkOut(){//退房功能函数
    system("cls");
        char ID[20];//用户身份证号，用于验证用户信息，避免退别人房间的情况
    Guest gst2[56];//gst1[]用来读入User.txt数据，gst2[]用来储存gst1[]中去掉取消预定的用户信息的信息
    int r;//房间号
    int b = 0;
    printf("请输入您要退的房间号：");
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
        if(strcmp(ID,allGuest[k].ID)==0&&allGuest[k].num==r&&allGuest[k].status==1){
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
                if(allGuest[k].time.year == temp.time.year&&allGuest[k].time.month == temp.time.month&&allGuest[k].time.day == temp.time.day&&allGuest[k].status==1){
                    k++;
                    count++;
                    continue;
                }

            }
            gst2[j]=allGuest[k];
            j++;
            k++;
        }

        int length = aLength-count;
        if(c==count){
            changeRStatusTo_0(r);
        }
        deleteGuest(gst2,length);
        printf("验证中......");
        Sleep(3000);
        printf("\n");
        printf("应付%d元！\n",count_money(temp.day,temp.num));
        printf("退房成功！欢迎再次光临!\n");
    }else {
        printf("验证中......");
        Sleep(3000);
        printf("\n");
        printf("退房失败!\n");
    }
    readGuest();
}

int count_money(int day,int num){//计算钱数
    int money;
    switch(num){
        case 101:
        case 102:
        case 103: money = 68*day;break;
        case 201:
        case 202:
        case 203: money = 168*day;break;
        case 301:
        case 302:
        case 303: money = 268*day;break;
    }
    return money;
}



void search_index(){//打印查询功能界面
    system("cls");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@                                   @\n");
    printf("@1.查看所有房间信息                 @\n");
    printf("@2.查看某房间客人信息               @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("请选择：");
}

void search(){//查询功能函数

    search_index();
    int i = 0;
    while((i=getch())!= 0x1B){
        now = getDt();
        readRoom();
        readGuest();
        switch(i)
        {
            case 49: searchAllRoom();
                     search_index();
                     continue;
            case 50: searchOneRoom();
                     search_index();
                     continue;
        }
    }
}

void searchAllRoom(){//查询所有房间
    printf("\n");
    int i =0;
    for(;i<9;i++){
        if(room[i].roomStatus==1){
            printf("%d有以下时间已占用:",room[i].num);
            int j = 0;
            Date temp;
            for(;j < aLength;j++){
                if(allGuest[j].num == room[i].num){
                    Date start = allGuest[j].time;
                    if(start.year!=temp.year||start.month!=temp.month||start.day!=temp.day){
                        Date last = getLastDt(start,allGuest[j].day);
                        printf("%d/%d/%d-%d/%d/%d\t",start.year,start.month,start.day,last.year,last.month,last.day);
                        temp = start;
                    }
                }
            }
            printf("\n");
        }else {
            printf("%d为空\n",room[i].num);
        }
    }
}

void searchOneRoom(){//查询一个房间具体信息
    printf("\n");
    int r;
    printf("请输入房间号：");
    scanf("%d",&r);
    while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
        printf("输入错误，请重新输入:");
        scanf("%d",&r);
    }
    printf("\n");
    int j = 0;
    Room temp;
    for(;j<9;j++){
        if(room[j].num==r){
            temp = room[j];
            break;
        }
    }
    if(temp.roomStatus == 1){
        int count = 0;
        //printf("%d\n",count);
        for(j = 0;j < aLength;j++){
            if(allGuest[j].num == r){
                count++;
                printf("第%d个客人：\n",count);
                printf("       身份证号码：%s\n",allGuest[j].ID);
                printf("       姓名：%s\n",allGuest[j].name);
                printf("       电话号码：%d\n",allGuest[j].phone);
                printf("       订房时间：%d/%d/%d\n",allGuest[j].time.year,allGuest[j].time.month,allGuest[j].time.day);
                printf("       订房天数：%d\n",allGuest[j].day);
            }
        }
    }else {
        printf("此房间为空房！\n");
    }
    printf("\n");

}
