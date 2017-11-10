#include <time.h>
#include "User.h"
#include "../struct/struct.h"

Date getDt()//�õ���ǰ�������գ�����ASII()������Calendar(),MonthIs()
{
    int y1,y2,y3,y4;//��ݵ��ĸ�����
    int m1,m2;//�·ݵ���������
    int d1,d2;//���ڵ���������
    //int year,month,day;//�ꡢ�¡���
    char Dt[9];
    time_t t = time(NULL);
    struct tm *ts = localtime(&t);
    mktime(ts);
    strftime(Dt, sizeof(Dt), "%Y%m%d", ts);
    y1 = Dt[0]-48;
    y2 = Dt[1]-48;
    y3 = Dt[2]-48;
    y4 = Dt[3]-48;
    m1 = Dt[4]-48;
    m2 = Dt[5]-48;
    d1 = Dt[6]-48;
    d2 = Dt[7]-48;
    Date now;
    now.year = y1*1000+y2*100+y3*10+y4;
    now.month = m1*10+m2;
    now.day = d1*10+d2;
    return now;
}

int IsLeap(int year)//�ж��Ƿ�������
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return 1;
    else
        return 0;
}

int MonthHas(int year,int month)//�ж�һ�����м���
{
    int IsLeap(int year);
    switch(month)
    {
        case 1:return 31;break;
        case 2:if(IsLeap(year))
                    return 29;
               else return 28;
               break;
        case 3:return 31;break;
        case 4:return 30;break;
        case 5:return 31;break;
        case 6:return 30;break;
        case 7:return 31;break;
        case 8:return 31;break;
        case 9:return 30;break;
        case 10:return 31;break;
        case 11:return 30;break;
        case 12:return 31;break;
    }
}
