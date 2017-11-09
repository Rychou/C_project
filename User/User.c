#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"
#include "time.h"

Room room[9];
int gNum;//Ԥ��ĳ���������
int rNum;//�洢�û�Ԥ���ķ����
int Day;//��ס����
int aLength=0;//ͳ��User.txt�ļ��������������鳤��
extern Date now;//��ǰʱ��
Date pre;//ԤԼ��ʱ��
Guest guest[9];
Guest allGuest[56];
int emptyRoom[3];

void User(){//����û�����
    system("cls");
    printf("\n");
    printf(" @@@@@@@@@@@@@@�û�@@@@@@@@@@@@@@@@@\n");
    printf("@                                   @\n");
    printf("@      1.ԤԼ                       @\n");
    printf("@      2.ȡ��ԤԼ                   @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("������ָ�");
    int i;
    scanf("%d",&i);
    while(i!=1&&i!=2)
    {
        printf("������������䣺");
        scanf("%d",&i);
    }
    switch(i){
        case 1 : Reserve();break;
        case 2 : cancelReservation();break;
    }
}



void Reserve(){//���ԤԼ����
    system("cls");
    printf("\n");
    printf(" @@@@@@@@@@@@@@ǰ̨@@@@@@@@@@@@@@@@@\n");
    printf("@                                   @\n");
    printf("@      1.���˼䣨68Ԫ/�죩          @\n");
    printf("@      2.˫�˼䣨168Ԫ/�죩         @\n");
    printf("@      3.VIP�׷���268Ԫ/�죩        @\n");
    printf("@                                   @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("����������ҪԤ���ķ���:");
    int k;
    scanf("%d",&k);
    while(k!=1&&k!=2&&k!=3)
    {
        printf("������������䣺");
        scanf("%d",&k);
    }
    if(isLeft(k)!=0){
        getRNum();
        getGNum();
        inputMsg(pre,2);
    }

}

int isLeft(int i){//��ѯĳ�ַ��ͷ�������������û���Ԥ������
    int k;
    int j = 0;
    printf("ԤԼ��ݣ�");
    scanf("%d",&pre.year);
    printf("ԤԼ�·ݣ�");
    scanf("%d",&pre.month);
    printf("ԤԼ�գ�");
    scanf("%d",&pre.day);
    while(1){
        if(judgeDate()==1) break;
        printf("ԤԼʱ�䲻��ȷ������������\n");
        printf("ԤԼ��ݣ�");
        scanf("%d",&pre.year);
        printf("ԤԼ�·ݣ�");
        scanf("%d",&pre.month);
        printf("ԤԼ�գ�");
        scanf("%d",&pre.day);
    }
    printf("Ԥ��������");
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
                printf("��ѡ��ķ���Ϊ���˷�,���·����Ԥ��\n");
                int z;
                for(z=0;z<j;z++)
                    printf("%d ",emptyRoom[z]);
                    printf("\n");
            }else {
                printf("���˷�������\n");
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
                printf("��ѡ��ķ���Ϊ˫�˷�,���·����Ԥ��\n");
                int z;
                for(z=0;z<j;z++)
                    printf("%d ",emptyRoom[z]);
                    printf("\n");
            }else {
                printf("˫�˷�������\n");
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
                printf("��ѡ��ķ���ΪVIP��,���·����Ԥ��\n");
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

int judgeDate(){//�ж������Ƿ�����Ҫ��
    int monthday = MonthHas(now.year,now.day);//������м���
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

int judgeLast(Date dt,int d,int i){//�ж�ʱ�����޿���
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

int judgeOrder(int k){//�жϷ���ɲ�����ԤԼ
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

void getRNum(){//��isLeft������ӡ����Ԥ�����ź� ��ȡ�û�ָ��
    printf("��������Ҫѡ��ķ���:");
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
        printf("������������Ҫѡ��ķ���:");
        scanf("%d",&rNum);
    }
}

void getGNum(){//��ȡԤ��ĳ���������
    printf("����������:");
    scanf("%d",&gNum);
    printf("\n");
}

void inputMsg(Date date,int i){//������ס�ͻ�����Ϣ�����Զ���ͻ�
    char ID[30];//���֤
    char name[30];//����
    int phone;//�绰
    int k;
    for(k=0;k<gNum;k++){
        guest[k].num = rNum;
        printf("�������%d�����˵���Ϣ\n",k+1);
        printf("���֤��:");
        scanf("%s",ID);
        //�ж�ID�����Ƿ�淶
        while(1){
            if(strlen(ID)==18||strlen(ID)==15){
                    strcpy(guest[k].ID,ID);//����ȡ����Ϣ���Ƶ�ȫ�ֱ���guest[k].ID��
                    break;
            }
            else {
                printf("���볤�Ȳ���������������(15λ����18λ):");
                scanf("%s",ID);
            }
        }
        printf("����:");
        scanf("%s",name);
        strcpy(guest[k].name,name);
        printf("�绰�ţ�");
        scanf("%d",&phone);
        guest[k].phone = phone;
        guest[k].time = date;
        guest[k].day = Day;
        guest[k].status = i;
    }
    printf("�����ɹ�����ѡ��ķ���Ϊ:%d\n",rNum);
    changeRStatusTo_1();
    writeGuest();
}

void changeRStatusTo_1(){//�ı䷿��״̬Ϊ1
    int i;
    for(i=0;i<9;i++){
        if(room[i].num==rNum)
            room[i].roomStatus = 1;
    }
    FILE *fp1;
    if((fp1=fopen("data/Room.txt","w"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    for(i=0;i<9;i++){
        fprintf(fp1,"%d %d %d %d \r\n",room[i].num,room[i].rank,room[i].price,room[i].roomStatus);
    }
    fclose(fp1);
}

void writeGuest(){//׷��д��ͻ���Ϣ
    FILE *fp;
    if((fp=fopen("data/User.txt","a"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    int i;
    for(i=0;i<gNum;i++){
        fprintf(fp,"%s %s %d %d %d %d %d %d %d \r\n",guest[i].ID,guest[i].name,guest[i].phone,guest[i].num,guest[i].status,guest[i].time.year,guest[i].time.month,guest[i].time.day,guest[i].day);
    }
    fclose(fp);
}



void cancelReservation(){//���ȡ��ԤԼ����
    char ID[20];//�û����֤�ţ�������֤�û���Ϣ�������˱��˷�������
    Guest gst2[56];//gst1[]��������User.txt���ݣ�gst2[]��������gst1[]��ȥ��ȡ��Ԥ�����û���Ϣ����Ϣ
    int r;//�����
    int b = 0;
    printf("��������Ҫȡ��Ԥ���ķ���ţ�");
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
        if(strcmp(ID,allGuest[k].ID)==0&&allGuest[k].num==r&&allGuest[k].status==2){
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
        int length = aLength-count;//gst2[]����ĳ���
        if(c==count){
            changeRStatusTo_0(r);
        }
        deleteGuest(gst2,length);
        printf("��֤��......");
        Sleep(3000);
        printf("\n");
        printf("ȡ��Ԥ���ɹ�����ӭ�ٴι���!\n");
    }else {
        printf("��֤��......");
        Sleep(3000);
        printf("\n");
        printf("ȡ��Ԥ��ʧ��!\n");
    }
    readGuest();
}

void changeRStatusTo_0(int roomNum){//�޸ķ���״̬Ϊ0
    int i;
    for(i=0;i<9;i++){
        if(room[i].num==roomNum)
            room[i].roomStatus = 0;
    }
    FILE *fp;
    if((fp=fopen("data/Room.txt","w"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    for(i=0;i<9;i++){
        fprintf(fp,"%d %d %d %d \r\n",room[i].num,room[i].rank,room[i].price,room[i].roomStatus);
    }
    fclose(fp);
}

void deleteGuest(Guest gst2[],int length){//�û�ȡ��Ԥ��ɾ���ض��û���Ϣ
    FILE *fp;
    if((fp=fopen("data/User.txt","w"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    int i;
    for(i=0;i<length;i++){
        fprintf(fp,"%s %s %d %d %d %d %d %d %d \r\n",gst2[i].ID,gst2[i].name,gst2[i].phone,gst2[i].num,gst2[i].status,gst2[i].time.year,gst2[i].time.month,gst2[i].time.day,gst2[i].day);
        //printf("%s %s %d %d %d %d %d %d %d \r\n",gst2[i].ID,gst2[i].name,gst2[i].phone,gst2[i].num,gst2[i].status,gst2[i].time.year,gst2[i].time.month,gst2[i].time.day,gst2[i].day);
    }
    fclose(fp);
}



void readRoom(){ //��ȡ�����ļ�
    FILE *fp;
    int i=0;
    if((fp=fopen("data/Room.txt","rb"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    while(!feof(fp)&&i<9){
        fscanf(fp,"%d%d%d%d",&room[i].num,&room[i].rank,&room[i].price,&room[i].roomStatus);
        i++;
    }
    fclose(fp);
}

void readGuest(){//��ȡUser.txt
    FILE *fp;
    int i=0;
    aLength = 0;
    if((fp=fopen("data/User.txt","rb"))==NULL){
        printf("�޷���ȡ�ļ�");
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
