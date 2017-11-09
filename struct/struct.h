#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED


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

/*typedef struct {
    int num;//�����
    char ID[18];//���֤
    Date time;//��סʱ��
    int day;//��ס����
    int status;//1Ϊ����ס��2ΪԤԼ
}RG;
*/
typedef struct {
    char ID[20];//���֤
    char name[30];//����
    int phone;//�绰
    int num;//��ס����
    int status;//1Ϊ����ס��2ΪԤԼ
    Date time;//��סʱ��
    int day;//��ס����
}Guest;

#endif // STRUCT_H_INCLUDED
