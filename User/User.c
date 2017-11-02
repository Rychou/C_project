#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"

Room room[9];
int gNum;//Ԥ��ĳ���������
int rNum;//�洢�û�Ԥ���ķ����
int Day;//��ס����
int aLength=0;//ͳ��User.txt�ļ��������������鳤��
Guest guest[9];

void User(){//����û�����
    system("cls");
    printf("=======================================\n");
    printf("1.Ԥ��\n");
    printf("2.ȡ��Ԥ��\n");
    printf("=======================================\n");
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
void Reserve(){
    system("cls");
    printf("=======================================\n");
    printf("1.���˼䣨68Ԫ/�죩\n");
    printf("2.˫�˼䣨168Ԫ/�죩\n");
    printf("3.VIP�׷���268Ԫ/�죩\n");
    printf("=======================================\n");
    printf("����������ҪԤ���ķ���:\n");
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
void cancelReservation(){
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
    int length = aLength-count;//gst2[]����ĳ���
    printf("���������֤�Ž�����֤��");
    scanf("%s",ID);
    for(int i=0;i<aLength;i++){
            if(strcmp(ID,gst1[i].ID)==0){
                printf("��֤�ɹ�,�����˷�......\n");
                changeRStatusTo_0(r);
                deleteGuest(gst2,length);
                printf("�˷��ɹ�����ӭ�ٴι���!");
            }
    }
}
void isLeft(int i){//��ѯĳ�ַ��ͷ�������������û���Ԥ������
    switch(i){
    case 1:
        printf("��ѡ��ķ���Ϊ���˷�,���·����Ԥ��\n");
        for(int k=0;k<3;k++)
            if(room[k].roomStatus==0)
                printf("%d ",room[k].num);
        printf("\n");
        break;
    case 2:
        printf("��ѡ��ķ���Ϊ˫�˷�,���·����Ԥ��:\n");
        for(int k=3;k<6;k++)
            if(room[k].roomStatus==0)
                printf("%d ",room[k].num);
        printf("\n");
        break;
    case 3:
        printf("��ѡ��ķ���ΪVIP��,���·����Ԥ��\n");
        for(int k=6;k<9;k++)
            if(room[k].roomStatus==0)
                printf("%d ",room[k].num);
        printf("\n");
        break;
    }
}
void getRNum(){//��isLeft������ӡ����Ԥ�����ź� ��ȡ�û�ָ��
    printf("��������ҪԤ���ķ���\n");
    scanf("%d",&rNum);
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
    for(int k=0;k<gNum;k++){
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
//��ȡUser.txt
void readGuest(Guest array[]){
    FILE *fp;
    int i=0;
    if((fp=fopen("data/User.txt","rb"))==NULL){
        printf("�޷���ȡ�ļ�");
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
//�ı䷿��״̬Ϊ1
void changeRStatusTo_1(){
    for(int i=0;i<9;i++){
        if(room[i].num==rNum)
            room[i].roomStatus = 1;
    }
    FILE *fp1;
    if((fp1=fopen("data/Room.txt","w"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    for(int i=0;i<9;i++){
        fprintf(fp1,"%d %d %d %d \r\n",room[i].num,room[i].rank,room[i].price,room[i].roomStatus);
    }
    fclose(fp1);
}
//�޸ķ���״̬Ϊ0
void changeRStatusTo_0(int roomNum){
    for(int i=0;i<9;i++){
        if(room[i].num==roomNum)
            room[i].roomStatus = 0;
    }
    FILE *fp;
    if((fp=fopen("data/Room.txt","w"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    for(int i=0;i<9;i++){
        fprintf(fp,"%d %d %d %d \r\n",room[i].num,room[i].rank,room[i].price,room[i].roomStatus);
    }
    fclose(fp);
}
//�û�ȡ��Ԥ��ɾ���ض��û���Ϣ
void deleteGuest(Guest gst2[],int length){
    FILE *fp;
    if((fp=fopen("data/User.txt","w"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    for(int i=0;i<length;i++){
        fprintf(fp,"%s %s %d %d \r\n",gst2[i].ID,gst2[i].name,gst2[i].phone,gst2[i].num);
    }
    fclose(fp);
}
//׷��д��ͻ���Ϣ
void writeGuest(){
    FILE *fp;
    if((fp=fopen("data/User.txt","a"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    for(int i=0;i<gNum;i++){
        fprintf(fp,"%s %s %d %d \r\n",guest[i].ID,guest[i].name,guest[i].phone,guest[i].num);
    }
    fclose(fp);
}
