#define PWDLEN 20
//ǰ̨��������
void getpwd(char *pwd, int pwdlen);//�õ�����
int comparePwd(char *pwd);//��֤����
void getPassword();//�����������

//ǰ̨����
void front();//ǰ̨���ܺ���
void front_index();//��ӡǰ̨����ҳ��

//��ס
void checkIn();//��ס���ܺ���
int checkReserve();//ԤԼ����ס����
void changeGStatusTo_1(int i);//���Ŀ��˵�status����ԤԼ����ס
void writeAllGuest();//����д��ȫ���ͻ���Ϣ
int front_isLeft(int i);//��ѯĳ�ַ��ͷ��������������ѡ�񷿺�
int front_judgeOrder(int k);//�жϷ���ɲ�������ס���������� User.h ��judgeLast()����

//�˷�
void checkOut();//�˷����ܺ���
int count_money(int day,int num);//����Ǯ��

//��ѯ
void search_index();//��ӡ��ѯ���ܽ���
void search();//��ѯ���ܺ���
void searchAllRoom();//��ѯ���з���
void searchOneRoom();//��ѯһ�����������Ϣ


