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
* ��ȡ�û����������
* @param  pwd     char*  ����������ڴ���׵�ַ
* @param  pwdlen  int    �������󳤶�
**/

void getPassword(){//�����������
    system("cls");
    char pwd[20];
    int count = 3;
    printf("�������¼���룺\n");
    getpwd(pwd, PWDLEN);
    while(comparePwd(pwd) != 1 && count > 0)
    {
        printf("������������䣺\n");
        getpwd(pwd, PWDLEN);
        -- count;
    }
    if(comparePwd(pwd) == 1)
    {
        front();
    }
}

void getpwd(char *pwd, int pwdlen){//�õ�����
    char ch = 0;
    int i = 0;
    while(i<pwdlen){
        ch = getch();
        if(ch == '\r'){  //�س���������
            printf("\n");
            break;
        }

        if(ch=='\b' && i>0){  //����ɾ����
            i--;
            printf("\b \b");
        }else if(isprint(ch)){  //����ɴ�ӡ�ַ�
            pwd[i] = ch;
            printf("*");
            i++;
        }
    }
    pwd[i] = '\0';
}

int comparePwd(char *pwd){//��֤����
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



void front(){//ǰ̨���ܺ���
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
                printf("��ѯ");
                pause();
                front_index();
                continue;
        }
    }
}

void front_index(){//��ӡǰ̨����ҳ��
    system("cls");
    printf("\n");
    printf(" @@@@@@@@@@@@@@ǰ̨@@@@@@@@@@@@@@@@@\n");
    printf("@                                   @\n");
    printf("@      1.��ס                       @\n");
    printf("@      2.����                       @\n");
    printf("@      3.��ѯ                       @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("������ָ�");
}



void checkIn(){//��ס���ܺ���

    system("cls");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@1.Ԥ����ס                         @\n");
    printf("@2.���˼�                           @\n");
    printf("@3.˫�˼�                           @\n");
    printf("@4.VIP��                            @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("������ָ��:");
    int k;
    scanf("%d",&k);
    while(k!=1&&k!=2&&k!=3)
    {
        printf("������������䣺");
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

int checkReserve(){//ԤԼ����ס����

    int check = -1;
    char ID[20];
    int r;
    printf("�����뷿��ţ�");
    scanf("%d",&r);
    while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
        printf("�����������������:");
        scanf("%d",&r);
    }
    printf("���������֤�ţ�");
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
                printf("���޴�ԤԼ��\n");
                printf("�����뷿��ţ�");
                scanf("%d",&r);
                while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
                    printf("�����������������:");
                    scanf("%d",&r);
                }
                printf("���������֤�ţ�");
                scanf("%s",ID);
           }else break;
    }

    printf("����ɹ���\n");
    return check;
}

void changeGStatusTo_1(int i){//���Ŀ��˵�status����ԤԼ����ס
    Guest g = allGuest[i];
    int j = 0;
    for(;j<aLength;j++){
        if(allGuest[j].num==g.num&&allGuest[j].time.year==g.time.year&&allGuest[j].time.month==g.time.month&&allGuest[j].time.day==g.time.day){
            allGuest[j].status = 1;
        }
    }
    writeAllGuest();
}

void writeAllGuest(){//����д��ȫ���ͻ���Ϣ
    FILE *fp;
    if((fp=fopen("data/User.txt","w"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    int i;
    for(i=0;i<aLength;i++){
        fprintf(fp,"%s %s %d %d %d %d %d %d %d \r\n",allGuest[i].ID,allGuest[i].name,allGuest[i].phone,allGuest[i].num,allGuest[i].status,allGuest[i].time.year,allGuest[i].time.month,allGuest[i].time.day,allGuest[i].day);
    }
    fclose(fp);
}

int front_isLeft(int i){//��ѯĳ�ַ��ͷ��������������ѡ�񷿺�
    int k;
    int j = 0;
    printf("��ס������");
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
            printf("��ѡ��ķ���Ϊ���˷�,���·������ס\n");
            int z;
            for(z=0;z<j;z++)
                printf("%d ",emptyRoom[z]);
                printf("\n");
        }else {
            printf("���˷�������\n");
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
            printf("��ѡ��ķ���Ϊ˫�˷�,���·������ס\n");
            int z;
            for(z=0;z<j;z++)
                printf("%d ",emptyRoom[z]);
                printf("\n");
        }else {
            printf("˫�˷�������\n");
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
            printf("��ѡ��ķ���ΪVIP��,���·������ס\n");
            int z;
            for(z=0;z<j;z++)
                printf("%d ",emptyRoom[z]);
                printf("\n");
        }else {
            printf("VIP��������\n");
        }
        break;
    }
    int t = j;
    for(;j<3;j++){
        emptyRoom[j]=0;
    }
    return t;
}

int front_judgeOrder(int k){//�жϷ���ɲ�������ס
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



void checkOut(){//�˷����ܺ���
    system("cls");
        char ID[20];//�û����֤�ţ�������֤�û���Ϣ�������˱��˷�������
    Guest gst2[56];//gst1[]��������User.txt���ݣ�gst2[]��������gst1[]��ȥ��ȡ��Ԥ�����û���Ϣ����Ϣ
    int r;//�����
    int b = 0;
    printf("��������Ҫ�˵ķ���ţ�");
    scanf("%d",&r);
    while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
        printf("�����������������:");
        scanf("%d",&r);
    }
    printf("���������֤�Ž�����֤��");
    scanf("%s",ID);
    /*�����û��ṹ�����ٴ���д���ļ� ʵ���˶�ɾ���û����ݹ���*/
    int count=0;//��¼Ԥ��ͬһ���������
    int k;
    Guest temp;
    for(k=0;k<aLength;k++){
        if(strcmp(ID,allGuest[k].ID)==0&&allGuest[k].num==r&&allGuest[k].status==1){
            temp = allGuest[k];
            b = 1;
            break;
        }
    }
    int c = 0;//ͳ�ƶ�����䷿������
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
        printf("��֤��......");
        Sleep(3000);
        printf("\n");
        printf("Ӧ��%dԪ��\n",count_money(temp.day,temp.num));
        printf("�˷��ɹ�����ӭ�ٴι���!\n");
    }else {
        printf("��֤��......");
        Sleep(3000);
        printf("\n");
        printf("�˷�ʧ��!\n");
    }
    readGuest();
}

int count_money(int day,int num){//����Ǯ��
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



void search_index(){//��ӡ��ѯ���ܽ���
    system("cls");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@                                   @\n");
    printf("@1.�鿴���з�����Ϣ                 @\n");
    printf("@2.�鿴ĳ���������Ϣ               @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("��ѡ��");
}

void search(){//��ѯ���ܺ���

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

void searchAllRoom(){//��ѯ���з���
    printf("\n");
    int i =0;
    for(;i<9;i++){
        if(room[i].roomStatus==1){
            printf("%d������ʱ����ռ��:",room[i].num);
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
            printf("%dΪ��\n",room[i].num);
        }
    }
}

void searchOneRoom(){//��ѯһ�����������Ϣ
    printf("\n");
    int r;
    printf("�����뷿��ţ�");
    scanf("%d",&r);
    while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
        printf("�����������������:");
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
                printf("��%d�����ˣ�\n",count);
                printf("       ���֤���룺%s\n",allGuest[j].ID);
                printf("       ������%s\n",allGuest[j].name);
                printf("       �绰���룺%d\n",allGuest[j].phone);
                printf("       ����ʱ�䣺%d/%d/%d\n",allGuest[j].time.year,allGuest[j].time.month,allGuest[j].time.day);
                printf("       ����������%d\n",allGuest[j].day);
            }
        }
    }else {
        printf("�˷���Ϊ�շ���\n");
    }
    printf("\n");

}
