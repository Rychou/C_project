#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"
Room room[9];
int gNum;//Ԥ��ĳ���������
int rNum;//�洢�û�Ԥ���ķ����
Guest guest[9];
void index2(){//����û�����
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
void isLeft(int i){//��ѯĳ�ַ��ͷ�������������û���Ԥ������
    switch(i){
    case 1:
        printf("��ѡ��ķ���Ϊ���˷�,���·����Ԥ��\n");
        for(int i=0;room[i].roomStatus!=1&&i<3;i++)
            printf("%d ",room[i].num);
        printf("\n");
        break;
    case 2:
        printf("��ѡ��ķ���Ϊ˫�˷�,���·����Ԥ��:\n");
        for(int i=3;room[i].roomStatus!=1&&i<6;i++)
            printf("%d ",room[i].num);
        printf("\n");
        break;
    case 3:
        printf("��ѡ��ķ���ΪVIP��,���·����Ԥ��\n");
        for(int i=6;room[i].roomStatus!=1&&i<9;i++)
            printf("%d ",room[i].num);
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
    char ID[18];//���֤
    char name[10];//����
    int phone;//�绰
    for(int k=0;k<gNum;k++){
        printf("�������%d�����˵���Ϣ\n",k+1);
        printf("���֤��:");
        scanf("%s",ID);
        strcpy(guest[k].ID,ID);//����ȡ����Ϣ���Ƶ�ȫ�ֱ���guest[k].ID��
        printf("\n");
        printf("����:");
        scanf("%s",name);
        strcpy(guest[k].name,name);
        printf("\n");
        printf("�绰�ţ�");
        scanf("%d",&phone);
        guest[k].phone = phone;
    }
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
}
void writeGuest(){//׷��д��ͻ���Ϣ
    FILE *fp;
    if((fp=fopen("data/User.txt","a"))==NULL){
        printf("�޷���ȡ�ļ�");
        exit(0);
    }
    for(int i=0;i<gNum;i++){
        fprintf(fp,"%s %s %d \r\n",guest[i].ID,guest[i].name,guest[i].phone);
    }
    fclose(fp);

}
