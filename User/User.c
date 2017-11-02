#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"
#include "time.h"

Room room[9];
int gNum;//Ԥ��ĳ���������
int rNum;//�洢�û�Ԥ���ķ����
int Day;//��ס����
int aLength=0;//ͳ��User.txt�ļ��������������鳤��
Date now;//��ǰʱ��
Date pre;//ԤԼ��ʱ��
Guest guest[9];
int emptyRoom[3];

void User(){//����û�����
    system("cls");
    printf("=======================================\n");
    printf("1.Ԥ��\n");
    printf("2.ȡ��Ԥ��\n");
    printf("ע��ֻ����7���ڵ�ԤԼ\n");
    printf("=======================================\n");
    now = getDt();
    int i;
    printf("��ѡ��:");
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
    printf("=======================================\n");
    printf("1.���˼䣨68Ԫ/�죩\n");
    printf("2.˫�˼䣨168Ԫ/�죩\n");
    printf("3.VIP�׷���268Ԫ/�죩\n");
    printf("=======================================\n");
    printf("����������ҪԤ���ķ���:");
    int k;
    scanf("%d",&k);
    while(k!=1&&k!=2&&k!=3)
    {
        printf("������������䣺");
        scanf("%d",&k);
    }
    isLeft(k);
    getRNum();
    getGNum();
    inputMsg();
}

void cancelReservation(){//���ȡ��ԤԼ����
    char ID[20];//�û����֤�ţ�������֤�û���Ϣ�������˱��˷�������
    Guest gst1[20],gst2[20];//gst1[]��������User.txt���ݣ�gst2[]��������gst1[]��ȥ��ȡ��Ԥ�����û���Ϣ����Ϣ
    readGuest(gst1);
    int r;//�����
    printf("��������Ҫȡ��Ԥ���ķ���ţ�");
    scanf("%d",&r);
    while(r!=101&&r!=102&&r!=103&&r!=201&&r!=202&&r!=203&&r!=301&&r!=302&&r!=303){
        printf("�����������������:");
        scanf("%d",&r);
    }
    /*�����û��ṹ�����ٴ���д���ļ� ʵ���˶�ɾ���û����ݹ���*/
    int count=0;//��¼Ԥ��ͬһ���������
    int k;
    for(k=0;k<20;k++){
        if(gst1[k].num ==r)
            count++;
    }
    int j;
    for(j=0;j<aLength;j++){
        if(gst1[j].num!=r){
                gst2[j] = gst1[j];
        }
        else {
            gst2[j]=gst1[j+count];
        }
    }
    int length = aLength-count;//gst2[]����ĳ���
    printf("���������֤�Ž�����֤��");
    scanf("%s",ID);
    int i;
    printf("��֤��......\n");
    for(i=0;i<aLength;i++){
            if(strcmp(ID,gst1[i].ID)==0){
                changeRStatusTo_0(r);
                deleteGuest(gst2,length);
                count--;
                if(count==0){
                    printf("�˷��ɹ�����ӭ�ٴι���!\n");
                }
            }
    }
}

void isLeft(int i){//��ѯĳ�ַ��ͷ�������������û���Ԥ������
    int k;
    int j = 0;
    switch(i){
    case 1:
        printf("��ѡ��ķ���Ϊ���˷�,���·����Ԥ��\n");
        for(k=0;k<3;k++)
            if(room[k].roomStatus==0){
                printf("%d ",room[k].num);
                emptyRoom[j]= room[k].num;
                j++;
            }

        printf("\n");
        break;
    case 2:
        printf("��ѡ��ķ���Ϊ˫�˷�,���·����Ԥ��:\n");
        for(k=3;k<6;k++)
            if(room[k].roomStatus==0){
                printf("%d ",room[k].num);
                emptyRoom[j]=room[k].num;
                j++;
            }

        printf("\n");
        break;
    case 3:
        printf("��ѡ��ķ���ΪVIP��,���·����Ԥ��\n");
        for(k=6;k<9;k++)
            if(room[k].roomStatus==0){
                printf("%d ",room[k].num);
                emptyRoom[j]=room[k].num;
                j++;
            }

        printf("\n");
        break;
    }
    for(;j<3;j++){
        emptyRoom[j]=0;
    }
}

void getRNum(){//��isLeft������ӡ����Ԥ�����ź� ��ȡ�û�ָ��
    printf("��������ҪԤ���ķ���:");
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
        printf("������������ҪԤ���ķ���:");
        scanf("%d",&rNum);
    }
}

void getGNum(){//��ȡԤ��ĳ���������
    printf("������Ԥ������:");
    scanf("%d",&gNum);
    printf("\n");
}

void inputMsg(){//������ס�ͻ�����Ϣ�����Զ���ͻ�
    char ID[30];//���֤
    char name[30];//����
    int phone;//�绰
    int k;
    printf("��ݣ�");
    scanf("%d",&pre.year);
    printf("�·ݣ�");
    scanf("%d",&pre.month);
    printf("�գ�");
    scanf("%d",&pre.day);
    //�ж�ԤԼ�����Ƿ�����Ҫ��
    while(1){
        if(judgeDate()==1) break;
        printf("ԤԼʱ�䲻��ȷ������������\n");
        printf("��ݣ�");
        scanf("%d",&pre.year);
        printf("�·ݣ�");
        scanf("%d",&pre.month);
        printf("�գ�");
        scanf("%d",&pre.day);
    }
    printf("Ԥ������:");
    scanf("%d",&Day);
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
        guest[k].time = pre;
        guest[k].day = Day;
    }
    printf("Ԥ���ɹ�����Ԥ���ķ���Ϊ:%d",rNum);
    changeRStatusTo_1();
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

void readGuest(Guest array[]){//��ȡUser.txt
    FILE *fp;
    int i=0;
    if((fp=fopen("data/User.txt","rb"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    while(!feof(fp)&&i<20){
        if(fscanf(fp,"%s%s%d%d%d%d%d%d",&array[i].ID,&array[i].name,&array[i].phone,&array[i].num,&array[i].time.year,&array[i].time.month,&array[i].time.day,&array[i].day)!=EOF){
                aLength++;
        }

        i++;
    }
    fclose(fp);
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
        fprintf(fp,"%s %s %d %d \r\n",gst2[i].ID,gst2[i].name,gst2[i].phone,gst2[i].num);
    }
    fclose(fp);
}

void writeGuest(){//׷��д��ͻ���Ϣ
    FILE *fp;
    if((fp=fopen("data/User.txt","a"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    int i;
    for(i=0;i<gNum;i++){
        fprintf(fp,"%s %s %d %d %d %d %d %d \r\n",guest[i].ID,guest[i].name,guest[i].phone,guest[i].num,guest[i].time.year,guest[i].time.month,guest[i].time.day,guest[i].day);
    }
    fclose(fp);
}

int judgeDate(){
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
