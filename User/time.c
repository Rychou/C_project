#include <time.h>
#include "User.h"
#include "../struct/struct.h"

Date getDt()//得到当前的年月日，调用ASII()函数，Calendar(),MonthIs()
{
    int y1,y2,y3,y4;//年份的四个数字
    int m1,m2;//月份的两个数字
    int d1,d2;//日期的两个数字
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

int IsLeap(int year)//判断是否是闰年
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return 1;
    else
        return 0;
}

int MonthHas(int year,int month)//判断一个月有几天
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

Date getLastDt(Date first,int day){//得到最后一天
    Date last = first;
    day = day-1;
    int monthday = MonthHas(first.year,first.month);//这个月有几天
    if(first.day+day > monthday){
        if(first.month == 12){
            last.year++;
            int leftday = last.day+day-monthday;
            int i = 1;
            while(1){
                int tempday = MonthHas(last.year,i);
                if(tempday < leftday){
                    leftday -= tempday;
                    last.month = i+1;
                }else{
                    last.day = leftday;
                    break;
                }
                i++;
                if(i==13){
                    last.year++;
                    i=1;
                }
            }
        }else {
            last.month++;
            last.day += day - monthday;
        }
    }else{
        last.day += day;
    }
    return last;
}

int bigger(Date d1,Date d2){//比较两个日期的大小
    if(d1.year > d2.year){
        return 1;
    }
    if(d1.year == d2.year){
        if(d1.month == d2.month){
            if(d1.day > d2.day){
                return 1;
            }
        }else if(d1.month > d2.month){
            return 1;
        }
    }
    return 0;
}
