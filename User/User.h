#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include "../struct/struct.h"


#endif // USER_H_INCLUDED
//�û�������ʼ����
void User();//����û�����

//ԤԼ
void Reserve();//���ԤԼ����
int isLeft();//��ѯĳ�ַ��ͷ�������������û���Ԥ������
void getRNum();//��isLeft������ӡ����Ԥ�����ź� ��ȡ�û�ָ��
void getGNum();//��ȡԤ��ĳ���������
void inputMsg(Date date,int i);//������ס�ͻ�����Ϣ�����Զ���ͻ�
void writeGuest();//׷��д��ͻ���Ϣ
void changeRStatusTo_1();//�ı䷿��״̬Ϊ1
int judgeDate();//�ж������Ƿ�����7���ڵ�Ҫ��
int judgeLast(Date dt,int d,int i);//�ж�ʱ�����޿���
int judgeOrder(int k);//�жϷ���ɲ�����ԤԼ

//ȡ��ԤԼ
void cancelReservation();//���ȡ��ԤԼ����
void changeRStatusTo_0();//�޸ķ���״̬Ϊ0
void deleteGuest(Guest gst2[],int length);//�û�ȡ��Ԥ��ɾ���ض��û���Ϣ


void readRoom(); //��ȡ�����ļ�
void readGuest();//��ȡUser.txt

