#include <stdio.h>
#include <windows.h>
#include "../struct/struct.h"
Room room[9];
void index2(){
    system("cls");
    printf("=======================================\n");
    printf("1.���˼�\n");
    printf("2.˫�˼�\n");
    printf("3.VIP�׷�\n");
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
}
void isLeft(int i){//��ѯĳ�ַ��ͷ�������������û���Ԥ������
    switch(i){
    case 1:
        printf("��ѡ��ķ���Ϊ���˷�,���·����Ԥ��\n");
        for(int i=0;room[i].roomStatus!=1&&i<3;i++)
            printf("%d ",room[i].num);
        break;
    case 2:
        printf("��ѡ��ķ���Ϊ˫�˷�,���·����Ԥ��:\n");
        for(int i=3;room[i].roomStatus!=1&&i<6;i++)
            printf("%d ",room[i].num);
        break;
    case 3:
        printf("��ѡ��ķ���ΪVIP��,���·����Ԥ��\n");
        for(int i=6;room[i].roomStatus!=1&&i<9;i++)
            printf("%d ",room[i].num);
        break;
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
