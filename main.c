#include <stdio.h>
#include <stdlib.h>
#include "./User/User.h"
#include "./Front/Front.h"

typedef struct {
    int num;//�����
    int rank;//��������
    int price;//����۸�
    int roomStatus;//����״̬��0Ϊ�գ�ԤԼ����סΪ1
}Room;

typedef struct{
    int year;
    int month;
    int day;
}Date;

typedef struct {
    int num;//�����
    char ID[18];//���֤
    Date time;//��סʱ��
    int day;//��ס����
    int status;//1Ϊ����ס��2ΪԤԼ
}RG;

typedef struct {
    char ID[18];//���֤
    char name[10];//����
    int phone;//�绰
}Guest;




int main()
{
    void index();
    int i;
    index();
    scanf("%d",&i);
    while(i!=1&&i!=2)
    {
        printf("������������䣺");
        scanf("%d",&i);
    }
    switch(i)
    {
     //   case 2: getPassword();break;
        case 1: index2();break;
    }

    return 0;
}

void index()
{
    printf("=======================================\n");
    printf("1.�ͻ�\n");
    printf("2.ǰ̨\n");
    printf("=======================================\n");
    printf("��ѡ��");
}
